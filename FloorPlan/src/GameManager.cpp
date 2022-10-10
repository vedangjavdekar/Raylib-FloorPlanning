#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

DragAndDropManager& GameManager::GetDragAndDropManager()
{
	return m_DragAndDropManager;
}

void GameManager::Update()
{
	CleanObjects();
	m_DragAndDropManager.Update();
	for (auto& obj : m_Entities)
	{
		Object* o = obj.second;
		if (o->IsActive() && o->CanUpdate())
		{
			o->Update();
		}
	}
}

void GameManager::Draw()
{
	for (auto& layer : m_DrawTable)
	{
		for (auto& id : layer.second)
		{
			Object* obj = m_Entities.at(id);
			if (obj->IsActive() && obj->CanDraw())
			{
				obj->Draw();
			}
		}
	}
}

void GameManager::AddForDelete(unsigned int entityId)
{
	m_DeleteObjects.push_back(entityId);
}

void GameManager::UpdateZIndex(unsigned int entityId, unsigned int prevZIndex, unsigned int newZIndex)
{
	if (m_DrawTable.find(prevZIndex) != m_DrawTable.end())
	{
		auto& layer = m_DrawTable.at(prevZIndex);
		if (layer.find(entityId) != layer.end())
		{
			layer.erase(entityId);
		}
	}

	if (m_DrawTable.find(newZIndex) == m_DrawTable.end())
	{
		m_DrawTable.emplace(newZIndex, std::unordered_set<unsigned int>{entityId});
	}
	else
	{
		m_DrawTable.at(newZIndex).emplace(entityId);
	}
}

void GameManager::CleanObjects()
{
	for (const auto& id : m_DeleteObjects)
	{
		if (m_Entities.find(id) != m_Entities.end())
		{
			Object* obj = m_Entities.at(id);
			if (m_DrawTable.find(obj->m_ZIndex) != m_DrawTable.end())
			{
				m_DrawTable.at(obj->m_ZIndex).erase(obj->m_EntityID);
			}
			delete m_Entities.at(id);
			m_Entities.erase(id);
		}
	}
	m_DeleteObjects.clear();
}

unsigned int GameManager::GetEntityID()
{
	if (m_IDs.size())
	{
		unsigned int id = m_IDs.front();
		m_IDs.pop();
		return id;
	}
	else
	{
		return ++m_CurrID;
	}
}

GameManager::GameManager()
{
	m_DrawTable.emplace(0, std::unordered_set<unsigned int>());
}

GameManager::~GameManager()
{
	for (auto& obj : m_Entities)
	{
		delete obj.second;
	}
	m_Entities.clear();
}

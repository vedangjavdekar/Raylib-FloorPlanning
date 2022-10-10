#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "DragAndDropManager.h"
#include "Object.h"

class GameManager
{
public:
	static GameManager& GetInstance();

	DragAndDropManager& GetDragAndDropManager();

	template<class T>
	Object* CreateObject()
	{
		Object* obj = new T();
		unsigned int id = GetEntityID();
		obj->m_EntityID = id;
		m_Entities.emplace(id, obj);
		UpdateZIndex(id, -1, 0);
		return obj;
	}

	void Update();
	void Draw();
	void AddForDelete(unsigned int entityId);
	void UpdateZIndex(unsigned int entityId, unsigned int prevZIndex, unsigned int newZIndex);
protected:
    void CleanObjects();
    
	unsigned int GetEntityID();
private:
	GameManager();
	~GameManager();

	DragAndDropManager m_DragAndDropManager;

    unsigned int m_CurrID = 0;
    std::queue<unsigned int> m_IDs;

	std::vector<unsigned int> m_DeleteObjects;
    std::map<int,std::unordered_set<unsigned int>> m_DrawTable;
    std::unordered_map<unsigned int,Object*> m_Entities;
};
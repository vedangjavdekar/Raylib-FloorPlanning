#include "DragAndDropManager.h"
#include "raylib.h"

void DragAndDropManager::Update()
{
	const Vector2 mouse = GetMousePosition();

	unsigned int newHovered = 0;
	if (m_CurrDraggingID == 0)
	{
		for (auto& draggable : m_Draggables)
		{
			Draggable* drag = draggable.second;
			if (drag->IsActive() && !drag->IsHitTestInvisible())
			{
				if (CheckCollisionPointRec(mouse, drag->m_Bounds))
				{
					newHovered = draggable.first;
				}
			}
		}
	}
	else
	{
		for (auto& dropTarget : m_DropTargets)
		{
			DropTarget* drop = dropTarget.second;
			if (drop->IsActive() && !drop->IsHitTestInvisible())
			{
				if (CheckCollisionPointRec(mouse, drop->m_Bounds))
				{
					newHovered = dropTarget.first;
				}
			}
		}

	}

	if (newHovered != m_CurrHoveredID)
	{
		if (m_CurrDraggingID == 0)
		{
			if (m_CurrHoveredID)
			{
				m_Draggables.at(m_CurrHoveredID)->OnHoverExit();
			}

			m_CurrHoveredID = newHovered;

			if (m_CurrHoveredID)
			{
				m_Draggables.at(m_CurrHoveredID)->OnHoverEnter();
			}
		}
		else
		{
			if (m_CurrHoveredID)
			{
				m_DropTargets.at(m_CurrHoveredID)->OnDraggableExit(m_Draggables.at(m_CurrDraggingID));
				m_Draggables.at(m_CurrDraggingID)->OnExitDropTarget(m_DropTargets.at(m_CurrHoveredID));
			}

			m_CurrHoveredID = newHovered;

			if (m_CurrHoveredID)
			{
				m_DropTargets.at(m_CurrHoveredID)->OnDraggableEnter(m_Draggables.at(m_CurrDraggingID));
				m_Draggables.at(m_CurrDraggingID)->OnEnterDropTarget(m_DropTargets.at(m_CurrHoveredID));
			}
		}
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_CurrHoveredID>0)
	{
		m_Draggables.at(m_CurrHoveredID)->OnDragStart();
		m_CurrDraggingID = m_CurrHoveredID;
		m_CurrHoveredID = 0;
	}

	if (m_CurrDraggingID)
	{
		Vector2 delta = GetMouseDelta();
		if (delta.x || delta.y)
		{
			m_Draggables.at(m_CurrDraggingID)->OnDrag();
		}
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_CurrDraggingID)
	{
		bool dropped = false;
		if (m_CurrHoveredID > 0)
		{
			m_DropTargets.at(m_CurrHoveredID)->OnDropped(m_Draggables.at(m_CurrDraggingID),dropped);
			m_CurrHoveredID = 0;
		}
		m_Draggables.at(m_CurrDraggingID)->OnDragEnd(dropped);
		m_CurrDraggingID = 0;
	}
}

void DragAndDropManager::RegisterDraggable(Draggable* draggable)
{
	if (!draggable)
	{
		return;
	}

	draggable->m_ID = GetNewID();
	m_Draggables.emplace(draggable->m_ID, draggable);
}

void DragAndDropManager::UnregisterDraggable(Draggable* draggable)
{
	if (!draggable)
	{
		return;
	}

	unsigned int id = draggable->m_ID;
    if(m_CurrHoveredID == id)
    {
        m_CurrHoveredID = 0;
    }
    if(m_CurrDraggingID == id)
    {
        m_CurrDraggingID = 0;
    }
	if (m_Draggables.find(id) != m_Draggables.end())
	{
		m_Draggables.erase(id);
		m_IDs.push(id);
	}
}

void DragAndDropManager::RegisterDropTarget(DropTarget* dropTarget)
{
	if (!dropTarget)
	{
		return;
	}

	dropTarget->m_ID = GetNewID();
	m_DropTargets.emplace(dropTarget->m_ID, dropTarget);
}

void DragAndDropManager::UnregisterDropTarget(DropTarget* dropTarget)
{
	if (!dropTarget)
	{
		return;
	}

	unsigned int id = dropTarget->m_ID;
    if(m_CurrHoveredID == id)
    {
        m_CurrHoveredID = 0;
    }

	if (m_Draggables.find(id) != m_Draggables.end())
	{
		m_Draggables.erase(id);
		m_IDs.push(id);
	}
}

unsigned int DragAndDropManager::GetNewID()
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

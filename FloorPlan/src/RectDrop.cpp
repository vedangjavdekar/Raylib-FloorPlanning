#include "RectDrop.h"
#include "GameManager.h"
#include "Room.h"

void RectDrop::Init(const RectSettings& initializer)
{
	m_Settings = initializer;
	MakeHitTestInvisible(false);
}

void RectDrop::OnDraggableEnter(Draggable* draggable)
{
	m_DraggableEnter = true;
}

void RectDrop::OnDraggableExit(Draggable* draggable)
{
	m_DraggableEnter = false;
}

void RectDrop::OnDropped(Draggable* draggable,bool&dropped)
{
	if (FloorPlan::GetInstance().GetRoot() == nullptr)
	{
		Rectangle bounds = draggable->GetBounds();
		bounds.x = m_Bounds.x;
		bounds.y = m_Bounds.y;
		TreeNode* roomNode = new RoomNode();
		RoomNode* room = static_cast<RoomNode*>(roomNode);
		room->x = bounds.x;
		room->y = bounds.y;
		room->width = bounds.width;
		room->height = bounds.height;
		
		Room* roomGraphic = static_cast<Room*>(GameManager::GetInstance().CreateObject<Room>());
		roomGraphic->Init(roomGraphic->DEFAULTS);
		roomGraphic->SetBounds(bounds);
		roomGraphic->SetRoomNode(room);

		room->room = roomGraphic;
		FloorPlan::GetInstance().AddRootNode(roomNode);
		m_DraggableEnter = false;
		dropped = true;
		return;
	}

	m_DraggableEnter = false;
	dropped = false;
}

void RectDrop::Update()
{
	if (CheckCollisionPointRec(GetMousePosition(), m_Bounds))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			FloorPlan::GetInstance().Reset();
		}
	}
}

void RectDrop::Draw()
{
	if (m_Settings.fill)
	{
		DrawRectangleRec(m_Bounds, m_DraggableEnter ? m_Settings.dragEnterColor : m_Settings.normalColor);
	}
	else
	{
		DrawRectangleLines(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Bounds.height,  m_DraggableEnter ? m_Settings.dragEnterColor : m_Settings.normalColor);
	}
}

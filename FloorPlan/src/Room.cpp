#include "Room.h"
#include "GameManager.h"
#include "FloorPlan.h"
#include "CutLine.h"

Room::Room()
{
	m_RightBox = new Object();
	m_BottomBox = new Object();
}

Room::~Room()
{
	delete m_RightBox;
	delete m_BottomBox;
}

void Room::Init(const RectSettings& settings)
{
	m_RectSettings = settings;
}

void Room::SetBounds(Rectangle bounds)
{
	Object::SetBounds(bounds);
	Rectangle right{ 0,0,0,0 };
	Rectangle bottom{ 0,0,0,0 };

	if (m_Bounds.width > 3)
	{
		right.x = m_Bounds.x + 0.75f * m_Bounds.width;
		right.y = m_Bounds.y;
		right.width = 0.25f * m_Bounds.width;
		right.height = 0.75f * m_Bounds.height;
		m_RightBox->SetBounds(right);
	}
	if (m_Bounds.height > 3)
	{
		bottom.x = m_Bounds.x;
		bottom.y = m_Bounds.y + 0.75f * m_Bounds.height;
		bottom.width = 0.75f * m_Bounds.width;
		bottom.height = 0.25f * m_Bounds.height;
		m_BottomBox->SetBounds(bottom);
	}
}

void Room::Update()
{
	if (m_DraggableEntered)
	{
		if (CheckCollisionPointRec(GetMousePosition(), m_RightBox->GetBounds()))
		{
			m_SelectedBox = m_RightBox;
		}
		else if (CheckCollisionPointRec(GetMousePosition(), m_BottomBox->GetBounds()))
		{
			m_SelectedBox = m_BottomBox;
		}
		else
		{
			m_SelectedBox = nullptr;
		}
	}
}

void Room::Draw()
{
	DrawRectangleRec(m_Bounds, m_DraggableEntered ? m_RectSettings.dragEnterColor : m_RectSettings.normalColor);
	if (m_DraggableEntered)
	{
		if (!m_RightUsed)
		{
		DrawRectangleRec(m_RightBox->GetBounds(), m_SelectedBox == m_RightBox ? Fade(ORANGE, 0.5f) : LIGHTGRAY);
		}
		if (!m_BottomUsed)
		{
		DrawRectangleRec(m_BottomBox->GetBounds(), m_SelectedBox == m_BottomBox ? Fade(ORANGE, 0.5f) : LIGHTGRAY);
		}
	}
}

void Room::SetRoomNode(RoomNode* roomNode)
{
	m_RoomNode = roomNode;
}

void Room::SetTempColor(Color color)
{
	m_BackupColor = m_RectSettings.normalColor;
	m_RectSettings.normalColor = color;
}

void Room::RemoveTempColor()
{
	m_RectSettings.normalColor = m_BackupColor;
}

void Room::OnDraggableEnter(Draggable* draggable)
{
	m_DraggableEntered = true;
	m_CurrDraggable = draggable;
}

void Room::OnDraggableExit(Draggable* draggable)
{
	m_DraggableEntered = false;
	m_CurrDraggable = nullptr;
}

void Room::OnDropped(Draggable* draggable, bool& dropped)
{
	if (m_SelectedBox)
	{
		dropped = true;
		Rectangle bounds = draggable->GetBounds();
		if (m_SelectedBox == m_RightBox)
		{
			bounds.x = m_Bounds.x + m_Bounds.width;
			bounds.y = m_Bounds.y;
		}
		else if (m_SelectedBox == m_BottomBox)
		{
			bounds.x = m_Bounds.x;
			bounds.y = m_Bounds.y + m_Bounds.height;
		}
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

		CutLine* cutLine = static_cast<CutLine*>(GameManager::GetInstance().CreateObject<CutLine>());
		cutLine->SetZIndex(1);

		if (m_SelectedBox == m_RightBox)
		{
			float x1 = m_Bounds.x + m_Bounds.width;
			float y1 = m_Bounds.y;
			float x2 = x1;
			float y2 = y1 + std::max(m_Bounds.height,bounds.height);
			cutLine->SetBounds({(float)x1,(float)y1,(float)x2,(float)y2});
			FloorPlan::GetInstance().AddNodeToRight(m_RoomNode, roomNode,cutLine);
		}
		else if (m_SelectedBox == m_BottomBox)
		{
			float x1 = m_Bounds.x;
			float y1 = m_Bounds.y + m_Bounds.height;
			float x2 = x1 + std::max(m_Bounds.width,bounds.width);
			float y2 = y1;
			cutLine->SetBounds({(float)x1,(float)y1,(float)x2,(float)y2});
			FloorPlan::GetInstance().AddNodeToBottom(m_RoomNode, roomNode,cutLine);
		}
	}
	else
	{
		dropped = false;
	}

	m_DraggableEntered = false;
	m_CurrDraggable = nullptr;
}

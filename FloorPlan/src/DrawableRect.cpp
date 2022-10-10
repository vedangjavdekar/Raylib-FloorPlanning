#include "DrawableRect.h"
#include "BoxConstraint.h"

void DrawableRect::Init(const RectSettings& initializer)
{
	m_Settings = initializer;

	MakeHitTestInvisible(false);
}

void DrawableRect::OnEnterDropTarget(DropTarget* dropTarget)
{
	m_FadeAmt = 0.25f;
}

void DrawableRect::OnExitDropTarget(DropTarget* dropTarget)
{
	m_FadeAmt = 1.0f;
}

void DrawableRect::OnHoverEnter()
{
	m_IsHovered = true;
}

void DrawableRect::OnHoverExit()
{
	m_IsHovered = false;
}

void DrawableRect::OnDragStart()
{
	m_StartPoint.x = m_Bounds.x;
	m_StartPoint.y = m_Bounds.y;
	Vector2 mouse = GetMousePosition();
	m_DragOffset.x = mouse.x - m_Bounds.x;
	m_DragOffset.y = mouse.y - m_Bounds.y;

	MakeHitTestInvisible(true);
	SetZIndex(2);
}

void DrawableRect::OnDrag()
{
	Vector2 mouse = GetMousePosition();
	m_Bounds.x = mouse.x - m_DragOffset.x;
	m_Bounds.y = mouse.y - m_DragOffset.y;
}

void DrawableRect::OnDragEnd(bool dropped)
{
	if (!dropped)
	{
		m_FadeAmt = 1.0f;
		m_Bounds.x = m_StartPoint.x;
		m_Bounds.y = m_StartPoint.y;
		m_IsHovered = false;
		MakeHitTestInvisible(false);
	}
	else
	{
		Clear();
		m_IsHovered = false;
		MakeHitTestInvisible(false);
	}

	SetZIndex(0);
}

void DrawableRect::Update()
{
	if (m_IsCleared)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_IsDrawing)
		{
			m_IsCleared = false;
			m_IsDrawing = true;
			m_RectStartPoint = GetMousePosition();
			MakeHitTestInvisible(true);
			if (m_Constraint)
			{
				m_Constraint->AttachObject(this);
			}
		}
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_IsDrawing)
	{
		m_IsDrawing = false;
		MakeHitTestInvisible(false);

		if (m_Constraint)
		{
			if (!m_Constraint->IsValidRect())
			{
				Clear();
			}
			m_Constraint->DetachObject();
		}
	}

	if (!m_IsCleared && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		Clear();
	}

	if (m_IsDrawing)
	{
		m_RectEndPoint = GetMousePosition();

		m_Bounds.x = std::min(m_RectStartPoint.x, m_RectEndPoint.x);
		m_Bounds.y = std::min(m_RectStartPoint.y, m_RectEndPoint.y);
		m_Bounds.width = std::abs(m_RectEndPoint.x - m_RectStartPoint.x);
		m_Bounds.height = std::abs(m_RectEndPoint.y - m_RectStartPoint.y);
	}
}

void DrawableRect::Draw()
{
	DrawRectangleRec(m_Bounds, Fade((m_IsHovered ? m_Settings.dragEnterColor : m_Settings.normalColor),m_FadeAmt));
}

void DrawableRect::Clear()
{
	m_FadeAmt = 1.0f;
	m_IsCleared = true;
	m_IsDrawing = false;
	m_Bounds = { 0,0,0,0 };
	m_RectStartPoint.x = 0;
	m_RectStartPoint.y = 0;
	m_RectEndPoint.x = 0;
	m_RectEndPoint.y = 0;
}

void DrawableRect::SetConstraintRect(BoxConstraint* boxConstraint)
{
	m_Constraint = boxConstraint;
}

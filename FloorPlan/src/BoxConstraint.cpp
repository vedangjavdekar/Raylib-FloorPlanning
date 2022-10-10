#include "BoxConstraint.h"
#include <iostream>

void BoxConstraint::Init(Color color, Rectangle bounds)
{
	m_Color = color;
	m_Bounds = bounds;
}

void BoxConstraint::Update()
{
	if (!m_ControlObject)
	{
		return;
	}

	Rectangle objBounds = m_ControlObject->GetBounds();
	if (CheckCollisionRecs(objBounds, m_Bounds))
	{
		objBounds.x = std::min(std::max(objBounds.x,m_Bounds.x), m_Bounds.x + m_Bounds.width);
		objBounds.y = std::min(std::max(objBounds.y,m_Bounds.y), m_Bounds.y + m_Bounds.height);
		if (objBounds.x + objBounds.width > m_Bounds.x + m_Bounds.width)
		{
			objBounds.width = m_Bounds.x + m_Bounds.width - objBounds.x;
		}
		if (objBounds.y + objBounds.height > m_Bounds.y + m_Bounds.height)
		{
			objBounds.height = m_Bounds.y + m_Bounds.height - objBounds.y;
		}
		m_ControlObject->SetBounds(objBounds);
		m_IsValidRect = true;
	}
	else
	{
		m_ControlObject->SetBounds({ m_Bounds.x,m_Bounds.y,0,0 });
		m_IsValidRect = false;
	}
}

void BoxConstraint::Draw()
{
	DrawRectangleLines(m_Bounds.x,m_Bounds.y,m_Bounds.width,m_Bounds.height, m_Color);
}

void BoxConstraint::AttachObject(Object* obj)
{
	m_ControlObject = obj;
	m_IsValidRect = false;
}

void BoxConstraint::DetachObject()
{
	m_ControlObject = nullptr;
}

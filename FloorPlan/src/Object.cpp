#include "Object.h"
#include "GameManager.h"


void Object::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

void Object::SetCanUpdate(bool canUpdate)
{
	m_CanUpdate = canUpdate;
}

void Object::SetCanDraw(bool canDraw)
{
	m_CanDraw = canDraw;
}

void Object::MakeHitTestInvisible(bool hitTestInvisible)
{
	m_IsHitTestInvisible = hitTestInvisible;
}

void Object::SetBounds(Rectangle bounds)
{
	m_Bounds = bounds;
}

void Object::SetZIndex(int newIndex)
{
	int currIndex = m_ZIndex;
	m_ZIndex = newIndex;
	GameManager::GetInstance().UpdateZIndex(m_EntityID, currIndex, m_ZIndex);
}

void Object::MarkForDelete()
{
	m_IsMarkedForDelete = true;
	GameManager::GetInstance().AddForDelete(m_EntityID);
}

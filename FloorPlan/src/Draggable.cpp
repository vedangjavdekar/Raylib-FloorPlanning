#include "Draggable.h"
#include "GameManager.h"

Draggable::Draggable()
{
	GameManager::GetInstance().GetDragAndDropManager().RegisterDraggable(this);
}

Draggable::~Draggable()
{
	GameManager::GetInstance().GetDragAndDropManager().UnregisterDraggable(this);
}


#include "DropTarget.h"
#include "GameManager.h"

DropTarget::DropTarget()
{
	GameManager::GetInstance().GetDragAndDropManager().RegisterDropTarget(this);
}

DropTarget::~DropTarget()
{
	GameManager::GetInstance().GetDragAndDropManager().UnregisterDropTarget(this);
}

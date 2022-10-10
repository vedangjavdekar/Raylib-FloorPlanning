#pragma once
#include "raylib.h"
#include "Object.h"
#include "DragAndDropManager.h"

class DropTarget;

class Draggable: public Object
{
public:
	Draggable();
	virtual ~Draggable();
	
	virtual void OnEnterDropTarget(DropTarget* dropTarget) = 0;
	virtual void OnExitDropTarget(DropTarget* dropTarget) = 0;
	virtual void OnHoverEnter() = 0;
	virtual void OnHoverExit() = 0;
	virtual void OnDragStart() = 0;
	virtual void OnDrag() = 0;
	virtual void OnDragEnd(bool dropped = false) = 0;

private:
	unsigned int m_ID = 0;
	friend class DragAndDropManager;
};
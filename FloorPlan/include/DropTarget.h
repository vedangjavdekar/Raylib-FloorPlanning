#pragma once 

#include "Object.h"
#include "DragAndDropManager.h"

class Draggable;

class DropTarget: public Object
{
public:
	DropTarget();
	virtual ~DropTarget();
	
	virtual void OnDraggableEnter(Draggable* draggable) = 0;
	virtual void OnDraggableExit(Draggable* draggable) = 0;
	virtual void OnDropped(Draggable* draggable,bool& dropped) = 0;

private:
	unsigned int m_ID = 0;
	friend class DragAndDropManager;
};
#pragma once
#include <queue>
#include<unordered_map>
#include "Draggable.h"
#include "DropTarget.h"

class DragAndDropManager
{
public:
	void Update();

	void RegisterDraggable(Draggable* draggable);
	void UnregisterDraggable(Draggable* draggable);
	void RegisterDropTarget(DropTarget* dropTarget);
	void UnregisterDropTarget(DropTarget* dropTarget);
protected:
    unsigned int GetNewID();

	unsigned int m_CurrHoveredID = 0;
	unsigned int m_CurrDraggingID = 0;

private:
    unsigned int m_CurrID = 0;
    std::queue<unsigned int> m_IDs;
	std::unordered_map<unsigned int, Draggable*> m_Draggables;
	std::unordered_map<unsigned int, DropTarget*> m_DropTargets;
};
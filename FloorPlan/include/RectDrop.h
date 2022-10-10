#pragma once

#include "DropTarget.h"
#include "RectSettings.h"
#include "Room.h"
#include "FloorPlan.h"

class RectDrop : public DropTarget
{
public:
	void Init(const RectSettings& initializer);

	// Inherited via DropTarget
	virtual void OnDraggableEnter(Draggable* draggable) override;

	virtual void OnDraggableExit(Draggable* draggable) override;

	virtual void OnDropped(Draggable* draggable,bool& dropped) override;

	// Inherited via Object
	virtual void Update()override;
	virtual void Draw()override;

private:
	bool m_DraggableEnter = false;
	RectSettings m_Settings;
};
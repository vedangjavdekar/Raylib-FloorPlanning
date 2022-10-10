#pragma once
#include "raylib.h"
#include "Draggable.h"
#include "RectSettings.h"

class BoxConstraint;

class DrawableRect : public Draggable
{
public:
	void Init(const RectSettings& initializer);
	// Inherited via Draggable
	virtual void OnEnterDropTarget(DropTarget* dropTarget) override;
	virtual void OnExitDropTarget(DropTarget* dropTarget) override;
	virtual void OnHoverEnter() override;
	virtual void OnHoverExit() override;
	virtual void OnDragStart() override;
	virtual void OnDrag() override;
	virtual void OnDragEnd(bool dropped = false) override;

	// Inherited via Object
	virtual void Update()override;
	virtual void Draw() override;

	void Clear();

	void SetConstraintRect(BoxConstraint* boxConstraint);

private:
	bool m_IsHovered = false;
	bool m_IsDrawing = false;
	bool m_IsCleared = true;
	float m_FadeAmt = 1.0f;
	RectSettings m_Settings;
	Vector2 m_StartPoint{0,0};
	Vector2 m_DragOffset{0,0};

	Vector2 m_RectStartPoint{ 0,0 };
	Vector2 m_RectEndPoint{ 0,0 };
	BoxConstraint* m_Constraint = nullptr;
};
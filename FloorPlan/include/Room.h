#pragma once
#include "DropTarget.h"
#include "RectSettings.h"

struct RoomNode;

class Room : public DropTarget
{
public:
	const RectSettings DEFAULTS{ DARKGRAY,GRAY,true };
public:
	Room();
	virtual ~Room()override;

	void Init(const RectSettings& settings);

	// Inherited via DropTarget
	virtual void OnDraggableEnter(Draggable* draggable) override;

	virtual void OnDraggableExit(Draggable* draggable) override;

	virtual void OnDropped(Draggable* draggable,bool& dropped) override;

	virtual void SetBounds(Rectangle bounds);
	virtual void Update()override;
	virtual void Draw()override;

	void SetRoomNode(RoomNode* roomNode);

	void SetTempColor(Color color);
	void RemoveTempColor();
private:
	bool m_DraggableEntered = false;
	RectSettings m_RectSettings;
	Draggable* m_CurrDraggable = nullptr;
	bool m_RightUsed = false;
	bool m_BottomUsed = false;
	Object* m_RightBox = nullptr;
	Object* m_BottomBox = nullptr;

	Object* m_SelectedBox = nullptr;
	RoomNode* m_RoomNode = nullptr;

	Color m_BackupColor = WHITE;
};
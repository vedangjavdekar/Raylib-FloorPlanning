#include "TreeNode.h"

TreeNode::~TreeNode()
{
	if (left)
	{
		delete left;
	}

	if (right)
	{
		delete right;
	}
}

CutNode::~CutNode()
{
	cutLine->MarkForDelete();
}

void CutNode::OnHoveredInViewer()
{
	cutLine->SetTempColor(SKYBLUE);
}

void CutNode::OnUnhoveredInViewer()
{
	cutLine->RemoveTempColor();
}

RoomNode::~RoomNode()
{
	room->MarkForDelete();
}

void RoomNode::OnHoveredInViewer()
{
	room->SetTempColor(SKYBLUE);
}

void RoomNode::OnUnhoveredInViewer()
{
	room->RemoveTempColor();
}

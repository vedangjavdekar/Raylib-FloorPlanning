#include "FloorPlan.h"
#include "raylib.h"
#include "CutLine.h"

Vector2 FloorPlan::GetNewDimensions(TreeNode* node)
{
	if (RoomNode* room = dynamic_cast<RoomNode*>(node))
	{
		room->newBounds.width = room->width;
		room->newBounds.height = room->height;
		return Vector2{ room->width,room->height };
	}

	if (CutNode* cut = dynamic_cast<CutNode*>(node))
	{
		if (cut->cutID == ECutType::VERTICAL)
		{
			Vector2 leftDimensions = GetNewDimensions(node->left);
			Vector2 rightDimensions = GetNewDimensions(node->right);

			Vector2 newBounds{ leftDimensions.x + rightDimensions.x, std::max(leftDimensions.y, rightDimensions.y) };
			node->newBounds.width = newBounds.x;
			node->newBounds.height = newBounds.y;
			return newBounds;

		}
		else if (cut->cutID == ECutType::HORIZONTAL)
		{
			Vector2 leftDimensions = GetNewDimensions(node->left);
			Vector2 rightDimensions = GetNewDimensions(node->right);
			Vector2 newBounds{ std::max(leftDimensions.x , rightDimensions.x) , leftDimensions.y + rightDimensions.y };
			node->newBounds.width = newBounds.x;
			node->newBounds.height = newBounds.y;
			return newBounds;
		}
	}

	return Vector2();
}

void FloorPlan::ResizeNode(TreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->parent)
	{
		if (CutNode* cutNode = dynamic_cast<CutNode*>(node->parent))
		{
			if (cutNode->cutID == ECutType::VERTICAL)
			{
				node->newBounds.height = cutNode->newBounds.height;
				if (node->parent->right == node)
				{
					int diff = cutNode->newBounds.width - node->parent->left->newBounds.width;
					if (diff != node->newBounds.width)
					{
						node->newBounds.width = diff;
					}
				}
			}
			else
			{
				node->newBounds.width = cutNode->newBounds.width;
				if (node->parent->right == node)
				{
					int diff = cutNode->newBounds.height - node->parent->left->newBounds.height;
					if (diff != node->newBounds.height)
					{
						node->newBounds.height = diff;
					}
				}
			}
		}
	}

	ResizeNode(node->left);
	ResizeNode(node->right);
}

void FloorPlan::PropogateChangesForward(TreeNode* node)
{
	if (RoomNode* room = dynamic_cast<RoomNode*>(node))
	{
		room->height = room->newBounds.height;
		room->width = room->newBounds.width;
		room->room->SetBounds(room->newBounds);
		return;
	}

	if (CutNode* cut = dynamic_cast<CutNode*>(node))
	{
		if (cut->left && cut->right)
		{
			cut->left->newBounds.x = cut->newBounds.x;
			cut->left->newBounds.y = cut->newBounds.y;

			if (cut->cutID == ECutType::VERTICAL)
			{
				cut->right->newBounds.x = cut->newBounds.x + cut->left->newBounds.width;
				cut->right->newBounds.y = cut->newBounds.y;
				cut->cutLine->SetBounds({
					cut->newBounds.x + cut->left->newBounds.width,
					cut->newBounds.y,
					cut->newBounds.x + cut->left->newBounds.width,
					cut->newBounds.y + cut->newBounds.height
					});
			}
			else if (cut->cutID == ECutType::HORIZONTAL)
			{
				cut->right->newBounds.x = cut->newBounds.x;
				cut->right->newBounds.y = cut->newBounds.y + cut->left->newBounds.height;
				cut->cutLine->SetBounds({
					cut->newBounds.x,
					cut->newBounds.y + cut->left->newBounds.height,
					cut->newBounds.x + cut->newBounds.width,
					cut->newBounds.y + cut->left->newBounds.height
					});
			}

			PropogateChangesForward(cut->left);
			PropogateChangesForward(cut->right);
		}
	}

}

FloorPlan::FloorPlan()
{

}

FloorPlan::~FloorPlan()
{
	delete m_Root;
}


FloorPlan& FloorPlan::GetInstance()
{
	static FloorPlan instance;
	return instance;
}

void FloorPlan::AddRootNode(TreeNode* root)
{
	m_Root = root;
}

void FloorPlan::AddNodeToRight(TreeNode* node, TreeNode* self, CutLine* cutLine)
{
	TreeNode* parent = node->parent;
	RoomNode* leftRoom = static_cast<RoomNode*>(node);
	RoomNode* rightRoom = static_cast<RoomNode*>(self);

	TreeNode* cutNode = new CutNode();
	CutNode* cut = static_cast<CutNode*>(cutNode);

	cut->cutLine = cutLine;
	cutLine->SetCutNode(cut);
	cut->cutID = ECutType::VERTICAL;
	cutNode->left = leftRoom;
	leftRoom->parent = cutNode;
	cutNode->right = rightRoom;
	rightRoom->parent = cutNode;

	if (parent == nullptr)
	{
		//Root node
		m_Root = cutNode;
	}
	else
	{
		if (parent->left == node)
		{
			parent->left = cutNode;
		}
		else
		{
			parent->right = cutNode;
		}
		cutNode->parent = parent;
	}
}

void FloorPlan::AddNodeToBottom(TreeNode* node, TreeNode* self, CutLine* cutLine)
{
	TreeNode* parent = node->parent;
	RoomNode* leftRoom = static_cast<RoomNode*>(node);
	RoomNode* rightRoom = static_cast<RoomNode*>(self);

	TreeNode* cutNode = new CutNode();
	CutNode* cut = static_cast<CutNode*>(cutNode);

	cut->cutLine = cutLine;
	cutLine->SetCutNode(cut);
	cut->cutID = ECutType::HORIZONTAL;
	cutNode->left = leftRoom;
	leftRoom->parent = cutNode;
	cutNode->right = rightRoom;
	rightRoom->parent = cutNode;

	if (parent == nullptr)
	{
		//Root node
		m_Root = cutNode;
	}
	else
	{
		if (parent->left == node)
		{
			parent->left = cutNode;
		}
		else
		{
			parent->right = cutNode;
		}
		cutNode->parent = parent;
	}
}

void FloorPlan::Reset()
{
	delete m_Root;
	m_Root = nullptr;
}

void FloorPlan::Compact(float originX, float originY)
{
	Vector2 newBounds = GetNewDimensions(m_Root);
	m_TotalWidth = newBounds.x;
	m_TotalHeight = newBounds.y;

	if (m_Root)
	{
		m_Root->newBounds.x = originX;
		m_Root->newBounds.y = originY;
	}

	ResizeNode(m_Root);
	PropogateChangesForward(m_Root);
}

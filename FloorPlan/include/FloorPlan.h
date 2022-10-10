#pragma once
#include <vector>
#include "TreeNode.h"

class CutLine;

class FloorPlan
{
public:
	static FloorPlan& GetInstance();
	void AddRootNode(TreeNode* root);
	void AddNodeToRight(TreeNode* node, TreeNode* self,CutLine* cutLine);
	void AddNodeToBottom(TreeNode* node, TreeNode* self,CutLine* cutLine);
	void Reset();
	void Compact(float originX,float originY);

	TreeNode* GetRoot()const { return m_Root; }
protected:
	Vector2 GetNewDimensions(TreeNode* node);
	void ResizeNode(TreeNode* node);
	void PropogateChangesForward(TreeNode* node);
private:
	FloorPlan();
	~FloorPlan();
	int m_TotalWidth = 0;
	int m_TotalHeight = 0;
	TreeNode* m_Root = nullptr;
};
#pragma once
#include "raylib.h"
#include "TreeNode.h"

class TreeDrawer
{
private:
    const int singleLineHeight = 25;
    const int xIndentWidth = 25;
     
public:
    void Init(TreeNode* root);
    void Update();
    void Draw(int startX,int startY);
protected:
    void DrawNode(int& startX, int& startY, TreeNode* node, const std::string& prefix);
    void DrawExpandTriangle(int startX, int startY, bool expanded = false);
protected:
    Vector2 m_MousePos;
    TreeNode* m_Hovered = nullptr;
    TreeNode* m_NewHovered = nullptr;
private:
    TreeNode* m_Root = nullptr;
};
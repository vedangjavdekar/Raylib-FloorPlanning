#include "TreeDrawer.h"

void TreeDrawer::Init(TreeNode* root)
{
	m_Root = root;
}

void TreeDrawer::Update()
{
	if (!m_Root)
	{
		return;
	}
	if (m_Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		m_Hovered->isExpanded = !m_Hovered->isExpanded;
	}
}

void TreeDrawer::Draw(int startX, int startY)
{
	if (!m_Root)
	{
		return;
	}
	int x = startX;
	int y = startY;

	m_MousePos = GetMousePosition();

	m_NewHovered = nullptr;
	DrawNode(x, y, m_Root, "");
	if (m_Hovered != m_NewHovered)
	{
		if (m_Hovered)
		{
			m_Hovered->OnUnhoveredInViewer();
		}
		m_Hovered = m_NewHovered;
		if (m_Hovered)
		{
			m_Hovered->OnHoveredInViewer();
		}
	}
}

void TreeDrawer::DrawNode(int& startX, int& startY, TreeNode* node, const std::string& prefix)
{
	if (node)
	{
		const std::string str = node->ToString(prefix);
		if (node->left || node->right)
		{
			DrawExpandTriangle(startX, startY, node->isExpanded);

		}
		int width = MeasureText(str.c_str(), 20);
		Rectangle r{ (float)startX,(float)startY,(float)width,(float)singleLineHeight };
		if (CheckCollisionPointRec(m_MousePos, r))
		{
			m_NewHovered = node;
		}
		startX += 25;
		DrawText(str.c_str(), startX, startY, 20, m_NewHovered == node?SKYBLUE:GRAY);

		startX += xIndentWidth;
		startY += singleLineHeight;
		if (node->isExpanded)
		{
			DrawNode(startX, startY, node->left, "L: ");
			DrawNode(startX, startY, node->right, "R: ");
		}

		startX -= xIndentWidth;
		startX -= 25;
	}
}

void TreeDrawer::DrawExpandTriangle(int startX, int startY, bool expanded)
{
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
	if (expanded)
	{
		v1.x = (float)(startX + 10);
		v1.y = (float)(startY);
		v2.x = (float)(startX);
		v2.y = (float)(startY + 0.5f * singleLineHeight);
		v3.x = (float)(startX + 10);
		v3.y = (float)(startY + 0.5f * singleLineHeight);
	}
	else
	{
		v1.x = (float)(startX);
		v1.y = (float)(startY);
		v2.x = (float)(startX);
		v2.y = (float)(startY + 0.75f * singleLineHeight);
		v3.x = (float)(startX + 10);
		v3.y = (float)(startY + 0.375f * singleLineHeight);
	}

	DrawTriangle(v1, v2, v3, DARKGRAY);
}

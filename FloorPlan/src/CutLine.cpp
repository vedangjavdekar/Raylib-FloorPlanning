#include "CutLine.h"
#include "TreeNode.h"

void CutLine::Draw()
{
	DrawLine(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Bounds.height, m_Color);
}

void CutLine::SetCutNode(CutNode* node)
{
	m_CutNode = node;
}

void CutLine::SetTempColor(Color color)
{
	m_Color = color;
}

void CutLine::RemoveTempColor()
{
	m_Color = RED;
}

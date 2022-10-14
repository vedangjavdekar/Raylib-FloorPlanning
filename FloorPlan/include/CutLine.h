#pragma once

#include "Object.h"

struct CutNode;

class CutLine : public Object
{
public:
	virtual void Draw()override;
	void SetCutNode(CutNode* node);
	void SetTempColor(Color color);
	void RemoveTempColor();
private:
	const Color NORMAL_COLOR = YELLOW;
	Color m_Color = NORMAL_COLOR;
	CutNode* m_CutNode = nullptr;
};
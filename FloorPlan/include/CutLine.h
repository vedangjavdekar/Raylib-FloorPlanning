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
	Color m_Color = RED;
	CutNode* m_CutNode = nullptr;
};
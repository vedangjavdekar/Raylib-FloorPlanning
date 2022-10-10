#pragma once 

#include "Object.h"
#include "raylib.h"

class BoxConstraint : public Object
{
public:
    void Init(Color color, Rectangle bounds);
    void Update()override;
    void Draw() override;

    void AttachObject(Object* obj);
    void DetachObject();
    bool IsValidRect()const { return m_IsValidRect; }

private:
    bool m_IsValidRect = false;
    Color m_Color = WHITE;
    Object* m_ControlObject = nullptr;
};
#pragma once
#include "raylib.h"

class Object
{
public:
	Object() {}
	virtual ~Object() {}

	void MakeHitTestInvisible(bool hitTestInvisible = true);
	bool IsHitTestInvisible()const { return m_IsHitTestInvisible; }

    void SetActive(bool isActive);
	bool IsActive()const { return m_IsActive; }

	void SetCanUpdate(bool canUpdate);
	bool CanUpdate()const { return m_CanUpdate; }

	void SetCanDraw(bool canDraw);
	bool CanDraw()const { return m_CanDraw; }

	virtual void SetBounds(Rectangle bounds);
	Rectangle GetBounds()const { return m_Bounds; }

    void SetZIndex(int newIndex);

	virtual void Update() {}
	virtual void Draw(){}
    virtual void MarkForDelete();
    bool IsMarkedForDelete() const{return m_IsMarkedForDelete;}


protected:
    unsigned int m_EntityID = 0;
    bool m_IsMarkedForDelete = false;
	bool m_IsActive = true;
	bool m_CanUpdate = true;
	bool m_CanDraw = true;
	bool m_IsHitTestInvisible = false;
    int m_ZIndex = 0;

	friend class GameManager;

	Rectangle m_Bounds{0,0,1,1};

};
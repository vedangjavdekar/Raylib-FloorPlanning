#pragma once 
#include <sstream>
#include <string>
#include "raylib.h"
#include "Room.h"
#include "CutLine.h"

enum class ECutType
{
	UNDEFINED = 0,
	VERTICAL,
	HORIZONTAL
};

struct TreeNode
{
	virtual	~TreeNode();

	TreeNode* parent = nullptr;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	bool isExpanded = false;
	virtual std::string ToString(const std::string& prefix)const
	{
		std::stringstream ss;
		ss << prefix << "TreeNode";
		return ss.str();
	}

	virtual void OnHoveredInViewer() {}
	virtual void OnUnhoveredInViewer() {}

	Rectangle newBounds{ 0,0,0,0 };
};

struct CutNode : public TreeNode
{
	virtual ~CutNode();
	/*
	* 0: no cut
	* 1: vertical
	* 2: horizontal
	*/
	ECutType cutID = ECutType::UNDEFINED;

	float startX = 0;
	float startY = 0;
	float endX = 0;
	float endY = 0;

	CutLine* cutLine = nullptr;

	virtual std::string ToString(const std::string& prefix)const override
	{
		std::stringstream ss;
		ss << prefix;
		switch (cutID)
		{
		case ECutType::VERTICAL:
		{
			ss << "Vertical Cut";
			break;
		}
		case ECutType::HORIZONTAL:
		{
			ss << "Horizontal Cut";
			break;
		}
		case ECutType::UNDEFINED:
		default:
		{
			ss << "No Cut";
			break;
		}
		}

		return ss.str();
	}

	virtual void OnHoveredInViewer();
	virtual void OnUnhoveredInViewer();
};

struct RoomNode : public TreeNode
{
	virtual ~RoomNode();
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;

	Room* room = nullptr;
	virtual std::string ToString(const std::string& prefix)const override
	{
		std::stringstream ss;
		ss << prefix << "Room(" << width << "x" << height << ")";
		return ss.str();
	}

	virtual void OnHoveredInViewer();
	virtual void OnUnhoveredInViewer();
};

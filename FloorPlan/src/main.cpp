#include "raylib.h"
#include "TreeDrawer.h"
#include "TreeNode.h"
#include "GameManager.h"
#include "RectSettings.h"
#include "DrawableRect.h"
#include "RectDrop.h"
#include "BoxConstraint.h"
#include "Room.h"

int main()
{
	TreeDrawer drawer;

	const Rectangle drawArea{ 20,20,250,250 };
	const Rectangle floorPlanArea{ 300,20,500,500 };
	const int screenWidth = 1280;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Floor Plan");
	SetTargetFPS(60);

	RectSettings settings;
	settings.fill = false;
	settings.normalColor = GRAY;
	settings.dragEnterColor = GREEN;

	DrawableRect* rect = static_cast<DrawableRect*>(GameManager::GetInstance().CreateObject<DrawableRect>());
	rect->Init(settings);

	RectDrop* rectDrop = static_cast<RectDrop*>(GameManager::GetInstance().CreateObject<RectDrop>());
	rectDrop->Init(settings);
	rectDrop->SetBounds({ 300,20,500,500 });

	BoxConstraint* boxConstraint = static_cast<BoxConstraint*>(GameManager::GetInstance().CreateObject<BoxConstraint>());
	boxConstraint->Init(GREEN, { 20,20,200,200 });

	rect->SetConstraintRect(boxConstraint);
	RectSettings roomSettings;
	roomSettings.fill = true;
	roomSettings.normalColor = DARKGRAY;
	roomSettings.dragEnterColor = GRAY;

	
	while (!WindowShouldClose())
	{
		// Update
		//----------------------------------------------------------------------------------
		GameManager::GetInstance().Update();
		drawer.Init(FloorPlan::GetInstance().GetRoot());
		drawer.Update();

		if (IsKeyPressed(KEY_SPACE))
		{
			FloorPlan::GetInstance().Compact(floorPlanArea.x,floorPlanArea.y);
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("1. Draw here\nLeft Click: Draw\nRightClick: Clear", 20, 300, 20, GRAY);
		DrawText("2. Drop here\nRightClick: Clear", 300, 550, 20, GRAY);
		DrawText("Press SPACE to compact the room.", 300, 650, 20, GRAY);
		GameManager::GetInstance().Draw();
		drawer.Draw(850, 20);
		EndDrawing();
		//----------------------------------------------------------------------------------

	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

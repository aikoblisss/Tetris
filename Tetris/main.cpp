#include <raylib.h>
#include "game.h"
#include "Colors.h"
#include <iostream>

double lastUpdateTime = 0;
double blockSpeed = 0.5;
double speedIncreaseRate = 0.005;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main() 
{
	InitWindow(500, 620, "Tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("Tetris/Font", 64, 0, 0);
	Image image = LoadImage("Tetris/Images/download.jpg");
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	Game game = Game();

	int blocksMoved = 0;

	while (WindowShouldClose() == false)
{
		UpdateMusicStream(game.music);
		game.HandleInput();
		if (EventTriggered(blockSpeed))
		{
			game.MoveBlockDown();
			blocksMoved++;
		}

		if (blocksMoved % 10 == 0 && blockSpeed > 0.1)
		{
			blockSpeed -= speedIncreaseRate;
		}

		BeginDrawing();
		//ClearBackground(darkBlue); 
		DrawTextEx(font, "Score", { 350, 15 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 350, 175 }, 38, 2, WHITE);
		if (game.gameOver)
		{ 
			DrawTextEx(font, "GAME OVER", { 320, 450 }, 25, 2, WHITE);
		}
		DrawTexture(texture, 400 - texture.width / 2, 300 - texture.height / 2, WHITE);
		
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);
		
		game.Draw();
		EndDrawing();
	}

	UnloadTexture(texture);
	CloseWindow(); 
}
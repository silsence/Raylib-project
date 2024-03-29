#include "raylib.h"

int main(void) {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	
	int mframesCounter = 0;
	int sframesCounter = 0;
	int MframesCounter = 0;
	int hframesCounter = 0;
	
	int horas = 0;
	
	int minutos = 0;
	
	int segundos = 0;
	
	int milisegundos = 0;
	
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	
	// Main game loop
	while (!WindowShouldClose()) {  // Detect window close button or ESC key
		// Update
		
		//帧计数器
		sframesCounter ++;
		
		//分秒计数器
		mframesCounter++;
		
		//分秒存储器
		milisegundos = mframesCounter;
		
		
		//分秒
		if (milisegundos >= 60) {
			mframesCounter = 0;
			segundos++;
		}
		//秒
		if (segundos >= 60) {
			segundos = 0;
			minutos ++;
		}
		//分钟
		if (minutos >= 60) {
			minutos = 0;
			horas ++;
		}
		//小时
		if (horas >= 24) {
			horas = 0;
		}
		
		
		
		
		
		
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		
		
		
		
		
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		
		DrawText(TextFormat("TIME: %i", horas), 10, 10, 20, BLACK);
		
		DrawText(TextFormat(":%i", minutos), 100, 10, 20, BLACK);
		
		DrawText(TextFormat(":%i", segundos), 130, 10, 20, BLACK);
		
		DrawText(TextFormat(":%i", milisegundos), 160, 10, 20, BLACK);
		
		
		
		
		
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	
	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	
	return 0;
}

/********************************************************************************************
  @filename:    rmpd.c
  @title:       Real Pixel Lighting RAMP DEMO
  @description: Simple gradient demo of RPL with shadows
  @author:      Samy Bencherif
  
  Copyright (C) 2020 Samy Bencherif (@deathstallion)
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to the following
  conditions:
  
  The above copyright notice and this permission notice shall be included in all copies
  or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  This program has been created using raylib 1.0 (www.raylib.com)
  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
  
  Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
  
 ********************************************************************************************/

#include <raylib.h>
#include <raymath.h>
#include <math.h>

// Constants
//--------------------------------------------------------------------------------------
const int screenWidth = 128;
const int screenHeight = 128;
const int scaleFactor = 3;
//--------------------------------------------------------------------------------------

//矩形判断函数，判断tx，ty是否在(x,y)矩形内
int withinRect(int tx, int ty, int x, int y, int w, int h) {
	return (tx > x) && (tx < x + w) && (ty > y) && (ty < y + h);
}
//像素绘制矩形,绘制(x,y)的矩形
void PixRect(int x, int y, int w, int h, Color c) {
	DrawRectangle(scaleFactor * x, scaleFactor * y, scaleFactor * w, scaleFactor * h, c);
}

int main(void) {
	// Initialization
	//--------------------------------------------------------------------------------------
	//模拟时间流逝
	int clock = 0;
	
	InitWindow(screenWidth * scaleFactor, screenHeight * scaleFactor, "真实像素照明");
	
	SetTargetFPS(30);
	//--------------------------------------------------------------------------------------
	
	// Main game loop
	while (!WindowShouldClose()) {
		// Update
		clock ++;
		
		// 开始绘制
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(WHITE);
		
		//获取鼠标位置
		int mouseX = GetMouseX() / scaleFactor;
		int mouseY = GetMouseY() / scaleFactor;
		
		//障碍物的宽高，和横纵坐标，表示在鼠标中心点
		int RW = 10;
		int RH = 10;
		int RX = mouseX - RW / 2;
		int RY = mouseY - RH / 2;
		
		//遍历屏幕像素
		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
				//定义光源中心点在屏幕中心，宏定义CLITERAL,编译时就确定，不可更改
				Vector2 lightSrc = CLITERAL(Vector2) {
					screenWidth / 2, screenHeight / 2
				};
				//当前像素所在位置，用于计算离光源的距离
				Vector2 screenPos = CLITERAL(Vector2) {
					x, y
				};
				
				//光源闪烁频率
				const float flickerRate = 4;
				//光源闪烁幅度
				const float flickerAmp = .003;
				//初始强度加上一个按时间（通过clock变量获取）变化的正弦波函数，模拟了光源的闪烁效果
				const float intensity = .4 + flickerAmp * sin(clock * flickerRate);
				//光源影响的距离范围。
				const float range = .95;
				//模拟光线反弹后的衰减率。
				const float bounceRate = .9;
				//全局照明(Global Illumination)的系数。
				const float gi = 0.3;
				
				
				
				//计算当前像素到光源的距离
				float d = Vector2Distance(lightSrc, screenPos);
				
				//根据得到的距离计算亮度值b，当距离超过一定范围时亮度降为0。
				int b = 255 * intensity - d / range;
				if (b < 0)
					b = 0;
				
				//初始化 emission 为1，准备用来累积反射衰减后的光线强度。
				float emission = 1;
				
				//使用一个内部循环模拟光线在空间中的扩散和反射,每一步计算采样点的光线强度并乘以衰减率 bounceRate。
				//100次采样
				float samples = 100;
				for (int i = 0; i < samples; i++) {
					//计算从屏幕中心出发，采样点沿着x和y出发
					float testX = screenWidth / 2 + (x - screenWidth / 2) * i / samples;
					float testY = screenHeight / 2 + (y - screenHeight / 2) * i / samples;
					
					//判断采样点是否在矩形内，如果在意味着倍阻挡了，就乘以0.9的强度代表衰减
					if (withinRect(testX, testY, RX, RY, RW, RH)) {
						emission *= bounceRate;
					}
				}
				
				//结合全局照明的影响来更新亮度值 b。
				b =  gi * b + (1 - gi) * b * emission;
				
				//将最终的亮度值转换成颜色，并设置Alpha通道为255，表示完全不透明。
				Color c = CLITERAL(Color) {
					b, b, b, 255
				};
				
				//使用 PixRect 函数将计算得到的颜色应用于当前像素点 (x, y)。
				PixRect(x, y, 1, 1, c );
			}
		}
		
		PixRect(mouseX, mouseY, 1, 1, BLUE);
		PixRect(RX, RY, RW, RH, RED);
		
		
		
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	
	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();    // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	
	return 0;
}

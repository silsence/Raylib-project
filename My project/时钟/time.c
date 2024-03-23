#include <stdio.h>
#include <time.h>
#include <raylib.h>

int main(int argc, char **argv) {
	
	const int screenWidth = 800;
	const int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "时钟");
	
	//读取字体文件
	unsigned int fileSize;
	unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\simhei.ttf", &fileSize);
	
	//变量
	int Hour, Minute, Second;
	time_t curr;
	time_t next;
	
	while (!WindowShouldClose()) {
		// Update
		//----------------------------------------------------------------------------------
		time(&curr);
		Second = curr % 60;
		Minute = curr / 60 % 60;
		Hour = ((curr / 60 / 60 % 24) + 8) % 24;
		while (1) {
			time(&next);
			if (next > curr)
				break;
		}
		
		//将要输出的内容放到字符串中,必须是utf8编码
		char text[32];
		snprintf(text, sizeof(text), "现在是%d时%d分%d秒", Hour, Minute, Second);
		
		// 将字符串中的字符逐一转换成Unicode码点，得到码点表
		int codepointsCount;
		int *codepoints=LoadCodepoints(text,&codepointsCount);
		
		// 读取仅码点表中各字符的字体
		Font font = LoadFontFromMemory(".ttf",fontFileData,fileSize,32,codepoints,codepointsCount);
		// 释放码点表
		UnloadCodepoints(codepoints);
		
		// 开始绘制
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		DrawTextEx(font,text,(Vector2){200,screenHeight/2.0f},32,5,RED);
		
		EndDrawing();
		//----------------------------------------------------------------------------------
		
		//释放字体
		UnloadFont(font);
	}
	//释放字体文件内容
	UnloadFileData(fontFileData);
//--------------------------------------------------------------------------------------
	CloseWindow();
	
	return 0;
}

#include <raylib.h>
#include <stdio.h>

typedef struct Line {
	Vector2 star;
	Vector2 end;
	Color color;
} Line;

int main() {

	const int screenWidth = 400;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "2048");

	Line line[] = {
		{(Vector2){100, 0}, (Vector2){100, 400}, WHITE},
		{(Vector2){200, 0}, (Vector2){200, 400}, WHITE},
		{(Vector2){300, 0}, (Vector2){300, 400}, WHITE},

		{(Vector2){0, 100}, (Vector2){400, 100}, WHITE},
		{(Vector2){0, 200}, (Vector2){400, 200}, WHITE},
		{(Vector2){0, 300}, (Vector2){400, 300}, WHITE}
	};

	int linelength = sizeof(line) / sizeof(line[0]);

	int abc[5][5] = {0};
	char textBuffer[1];

	//初始化第一个数为2或4
	abc[GetRandomValue(1, 4)][GetRandomValue(1, 4)] = (GetRandomValue(0, 1) ? 2 : 4);

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		//--------------------------------------------------------------
		//up
		if (IsKeyPressed(KEY_UP)) {
			for (int i = 3; i >0; i--) {
				//上面没数字,就往上走
				if (abc[i][1] == 0 && abc[i + 1][1] != 0) {
					abc[i][1] = abc[i + 1][1];
					abc[i + 1][1] = 0;
				}
				//前后都有数字，合并到上面，执行一次
				if (abc[i][1] != 0 && abc[i + 1][1] != 0) {
					if(abc[i][1]==abc[i + 1][1]){
						abc[i][1] += abc[i + 1][1];
						abc[i + 1][1] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				if (abc[i][2] == 0 && abc[i + 1][2] != 0) {
					abc[i][2] = abc[i + 1][2];
					abc[i + 1][2] = 0;
				}
				if (abc[i][2] != 0 && abc[i + 1][2] != 0) {
					if(abc[i][2]==abc[i + 1][2]){
						abc[i][2] += abc[i + 1][2];
						abc[i + 1][2] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				if (abc[i][3] == 0 && abc[i + 1][3] != 0) {
					abc[i][3] = abc[i + 1][3];
					abc[i + 1][3] = 0;
				}
				if (abc[i][3] != 0 && abc[i + 1][3] != 0) {
					if(abc[i][3]==abc[i + 1][3]){
						abc[i][3] += abc[i + 1][3];
						abc[i + 1][3] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				if (abc[i][4] == 0 && abc[i + 1][4] != 0) {
					abc[i][4] = abc[i + 1][4];
					abc[i + 1][4] = 0;
				}
				if (abc[i][4] != 0 && abc[i + 1][4] != 0) {
					if(abc[i][4]==abc[i + 1][4]){
						abc[i][4] += abc[i + 1][4];
						abc[i + 1][4] = 0;
						break;
					}
				}
			}
			//添加随机数字
			while(1){
				int hor=GetRandomValue(1, 4);
				int ver=GetRandomValue(1, 4);
				if(abc[hor][ver] == 0){
					abc[hor][ver] = (GetRandomValue(0, 1) ? 2 : 4);
					break;
				}
			}
		}
		
		//--------------------------------------------------------------
		//down
		if(IsKeyPressed(KEY_DOWN)){
			for (int i = 1; i < 4; i++) {
				//下面没数字,就往下走
				if (abc[i][1] != 0 && abc[i+1][1] == 0) {
					abc[i+1][1] = abc[i][1];
					abc[i][1] = 0;
				}
				//前后都有数字，合并到下一个，执行一次
				if (abc[i][1] != 0 && abc[i + 1][1] != 0) {
					if(abc[i][1]==abc[i + 1][1]){
						abc[i+1][1] += abc[i][1];
						abc[i][1] = 0;
						break;
					}
				}
			}
			for (int i = 1; i < 4; i++) {
				if (abc[i][2] != 0 && abc[i+1][2] == 0) {
					abc[i+1][2] = abc[i][2];
					abc[i][2] = 0;
				}
				if (abc[i][2] != 0 && abc[i + 1][2] != 0) {
					if(abc[i][2]==abc[i + 1][2]){
						abc[i+1][2] += abc[i][2];
						abc[i][2] = 0;
						break;
					}
				}
			}
			for (int i = 1; i < 4; i++) {
				if (abc[i][3] != 0 && abc[i+1][3] == 0) {
					abc[i+1][3] = abc[i][3];
					abc[i][3] = 0;
				}
				if (abc[i][3] != 0 && abc[i + 1][3] != 0) {
					if(abc[i][3]==abc[i + 1][3]){
						abc[i+1][3] += abc[i][3];
						abc[i][3] = 0;
						break;
					}
				}
			}
			for (int i = 1; i < 4; i++) {
				if (abc[i][4] != 0 && abc[i+1][4] == 0) {
					abc[i+1][4] = abc[i][4];
					abc[i][4] = 0;
				}
				if (abc[i][4] != 0 && abc[i + 1][4] != 0) {
					if(abc[i][4]==abc[i + 1][4]){
						abc[i+1][4] += abc[i][4];
						abc[i][4] = 0;
						break;
					}
				}
			}
			
			//添加随机数字
			while(1){
				int hor=GetRandomValue(1, 4);
				int ver=GetRandomValue(1, 4);
				if(abc[hor][ver] == 0){
					abc[hor][ver] = (GetRandomValue(0, 1) ? 2 : 4);
					break;
				}
			}
		}
		
		//--------------------------------------------------------------
		//left
		if(IsKeyPressed(KEY_LEFT)){
			for (int i = 3; i > 0; i--) {
				//下面没数字,就往下走
				if (abc[1][i] == 0 && abc[1][i+1] != 0) {
					abc[1][i] = abc[1][i+1];
					abc[1][i+1] = 0;
				}
				//左右都有数字，合并到左一个，执行一次
				if (abc[1][i] != 0 && abc[1][i+1] != 0) {
					if(abc[1][i]==abc[1][i+1]){
						abc[1][i] += abc[1][i+1];
						abc[1][i+1] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				//下面没数字,就往下走
				if (abc[2][i] == 0 && abc[2][i+1] != 0) {
					abc[2][i] = abc[2][i+1];
					abc[2][i+1] = 0;
				}
				if (abc[2][i] != 0 && abc[2][i+1] != 0) {
					if(abc[2][i]==abc[2][i+1]){
						abc[2][i] += abc[2][i+1];
						abc[2][i+1] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				//下面没数字,就往下走
				if (abc[3][i] == 0 && abc[3][i+1] != 0) {
					abc[3][i] = abc[3][i+1];
					abc[3][i+1] = 0;
				}
				if (abc[1][i] != 0 && abc[3][i+1] != 0) {
					if(abc[3][i]==abc[3][i+1]){
						abc[3][i] += abc[3][i+1];
						abc[3][i+1] = 0;
						break;
					}
				}
			}
			for (int i = 3; i > 0; i--) {
				//下面没数字,就往下走
				if (abc[4][i] == 0 && abc[4][i+1] != 0) {
					abc[4][i] = abc[4][i+1];
					abc[4][i+1] = 0;
				}
				if (abc[4][i] != 0 && abc[4][i+1] != 0) {
					if(abc[4][i]==abc[4][i+1]){
						abc[4][i] += abc[4][i+1];
						abc[4][i+1] = 0;
						break;
					}
				}
			}
			
			//添加随机数字
			while(1){
				int hor=GetRandomValue(1, 4);
				int ver=GetRandomValue(1, 4);
				if(abc[hor][ver] == 0){
					abc[hor][ver] = (GetRandomValue(0, 1) ? 2 : 4);
					break;
				}
			}
		}
		
		//--------------------------------------------------------------
		//right
		if(IsKeyPressed(KEY_RIGHT)){
			for (int i = 1; i <4; i++) {
				//右边没数字,就往右走
				if (abc[1][i] != 0 && abc[1][i+1] == 0) {
					abc[1][i+1] = abc[1][i];
					abc[1][i] = 0;
				}
				//左右都有数字，合并到左一个，执行一次
				if (abc[1][i] != 0 && abc[1][i+1] != 0) {
					if(abc[1][i]==abc[1][i+1]){
						abc[1][i+1] += abc[1][i];
						abc[1][i] = 0;
						break;
					}
				}
			}
			for (int i = 1; i <4; i++) {
				//右边没数字,就往右走
				if (abc[2][i] != 0 && abc[2][i+1] == 0) {
					abc[2][i+1] = abc[2][i];
					abc[2][i] = 0;
				}
				//左右都有数字，合并到左一个，执行一次
				if (abc[2][i] != 0 && abc[2][i+1] != 0) {
					if(abc[2][i]==abc[2][i+1]){
						abc[2][i+1] += abc[2][i];
						abc[2][i] = 0;
						break;
					}
				}
			}
			for (int i = 1; i <4; i++) {
				//右边没数字,就往右走
				if (abc[3][i] != 0 && abc[3][i+1] == 0) {
					abc[3][i+1] = abc[3][i];
					abc[3][i] = 0;
				}
				//左右都有数字，合并到左一个，执行一次
				if (abc[3][i] != 0 && abc[3][i+1] != 0) {
					if(abc[3][i]==abc[3][i+1]){
						abc[3][i+1] += abc[3][i];
						abc[3][i] = 0;
						break;
					}
				}
			}
			for (int i = 1; i <4; i++) {
				//右边没数字,就往右走
				if (abc[4][i] != 0 && abc[4][i+1] == 0) {
					abc[4][i+1] = abc[4][i];
					abc[4][i] = 0;
				}
				//左右都有数字，合并到左一个，执行一次
				if (abc[4][i] != 0 && abc[4][i+1] != 0) {
					if(abc[4][i]==abc[4][i+1]){
						abc[4][i+1] += abc[4][i];
						abc[4][i] = 0;
						break;
					}
				}
			}
			
			
			//添加随机数字
			while(1){
				int hor=GetRandomValue(1, 4);
				int ver=GetRandomValue(1, 4);
				if(abc[hor][ver] == 0){
					abc[hor][ver] = (GetRandomValue(0, 1) ? 2 : 4);
					break;
				}
			}
		}
		
		BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < linelength; i++) {
			DrawLineV(line[i].star, line[i].end, line[i].color);
		}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (abc[i + 1][j + 1] == 0)
					continue;
				sprintf(textBuffer, "%d", abc[i + 1][j + 1]); //转换为char类型
				DrawText(textBuffer, j * 100 + 50, i * 100 + 50, 20, GREEN);
			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}


//1,1，2,1，3,1，4,1
//1,2，2,2，3,2，4,2
//1,3，2,3，3,3，4,3
//1,4，2,4，3,4，4,4

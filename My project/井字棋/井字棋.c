#include <raylib.h>
#include <stdio.h>

int main() {

	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "井字棋");

	int wi = screenWidth / 3;
	int he = screenHeight / 3;

	int wi2 = screenWidth / 3 * 2;
	int he2 = screenHeight / 3 * 2;

	int a[10] = {0};
	int x, y;
	int npc[8]={123,159,147,258,357,369,456,789};
	
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		
		if (IsMouseButtonPressed(0)) {
			x = GetMouseX();
			y = GetMouseY();
			if (x < wi && y < he)
				a[1] = 1;
			if (x < wi && (y > he && y < he2))
				a[2] = 1;
			if (x < wi && y > he2)
				a[3] = 1;
			if ((x > wi && x < wi2) && y < he)
				a[4] = 1;
			if ((x > wi && x < wi2) && (y > he && y < he2))
				a[5] = 1;
			if ((x > wi && x < wi2) && y > he2)
				a[6] = 1;
			if (x > wi2 && y < he)
				a[7] = 1;
			if (x > wi2 && (y > he && y < he2))
				a[8] = 1;
			if (x > wi2 && y > he2)
				a[9] = 1;
			
		//npc ai
			
			//排除错误方案
			for(int i=1;i<10;i++){
				if(a[i]==1)					//代表已经被选了
					for(int j=0;j<8;j++){	//8个选项中去除被选的选项
						if((npc[j]%10 == i) || (npc[j]/10%10 == i) || (npc[j]/100 == i))
							npc[j]=0;
					}
			}
			
			for(int j=0;j<8;j++){
				if(npc[j]==0)
					continue;
				printf("%d,",npc[j]);
			}
			printf("\n");
				
			
			//有方块，有方案
			for(int i=1;i<10;i++){
				if(a[i]==2)					//如果有npc的数字,就开始找有npc的选项
					for(int j=0;j<8;j++){
						if(npc[j]!=0)		//去除0的选项找到有i的选项
							if((npc[j]%10 == i) || (npc[j]/10%10 == i) || (npc[j]/100 == i)){
								if(npc[j]/100 != i)
									if(a[npc[j]/100] == 0){
										a[npc[j]/100] = 2;
										goto one;
									}
								if(npc[j]/10%10 != i)
									if(a[npc[j]/10%10] == 0){
										a[npc[j]/10%10] = 2;
										goto one;
									}								
								if(npc[j]%10 != i)
									if(a[npc[j]%10] == 0){
										a[npc[j]%10] = 2;
										goto one;
									}
							}
					}
			}
			
			//没方块，有方案
			for(int i=1;i<10;i++){
				if(a[i]==0)	//找到空方块
					for(int j=0;j<8;j++){
						if(npc[j] != 0){	//去除npc0的选项
							a[npc[j]/100]=2;
							goto one;
						}
					}
			}
			//没方块，没方案,堵对方
			for(int i=1;i<10;i++){
				if(a[i]==0){
					a[i]=2;
					break;
				}
					
			}
		}
		
		one:
		
		BeginDrawing();

		ClearBackground(RED);

		if (a[1] == 1)
			DrawRectangle(0, 0, wi, he, BLACK);
		else if (a[1] == 2)
			DrawRectangle(0, 0, wi, he, WHITE);

		if (a[2] == 1)
			DrawRectangle(0, he, wi, he, BLACK);
		else if (a[2] == 2)
			DrawRectangle(0, he, wi, he, WHITE);

		if (a[3] == 1)
			DrawRectangle(0, he2, wi, he, BLACK);
		else if (a[3] == 2)
			DrawRectangle(0, he2, wi, he, WHITE);

		//-------------------------------------------------
		if (a[4] == 1)
			DrawRectangle(wi, 0, wi, he, BLACK);
		else if (a[4] == 2)
			DrawRectangle(wi, 0, wi, he, WHITE);

		if (a[5] == 1)
			DrawRectangle(wi, he, wi, he, BLACK);
		else if (a[5] == 2)
			DrawRectangle(wi, he, wi, he, WHITE);

		if (a[6] == 1)
			DrawRectangle(wi, he2, wi, he, BLACK);
		else if (a[6] == 2)
			DrawRectangle(wi, he2, wi, he, WHITE);

		//-------------------------------------------------

		if (a[7] == 1)
			DrawRectangle(wi2, 0, wi, he, BLACK);
		else if (a[7] == 2)
			DrawRectangle(wi2, 0, wi, he, WHITE);

		if (a[8] == 1)
			DrawRectangle(wi2, he, wi, he, BLACK);
		else if (a[8] == 2)
			DrawRectangle(wi2, he, wi, he, WHITE);

		if (a[9] == 1)
			DrawRectangle(wi2, he2, wi, he, BLACK);
		else if (a[9] == 2)
			DrawRectangle(wi2, he2, wi, he, WHITE);

		EndDrawing();
	}

	CloseWindow();
}

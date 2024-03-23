#include <raylib.h>
#include <raymath.h>
#include <math.h>

//光线属性
typedef struct Light {
	Vector2 position;//光线坐标
	bool activity;	//允许前进
} Light;

//360条前进光线
Light Light_adv_pos[360] = {
};

//障碍物属性
typedef struct Envitem {
	int blocking;	//碰撞
	Rectangle rect;	//形状
	Color color;	//颜色
} Envitem;

Envitem envitems[] = {
	//{1,{ 0, 0, 850, 450 }, 0, BLACK },		//大地图背景,不可碰撞
	{1,{ 0, 400, 850, 50 }, BLUE },		//地面
	{1,{ 300, 200, 100, 50 },  GRAY },	//二层
	{1,{ 600, 200, 100, 50 },  GRAY },
	{1,{ 250, 300, 100, 10 }, GRAY },	//一层
	{1,{ 450, 300, 100, 10}, GRAY},
	{1,{ 650, 300, 100, 10 },  GRAY },
	
	{1,{0,0,850,5},RED},					//屏幕上部绘制红色边框矩形
	{1,{0,445,850,5},YELLOW},				//屏幕下部绘制黄色边框矩形
	{1,{0,5,5,440},BLUE}, 				//屏幕左部绘制蓝色边框矩形
	{1,{845,5,5,440},GREEN}				//屏幕右部绘制绿色边框矩形
	
};

//----------------------------------------------------------------------------------
// 函数：计算点围绕另一点旋转后的坐标
Vector2 rotate(Vector2 p, Vector2 center, double angle) {
	Vector2 result;
	double radian = angle * M_PI / 180.0; // 将角度转换为弧度
	double cosVal = cos(radian);
	double sinVal = sin(radian);
	
	// 应用旋转公式
	result.x = (p.x - center.x) * cosVal - (p.y - center.y) * sinVal + center.x;
	result.y = (p.x - center.x) * sinVal + (p.y - center.y) * cosVal + center.y;
	
	return result;
}


int main(void) {
	//初始化
	//----------------------------------------------------------------------------------
	const int screenWidth = 850;
	const int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "2d光线阴影");
	
	//障碍物数量
	int envitemsLength = sizeof(envitems) / sizeof(envitems[0]);
	
	SetTargetFPS(60);
	//----------------------------------------------------------------------------------
	//主游戏循环
	while (!WindowShouldClose()) {
		//更新数据
		//----------------------------------------------------------------------------------
		
		Vector2 mouse_pos = GetMousePosition();	//获取鼠标位置
		
		Vector2 init_point[360];					//创建50个光线初始点
		init_point[0] = (Vector2) {
			mouse_pos.x, mouse_pos.y - 1 		//第一个光线点在鼠标上方1个距离点
		};
		
		//求出剩下359个初始点的位置
		for (double i = 1,angle = 1; i < 360; i++) {
			init_point[(int)i] = rotate(init_point[0], mouse_pos, angle); //要旋转点，中心点，角度
			angle += 1;
		}
		
		//求出50个光线点的方向向量
		Vector2 light_dir[360];
		for (int i = 0; i < 360; i++) {
			light_dir[i] = (Vector2) {
				init_point[i].x - mouse_pos.x, init_point[i].y - mouse_pos.y//更新每个坐标方向向量
			};
			light_dir[i] = Vector2Normalize(light_dir[i]);				//进行标准化
		}
		
		for(int i = 0; i < 360; i++)
		{
			Light_adv_pos[i].position = init_point[i];	//重置每个光线前进点的初始位置
			Light_adv_pos[i].activity = true;			//重置每个光线前进点的前进状态
			
			for (int j = 1; j <= 850; j++)				//前进距离为100
			{
				//如果当前光线不允许前进,切换到下条光线
				if(Light_adv_pos[i].activity == false)
					break;
				else
				{
					for(int k = 0; k < envitemsLength; k++)
					{
						//如果碰到任意障碍物，停下本条光线的状态
						if(envitems[k].blocking && 
							CheckCollisionPointRec(Light_adv_pos[i].position, envitems[k].rect))
						{
							Light_adv_pos[i].activity = false;
							break;
						} 
						else
						{	//如果没有碰到障碍物,光线就每次前进一个距离
							Light_adv_pos[i].position = (Vector2)
							{
								init_point[i].x + light_dir[i].x * j,
								init_point[i].y + light_dir[i].y * j
							};
						}
					}
				}
			}
		}
		
		
		//开始绘制
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		
		for(int i=0;i<89;i++)
			DrawTriangle(Light_adv_pos[i].position,Light_adv_pos[i+1].position,(Vector2){850,0},BLACK);
		DrawTriangle((Vector2){850,0},Light_adv_pos[89].position,(Vector2){850,450},BLACK);
		
		for(int i=89;i<179;i++)
			DrawTriangle(Light_adv_pos[i].position,Light_adv_pos[i+1].position,(Vector2){850,450},BLACK);
		DrawTriangle(Light_adv_pos[179].position,(Vector2){0,450},(Vector2){850,450},BLACK);
		
		for(int i=179;i<269;i++)
			DrawTriangle(Light_adv_pos[i].position,Light_adv_pos[i+1].position,(Vector2){0,450},BLACK);
		DrawTriangle((Vector2){0,0},(Vector2){0,450},Light_adv_pos[269].position,BLACK);
		
		for(int i=269;i<359;i++)
			DrawTriangle((Vector2){0,0},Light_adv_pos[i].position,Light_adv_pos[i+1].position,BLACK);
		DrawTriangle((Vector2){0,0},Light_adv_pos[359].position,Light_adv_pos[0].position,BLACK);
		DrawTriangle((Vector2){0,0},Light_adv_pos[0].position,(Vector2){850,0},BLACK);
		
		
		for (int i = 0; i < envitemsLength; i++) {
			DrawRectangleRec(envitems[i].rect, envitems[i].color);
		}
		
//		for(int i=0;i<360;i++){
//			int nextIndex = (i + 1) % 360;
//			DrawTriangle(Light_adv_pos[i].position,mouse_pos,Light_adv_pos[nextIndex].position,RED);
//		}
		
//		for (int i = 0; i < 360; i++){
//			DrawLineEx(mouse_pos, Light_adv_pos[i].position, 1.0f, RED);
//			DrawCircleV(Light_adv_pos[i].position, 5, RED);
//		}	
		
		//----------------------------------------------------------------------------------
		//绘制结束
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}

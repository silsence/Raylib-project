#include <raylib.h>
#include <string.h>

typedef struct matrix {
	Vector2 position;
	Color color;
} matrix;

void Matrix_transformation(
    matrix *mat, int matLength);

int main() {
	const int screenWidth = 850;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "基于屏幕坐标系的2D矩阵变换");

	Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f}; //屏幕中心

	Camera2D camera = {0};
	camera.target = center;
	camera.offset = (Vector2) {
		screenWidth / 2.0f, screenHeight / 2.0f
	};
	camera.zoom = 1.0f;

	double a = -1.0f;
	matrix mat[] = {
		//中心
		{{0, 0}, RED},
		//左上
		{{- 10.0f, 10.0f * a}, GREEN},
		{{- 20.0f, 20.0f * a}, GREEN},
		{{- 30.0f, 30.0f * a}, GREEN},
		{{- 40.0f, 40.0f * a}, GREEN},
		{{- 50.0f, 50.0f * a}, GREEN},
		{{- 60.0f, 60.0f * a}, GREEN},
		{{- 60.0f, 45.0f * a}, GREEN},
		{{- 60.0f, 30.0f * a}, GREEN},
		{{- 60.0f, 15.0f * a}, GREEN},
		{{- 60.0f, 0}, GREEN},
		//左下
		{{- 60.0f, -15.0f * a}, GREEN},
		{{- 60.0f, -30.0f * a}, GREEN},
		{{- 60.0f, -45.0f * a}, GREEN},
		{{- 60.0f, -60.0f * a}, GREEN},

		//右上
		{{10.0f, 10.0f * a}, BLUE},
		{{20.0f, 20.0f * a}, BLUE},
		{{30.0f, 30.0f * a}, BLUE},
		{{40.0f, 40.0f * a}, BLUE},
		{{50.0f, 50.0f * a}, BLUE},
		{{60.0f, 60.0f * a}, BLUE},
		{{60.0f, 45.0f * a}, BLUE},
		{{60.0f, 30.0f * a}, BLUE},
		{{60.0f, 15.0f * a}, BLUE},
		{{60.0f, 0}, BLUE},
		//右下
		{{60.0f, -15.0f * a}, BLUE},
		{{60.0f, -30.0f * a}, BLUE},
		{{60.0f, -45.0f * a}, BLUE},
		{{60.0f, -60.0f * a}, BLUE}
	};

	int matLength = sizeof(mat) / sizeof(mat[0]);
	
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

		if (camera.zoom > 3.0f) {
			camera.zoom = 3.0f;
		} else if (camera.zoom < 0.25f) {
			camera.zoom = 0.25f;
		}
		if (IsKeyPressed(KEY_SPACE)) {

			Matrix_transformation(mat, matLength);//传递数组和长度
		}

		BeginDrawing();

		BeginMode2D(camera);

		ClearBackground(BLACK);

		for (int i = 0; i < matLength; i++)
			DrawCircle(mat[i].position.x + 425, (mat[i].position.y + 225), 5, mat[i].color);


		EndMode2D();

		EndDrawing();
	}
	CloseWindow();

	return 0;
}


void Matrix_transformation(matrix *mat, int matLength) {
	double x = 0, y = 0, z = 1;
	double tranf[3][3] = {
		{0.0f, 1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};

	for (int i = 0; i < matLength; i++) {
		matrix *m = mat + i;

		x = (tranf[0][0] * m->position.x) + (tranf[0][1] * m->position.y) + (tranf[0][2] * z);
		y = (tranf[1][0] * m->position.x) + (tranf[1][1] * m->position.y) + (tranf[1][2] * z);
		z = (tranf[2][0] * m->position.x) + (tranf[2][1] * m->position.y) + (tranf[2][2] * z);

		//矩阵变换后的坐标
		m->position.x = x;
		m->position.y = y;
	}
}

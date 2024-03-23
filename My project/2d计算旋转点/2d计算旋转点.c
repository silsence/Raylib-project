#include <stdio.h>
#include <math.h>

// 定义一个结构体表示点的坐标
typedef struct {
	double x;
	double y;
} Point;

// 函数：计算点围绕另一点旋转后的坐标
//旋转点，中心点,角度
Point rotate(Point pos, Point center, double angle) {
	Point result;
	double radian = angle * M_PI / 180.0; // 将角度转换为弧度
	double cosVal = cos(radian);
	double sinVal = sin(radian);

	// 应用旋转公式
	result.x = (pos.x - center.x) * cosVal - (pos.y - center.y) * sinVal + center.x;
	result.y = (pos.x - center.x) * sinVal + (pos.y - center.y) * cosVal + center.y;

	return result;
}

int main() {

	double x = 0, y = 1; //初始坐标
	Point center = {0, 0}; // 旋转中心的坐标
	double angle; //旋转的角度
	int count;
	printf("请输入旋转的角度: ");
	scanf("%lf",&angle);
	printf("请输入旋转的次数: ");
	scanf("%d",&count);
	double temp ;
	
	for (int i = 0; i < count; i++) {
		temp += angle ; 		// 逆时针,旋转角度
		Point p = {x, y}; 		// 要旋转的点的坐标
		printf("第%d次,(%.2lf, %.2lf)旋转\n", i + 1, p.x, p.y);
		Point rotatedPoint = rotate(p, center, temp);
		printf("%.1lf度:(%.2lf, %.2lf)\n", temp, rotatedPoint.x, rotatedPoint.y);
		printf("\n");

		x = rotatedPoint.x;
		y = rotatedPoint.y;
	}
	return 0;
}

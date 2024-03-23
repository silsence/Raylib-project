#include <stdio.h>

struct st {
	int i;   		// 通常 4 字节
	char c1; 		// 对齐前面的int 4 字节
	struct {		// 内嵌匿名结构体
		char c2;  	// 1 字节，对齐后面的double，加了7个字节
		double d; 	// 通常 8 字节
	};
	short s; 		// 对齐最大的 8 字节
};
//求内存时，总是对齐前面最大的
//4,4,16,8

int main() {
	printf("%zu",sizeof(struct st));
	return 0;
}

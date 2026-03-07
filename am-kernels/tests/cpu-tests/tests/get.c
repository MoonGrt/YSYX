#include "trap.h"

int main() {
	// 使用 scanf 测试输入
	char str[100];
	int a, b;
	char c;
	printf("You entered: %s\n", str);
	printf("Enter two integers and a character (e.g., 10 20 X): ");
	scanf("%d %d %c", &a, &b, &c);
	printf("Read values: a=%d, b=%d, c=%c\n", a, b, c);
	// 使用 sscanf 测试缓冲区解析
	char buf[] = "123 456 Z";
	int x, y;
	char ch;
	sscanf(buf, "%d %d %c", &x, &y, &ch);
	printf("sscanf result: x=%d, y=%d, ch=%c\n", x, y, ch);
	return 0;
}

#include "trap.h"

int main() {
	char c = io_read(AM_UART_RX).data;
	// 使用 scanf 测试输入
	int a, b;
	printf("Enter two integers and a character (e.g., 10 20 X): ");
	scanf("%d %d %c", &a, &b, &c);
	printf("Read values: a=%d, b=%d, c=%c\n", a, b, c);
	// 使用 sscanf 测试缓冲区解析
	char buf[] = "123 456 Z";
	int x, y;
	sscanf(buf, "%d %d %c", &x, &y, &c);
	printf("sscanf result: x=%d, y=%d, c=%c\n", x, y, c);
	return 0;
}

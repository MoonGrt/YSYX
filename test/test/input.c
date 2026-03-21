#include <stdio.h>

int main() {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch == '#') {   // 触发字符
            printf("检测到触发字符 #\n");
            // 在这里写触发逻辑
        } else {
            printf("收到字符: %c\n", ch);
        }
    }

    return 0;
}

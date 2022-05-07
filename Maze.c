#include <stdio.h>
#include <stdlib.h>

#define DEBUG

// 迷宫单元的类型
typedef enum {
	SPACE = 0, // 可走
	WALL = 1, // 墙壁
	VISITED = 2, // 在路径上
	UNREACHABLE = 3 // 不可走
} UnitType;

// 迷宫
UnitType maze[10][10];

// 行进方向
typedef enum {
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	NORTH = 4
} Direction;

// 位置坐标
typedef struct {
	int x;
	int y;
} Position;

#define MAX_STACK_SIZE 100 // 栈元素最大个数

// 栈元素类型
typedef struct {
	int step; // 步数
	Position pos; // 位置
	Direction direction; // 方向
} SElemType;

// 栈定义
typedef struct {
	SElemType* base; // 栈底指针
	SElemType* top; // 栈顶指针
	int stackSize; // 栈当前可使用的最大容量
} Stack;

// 栈的初始化
Stack initStack() {
	Stack stack;
	stack.base = (SElemType*)malloc(MAX_STACK_SIZE * sizeof(SElemType));
	if (!stack.base) {
		exit(-1);
	}
	stack.top = stack.base;
	stack.stackSize = MAX_STACK_SIZE;
	return stack;
}

// 入栈
Stack push(Stack stack, SElemType elem) {
	if (stack.top - stack.base >= stack.stackSize) {
		// 栈满
		exit(-2);
	}
	*stack.top = elem;
	stack.top++;
	return stack;
}

// 出栈
Stack pop(Stack stack, SElemType* elem) {
	if (stack.top == stack.base) {
		// 栈为空
		exit(-2);
	}
	stack.top--;
	*elem = *stack.top;
	return stack;
}

// 判断是否为空
int isEmpty(Stack stack) {
	return stack.top == stack.base;
}

// 求下一个位置
Position getNextPos(Position currentPos, Direction direction) {
	// 增量
	Position delta[] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
	Position newPos;
	newPos.x = currentPos.x + delta[direction - 1].x;
	newPos.y = currentPos.y + delta[direction - 1].y;
	return newPos;
}

// 判断位置是否可通过
int isReachable(Position position) {
	if (maze[position.y][position.x] == SPACE) {
		return 1;
	}
	return 0;
}

// 标记为已走过
void markVisited(Position position) {
	maze[position.y][position.x] = VISITED;
}

// 标记为不可通
void markUnreachable(Position position) {
	maze[position.y][position.x] = UNREACHABLE;
}

void main() {
	// 初始化迷宫
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			maze[i][j] = WALL;
		}
	}
	// 字符串表达的迷宫序列
	char sequence[] = "0010001000100010000011000111000000010000010001000111011010001000";
	int index = 0;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			maze[i][j] = sequence[index] == '0' ? 0 : 1;
			index++;
		}
	}
	Stack stack = initStack(); // 初始化栈
	Position currentPos = { 1,1 }; // 当前位置
	Position goalPos = { 8,8 }; // 终点位置
	int currentStep = 1; // 当前步数
	int flag = 0; // 指示是否成功找到路径
	do {
#ifdef DEBUG
		printf("[第%d步] 当前位置：%d, %d\n", currentStep, currentPos.x, currentPos.y);
		printf(isReachable(currentPos) ? "√ 当前位置可通过\n" : "× 当前位置不可通过\n");
#endif
		// 当前位置可通过
		if (isReachable(currentPos)) {
			markVisited(currentPos); // 把当前位置标记为已走过
			SElemType elem = { currentStep, currentPos, EAST };
			stack = push(stack, elem); // 加入路径
			// 到达终点
			if (currentPos.x == goalPos.x && currentPos.y == goalPos.y) {
				flag = 1;
				break;
			}
			currentPos = getNextPos(currentPos, EAST);
			currentStep++;
		}
		// 当前位置不可通过
		else {
			if (!isEmpty(stack)) {
				SElemType elem;
				stack = pop(stack, &elem); // 出栈
#ifdef DEBUG
				printf("栈顶元素：%d, %d, 步数为%d, 方向为%d\n", elem.pos.x, elem.pos.y, elem.step, elem.direction);
#endif
				while (elem.direction == NORTH && !isEmpty(stack)) {
					markUnreachable(elem.pos); // 把栈顶元素标记为不可通
					stack = pop(stack, &elem); // 再次出栈
					currentStep--;
#ifdef DEBUG
					printf("→ 出栈\n");
					printf("栈顶元素：%d, %d, 步数为%d, 方向为%d\n", elem.pos.x, elem.pos.y, elem.step, elem.direction);
#endif
				}
				if (elem.direction != NORTH) {
					// 换下一个方向探索
					elem.direction++;
#ifdef DEBUG
					printf("探索下一个方向\n");
#endif
					stack = push(stack, elem);
					currentPos = getNextPos(elem.pos, elem.direction);
				}
			}
		}
	} while (!isEmpty(stack));
	if (flag) {
		// 用一个数组来存放栈内元素
		Position steps[100];
		int index = 0;
		while (!isEmpty(stack)) {
			SElemType elem;
			stack = pop(stack, &elem);
			steps[index] = elem.pos;
			index++;
		}
		printf("走迷宫成功，路径为：\n");
		int step = 1;
		index--;
		while (index >= 0) {
			printf("第%02d步：%d, %d\n", step, steps[index].x, steps[index].y);
			step++;
			index--;
		}
	}
	else {
		printf("未找到有效路径\n");
	}
}
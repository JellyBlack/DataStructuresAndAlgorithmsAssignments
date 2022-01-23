#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACK_INCREMENT 10 // 存储空间分配增量

typedef int Elemtype;
typedef struct {
	Elemtype* base; // 栈底指针
	Elemtype* top; // 栈顶指针
	int stacksize; // 栈可用容量
}SqStack;

// 初始化
SqStack initStack() {
	SqStack stack;
	stack.base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (!stack.base) {
		printf("内存分配失败\n");
		exit(0);
	}
	stack.top = stack.base;
	stack.stacksize = STACK_INIT_SIZE;
	return stack;
}

// 入栈
SqStack push(SqStack stack, Elemtype element) {
	if (stack.top - stack.base >= stack.stacksize) {
		// 追加存储空间
		stack.base = (Elemtype*)realloc(stack.base, (stack.stacksize + STACK_INCREMENT) * sizeof(Elemtype));
		if (!stack.base) {
			printf("内存分配失败\n");
			exit(0);
		}
		stack.top = stack.base + stack.stacksize;
	}
	stack.top++;
	*stack.top = element;
	return stack;
}

// 出栈
SqStack pop(SqStack stack, Elemtype *element) {
	if (stack.top == stack.base) {
		printf("栈为空\n");
		exit(0);
	}
	stack.top--;
	*element = *stack.top;
	return stack;
}

// 取栈顶元素
Elemtype getTop(SqStack stack) {
	if (stack.top == stack.base) {
		printf("栈为空\n");
		exit(0);
	}
	return *stack.top;
}

// 测试代码
int main() {
	SqStack stack = initStack();
	printf("将1,2,3放入栈\n");
	stack = push(stack, 1);
	stack = push(stack, 2);
	stack = push(stack, 3);
	printf("栈顶元素为%d\n", getTop(stack));
	Elemtype element;
	stack = pop(stack, &element);
	printf("出栈元素%d\n", element);
	printf("栈顶元素为%d\n", getTop(stack));
	stack = pop(stack, &element);
	printf("出栈元素%d\n", element);
	printf("栈顶元素为%d\n", getTop(stack));
	printf("将4放入栈\n");
	stack = push(stack, 4);
	printf("栈顶元素为%d\n", getTop(stack));
	return 0;
}

#include <stdlib.h>
#include "BiTree.h"

// 初始化队列
SqQueue initQueue() {
	SqQueue queue;
	queue.base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
	if (!queue.base) {
		// 内存分配失败
		exit(1);
	}
	queue.front = 0;
	queue.rear = 0; // 队列为空
	return queue;
}

// 求队列长度
int queueLength(SqQueue queue) {
	return (queue.rear - queue.front + MAXSIZE) % MAXSIZE;
}

// 插入元素
SqQueue enQueue(SqQueue queue, QElemType element) {
	// 判断是否队满
	if ((queue.rear + 1) % MAXSIZE == queue.front) {
		exit(1);
	}
	queue.base[queue.rear] = element;
	queue.rear = (queue.rear + 1) % MAXSIZE;
	return queue;
}

// 删除元素，element为返回的元素
SqQueue deQueue(SqQueue queue, QElemType *element) {
	if (queue.front == queue.rear) {
		exit(1);
	}
	*element = queue.base[queue.front];
	queue.front = (queue.front + 1) % MAXSIZE;
	return queue;
}

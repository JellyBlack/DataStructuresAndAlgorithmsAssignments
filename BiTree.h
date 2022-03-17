#pragma once

#define MAXSIZE 100 // 队列的最大节点数

typedef char TElemType; // 二叉树节点数据类型

// 二叉树节点
typedef struct {
	TElemType data; // 节点数据
	struct BiTNode* lchild, * rchild; // 左右孩子指针
} BiTNode, * BiTree;

typedef BiTree QElemType; // 队列节点的数据类型

// 队列
typedef struct {
	QElemType* base; // 初始化的动态分配的存储空间
	int front; // 头指针，若队列不空，指向队列头元
	int rear; // 尾指针，若队列不空，指向对尾元素的  下一个位置
}SqQueue;

// 队列节点
typedef struct {
	QElemType data; // 节点数据
	struct QNode* next; // 下一个节点的指针
}QNode, * QueuePtr;

// 初始化队列
SqQueue initQueue();

// 求队列长度
int queueLength(SqQueue queue);

// 插入元素
SqQueue enQueue(SqQueue queue, QElemType element);

// 删除元素，element为返回的元素
SqQueue deQueue(SqQueue queue, QElemType* element);

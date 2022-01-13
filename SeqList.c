#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
#define LIST_INCREMENT 10 // 线性表存储空间的分配增量

typedef int ElemType;
typedef struct {
	ElemType* elem; // 存储空间基址
	int length; // 当前长度
	int listsize; // 当前分配的存储容量
}SeqList;

// 初始化
SeqList SeqListInit() {
	SeqList list;
	list.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!list.elem) {
		printf("初始化失败\n");
		exit(0);
	}
	list.length = 0;
	list.listsize = LIST_INIT_SIZE;
	return list;
}

// 创建
SeqList SeqListCreate(SeqList list) {
	printf("输入元素个数：");
	int num;
	scanf("%d", &num);
	if (num < 0) {
		printf("输入不合法\n");
		exit(0);
	}
	if (num > list.listsize) {
		// 增加分配
		int newSize = (int)((double)num / LIST_INCREMENT) + 0.5;
		ElemType* newBase = (ElemType*)realloc(list.elem, (list.listsize + newSize) * sizeof(ElemType));
		if (!newBase) {
			printf("存储分配失败\n");
			exit(0);
		}
		list.elem = newBase;
		list.listsize += newSize;
	}
	printf("输入各元素：\n");
	for (int i = 0; i < num; i++) {
		scanf("%d", list.elem + i);
	}
	list.length += num;
	return list;
}

// 遍历
void SeqListTraverse(SeqList list) {
	if (list.length == 0) {
		printf("空表\n");
		return;
	}
	for (int i = 0; i < list.length; i++) {
		printf("%d\t", list.elem[i]);
	}
	printf("\n");
}

// 按值查找，从1开始，若没找到则返回0
int SeqListLocate(SeqList list, ElemType x) {
	int i = 1;
	while (i <= list.length && list.elem[i - 1] != x) {
		i++;
	}
	if (i <= list.length) {
		return i;
	}
	return 0;
}

// 插入
SeqList SeqListInsert(SeqList list, int i, ElemType x) {
	if (i < 1 || i > list.length + 1) {
		printf("插入位置错\n");
		exit(0);
	}
	if (list.length >= list.listsize) {
		// 增加分配
		ElemType* newBase = (ElemType*)realloc(list.elem, (list.listsize + LIST_INCREMENT) * sizeof(ElemType));
		if (!newBase) {
			printf("存储分配失败\n");
			exit(0);
		}
		list.elem = newBase;
		list.listsize += LIST_INCREMENT;
	}
	for (int j = list.length - 1; j >= i - 1; j--) {
		list.elem[j + 1] = list.elem[j];
	}
	list.elem[i - 1] = x;
	list.length++;
	return list;
}

// 删除
SeqList SeqListDelete(SeqList list, int i) {
	if (i < 1 || i > list.length) {
		printf("位置非法\n");
		exit(0);
	}
	for (int j = i; j <= list.length - 1; j++) {
		list.elem[j - 1] = list.elem[j];
	}
	list.length--;
	return list;
}

// 合并
SeqList SeqListMerge(SeqList list1, SeqList list2) {
	SeqList list = SeqListInit(); // 合并后的顺序表
	int size = list1.length + list2.length;
	if (size > list.listsize) {
		// 增加分配
		int newSize = (int)((double)size / LIST_INCREMENT) + 0.5;
		ElemType* newBase = (ElemType*)realloc(list.elem, (list.listsize + newSize) * sizeof(ElemType));
		if (!newBase) {
			printf("存储分配失败\n");
			exit(0);
		}
		list.elem = newBase;
		list.listsize += newSize;
	}
	int i = 0, j = 0, k = 1;
	while (i < list1.length && j < list2.length) {
		ElemType ai = list1.elem[i];
		ElemType bj = list2.elem[j];
		if (ai < bj) {
			list = SeqListInsert(list, k++, ai);
			i++;
		}
		else {
			list = SeqListInsert(list, k++, bj);
			j++;
		}
	}
	while (i < list1.length) {
		ElemType ai = list1.elem[i];
		list = SeqListInsert(list, k++, ai);
		i++;
	}
	while (j < list2.length) {
		ElemType bj = list2.elem[j];
		list = SeqListInsert(list, k++, bj);
		j++;
	}
	return list;
}

// 测试代码
int main() {
	// 初始化顺序表
	SeqList list = SeqListInit();
	// 从键盘输入
	list = SeqListCreate(list);
	// 遍历顺序表
	SeqListTraverse(list);

	// 在第3个位置插入5
	printf("在第3个位置插入5\n");
	list = SeqListInsert(list, 3, 5);
	// 遍历顺序表
	SeqListTraverse(list);

	// 删除第2个数据
	printf("删除第2个数据\n");
	list = SeqListDelete(list, 2);
	// 遍历顺序表
	SeqListTraverse(list);

	// 初始化另一个顺序表
	SeqList list2 = SeqListInit();
	// 从键盘输入
	list2 = SeqListCreate(list2);
	// 遍历顺序表
	SeqListTraverse(list2);

	// 合并顺序表
	SeqList list3 = SeqListMerge(list, list2);
	// 遍历顺序表
	printf("合并后的顺序表为\n");
	SeqListTraverse(list3);
	return 0;
}
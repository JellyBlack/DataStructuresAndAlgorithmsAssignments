#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 // 顺序表的最大容量
typedef int ElemType;
typedef struct {
	ElemType data[MAXSIZE]; // 存放顺序表的数组
	int last; // 顺序表的长度
}SeqList;

// 初始化
SeqList SeqListInit() {
	SeqList list;
	list.last = 0;
	return list;
}

// 创建
SeqList SeqListCreate(SeqList list) {
	printf("输入元素个数：");
	int num;
	scanf("%d", &num);
	if (num < 0 || num > MAXSIZE) {
		printf("输入不合法\n");
		exit(0);
	}
	printf("输入各元素：\n");
	for (int i = 0; i < num; i++) {
		scanf("%d", list.data + i);
	}
	list.last += num;
	return list;
}

// 遍历
void SeqListTraverse(SeqList list) {
	if (list.last == 0) {
		printf("空表\n");
		return;
	}
	for (int i = 0; i < list.last; i++) {
		printf("%d\t", list.data[i]);
	}
	printf("\n");
}

// 按值查找，从1开始，若没找到则返回0
int SeqListLocate(SeqList list, ElemType x) {
	int i = 1;
	while (i <= list.last && list.data[i - 1] != x) {
		i++;
	}
	if (i <= list.last) {
		return i;
	}
	return 0;
}

// 插入
SeqList SeqListInsert(SeqList list, int i, ElemType x) {
	if (list.last == MAXSIZE) {
		printf("表满\n");
		exit(0);
	}
	if (i < 1 || i > list.last + 1) {
		printf("插入位置错\n");
		exit(0);
	}
	for (int j = list.last - 1; j >= i - 1; j--) {
		list.data[j + 1] = list.data[j];
	}
	list.data[i - 1] = x;
	list.last++;
	return list;
}

// 删除
SeqList SeqListDelete(SeqList list, int i) {
	if (i < 1 || i > list.last) {
		printf("位置非法\n");
		exit(0);
	}
	for (int j = i; j <= list.last - 1; j++) {
		list.data[j - 1] = list.data[j];
	}
	list.last--;
	return list;
}

// 合并
SeqList SeqListMerge(SeqList list1, SeqList list2) {
	if (list1.last + list2.last > MAXSIZE) {
		printf("超出最大容量\n");
		exit(0);
	}
	SeqList list = SeqListInit(); // 合并后的顺序表
	int i = 0, j = 0, k = 1;
	while (i < list1.last && j < list2.last) {
		ElemType ai = list1.data[i];
		ElemType bj = list2.data[j];
		if (ai < bj) {
			list = SeqListInsert(list, k++, ai);
			i++;
		}
		else {
			list = SeqListInsert(list, k++, bj);
			j++;
		}
	}
	while (i < list1.last) {
		ElemType ai = list1.data[i];
		list = SeqListInsert(list, k++, ai);
		i++;
	}
	while (j < list2.last) {
		ElemType bj = list2.data[j];
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
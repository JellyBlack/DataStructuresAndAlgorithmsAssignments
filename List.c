#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 链表节点定义
typedef struct TagList{
	int data;
	struct TagList* next;
}ListNode, *List;

// 判断用户输入的字符串是否为合法的数字
int isValid(const char string[]) {
	int length = (int)strlen(string);
	// 长度为0，非法
	if (length == 0) {
		return 0;
	}
	// 第一个字符为负号
	if (string[0] == '-') {
		for (int i = 1; i < length; i++) {
			if (string[i] < '0' || string[i] > '9') {
				return 0;
			}
			if (length > 11 || (length == 11 && string[1] >= '2')) {
				return 0;
			}
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			if (string[i] < '0' || string[i] > '9') {
				return 0;
			}
			if (length > 10 || (length == 10 && string[0] >= '2')) {
				return 0;
			}
		}
	}
	return 1;
}

// 初始化链表
List initList() {
	List list = (List)malloc(sizeof(List));
	if (!list) {
		exit(-1);
	}
	list->data = 0;
	list->next = NULL;
	return list;
}

// 头插法添加元素
List headInsert(List list, int data) {
	// 链表为空
	if (list->next == NULL) {
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (!node) {
			exit(-1);
		}
		node->data = data;
		node->next = NULL;
		list->next = node;
	}
	// 链表不为空
	else {
		ListNode* firstNode = list->next;
		ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
		if (!newNode) {
			exit(-1);
		}
		list->next = newNode;
		newNode->data = data;
		newNode->next = firstNode;
	}
	return list;
}

// 尾插法插入元素
List TailInsert(List list, int data) {
	ListNode* node = list;
	while (node->next != NULL) {
		node = node->next;
	}
	// node为最后一个节点
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if (!newNode) {
		exit(-1);
	}
	newNode->data = data;
	node->next = newNode;
	newNode->next = NULL;
	return list;
}

// 按值查找
int listLocate(List list, int data, int* index) {
	ListNode* node = list;
	int i = 0;
	while (node->next != NULL) {
		node = node->next;
		i++;
		if (node->data == data) {
			*index = i;
			return 1;
		}
	}
	return 0;
}

// 遍历链表
void listTraverse(List list, void (*callback)(int)) {
	ListNode* node = list;
	if (node->next == NULL) {
		printf("链表为空\n");
		return;
	}
	while (node->next != NULL) {
		node = node->next;
		callback(node->data);
	}
}

// 插入元素
List listInsert(List list, int data, int index, int* status) {
	if (index <= 0) {
		*status = 0;
	}
	else {
		ListNode* node = list;
		ListNode* lastNode = node;
		int i = 0;
		while (node->next != NULL) {
			lastNode = node; // 保存上一个节点
			node = node->next;
			i++;
			if (i == index) {
				// 插入
				ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
				if (!newNode) {
					exit(-1);
				}
				newNode->data = data;
				lastNode->next = newNode;
				newNode->next = node;
				*status = 1;
				return list;
			}
		}
	}
	return list;
}

// 删除元素
List listDelete(List list, int data, int* status) {
	ListNode* node = list;
	ListNode* lastNode = node;
	while (node->next != NULL) {
		lastNode = node; // 保存上一个节点
		node = node->next;
		if (node->data == data) {
			// 删除
			if (node->next == NULL) {
				free(node);
				lastNode->next = NULL;
			}
			else {
				ListNode* nextNode = node->next;
				lastNode->next = nextNode;
				free(node);
				*status = 1;
			}
			return list;
		}
	}
	*status = 0;
	return list;
}

// 遍历函数
void visit(int data) {
	printf("%d ", data);
}

void main() {
	// 初始化链表
	List list = initList();
	while (1) {
		printf("请输入操作\n[1]头插法插入元素\n[2]尾插法插入元素\n[3]按值查找\n[4]遍历链表\n[5]插入元素\n[6]删除元素\n[7]退出\n");
		char string[100];
		gets_s(string, 100);
		int operation = 0;
		if (isValid(string)) {
			operation = atoi(string);
		}
		else {
			printf("输入错误！\n");
		}
		switch (operation) {
		case 1:
			printf("请输入元素，以回车分隔，输入任意非数字结束\n");
			int count1 = 0;
			while (1) {
				char string[100];
				gets_s(string, 100);
				if (isValid(string)) {
					list = headInsert(list, atoi(string));
					count1++;
				}
				else {
					printf("插入了 %d 个元素\n", count1);
					break;
				}
			}
			break;
		case 2:
			printf("请输入元素，以回车分隔，输入任意非数字结束\n");
			int count2 = 0;
			while (1) {
				char string[100];
				gets_s(string, 100);
				if (isValid(string)) {
					list = TailInsert(list, atoi(string));
					count2++;
				}
				else {
					printf("插入了 %d 个元素\n", count2);
					break;
				}
			}
			break;
		case 3:
			while (1) {
				printf("请输入待查找的值：");
				char string[100];
				gets_s(string, 100);
				if (isValid(string)) {
					int index;
					int status = listLocate(list, atoi(string), &index);
					if (status) {
						printf("元素位于第 %d 个位置\n", index);
					}
					else {
						printf("未找到该元素\n");
					}
				}
				else {
					printf("输入错误！\n");
				}
				printf("继续查找请输入y：");
				char c;
				(void)scanf("%c", &c);
				rewind(stdin);
				if (c != 'y' && c != 'Y') {
					break;
				}
			}
			break;
		case 4:
			listTraverse(list, visit);
			printf("\n");
			break;
		case 5:
			while (1) {
				printf("请输入插入的元素：");
				char data[100];
				gets_s(data, 100);
				if (isValid(data)) {
					printf("请输入位置：");
					char index[100];
					gets_s(index, 100);
					if (isValid(index)) {
						int status;
						list = listInsert(list, atoi(data), atoi(index), &status);
						if (status) {
							printf("插入成功\n");
						}
						else {
							printf("未在链表中找到位置为 %d 的元素！\n", atoi(index));
						}
					}
					else {
						printf("输入错误！\n");
					}
				}
				else {
					printf("输入错误！\n");
				}
				printf("继续插入请输入y：");
				char c;
				(void)scanf("%c", &c);
				rewind(stdin);
				if (c != 'y' && c != 'Y') {
					break;
				}
			}
			break;
		case 6:
			while (1) {
				printf("请输入删除的元素：");
				char data[100];
				gets_s(data, 100);
				if (isValid(data)) {
					int status;
					list = listDelete(list, atoi(data), &status);
					if (status) {
						printf("删除成功\n");
					}
					else {
						printf("未在链表中找到指定元素！\n");
					}
				}
				else {
					printf("输入错误！\n");
				}
				printf("继续删除请输入y：");
				char c;
				(void)scanf("%c", &c);
				rewind(stdin);
				if (c != 'y' && c != 'Y') {
					break;
				}
			}
			break;
		case 7:
			exit(0);
			break;
		default:
			printf("操作不存在！\n");
			break;
		}
	}
}
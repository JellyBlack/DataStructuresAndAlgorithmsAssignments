#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 赫夫曼树类型定义
typedef struct {
	int weight; // 权值
	int parent;
	int lchild, rchild;
} HuffmanTree;

// 赫夫曼编码的存储结构
typedef struct {
	char ch;
	char bits[MAX_SIZE];
} CodeNode;

// 统计每个字符出现的频率
int getFrequency(char pattern[], char frequency[2][MAX_SIZE]) {
	int num = 0;
	// 初始化pattern
	for (int i = 0; i < MAX_SIZE; i++) {
		frequency[0][i] = '\0'; // 字符
		frequency[1][i] = 0; // 频率
	}
	int index = 0; // 当前读取的位置
	while (pattern[index] != '\0') {
		//判断字符是否在频率表中出现过
		int flag = 0;
		int i = 0; // 出现的位置
		for (; i < MAX_SIZE; i++) {
			if (frequency[0][i] == '\0') {
				break;
			}
			if (pattern[index] == frequency[0][i]) {
				flag = 1;
				break;
			}
		}
		// 出现过，则频率+1
		if (flag) {
			frequency[1][i]++;
		}
		// 没出现，则新增一个字符
		else {
			num++;
			frequency[0][i] = pattern[index];
			frequency[1][i]++;
		}
		index++;
	}
	return num;
}

// 选出parent值为0且权值最小的两个节点
void selectMinimum(HuffmanTree tree[], int num, int* p1, int* p2) {
	int min = MAX_SIZE;
	// 寻找第一个
	for (int i = 1; i <= num; i++) {
		if (tree[i].weight < min && tree[i].parent == 0) {
			*p1 = i;
			min = tree[i].weight;
		}
	}
	// 寻找第二个
	min = MAX_SIZE;
	for (int i = 1; i <= num; i++) {
		if (tree[i].weight < min && tree[i].parent == 0 && i != *p1) {
			*p2 = i;
			min = tree[i].weight;
		}
	}
}

// 构造赫夫曼树
void createHuffman(char frequency[2][MAX_SIZE], int num, HuffmanTree tree[]) {
	int total = 2 * num; // 节点总数
	// 初始化数组
	for (int i = 1; i < total; i++) {
		tree[i].parent = 0;
		tree[i].weight = 0;
		tree[i].lchild = 0;
		tree[i].rchild = 0;
	}
	// 读入叶子节点权值
	for (int i = 1; i <= num; i++) {
		tree[i].weight = frequency[1][i - 1];
	}
	// 合并，产生n-1个新节点
	for (int i = num + 1; i < total; i++) {
		int p1, p2;
		selectMinimum(tree, i-1, &p1, &p2);
		tree[p1].parent = i;
		tree[p2].parent = i;
		// p1值小在左边
		tree[i].lchild = p1;
		tree[i].rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
	// 打印赫夫曼树
	printf("赫夫曼树：\n");
	for (int i = 1; i < total; i++) {
		printf("%d\t%d\t%d\t%d\n", tree[i].weight, tree[i].parent, tree[i].lchild, tree[i].rchild);
	}
}

// 求赫夫曼编码
void encode(HuffmanTree tree[], int num, char frequency[2][MAX_SIZE]) {
	CodeNode codeNodes[MAX_SIZE];
	for (int i = 0; i < num; i++) {
		codeNodes[i] = (CodeNode){ '\0',NULL };
	}
	int nodes = 0;
	for (int i = 0; i < num; i++) {
		if (frequency[0][i] == '\0') {
			break;
		}
		nodes++;
		char temp[MAX_SIZE]; // 暂存每个字符的编码
		codeNodes[i].ch = frequency[0][i];
		int index = 0; // 当前编码的位置
		int currentChild = i + 1;
		int currentParent = tree[currentChild].parent;
		while (currentParent) {
			// 左孩子编码为0
			if (tree[currentParent].lchild == currentChild) {
				temp[index] = '0';
			}
			// 右孩子编码为1
			else {
				temp[index] = '1';
			}
			index++;
			// 继续上溯
			currentChild = currentParent;
			currentParent = tree[currentChild].parent;
		}
		// 转存编码
		int cursor = 0;
		for (int j = index - 1; j >= 0; j--) {
			codeNodes[i].bits[cursor] = temp[j];
			cursor++;
		}
		codeNodes[i].bits[cursor] = '\0';
	}
	// 打印赫夫曼编码
	printf("赫夫曼编码：\n");
	for (int i = 0; i < nodes; i++) {
		int cursor = 0;
		printf("%c: ", codeNodes[i].ch);
		while (codeNodes[i].bits[cursor] != '\0') {
			printf("%c", codeNodes[i].bits[cursor]);
			cursor++;
		}
		printf("\n");
	}
}

void main() {
	HuffmanTree tree[MAX_SIZE];
	int num = 0; // 输入的字符个数
	char pattern[MAX_SIZE];
	gets(pattern);
	// 统计字符个数
	int index = 0;
	while (pattern && pattern[index] != '\0') {
		index++;
		num++;
	}
	if (num < 1) {
		printf("请输入至少1个字符\n");
		return;
	}
	if (num > MAX_SIZE - 1) {
		printf("输入字符超过最大值");
		return;
	}
	// 节点个数
	int nodes;
	char frequency[2][MAX_SIZE];
	nodes = getFrequency(pattern, frequency);
	createHuffman(frequency, nodes, tree);
	if (nodes == 1) {
		printf("只有1个节点，无法完成编码");
		return;
	}
	encode(tree, num, frequency);
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// �շ��������Ͷ���
typedef struct {
	int weight; // Ȩֵ
	int parent;
	int lchild, rchild;
} HuffmanTree;

// �շ�������Ĵ洢�ṹ
typedef struct {
	char ch;
	char bits[MAX_SIZE];
} CodeNode;

// ͳ��ÿ���ַ����ֵ�Ƶ��
int getFrequency(char pattern[], char frequency[2][MAX_SIZE]) {
	int num = 0;
	// ��ʼ��pattern
	for (int i = 0; i < MAX_SIZE; i++) {
		frequency[0][i] = '\0'; // �ַ�
		frequency[1][i] = 0; // Ƶ��
	}
	int index = 0; // ��ǰ��ȡ��λ��
	while (pattern[index] != '\0') {
		//�ж��ַ��Ƿ���Ƶ�ʱ��г��ֹ�
		int flag = 0;
		int i = 0; // ���ֵ�λ��
		for (; i < MAX_SIZE; i++) {
			if (frequency[0][i] == '\0') {
				break;
			}
			if (pattern[index] == frequency[0][i]) {
				flag = 1;
				break;
			}
		}
		// ���ֹ�����Ƶ��+1
		if (flag) {
			frequency[1][i]++;
		}
		// û���֣�������һ���ַ�
		else {
			num++;
			frequency[0][i] = pattern[index];
			frequency[1][i]++;
		}
		index++;
	}
	return num;
}

// ѡ��parentֵΪ0��Ȩֵ��С�������ڵ�
void selectMinimum(HuffmanTree tree[], int num, int* p1, int* p2) {
	int min = MAX_SIZE;
	// Ѱ�ҵ�һ��
	for (int i = 1; i <= num; i++) {
		if (tree[i].weight < min && tree[i].parent == 0) {
			*p1 = i;
			min = tree[i].weight;
		}
	}
	// Ѱ�ҵڶ���
	min = MAX_SIZE;
	for (int i = 1; i <= num; i++) {
		if (tree[i].weight < min && tree[i].parent == 0 && i != *p1) {
			*p2 = i;
			min = tree[i].weight;
		}
	}
}

// ����շ�����
void createHuffman(char frequency[2][MAX_SIZE], int num, HuffmanTree tree[]) {
	int total = 2 * num; // �ڵ�����
	// ��ʼ������
	for (int i = 1; i < total; i++) {
		tree[i].parent = 0;
		tree[i].weight = 0;
		tree[i].lchild = 0;
		tree[i].rchild = 0;
	}
	// ����Ҷ�ӽڵ�Ȩֵ
	for (int i = 1; i <= num; i++) {
		tree[i].weight = frequency[1][i - 1];
	}
	// �ϲ�������n-1���½ڵ�
	for (int i = num + 1; i < total; i++) {
		int p1, p2;
		selectMinimum(tree, i-1, &p1, &p2);
		tree[p1].parent = i;
		tree[p2].parent = i;
		// p1ֵС�����
		tree[i].lchild = p1;
		tree[i].rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
	// ��ӡ�շ�����
	printf("�շ�������\n");
	for (int i = 1; i < total; i++) {
		printf("%d\t%d\t%d\t%d\n", tree[i].weight, tree[i].parent, tree[i].lchild, tree[i].rchild);
	}
}

// ��շ�������
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
		char temp[MAX_SIZE]; // �ݴ�ÿ���ַ��ı���
		codeNodes[i].ch = frequency[0][i];
		int index = 0; // ��ǰ�����λ��
		int currentChild = i + 1;
		int currentParent = tree[currentChild].parent;
		while (currentParent) {
			// ���ӱ���Ϊ0
			if (tree[currentParent].lchild == currentChild) {
				temp[index] = '0';
			}
			// �Һ��ӱ���Ϊ1
			else {
				temp[index] = '1';
			}
			index++;
			// ��������
			currentChild = currentParent;
			currentParent = tree[currentChild].parent;
		}
		// ת�����
		int cursor = 0;
		for (int j = index - 1; j >= 0; j--) {
			codeNodes[i].bits[cursor] = temp[j];
			cursor++;
		}
		codeNodes[i].bits[cursor] = '\0';
	}
	// ��ӡ�շ�������
	printf("�շ������룺\n");
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
	int num = 0; // ������ַ�����
	char pattern[MAX_SIZE];
	gets(pattern);
	// ͳ���ַ�����
	int index = 0;
	while (pattern && pattern[index] != '\0') {
		index++;
		num++;
	}
	if (num < 1) {
		printf("����������1���ַ�\n");
		return;
	}
	if (num > MAX_SIZE - 1) {
		printf("�����ַ��������ֵ");
		return;
	}
	// �ڵ����
	int nodes;
	char frequency[2][MAX_SIZE];
	nodes = getFrequency(pattern, frequency);
	createHuffman(frequency, nodes, tree);
	if (nodes == 1) {
		printf("ֻ��1���ڵ㣬�޷���ɱ���");
		return;
	}
	encode(tree, num, frequency);
}
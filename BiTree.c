#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"

// 先序遍历二叉树
void preOrderTraverse(BiTree tree, void (*callback)(TElemType)/*回调函数*/) {
	// 判断树是否为空
	if (tree) {
		callback(tree->data); // 访问节点
		preOrderTraverse(tree->lchild, callback); // 递归遍历左子树
		preOrderTraverse(tree->rchild, callback); // 递归遍历右子树
	}
}

// 中序遍历二叉树
void inOrderTraverse(BiTree tree, void (*callback)(TElemType)) {
	if (tree) {
		preOrderTraverse(tree->lchild, callback); // 递归遍历左子树
		callback(tree->data); // 访问节点
		preOrderTraverse(tree->rchild, callback); // 递归遍历右子树
	}
}

// 后序遍历二叉树
void postOrderTraverse(BiTree tree, void (*callback)(TElemType)) {
	if (tree) {
		preOrderTraverse(tree->lchild, callback); // 递归遍历左子树
		preOrderTraverse(tree->rchild, callback); // 递归遍历右子树
		callback(tree->data); // 访问节点
	}
}

// 层次遍历二叉树
void hierarchicalTraversal(BiTree tree, void (*callback)(TElemType)) {
	// 建立队列，用于存储临时节点
	SqQueue queue = initQueue();
	if (!tree) {
		// 树为空
		return;
	}
	// 将根节点添加至队列
	BiTNode treeNode = *tree;
	queue = enQueue(queue, &treeNode);
	while (queueLength(queue) != 0) {
		// 从队列中取出二叉树节点
		BiTNode *node;
		queue = deQueue(queue, &node);
		// 访问节点
		callback(node->data);
		// 将左右孩子添加至队列
		if (node->lchild) {
			queue = enQueue(queue, node->lchild);
		}
		if (node->rchild) {
			queue = enQueue(queue, node->rchild);
		}
	}
}

// 建立二叉树
BiTree createBiTree() {
	BiTree tree;
	char c;
	// 输入遍历序列，#表示空节点
	scanf_s("%c", &c);
	if (c == '\n') {
		return createBiTree();
	}
	if (c == '#') {
		tree = NULL;
	}
	else {
		tree = (BiTNode*)malloc(sizeof(BiTNode));
		if (tree == NULL) {
			exit(1);
		}
		tree->data = c; // 生成根节点
		tree->lchild = createBiTree(); // 生成左子树
		tree->rchild = createBiTree(); // 生成右子树
	}
	return tree;
}

// 访问函数
void visit(char c) {
	printf("%c ", c);
}

// 测试代码
void main() {
	printf("创建二叉树：");
	BiTree tree = createBiTree();
	printf("先序遍历二叉树：");
	preOrderTraverse(tree, visit);

	printf("\n\n创建二叉树：");
	tree = createBiTree();
	printf("中序遍历二叉树：");
	inOrderTraverse(tree, visit);

	printf("\n\n创建二叉树：");
	tree = createBiTree();
	printf("后序遍历二叉树：");
	postOrderTraverse(tree, visit);

	printf("\n\n创建二叉树：");
	tree = createBiTree();
	printf("层次遍历二叉树：");
	hierarchicalTraversal(tree, visit);

	free(tree);
	tree = NULL;
}
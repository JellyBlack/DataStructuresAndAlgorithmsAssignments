#include <stdio.h>

typedef int TElemType; // 二叉树节点数据类型

// 二叉树节点
typedef struct BiTNode {
	TElemType data; // 节点数据
	struct BiTNode* lchild, * rchild; // 左右孩子指针
} BiTNode, *BiTree;

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
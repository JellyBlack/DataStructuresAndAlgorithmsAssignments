#include <stdio.h>
#include <stdlib.h>

// 邻接矩阵中顶点的最大个数
#define MAXNODE 8

// 队列的最大节点数
#define MAXSIZE 20

// 邻接表存储的最大顶点数
#define MAX_VERTEX_NUM 20

// 顶点的数据类型
typedef char VertexType;
// 边的类型
typedef int EdgeType;

// 队列节点的数据类型
typedef int QElemType;

// 图的类型
typedef enum {
	directedGraph, // 有向图
	undirectedGraph // 无向图
} GraphType;

// 队列
typedef struct {
	QElemType* base; // 初始化的动态分配的存储空间
	int front; // 头指针，若队列不空，指向队列头元
	int rear; // 尾指针，若队列不空，指向对尾元素的  下一个位置
} SqQueue;

// 队列节点
typedef struct {
	QElemType data; // 节点数据
	struct QNode* next; // 下一个节点的指针
} QNode, * QueuePtr;

// 以邻接矩阵存储的图
typedef struct {
	VertexType vertexs[MAXNODE]; // 顶点
	EdgeType arcs[MAXNODE][MAXNODE]; // 邻接矩阵
	int vexnum; // 顶点数
	int arcnum; // 边数
} MGraph;

// 邻接表每个顶点对应的链表节点
typedef struct ArcNode {
	int adjvex; // 该弧指向的顶点的位置
	struct ArcNode* next; // 指向下一条弧的指针
	EdgeType info; // 弧存储的信息
} ArcNode;

// 头节点信息
typedef struct {
	VertexType vertex; // 顶点
	ArcNode* firstArc; // 指向第一条依附该顶点的弧的指针
} VNode;

// 邻接表存储的图
typedef struct {
	VNode vertices[MAX_VERTEX_NUM]; // 头节点的数组
	int vexnum; // 顶点数
	int arcnum; // 边数
} ALGraph;

// 初始化邻接矩阵存储的图
MGraph initMGraph() {
	MGraph* mgraph = (MGraph*)malloc(sizeof(MGraph));
	if (!mgraph) {
		exit(-1);
	}
	mgraph->vexnum = 0;
	mgraph->arcnum = 0;
	return *mgraph;
}

// 初始化邻接表存储的图
ALGraph initALGraph() {
	ALGraph* alGraph = (ALGraph*)malloc(sizeof(MGraph));
	if (!alGraph) {
		exit(-1);
	}
	alGraph->vexnum = 0;
	alGraph->arcnum = 0;
	return *alGraph;
}

// 创建邻接矩阵存储的图
MGraph createMGraph(MGraph mgraph, GraphType type) {
	int num; // 顶点数
	printf("输入图的顶点数：");
	(void)scanf("%d", &num);
	if (num < 0) {
		printf("输入错误！\n");
		return mgraph;
	}
	if (num > MAXNODE) {
		printf("节点数超出最大值！\n");
		return mgraph;
	}
	mgraph.vexnum = num;

	// 顶点值
	printf("依次输入%d个顶点的字符：\n", num);
	rewind(stdin);
	for (int i = 0; i < num; i++) {
		(void)scanf("%c", mgraph.vertexs + i);
	}

	// 边
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			mgraph.arcs[i][j] = 0;
		}
	}
	printf("输入图的边，以半角逗号分隔，任意边为0结束\n");
	rewind(stdin);
	while (1) {
		int i, j;
		(void)scanf("%d,%d", &i, &j);
		if (i == 0 || j == 0) {
			break;
		}
		if (i < 0 || j < 0 || i > num || j > num) {
			printf("输入非法！\n");
			continue;
		}
		// 有向图
		if (type == directedGraph) {
			mgraph.arcs[i - 1][j - 1] = 1;
			mgraph.arcnum++;
		}
		// 无向图
		else {
			mgraph.arcs[i - 1][j - 1] = 1;
			mgraph.arcs[j - 1][i - 1] = 1;
			mgraph.arcnum += 2;
		}
	}
	return mgraph;
}

// 定位顶点在数组中的位置，未找到则返回-1 
int locateVertex(ALGraph alGraph, VertexType vertex) {
	for (int i = 0; i < alGraph.vexnum; i++) {
		if (vertex == alGraph.vertices[i].vertex) {
			return i;
		}
	}
	return -1;
}

// 创建邻接表存储的图
ALGraph createALGraph(ALGraph alGraph, GraphType type) {
	int num; // 顶点数
	printf("输入图的顶点数：");
	(void)scanf("%d", &num);
	if (num < 0) {
		printf("输入错误！\n");
		return alGraph;
	}
	if (num > MAX_VERTEX_NUM) {
		printf("节点数超出最大值！\n");
		return alGraph;
	}

	// 顶点值
	printf("依次输入%d个顶点的字符（不可重复，不可出现'0'）：\n", num);
	rewind(stdin);
	for (int i = 0; i < num; i++) {
		char input;
		(void)scanf("%c", &input);
		if (input == '0') {
			printf("不可出现'0'，请重新输入所有顶点\n");
			alGraph.vexnum = 0;
			rewind(stdin);
			i = -1;
			continue;
		}
		if (locateVertex(alGraph, input) != -1) {
			printf("顶点有重复值，请重新输入所有顶点\n");
			alGraph.vexnum = 0;
			rewind(stdin);
			i = -1;
			continue;
		}
		alGraph.vertices[i].vertex = input;
		alGraph.vexnum++;
		alGraph.vertices[i].firstArc = NULL;
	}

	// 边
	printf("输入图的边，例如\"AB\"，输入00结束\n");
	while (1) {
		char vertex1, vertex2;
		rewind(stdin);
		(void)scanf("%c%c", &vertex1, &vertex2);
		if (vertex1 == '0' && vertex2 == '0') {
			break;
		}
		// 两顶点的位置
		int i = locateVertex(alGraph, vertex1);
		int j = locateVertex(alGraph, vertex2);
		if (i == -1 || j == -1) {
			printf("顶点不存在！\n");
			continue;
		}

		// 创建弧
		ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
		if (!arcNode) {
			exit(-1);
		}
		arcNode->adjvex = j; // 指向的顶点
		// 使用头插法把弧插入链表
		arcNode->next = alGraph.vertices[i].firstArc;
		alGraph.vertices[i].firstArc = arcNode;
		alGraph.arcnum++;

		// 若为无向图，再创建一个弧
		if (type == undirectedGraph) {
			ArcNode* arcNode = (ArcNode*)malloc(sizeof(ArcNode));
			if (!arcNode) {
				exit(-1);
			}
			arcNode->adjvex = i;
			arcNode->next = alGraph.vertices[j].firstArc;
			alGraph.vertices[j].firstArc = arcNode;
			alGraph.arcnum++;
		}
	}
	return alGraph;
}

// 打印邻接矩阵存储的图的顶点和边
void printMGraph(MGraph mgraph) {
	if (mgraph.vexnum == 0) {
		printf("图为空\n");
		return;
	}
	printf("顶点：\n\t");
	for (int i = 0; i < mgraph.vexnum; i++) {
		if (i != mgraph.vexnum - 1) {
			printf("%d\t", i + 1);
		}
		else {
			printf("%d\n", i + 1);
		}
	}
	printf("\t");
	for (int i = 0; i < mgraph.vexnum; i++) {
		if (i != mgraph.vexnum - 1) {
			printf("%c\t", mgraph.vertexs[i]);
		}
		else {
			printf("%c\n", mgraph.vertexs[i]);
		}
	}

	printf("边：\n");
	for (int i = 0; i <= mgraph.vexnum; i++) {
		if (i == 0) {
			for (int j = 0; j <= mgraph.vexnum; j++) {
				if (j == 0) {
					printf(" ");
				}
				else if (j < mgraph.vexnum) {
					printf("\t%d", j);
				}
				else {
					printf("\t%d\n", j);
				}
			}
			continue;
		}
		for (int j = 0; j <= mgraph.vexnum; j++) {
			if (j == 0) {
				printf("%d", i);
			}
			else if (j < mgraph.vexnum) {
				printf("\t%d", mgraph.arcs[i - 1][j - 1]);
			}
			else {
				printf("\t%d\n", mgraph.arcs[i - 1][j - 1]);
			}
		}
	}
}

// 深度优先遍历实现函数
void DFS(ALGraph alGraph, int* visited, int vertex) {
	if (visited[vertex]) {
		return;
	}
	// 访问
	printf("位于位置 %d 的顶点的值为 %c\n", vertex + 1, alGraph.vertices[vertex].vertex);
	visited[vertex] = 1;
	// 该顶点的弧
	ArcNode* arc = alGraph.vertices[vertex].firstArc;
	while (1) {
		// 递归调用
		if (!arc) {
			break;
		}
		DFS(alGraph, visited, arc->adjvex);
		arc = arc->next;
	}
}

// 深度优先遍历
void DFSTraverse(ALGraph alGraph) {
	if (alGraph.vexnum == 0) {
		return;
	}
	// 定义已访问过的数组
	int* visited = (int*)malloc(alGraph.vexnum * sizeof(int));
	if (!visited) {
		exit(-1);
	}
	// 初始化数组
	for (int i = 0; i < alGraph.vexnum; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < alGraph.vexnum; i++) {
		if (!visited[i]) {
			DFS(alGraph, visited, i);
		}
	}
}

// 初始化队列
SqQueue initQueue() {
	SqQueue queue;
	queue.base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
	if (!queue.base) {
		exit(-1);
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
		exit(-2);
	}
	queue.base[queue.rear] = element;
	queue.rear = (queue.rear + 1) % MAXSIZE;
	return queue;
}

// 删除元素，element为返回的元素
SqQueue deQueue(SqQueue queue, QElemType* element) {
	if (queue.front == queue.rear) {
		exit(-2);
	}
	*element = queue.base[queue.front];
	queue.front = (queue.front + 1) % MAXSIZE;
	return queue;
}

// 广度优先遍历
void BFSTraverse(ALGraph alGraph) {
	if (alGraph.vexnum == 0) {
		return;
	}
	// 定义已访问过的数组
	int* visited = (int*)malloc(alGraph.vexnum * sizeof(int));
	if (!visited) {
		exit(-1);
	}
	// 初始化数组
	for (int i = 0; i < alGraph.vexnum; i++) {
		visited[i] = 0;
	}

	// 初始化队列
	SqQueue queue = initQueue();
	for (int i = 0; i < alGraph.vexnum; i++) {
		if (visited[i]) {
			continue;
		}
		queue = enQueue(queue, i); // 将顶点添加至队尾
		while (queueLength(queue) != 0) {
			int vertex;
			queue = deQueue(queue, &vertex);
			if (visited[vertex] == 0) {
				// 访问顶点
				printf("位于位置 %d 的顶点的值为 %c\n", vertex + 1, alGraph.vertices[vertex].vertex);
				visited[vertex] = 1;
			}
			else {
				continue;
			}
			// 将该顶点的邻接点添加至队列
			ArcNode* arc = alGraph.vertices[vertex].firstArc;
			while (1) {
				if (!arc) {
					break;
				}
				if (!visited[arc->adjvex]) {
					queue = enQueue(queue, arc->adjvex);
				}
				arc = arc->next;
			}
		}
	}
	free(queue.base);
}

// 测试代码
void main() {
	// 邻接矩阵存储的图
	printf("===创建以邻接矩阵存储的有向图===\n");
	MGraph mgraph = initMGraph();
	mgraph = createMGraph(mgraph, directedGraph);
	printMGraph(mgraph);
	printf("===创建以邻接矩阵存储的无向图===\n");
	mgraph = initMGraph();
	mgraph = createMGraph(mgraph, undirectedGraph);
	printMGraph(mgraph);
	printf("\n===创建以邻接表存储的有向图===\n");
	ALGraph alGraph = initALGraph();
	alGraph = createALGraph(alGraph, directedGraph);
	printf("深度优先遍历：\n");
	DFSTraverse(alGraph);
	printf("广度优先遍历：\n");
	BFSTraverse(alGraph);
	printf("\n===创建以邻接表存储的无向图===\n");
	alGraph = initALGraph();
	alGraph = createALGraph(alGraph, undirectedGraph);
	printf("深度优先遍历：\n");
	DFSTraverse(alGraph);
	printf("广度优先遍历：\n");
	BFSTraverse(alGraph);
}

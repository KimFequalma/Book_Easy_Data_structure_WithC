#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

// �׷����� ���� ���� ����Ʈ�� ��� ���� ����
typedef struct graphNode {
	int vertex;
	struct graphNode* link;
}graphNode;

typedef struct graphType {
	int n;								// ���� ����
	graphNode* adjList_H[MAX_VERTEX];	// ������ ���� ���� ����Ʈ�� ��� ��� �迭
	int visited[MAX_VERTEX];			// ������ ���� �湮 ǥ�ø� ���� �迭
}graphType;

typedef int element;

// << ť (6�忡�� ������ ���� ����Ʈ�� �̿��� ť ���� ����:[���� 6-3]�� 05~60��� ����)
typedef struct QNode {
	int data;
	struct QNode *link;
} QNode;

typedef struct {
	QNode *front, *rear;
} LQueueType;

LQueueType *createLinkedQueue() {
	LQueueType *LQ;
	LQ = (LQueueType *)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

int isEmpty(LQueueType *LQ) {
	if (LQ->front == NULL) {
		printf("\n Linked Queue is empty! \n");
		return 1;
	}
	else return 0;
}

void enQueue(LQueueType *LQ, int item) {
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

int deQueue(LQueueType *LQ) {
	QNode *old = LQ->front;
	int item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
} // ť >>

// �ʺ� �켱 Ž���� ���� �ʱ� ���� �׷����� �����ϴ� ����
void createGraph(graphType* g) {
	int v;
	g->n = 0;						// �׷����� ���� ������ 0���� �ʱ�ȭ
	for (v = 0; v<MAX_VERTEX; v++) {
		g->visited[v] = FALSE;		// �׷��� ������ ���� �迭 visited�� FALSE�� �ʱ�ȭ
		g->adjList_H[v] = NULL;		// ���� ����Ʈ�� ���� ��� ��� �迭�� NULL�� �ʱ�ȭ
	}
}

// �׷��� g�� ���� v�� �����ϴ� ���� : [���� 8-2]�� 26~32��� ����
void insertVertex(graphType* g, int v) {
	if (((g->n) + 1)>MAX_VERTEX) {
		printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
		return;
	}
	g->n++;
}

// �׷��� g�� ���� (u, v)�� �����ϴ� ���� : [���� 8-2]�� 35~47��� ����
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("\n �׷����� ���� �����Դϴ�!");
		return;
	}
	node = (graphNode *)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = g->adjList_H[u];
	g->adjList_H[u] = node;
}

// �׷��� g�� ���� ���� ����Ʈ�� ����ϴ� ���� : [���� 8-2]�� 50~61��� ����
void print_adjList(graphType* g) {
	int i;
	graphNode* p;
	for (i = 0; i<g->n; i++) {
		printf("\n\t\t���� %c�� ���� ����Ʈ", i + 65);
		p = g->adjList_H[i];
		while (p) {
			printf(" -> %c", p->vertex + 65);
			p = p->link;
		}
	}
}

// �׷��� g���� ���� v�� ���� �ʺ� �켱 Ž�� ����
void BFS_adjList(graphType* g, int v) {
	graphNode* w;
	LQueueType* Q;				// ť
	Q = createLinkedQueue();	// ť ����
	g->visited[v] = TRUE;		// ���� ���� v�� ���� �迭 ���� TRUE�� ����
	printf(" %c", v + 65);
	enQueue(Q, v);			// ���� ���� v�� ť�� enQueue

	// ť�� ������ �ƴ� ���� �ʺ� �켱 Ž�� ����
	while (!isEmpty(Q)) {
		v = deQueue(Q);
		// ���� ���� w�� �湮���� ���� ��� 
		for (w = g->adjList_H[v]; w; w = w->link)	// ���� ������ �ִ� ���� ����
			if (!g->visited[w->vertex]) {	// ���� w�� �湮���� ���� ������ ���
				g->visited[w->vertex] = TRUE;
				printf(" %c", w->vertex + 65); // ���� 0~6�� A~G�� �ٲپ� ���
				enQueue(Q, w->vertex);
			}
	} // ť�� �����̸� �ʺ� �켱 Ž�� ����
}

void main() {
	int i;
	graphType *G9;
	G9 = (graphType *)malloc(sizeof(graphType));
	createGraph(G9);

	// �׷��� G9 ����
	for (i = 0; i<7; i++)
		insertVertex(G9, i);
	insertEdge(G9, 0, 2);
	insertEdge(G9, 0, 1);
	insertEdge(G9, 1, 4);
	insertEdge(G9, 1, 3);
	insertEdge(G9, 1, 0);
	insertEdge(G9, 2, 4);
	insertEdge(G9, 2, 0);
	insertEdge(G9, 3, 6);
	insertEdge(G9, 3, 1);
	insertEdge(G9, 4, 6);
	insertEdge(G9, 4, 2);
	insertEdge(G9, 4, 1);
	insertEdge(G9, 5, 6);
	insertEdge(G9, 6, 5);
	insertEdge(G9, 6, 4);
	insertEdge(G9, 6, 3);
	printf("\n G9�� ���� ����Ʈ ");
	print_adjList(G9);

	printf("\n\n///////////////\n\n�ʺ� �켱 Ž�� >> ");
	BFS_adjList(G9, 0);      // 0�� ������ ���� A���� �ʺ� �켱 Ž�� ����

	getchar();
}
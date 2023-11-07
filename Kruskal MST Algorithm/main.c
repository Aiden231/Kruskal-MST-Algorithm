#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 10
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n) 
{
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

int set_find(int curr)
{
	if (parent[curr] == -1) {
		return curr;
	}

	while (parent[curr] != -1)	{
		curr = parent[curr];
	}

	return curr;
}

void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) {
		parent[root1] = root2;
	}
}

typedef struct edge {
	int start, end, weight;
}Edge;

typedef struct graphType {
	int n;
	Edge edges[2 * MAX_VERTICES];
}GraphType;

// 그래프 초기화
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// 최소 힙을 구현하는 함수
void min_heapify(Edge* heap, int size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < size && heap[left].weight < heap[smallest].weight) {
        smallest = left;
    }

    if (right < size && heap[right].weight < heap[smallest].weight) {
        smallest = right;
    }

    if (smallest != i) {
        Edge temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        min_heapify(heap, size, smallest);
    }
}

// 최소 힙에서 최소값을 추출하는 함수
Edge extract_min(Edge* heap, int* size) {
    Edge min = heap[0];
    heap[0] = heap[(*size) - 1];
    (*size)--;
    min_heapify(heap, *size, 0);
    return min;
}

// 최소 힙에 새로운 원소를 삽입하는 함수
void insert_min_heap(Edge* heap, int* size, Edge new_edge) {
    (*size)++;
    int i = (*size) - 1;
    heap[i] = new_edge;

    while (i != 0 && heap[(i - 1) / 2].weight > heap[i].weight) {
        Edge temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void kruskal(GraphType* g) {
    int edge_accepted = 0;
    Edge e;
    Edge* min_heap = (Edge*)malloc(g->n * sizeof(Edge));
    int heap_size = 0;

    set_init(g->n);

    for (int i = 0; i < g->n; i++) {
        insert_min_heap(min_heap, &heap_size, g->edges[i]);
    }

    printf("크루스칼 최소 신장 트리 알고리즘\n");
	printf("MinHeap 사용\n\n");

    while (edge_accepted < (g->n / 2) - 1) {
        e = extract_min(min_heap, &heap_size);
        int uset = set_find(e.start);
        int vset = set_find(e.end);

        if (uset != vset) {
            printf("간선 (%d,%d) %d 선택\n", e.start + 1, e.end + 1, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }

    free(min_heap);
}

int main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g,0,1,3);
	insert_edge(g, 0, 5, 11);
	insert_edge(g, 0, 6, 12);
	insert_edge(g, 1, 4, 5);
	insert_edge(g, 1, 3, 4);
	insert_edge(g, 1, 4, 1);
	insert_edge(g, 1, 5, 7);
	insert_edge(g, 1, 6, 8);
	insert_edge(g, 2, 3, 2);
	insert_edge(g, 2, 6, 6);
	insert_edge(g, 2, 7, 5);
	insert_edge(g, 3, 4, 13);
	insert_edge(g, 3, 7, 14);
	insert_edge(g, 3, 9, 16);
	insert_edge(g, 4, 5, 9);
	insert_edge(g, 4, 8, 18);
	insert_edge(g, 4, 9, 17);
	insert_edge(g, 6, 7, 13);
	insert_edge(g, 7, 9, 15);
	insert_edge(g, 8, 9, 10);

	kruskal(g);
	
	free(g);
	return 0;
}
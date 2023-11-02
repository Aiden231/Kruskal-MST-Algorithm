#include <stdio.h>
#include <stdlib.h>

#define MAx_VERTICEX 100
#define INF 1000

int parent[MAx_VERTICEX];

void set_init(int n) 
{
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

int set_find(int curr)
{
	if (parent[curr] == -1) { // 오류 고쳐야됨
		return curr;
	}
	while (parent[curr]!=-1)	{
		curr = parent[curr];
		return curr;
	}
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
	Edge edges[2 * MAx_VERTICEX];
}GraphType;

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAx_VERTICEX; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

int compare(const void* a, const void* b)
{
	Edge* x = (Edge*)a;
	Edge* y = (Edge*)b;
	return(x->weight - y->weight);
}

void kruskal(GraphType* g)
{
	int edge_accepted = 0;
	int uset, vset;
	Edge e;

	set_init(g->n);
	qsort(g->edges, g->n, sizeof(Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	while (edge_accepted < (g->n) - 1) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

int main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g,1,2,3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 3);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);

	kruskal(g);
	free(g);
	return 0;
}
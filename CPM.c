#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN  1000
#define CPM_INPUT_FILE   "cpm_data.txt"
//Gabriel castro- designed graph and criteria, 
//Mitchell Oriahi- made the beginning functions for graph and 

typedef struct Edge {
    int to, dur;
    struct Edge *next;
} Edge;

// globals (or wrap in a struct for cleanliness)
int  N, M;
Edge *adjList[MAXN], *revAdjList[MAXN];
int  inDeg[MAXN], revInDeg[MAXN];
int  earliest[MAXN], latest[MAXN], slack[MAXN], origin[MAXN];

// --- Function prototypes ---
void  readGraph(const char *fname);
void  topoLongestPath(void);
void  computeLatestTimes(void);
void  computeSlackAndCP(void);
void  printResults(void);

int main(void) {
    readGraph(CPM_INPUT_FILE);
    topoLongestPath();
    computeLatestTimes();
    computeSlackAndCP();
    printResults();
    return 0;
}

// --- Implementation details ---

void readGraph(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (!f) { perror("fopen"); exit(1); }
    fscanf(f, "%d %d", &N, &M);
    // init
    for (int i = 0; i < N; i++) {
        adjList[i] = revAdjList[i] = NULL;
        inDeg[i] = revInDeg[i] = 0;
    }
    // read edges
    for (int i = 0, u, v, d; i < M; i++) {
        fscanf(f, "%d %d %d", &u, &v, &d);
        // forward
        Edge *e = malloc(sizeof *e);
        e->to = v; e->dur = d; e->next = adjList[u];
        adjList[u] = e; inDeg[v]++;
        // reverse
        Edge *re = malloc(sizeof *re);
        re->to = u; re->dur = d; re->next = revAdjList[v];
        revAdjList[v] = re; revInDeg[u]++;
    }
    fclose(f);
}

void topoLongestPath(void) {
    int queue[MAXN], qh = 0, qt = 0;
    for (int i = 0; i < N; i++) {
        earliest[i] = 0;
        origin[i] = -1;
        if (inDeg[i] == 0) queue[qt++] = i;
    }
    while (qh < qt) {
        int u = queue[qh++];
        for (Edge *e = adjList[u]; e; e = e->next) {
            int v = e->to, d = e->dur;
            if (earliest[u] + d > earliest[v]) {
                earliest[v] = earliest[u] + d;
                origin[v] = u;
            }
            if (--inDeg[v] == 0) queue[qt++] = v;
        }
    }
}

void computeLatestTimes(void) {
    // find project finish time
    int Tmax = 0;
    for (int i = 0; i < N; i++)
        if (earliest[i] > Tmax) Tmax = earliest[i];
    // init latest[] to Tmax
    for (int i = 0; i < N; i++) latest[i] = Tmax;
    // reverse topo pass
    int queue[MAXN], qh = 0, qt = 0;
    for (int i = 0; i < N; i++)
        if (revInDeg[i] == 0) queue[qt++] = i;
    while (qh < qt) {
        int u = queue[qh++];
        for (Edge *e = revAdjList[u]; e; e = e->next) {
            int v = e->to, d = e->dur;
            if (latest[u] - d < latest[v])
                latest[v] = latest[u] - d;
            if (--revInDeg[v] == 0) queue[qt++] = v;
        }
    }
}

void computeSlackAndCP(void) {
    for (int i = 0; i < N; i++)
        slack[i] = latest[i] - earliest[i];
    // critical path can be traced via origin[] from sink
}

void printResults(void) {
    printf("\n Vertex | Earliest | Latest | Slack\n");
    printf("--------+----------+--------+------\n");
    for (int i = 0; i < N; i++) {
        printf("%7d | %8d | %6d | %5d\n",
            i, earliest[i], latest[i], slack[i]);
    }
    // find and print critical path
    // e.g., trace from v_max back to 0 using origin[]
}

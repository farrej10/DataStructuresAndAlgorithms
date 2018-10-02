#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INFINITY 999999;
//queue variables


struct vertex *queue[MAX];
int front = -1,rear = -1;
void insertQueue(struct vertex *v);
struct vertex* deleteQueue();
int isEmptyQueue();

struct heap{
    int *data;
    int *prio;
    int *index;
    int len;
    int size;
};

struct heap *createHeap (int n);

struct vertex
{
    char id;
    struct edge *edges;
    struct vertex *pred;
    int distanceFromSource;
    int visited;
};

void vertexFree(struct vertex *v);
int vertexInit(struct vertex *v,char id);
struct vertex* vertexNew(char id);

struct edge
{
    struct vertex *dest;
    int weight;
    struct edge *next;
};

void edgeFree(struct edge *e);
int edgeInit(struct edge *e,struct vertex *destVertex, int weights);
struct edge* edgeNew(struct vertex *destVertex,int weights);

struct graph
{
    struct vertex **list;
    int numVertex;
};

void graphFree(struct graph *g);
int graphInit(struct graph *g,int size);
struct graph* graphNew(int size);
void printGraph(struct graph* g);
void addVertexToGraph(struct graph *g,char id);
struct vertex* searchGraphforVertex(struct graph *g,char id);
void addEdgeToVertex(struct graph *g,char src,char dest,int weight);
void DFS(struct graph *g, char startId);
void BFS(struct graph *g,char startId);
void graphReset(struct graph *g);
void dijkstra (struct graph *g, char srcId, char destId);

int main(int argc, char *argv[])
{


    int size = 100;
    struct graph *g = graphNew(size);
    //vertices added to graph
    addVertexToGraph(g,'A');
    addVertexToGraph(g,'B');
    addVertexToGraph(g,'C');
    addVertexToGraph(g,'D');
    addVertexToGraph(g,'E');
    addVertexToGraph(g,'F');
    addVertexToGraph(g,'G');

    //A edges
    addEdgeToVertex(g,'A','B',1);
    addEdgeToVertex(g,'A','C',3);
    addEdgeToVertex(g,'A','F',10);
    //B edges
    addEdgeToVertex(g,'B','A',1);
    addEdgeToVertex(g,'B','C',1);
    addEdgeToVertex(g,'B','E',5);
    addEdgeToVertex(g,'B','D',7);
    addEdgeToVertex(g,'B','G',2);
    //C edges
    addEdgeToVertex(g,'C','A',3);
    addEdgeToVertex(g,'C','B',1);
    addEdgeToVertex(g,'C','D',9);
    addEdgeToVertex(g,'C','E',3);
    //D edges
    addEdgeToVertex(g,'D','B',7);
    addEdgeToVertex(g,'D','G',12);
    addEdgeToVertex(g,'D','F',1);
    addEdgeToVertex(g,'D','E',2);
    addEdgeToVertex(g,'D','C',9);
    //E edges
    addEdgeToVertex(g,'E','C',3);
    addEdgeToVertex(g,'E','B',5);
    addEdgeToVertex(g,'E','D',2);
    addEdgeToVertex(g,'E','F',2);
    //F edges
    addEdgeToVertex(g,'F','A',10);
    addEdgeToVertex(g,'F','E',2);
    addEdgeToVertex(g,'F','D',1);
    //G edges
    addEdgeToVertex(g,'G','B',2);
    addEdgeToVertex(g,'G','D',12);

    printGraph(g);

    graphFree(g);
    return 0;
}

void vertexFree(struct vertex *v)
{
    if(v)
    {
        free(v);
    }
}

int vertexInit(struct vertex *v,char id)
{
    if(v==NULL)
        return 0;
    //init if not null
    v->id = id;
    v->edges = NULL;
    v->pred = NULL;
    v->distanceFromSource = INFINITY;
    v->visited = 0;
    return 1;
}

struct vertex* vertexNew(char id)
{
    struct vertex *v;
    v = malloc(sizeof(struct vertex));

    if (!vertexInit(v,id))
    {
        vertexFree(v);
        v=NULL;
    }
    return v;
}

void addVertexToGraph(struct graph *g,char id)
{
    struct vertex *newVertex = vertexNew(id);
    g->list[g->numVertex] = newVertex;
    g->numVertex++;
}


//need to do this properly
void graphFree(struct graph *g)
{
    if(g)
    {      
        free(g);
    }
}

int graphInit(struct graph *g,int size)
{
    if(g == NULL)
        return 0;

    g->numVertex = 0;
    g->list = malloc(sizeof(struct vertex)*size);
    int i;

    for(i=0;i<size;i++)
        g->list[i] = NULL;
   
    return 1;
}

struct graph* graphNew(int size)
{
    struct graph *g;
    g = malloc(sizeof(struct vertex));
    if(!graphInit(g,size))
    {
        graphFree(g);
        g=NULL;
    }
    return g;
}
//prints graph and weights
void printGraph(struct graph* g)
{
    int v;
    struct vertex* temp;
    for (v = 0; v < g->numVertex; v++)
    {
        temp = g->list[v];
        struct edge *tempedge = temp->edges;

        if(temp)
        {
            printf("\n Adjacency list of vertex %c\n ", temp->id);
            while (tempedge)
            {
                printf("->%c%i", tempedge->dest->id,tempedge->weight);
                tempedge = tempedge->next;
           }
            printf("\n");
        }
    }
}

//linear search
struct vertex* searchGraphforVertex(struct graph *g,char id)
{
    int i;
    for(i=0;i<g->numVertex;i++)
    {
        if(id == g->list[i]->id)
            return g->list[i];
    }
    return NULL;
}

void edgeFree(struct edge *e)
{
    if(e)
    {
        free(e);
    }
}


int edgeInit(struct edge *e,struct vertex *destVertex, int weights)
{
    if(e == NULL)
        return 0;

    e->dest = destVertex;
    e->weight = weights;
    e->next = NULL;
    return 1;

}

struct edge* edgeNew(struct vertex *destVertex,int weights)
{
    struct edge *e;
    e = malloc(sizeof(struct vertex));
    if(!edgeInit(e,destVertex,weights))
    {
        edgeFree(e);
        e=NULL;
    }
    return e;
}

void addEdgeToVertex(struct graph *g,char src,char dest,int weight)
{
    struct vertex *tempsrc = searchGraphforVertex(g,src);
    struct vertex *tempdest = searchGraphforVertex(g,dest);

    if(tempsrc == NULL)
        printf("Source Not Found\n");
    else if (tempdest == NULL)
        printf("Dest Not Found\n");
    else
    {
        if(tempsrc->edges == NULL)
            tempsrc->edges = edgeNew(tempdest,weight);
        else
        {
            struct edge *tempedge =tempsrc->edges;
            if(tempedge->next == NULL)
            {
                 tempedge->next = edgeNew(tempdest,weight);
            }
            else
            {
                while(tempedge->next != NULL)
                {
                        tempedge = tempedge->next;
                }

                tempedge->next = edgeNew(tempdest,weight);
            }
        }
    }

    
}

void DFS(struct graph *g,char startId)
{
    struct vertex *temp = searchGraphforVertex(g,startId);
    
    printf("%c ",temp->id);
    temp->visited=1;
    struct edge *e;
    e =temp->edges;
    while(e)
    {
       if(e->dest->visited == 0)
       {
           DFS(g,e->dest->id);
       }
        
        e=e->next;
    }
}

void insertQueue(struct vertex *v)
{
    if(rear == MAX-1)
        printf("Queue OverflowV2\n");
    else
    {
        if(front == -1) 
            front = 0;
        rear = rear+1;
        queue[rear] = v ;
    }
}
 
int isEmptyQueue()
{
    if(front == -1 || front > rear)
        return 1;
    else
        return 0;
}
 
struct vertex* deleteQueue()
{
    struct vertex *delete_item;
    if(front == -1 || front > rear)
    {
        printf("Queue Underflow V1\n");
        exit(1);
    }
    
    delete_item = queue[front];
    front = front+1;
    return delete_item;
}


void BFS(struct graph *g,char startId)
{

    struct vertex *temp = searchGraphforVertex(g,startId);
    insertQueue(temp);
    temp->visited = 1;
    

    while(!isEmptyQueue())
    {
        temp = deleteQueue( );
        printf("%c ",temp->id);
        temp->visited = 1;
        struct edge *tempedge = temp->edges;
        if(tempedge != NULL)
        {
            while(tempedge != NULL && tempedge->dest->visited != 1)
            {
                insertQueue(tempedge->dest);
                tempedge->dest->visited = 1;
                tempedge = tempedge->next;
            }
        }
        
    }
}

void graphReset(struct graph *g)
{
    int i;
    for(i=0;i<g->numVertex;i++)
    {
        g->list[i]->visited = 0;
        
    }
}
/*
void dijkstra (struct graph *g, char srcId, char destId) {


    struct vertex *v = searchGraphforVertex(g,a);
    v->distanceFromSource = 0;
    struct heap *h = createHeap(g->numVertex);
    pushHeap(h, srcId, v->distanceFromSource);
    while (h->len) {
        i = popHeap(h);
        if (i == b)
            break;
        v = g->list[i];
        v->visited = 1;
        
        struct edge *e = v->edges;
        while(e->next !=NULL) 
        {
            struct vertex *u = searchGraphforVertex(g,e->dest->id);
            if (!u->visited && v->distanceFromSource + e->weight <= u->distanceFromSource) {
                u->pred = i;
                u->distanceFromSource = v->distanceFromSource + e->weight;
                pushHeap(h, e->dest, u->distanceFromSource);
            }
        }
        i++
    }
}*/
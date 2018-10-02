#include <stdio.h>
#include <stdlib.h>

#define MAX 10
//queue variables


struct vertex *queue[MAX];
int front = -1,rear = -1;
void insertQueue(struct vertex *v);
struct vertex* deleteQueue();
int isEmptyQueue();

struct vertex
{
    char id;
    struct edge *edges;
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
    //A edges
    addEdgeToVertex(g,'A','B',1);
    addEdgeToVertex(g,'A','D',1);
    addEdgeToVertex(g,'A','E',1);
    //B edges
    addEdgeToVertex(g,'B','C',1);
    addEdgeToVertex(g,'B','D',1);
    //C edges
    addEdgeToVertex(g,'C','B',1);
    addEdgeToVertex(g,'C','D',1);
    //D edges
    addEdgeToVertex(g,'D','F',1);
    //E edges
    addEdgeToVertex(g,'E','D',1);
    //F edges
    addEdgeToVertex(g,'F','C',1);

    //printGraph(g);
    printf("DFS: ");
    DFS(g,'D');
    printf("\n");

    graphReset(g);

    printf("BFS: ");
    BFS(g,'D');
    printf("\n");

    
    
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
                printf("->%c", tempedge->dest->id);
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
#include <stdio.h>
#include <stdlib.h>


typedef struct node 
{
    char value;
    struct node *next;
} node;


int linked_list(void)
{
    node *lista = malloc(sizeof(node));
    lista->value = 'a';
    lista->next = NULL;
}


typedef struct Vector
{
    int *data;
    size_t size;
    size_t capacity;
}Vector;


void vector_init(Vector *v)
{
    if(sizeof(*v) == sizeof(Vector))
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * sizeof(int));
    return;
}


void vector_realloc(Vector *v)
{
    v->capacity *= 2;
    v->data = realloc(v->data, v->capacity * sizeof(int));
}


void vector_push(Vector *v, int value)
{
    if(v->size == v->capacity)
        vector_realloc(v);

    v->data[v->size++] = value;
}


void vector_free(Vector *v)
{
    free(v->data);
}


typedef struct Heap 
{
    int *data;
    size_t size;
    size_t capacity;
} Heap;


void heap_insert(Heap *heap, int i)
{
    if(heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        realloc(heap->data, heap->capacity);
    }

    heap->data[heap->size++] = i;
}


void heap_extract_max(Heap *h)
{
    int max = h->data[0];
    h->data[0] = h->data[h->size-1];
    h->size--;
    heapify_down(h, 0);
    return max;
}


void heapify_up(Heap *h, int i)
{
    while(i > 0)
    {
        int parent = (i - 1) / 2;

        if(h->data[parent] >= h->data[i])
            break;
        
        int temp = h->data[parent];
        h->data[parent] = h->data[i];
        h->data[i] = temp;

        i = parent;
    }
}


void heapify_down(Heap *h, int i)
{
    while(true)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;

        if(left < h->size && h->data[left] > h->data[i])
            largest = left;

        if(right < h->size && h->data[right] > h->data[i])
            largest = right;

        if(largest == i)
            break;

        int temp = h->data[i];
        h->data[i] = h->data[largest];
        h->data[largest] = temp;
        
        i = largest;
    }
}


typedef struct AVLnode
{
    int key;
    int height;
    struct AVLnode *left;
    struct AVLnode *right;
} AVLnode;


void AVLinsert(AVLnode *node, int i)
{
    if(node->height == 0)
    {   
        AVLnode *new_node = malloc(sizeof(AVLnode));
    }
}
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node* next;
    struct node* prev;
};

typedef struct node Node;

struct list
{
    Node* head;
    Node* tail;
    size_t size;
};
typedef struct list List;

List init(size_t n)
{
    List lst;
    lst.head = NULL;
    lst.tail = NULL;
    lst.size = 0;
    return lst;
}

void print(const List* pl)
{
    const Node* current = pl->head;
    while(current != NULL)
    {
        printf("%i ", current->value);
        current = current->next;
    }
}

void push_back(List* pl, int value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) 
    {
        printf("Ошибка выделения памяти");
        exit(1);
    }   
    new_node->value = value;
    new_node->prev = pl->tail;
    new_node->next = NULL;
    if (pl->tail != NULL) // если вдруг список был пуст
    {
        pl->tail->next = new_node;
    } 
    else 
    {
        pl->head = new_node;
    }
    pl->tail = new_node;
    pl->size++;
}

int pop_back(List* pl)
{
    Node* last_node = pl->tail;
    int value = last_node->value;
    
    if (last_node->prev != NULL)
    {
        pl->tail = last_node->prev;
        last_node->prev->next = NULL;
    }
    else
    {
        pl->head = NULL;
        pl->tail = NULL;
    }
    free(last_node);
    pl->size--;

    return value;
}

void push_front(List* pl, int value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) 
    {
        printf("Ошибка выделения памяти");
        exit(1);
    }
    new_node->value = value;
    new_node->prev = NULL;
    if (pl->head != NULL) // если вдруг список был пуст
    {
        new_node->next = pl->head;
        pl->head->prev = new_node;
    } 
    else 
    {
        new_node->next = NULL;
        pl->tail = new_node;
    }
    pl->size++;
    pl->head = new_node;
}

int pop_front(List* pl)
{
    Node* first_node = pl->head;
    int value = first_node->value;
    
    if (first_node->next != NULL)
    {
        pl->head = first_node->next;
        first_node->next->prev = NULL;
    }
    else
    {
        pl->head = NULL;
        pl->tail = NULL;
    }
    free(first_node);
    pl->size--;

    return value;
}

Node* erase(List* pl, Node* p)
{
    if (p->prev != NULL)
    {
        p->prev->next = p->next;
    }
    else
    {
        pl->head = p->next;
    }
    if (p->next != NULL)
    {
        p->next->prev = p->prev;
    }
    else
    {
        pl->tail = p->prev;
    }
    Node* next_node = p->next;
    free(p);
    pl->size--;
    
    return next_node;
}

void splice(List* plist, Node* p, List* pother)
{
    if (plist->size == 0)
    {
        plist->head = pother->head;
        plist->tail = pother->tail;
        plist->size = pother->size;
    }

    if (p != NULL)
    {
        pother->tail->next = p;
        p->prev->next = pother->head;
        pother->head->prev = p->prev;
        p->prev = pother->tail;
    }
    else
    {
        plist->tail->next = pother->head; // ну просто в конец списка
        pother->head->prev = plist->tail;
        plist->tail = pother->tail;
    }

    plist->size += pother->size;
    pother->head = NULL;
    pother->tail = NULL;
    pother->size = 0;
}

void destroy(List* pl)
{
    Node* current = pl->head;
    while(current)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    pl->head = NULL;
    pl->tail = NULL;
    pl->size = 0;
}

void advance(Node** pp, size_t n)
{
    Node* current = *pp;
    size_t count = 0;

    while (current != NULL && count < n)
    {
        current = current->next;
        count++;
    }

    *pp = current; 
}

#include <stdio.h>

struct node
{
    int value;
    struct node* ptr;
};

typedef struct node Node;

int main()
{
    Node node1;
    Node node2;

    node1.value = 1;
    node2.value = 2;

    node1.ptr = &node2;
    node2.ptr = &node1;

    printf("Node1 value: %d, Node1.ptr->value: %d\n", node1.value, node1.ptr->value);
    printf("Node2 value: %d, Node2.ptr->value: %d\n", node2.value, node2.ptr->value);

    return 0;
}
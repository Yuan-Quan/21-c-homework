
#include <stdlib.h>
#include "list.h"

// -----------------------------------------------------------------------------

static Link* get_link(Int n, Int x)
{
    Link* link = malloc(sizeof(Link));
    link->n     = n;
    link->x     = x;
    link->prior = link->next = 0;
    return link;
}

// -----------------------------------------------------------------------------

List* get_list(void)
{
    // 在此处补充完整
}

void insert_front(List* list, Int n, Int x)
{
    // 在此处补充完整
}

void insert_back(List* list, Int n, Int x)
{
    // 在此处补充完整
}

void remove_front(List* list)
{
    // 在此处补充完整
}

void bubble_sort_x(List* list)
{
    // 在此处补充完整
}

void list_free(List* list)
{
    if (!list)
        return;

    Link* link = list->head;
    while (link) {
        Link* p = link;
        link = link->next;
        free(p);
    }
    free(list);
}

// -----------------------------------------------------------------------------

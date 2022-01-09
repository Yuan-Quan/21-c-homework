
#include <stdlib.h>
#include "list.h"

// -----------------------------------------------------------------------------

static Link *get_link(Int n, Int x)
{
    Link *link = malloc(sizeof(Link));
    link->n = n;
    link->x = x;
    link->prior = link->next = 0;
    return link;
}

// -----------------------------------------------------------------------------

List *get_list(void)
{
    // 在此处补充完整
    List *list = malloc(sizeof(List));
    list->size = 0;
    list->head = 0;
    list->tail = 0;
}

void insert_front(List *list, Int n, Int x)
{
    // 在此处补充完整
    Link *org_head = list->head;
    Link *new_head = get_link(n, x);
    list->head = new_head;
    new_head->next = org_head;
    list->size += 1;
    if (org_head == 0) // in case that, this is the only node of this list, also set the tail of list to this node
    {
        list->tail = new_head;
    }
    else // other wise, set the prior of the original head
    {
        org_head->prior = new_head;
    }
}

void insert_back(List *list, Int n, Int x)
{
    // 在此处补充完整
    Link *org_tail = list->tail;
    Link *new_tail = get_link(n, x);
    list->tail = new_tail;
    new_tail->prior = org_tail;
    list->size += 1;
    if (org_tail == 0) // in case that, this is the only node of this list, also set the head of list to this node
    {
        list->head = new_tail;
    }
    else // other wise, set the next of the original tail
    {
        org_tail->next = new_tail;
    }
}

void remove_front(List *list)
{
    // 在此处补充完整
    Link *org_head = list->head;

    if (list->size == 1) // if it only gotta one link, just empty it and return
    {
        list->head = 0;
        list->tail = 0;
        list->size = 0;
        // cut the poor computer some slack
        free(org_head);
        return;
    }

    Link *new_head = org_head->next;
    list->head = new_head;
    list->size -= 1;
    new_head->prior = 0;
}

void bubble_sort_x(List *list)
{
    // 在此处补充完整
    // Not Implemented: it seems this function is not used
    return; // pass
}

void list_free(List *list)
{
    if (!list)
        return;

    Link *link = list->head;
    while (link)
    {
        Link *p = link;
        link = link->next;
        free(p);
    }
    free(list);
}

// -----------------------------------------------------------------------------


#include <stdlib.h>
#include "unsigned.h"

// -----------------------------------------------------------------------------

static const Int ignore = 42;

// 在此处可定义若干辅助函数，以供定义其它函数时使用

static const Int epsilon = 10e-6;

// return the n value of link, return 0 if it is NULL
int get_link_value(Link *link)
{
    if (link == 0)
    {
        return 0;
    }
    else
    {
        return link->n;
    }
}

// return 1 if x >= y, otherwise 0
int unsigned_is_greater_than(const Unsigned *x, const Unsigned *y)
{
    if (x->size < y->size) // if y have more digit than x (thus greater than x), abort
    {
        return 0;
    }
    else if (x->size == y->size)
    {
        Link *ptrx = x->head;
        Link *ptry = y->head; // if y is greater than x , abort
        while (ptrx != 0)
        {
            if (ptry->n > ptrx->n)
            {
                return 0;
            }
            else if (ptrx->n > ptry->n)
            {
                break;
            }

            ptrx = ptrx->next;
            ptry = ptry->next;
        }
    }
    return 1;
}

int unsigned_is_equal(const Unsigned *x, const Unsigned *y)
{
    // if two list is not the same size, no need to compare
    if (x->size != y->size)
    {
        return 0;
    }

    int flag = 1;
    Link *ptrx = x->head;
    Link *ptry = y->head;

    while (flag && ptrx != 0 && ptry != 0) // keeep comparing and update flag, until something goes wrong
    {
        flag = ptrx->n == ptry->n;
        ptrx = ptrx->next;
        ptry = ptry->next;
    }

    return flag;
}
// remove the leading 0s
void unsigned_remove_leading_zero(Unsigned *list)
{
    if (list->size == 0)
    {
        return;
    }

    Link *ptr = list->head;

    while (ptr && ptr->n == 0)
    {
        ptr = ptr->next;
        remove_front(list);
    }
}
// -----------------------------------------------------------------------------

Unsigned *unsigned_from_ll(long long x)
{
    Unsigned *ret = get_list();

    insert_front(ret, x % 10, ignore);
    while (x /= 10)
        insert_front(ret, x % 10, ignore);
    return ret;
}

Unsigned *unsigned_copy(const Unsigned *x)
{
    if (!x)
        return 0;

    Unsigned *y = get_list();
    for (Link *link = x->head; link; link = link->next)
        insert_back(y, link->n, link->x);
    return y;
}

void unsigned_free(Unsigned *x)
{
    list_free(x);
}

long long unsigned_to_ll(const Unsigned *x)
{
    long long ret = 0;
    for (Link *link = x->head; link; link = link->next)
    {
        ret *= 10;
        ret += link->n;
    }
    return ret;
}

int unsigned_cmp(const Unsigned *x, const Unsigned *y)
{
    // 在此处补充完整
    if (unsigned_is_greater_than(x, y))
    {
        if (unsigned_is_equal(x, y))
        {
            return 0;
        }
        return 1;
    }
    else
    {
        return -1;
    }
}

Unsigned *unsigned_add(const Unsigned *x, const Unsigned *y)
{
    // 在此处补充完整
    int carry_bit = 0;
    Link *ptrx = x->tail;
    Link *ptry = y->tail;
    Unsigned *result = get_list();
    int sum = 0;

    while (ptrx || ptry || carry_bit)
    {
        sum = get_link_value(ptrx) + get_link_value(ptry);
        if (carry_bit)
        {
            sum++;
            carry_bit = 0;
        }

        insert_front(result, sum % 10, ignore);
        if (sum >= 10)
        {
            carry_bit = 1;
        }
        if (ptrx != 0)
        {
            ptrx = ptrx->prior;
        }
        if (ptry != 0)
        {
            ptry = ptry->prior;
        }
    }
    return result;
}

Unsigned *unsigned_sub(const Unsigned *x, const Unsigned *y)
{
    if (!unsigned_is_greater_than(x, y))
    {
        return NULL; // abort if y is greater than x
    }

    Unsigned *result = get_list();
    Link *ptrx = x->tail;
    Link *ptry = y->tail;
    int sub = 0;
    int borrow_bit = 0;
    // we will do it from tail to head

    while (ptrx || ptry)
    {
        sub = get_link_value(ptrx) - get_link_value(ptry);
        if (borrow_bit)
        {
            sub--;
            borrow_bit = 0;
        }

        if (sub < 0)
        {
            borrow_bit = 1;
            sub += 10;
        }

        insert_front(result, sub, ignore);

        if (ptrx != 0)
        {
            ptrx = ptrx->prior;
        }
        if (ptry != 0)
        {
            ptry = ptry->prior;
        }
    }

    unsigned_remove_leading_zero(result);
    return result;
}

Unsigned *unsigned_mul(const Unsigned *x, const Unsigned *y)
{
    // 在此处补充完整
    int carry_bit = 0;
    Link *ptrx = x->tail;
    Link *ptry = y->tail;
    Unsigned *result = get_list();
    Unsigned *mul = get_list();
    int product = 0;

    // keep track of how many 10s should be multiplied
    int count = 0;
    // for each digit of y, multiply with x, multiply some number of 10s, add to result
    while (ptry)
    {
        // reset the mul for next round of calculation
        list_free(mul);
        mul = get_list();
        ptrx = x->tail;

        // calculate x * a digit of y
        while (ptrx || carry_bit)
        {
            product = get_link_value(ptrx) * get_link_value(ptry);
            if (carry_bit)
            {
                product += carry_bit;
                carry_bit = 0;
            }

            insert_front(mul, product % 10, ignore);
            if (product >= 10)
            {
                carry_bit = product / 10;
            }
            if (ptrx != 0)
            {
                ptrx = ptrx->prior;
            }
        }

        // *10's, add with result
        for (size_t i = 0; i < count; i++)
        {
            insert_back(mul, 0, ignore);
        }
        result = unsigned_add(result, mul);

        // keep track of how much 10s should be multiplied
        count++;

        // increment ptry to next digit
        if (ptry != 0)
        {
            ptry = ptry->prior;
        }
    }

    return result;
}

Unsigned *unsigned_div(const Unsigned *x, const Unsigned *y, Unsigned **rem)
{
    // 在此处补充完整
    Unsigned *result = get_list();
    Unsigned *one = get_list();
    insert_front(one, 1, ignore);

    while (unsigned_is_greater_than(x, y))
    {
        x = unsigned_sub(x, y);
        result = unsigned_add(result, one);
    }

    *rem = x;

    return result;
}

// -----------------------------------------------------------------------------

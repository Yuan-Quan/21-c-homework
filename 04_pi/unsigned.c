
#include <stdlib.h>
#include "unsigned.h"

// -----------------------------------------------------------------------------

static const Int ignore = 42;

// 在此处可定义若干辅助函数，以供定义其它函数时使用

// -----------------------------------------------------------------------------

Unsigned* unsigned_from_ll(long long x)
{
    Unsigned* ret = get_list();

    insert_front(ret, x % 10, ignore);
    while (x /= 10)
        insert_front(ret, x % 10, ignore);
    return ret;
}

Unsigned* unsigned_copy(const Unsigned* x)
{
    if (!x)
        return 0;

    Unsigned* y = get_list();
    for (Link* link = x->head; link; link = link->next)
        insert_back(y, link->n, link->x);
    return y;
}

void unsigned_free(Unsigned* x)
{
    list_free(x);
}

long long unsigned_to_ll(const Unsigned* x)
{
    long long ret = 0;
    for (Link* link = x->head; link; link = link->next) {
        ret *= 10;
        ret += link->n;
    }
    return ret;
}

int unsigned_cmp(const Unsigned* x, const Unsigned* y)
{
    // 在此处补充完整
}

Unsigned* unsigned_add(const Unsigned* x, const Unsigned* y)
{
    // 在此处补充完整
}

Unsigned* unsigned_sub(const Unsigned* x, const Unsigned* y)
{
    // 在此处补充完整
}

Unsigned* unsigned_mul(const Unsigned* x, const Unsigned* y)
{
    // 在此处补充完整
}

Unsigned* unsigned_div(const Unsigned* x, const Unsigned* y, Unsigned** rem)
{
    // 在此处补充完整
}

// -----------------------------------------------------------------------------

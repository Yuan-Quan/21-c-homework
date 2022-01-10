
#include <stdlib.h>
#include "big_int.h"

// -----------------------------------------------------------------------------

static BigInt *get_big_int(void)
{
    BigInt *bi = malloc(sizeof(BigInt));
    bi->sign = plus;
    bi->val = 0;
    return bi;
}

// 在此处可定义若干辅助函数，以供定义其它函数时使用

// -----------------------------------------------------------------------------

BigInt *big_int_from_ll(long long x)
{
    BigInt *bi = get_big_int();
    bi->sign = (x >= 0) ? plus : minus;
    bi->val = unsigned_from_ll(bi->sign * x);
    return bi;
}

BigInt *big_int_copy(const BigInt *x)
{
    if (!x)
        return 0;

    BigInt *y = get_big_int();
    y->sign = x->sign;
    y->val = unsigned_copy(x->val);
    return y;
}

void big_int_free(BigInt *bi)
{
    if (!bi)
        return;

    unsigned_free(bi->val);
    free(bi);
}

char *big_int_to_str(const BigInt *bi)
{
    if (!(bi && bi->val->size > 0))
        return 0;

    Int n = (bi->sign == minus) ? bi->val->size + 2
                                : bi->val->size + 1;

    char *ret = calloc(n, sizeof(char));
    char *p = ret;
    if (bi->sign == minus)
        *p++ = '-';

    for (Link *link = bi->val->head; link; ++p, link = link->next)
        *p = link->n + '0';
    *p = '\0';
    return ret;
}

long long big_int_to_ll(const BigInt *bi)
{
    return bi->sign * unsigned_to_ll(bi->val);
}

int big_int_cmp(const BigInt *x, const BigInt *y)
{
    // 在此处补充完整
    // positive always bigger than negative
    if (x->sign != y->sign)
    {
        if (x->sign == plus)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (x->sign == plus)
        {
            return unsigned_cmp(x->val, y->val);
        }
        else
        {
            return -1 * unsigned_cmp(x->val, y->val);
        }
    }
}

BigInt *big_int_add(const BigInt *x, const BigInt *y)
{
    // 在此处补充完整
    BigInt *result = get_big_int();
    // sign is different,
    if (x->sign != y->sign)
    {
        if (x->sign == plus)
        {
            switch (unsigned_cmp(x->val, y->val))
            {
            case 0:
            case 1:
                result->val = unsigned_sub(x->val, y->val);
                result->sign = plus;
                break;
            case -1:
                result->val = unsigned_sub(y->val, x->val);
                result->sign = minus;
                break;
            }
        }
        else
        {
            switch (unsigned_cmp(x->val, y->val))
            {
            case 0:
            case 1:
                result->val = unsigned_sub(x->val, y->val);
                result->sign = minus;
                break;
            case -1:
                result->val = unsigned_sub(y->val, x->val);
                result->sign = plus;
                break;
            }
        }
    }
    else
    {
        // if they have same sign
        result->sign = x->sign;
        result->val = unsigned_add(x->val, y->val);
    }
    return result;
}

BigInt *big_int_sub(const BigInt *x, const BigInt *y)
{
    // 在此处补充完整
    // get a copy of y
    BigInt *flipped_y = big_int_copy(y);
    // flip it
    if (flipped_y->sign == plus)
    {
        flipped_y->sign = minus;
    }
    else
    {
        flipped_y->sign = plus;
    }

    return big_int_add(x, flipped_y);
}

BigInt *big_int_mul(const BigInt *x, const BigInt *y)
{
    // 在此处补充完整
    BigInt *result = get_big_int();
    if (x->sign != y->sign)
    {
        result->sign = minus;
    }
    else
    {
        result->sign = plus;
    }

    result->val = unsigned_mul(x->val, y->val);

    return result;
}

BigInt *big_int_div(const BigInt *x, const BigInt *y, BigInt **rem)
{
    // 在此处补充完整
    BigInt *result = get_big_int();
    Unsigned *remainder = unsigned_from_ll(0);
    if (!*rem)
    {
        *rem = get_big_int();
    }

    if (x->sign != y->sign)
    {
        result->sign = minus;
    }
    else
    {
        result->sign = plus;
    }

    result->val = unsigned_div(x->val, y->val, &remainder);

    (*rem)->sign = x->sign;
    (*rem)->val = remainder;

    return result;
}

// -----------------------------------------------------------------------------

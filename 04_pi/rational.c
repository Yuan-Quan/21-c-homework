
#include <stdlib.h>
#include <string.h>
#include "rational.h"

// -----------------------------------------------------------------------------

static void unsigned_swap(Unsigned *x, Unsigned *y)
{
    Unsigned z = *x;
    *x = *y;
    *y = z;
}

static void big_int_swap(BigInt *x, BigInt *y)
{
    BigInt z = *x;
    *x = *y;
    *y = z;
}

static int unsigned_is_zero(const Unsigned *x)
{
    return x && x->size == 1 && x->head->n == 0;
}

static int big_int_is_zero(const BigInt *bi)
{
    return bi && unsigned_is_zero(bi->val);
}

// 求 x 和 y 的最大公约数。提示：使用欧几里得算法。
static Unsigned *unsigned_gcd(const Unsigned *x, const Unsigned *y)
{
    // 在此处补充完整

    // get a copy of x and y
    Unsigned *thisx = unsigned_copy(x);
    Unsigned *thisy = unsigned_copy(y);

    // Euclid's algorithm:
    Unsigned *remainder = unsigned_from_ll(0);

    while (1)
    {
        unsigned_div(thisx, thisy, &remainder);
        if (remainder->size == 0) // aka remainder is 0
        {
            break;
        }

        thisx = thisy;
        thisy = remainder;
    }
    return thisy;
}

// 以 x 作分子，y 作分母，将它们化简，即同时除以它们
// 的最大公约数。化简后分母应为正数，且若分子为 0，
// 分母应化为 1。若分母为 0，则不用化简。
static void big_int_cancel(BigInt *x, BigInt *y)
{
    // 在此处补充完整
    // make denuminator 1 if numinator is 0
    if (big_int_is_zero(x))
    {
        y = big_int_from_ll(1);
    }

    Unsigned *gcd = unsigned_gcd(x->val, y->val);

    Unsigned *dummy = unsigned_from_ll(0);
    x->val = unsigned_div(x->val, gcd, &dummy);
    y->val = unsigned_div(y->val, gcd, &dummy);

    if (x->sign == y->sign)
    {
        x->sign = plus;
        y->sign = plus;
    }
}

static BigRat *get_big_rat()
{
    BigRat *br = malloc(sizeof(BigRat));
    br->num = br->denom = 0;
    return br;
}

static int big_int_is_one(const BigInt *bi)
{
    return bi &&
           bi->sign == plus &&
           bi->val->size == 1 &&
           bi->val->head->n == 1;
}

// 在此处可定义若干辅助函数，以供定义其它函数时使用

// return the sign of bigrat, also fix sign, 1 positive, 0 zero, -1 negative
int get_big_rat_sign(const BigRat *x)
{
    if (x->num->val->size = 0)
    {
        return 0;
    }

    if (x->num->sign != x->denom->sign)
    {
        x->num->sign = minus;
        x->denom->sign = plus;
        return -1;
    }
    else
    {
        x->num->sign = plus;
        x->denom->sign = plus;
        return 1;
    }
}

// -----------------------------------------------------------------------------

BigRat *big_rat_from_ll(long long num, long long denom)
{
    BigInt *x = big_int_from_ll(num);
    BigInt *y = big_int_from_ll(denom);

    BigRat *ret = 0;

    if (!big_int_is_zero(y))
    {
        ret = get_big_rat();
        big_int_cancel(x, y);
        ret->num = x;
        ret->denom = y;
        x = y = 0;
    }

    big_int_free(x);
    big_int_free(y);
    return ret;
}

BigRat *big_rat_copy(const BigRat *x)
{
    if (!x)
        return 0;

    BigRat *y = get_big_rat();
    y->num = big_int_copy(x->num);
    y->denom = big_int_copy(x->denom);
    return y;
}

void big_rat_free(BigRat *br)
{
    if (!br)
        return;

    big_int_free(br->num);
    big_int_free(br->denom);
    free(br);
}

char *big_rat_to_str(const BigRat *br)
{
    if (!br)
        return 0;

    if (big_int_is_one(br->denom))
        return big_int_to_str(br->num);

    char *x = big_int_to_str(br->num);
    char *y = big_int_to_str(br->denom);

    char *ret = 0;
    if (x && y && (ret = malloc(strlen(x) + strlen(y) + 4)))
    {
        strcpy(ret, "(");
        strcat(ret, x);
        strcat(ret, "/");
        strcat(ret, y);
        strcat(ret, ")");
    }

    free(x);
    free(y);
    return ret;
}

void big_rat_to_ll(const BigRat *br, long long *num, long long *denom)
{
    if (!br)
        return;

    if (num)
    {
        *num = big_int_to_ll(br->num);
    }
    if (denom)
    {
        *denom = big_int_to_ll(br->denom);
    }
}

BigRat *big_rat_add(const BigRat *x, const BigRat *y)
{
    // 在此处补充完整
    BigInt *denom = big_int_mul(x->denom, y->denom);
    BigInt *nom = big_int_add(big_int_mul(x->num, y->denom), big_int_mul(y->num, x->denom));

    big_int_cancel(nom, denom);

    BigRat *result = get_big_rat();
    result->num = nom;
    result->denom = denom;
}

BigRat *big_rat_sub(const BigRat *x, const BigRat *y)
{
    // 在此处补充完整

    // get a copy of y
    BigRat *thisy = big_rat_copy(y);

    if (get_big_rat_sign(thisy) >= 0)
    {
        thisy->num->sign = minus;
    }
    else
    {
        thisy->num->sign = plus;
    }

    return big_rat_add(x, thisy);
}

BigRat *big_rat_mul(const BigRat *x, const BigRat *y)
{
    // 在此处补充完整
    BigRat *result = get_big_rat();

    BigInt *nom = big_int_mul(x->num, y->num);
    BigInt *denom = big_int_mul(x->denom, y->denom);

    big_int_cancel(nom, denom);

    result->num = nom;
    result->denom = denom;

    get_big_rat_sign(result); // to fix potential sign issue
    return result;
}

BigRat *big_rat_div(const BigRat *x, const BigRat *y)
{
    // 在此处补充完整

    // get a copy of y
    BigRat *thisy = big_rat_copy(y);

    // flip y
    BigInt *temp = big_int_from_ll(0);
    temp = thisy->denom;
    thisy->denom = thisy->num;
    thisy->num = temp;

    return big_rat_mul(x, thisy);
}

// -----------------------------------------------------------------------------

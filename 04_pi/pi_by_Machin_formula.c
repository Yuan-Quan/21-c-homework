
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rational.h"

// -----------------------------------------------------------------------------

// 精确到小数点后 1000 位的 π 值，供与自己求得的 π 值比较，
// 以确定自己所求 π 值的精度（精确到小数点后的位数）。
const char pi_string[] =
    "3."
    "14159265358979323846264338327950288419716939937510"
    "58209749445923078164062862089986280348253421170679"
    "82148086513282306647093844609550582231725359408128"
    "48111745028410270193852110555964462294895493038196"
    "44288109756659334461284756482337867831652712019091"
    "45648566923460348610454326648213393607260249141273"
    "72458700660631558817488152092096282925409171536436"
    "78925903600113305305488204665213841469519415116094"
    "33057270365759591953092186117381932611793105118548"
    "07446237996274956735188575272489122793818301194912"
    "98336733624406566430860213949463952247371907021798"
    "60943702770539217176293176752384674818467669405132"
    "00056812714526356082778577134275778960917363717872"
    "14684409012249534301465495853710507922796892589235"
    "42019956112129021960864034418159813629774771309960"
    "51870721134999999837297804995105973173281609631859"
    "50244594553469083026425223082533446850352619311881"
    "71010003137838752886587533208381420617177669147303"
    "59825349042875546873115956286388235378759375195778"
    "18577805321712268066130019278766111959092164201989";

// -----------------------------------------------------------------------------

// 在此处可定义若干辅助函数，以供定义其它函数时使用

// return the nth of arctan's Maclaurin series
BigRat *maclaurin_of_arctan(const BigRat *x, int n)
{

    BigRat *denominator = big_rat_from_ll(2 * n + 2, 1);
    BigRat *nominator = big_rat_copy(x);
    int count = 2 * n + 1;
    for (size_t i = 0; i < count; i++)
    {
        nominator = big_rat_mul(nominator, nominator);
    }

    if (n % 2 == 0)
    {
        nominator->num->sign = minus;
    }

    BigRat *result = big_rat_div(denominator, nominator);
    free(denominator);
    free(nominator);
    return result;
}

// 求 arctan(x) 的前 n 项。
BigRat *arctan(const BigRat *x, int n)
{
    // 在此处补充完整
    // Maclaurin series to get a proximation of arctan
    BigRat *result = big_rat_from_ll(0, 1);

    for (size_t i = 0; i < n; i++)
    {
        result = big_rat_add(maclaurin_of_arctan(x, i), result);
    }

    return result;
}

// 求 10 的 n 次方。
BigInt *power10(int n)
{
    static const Int ignore = 42;

    BigInt *ret = big_int_from_ll(1);
    for (int i = 0; i < n; ++i)
        insert_back(ret->val, 0, ignore);
    return ret;
}

// 使用 Machin 公式，通过求 arctan(x) 的前 items 项来求 π 值。
BigRat *get_pi(int items)
{
    // 在此处补充完整
    BigRat *result = big_rat_from_ll(0, 1);
    result = big_rat_sub(
        big_rat_mul(big_rat_from_ll(16, 1), arctan(big_rat_from_ll(1, 5), items)),
        big_rat_mul(big_rat_from_ll(4, 1), arctan(big_rat_from_ll(1, 239), items)));
    return result;
}

// 将以分数形式表示的 π 值 pi 转换为以小数形式表示。
// 提示：若 pi 是使用 Machin 公式，通过求 arctan(x)
// 的前 items 项求得的 π 值，则将其转换为小数形式后，
// 其精度不超过小数点后 2*items 位。比如，求 arctan(x)
// 的前 2 项得到的 pi 值为 5359397032/1706489875，它
// 化为小数为：3.1405970293260603143045311065792，该小数
// 形式的 π 值的精度不会超过 2*2=4 位，实际只精确到小数点
// 后两位，即 3.14。因此，在将 pi 转换为小数形式时，最多
// 只需保留小数点后 2*items 位。为了保留 pi 的小数点后
// 2*items 位，可将 pi 的分子放大“10 的 2*items 次方”倍，再
// 用分子和分母做整数除法。比如，5359397032/1706489875 的分子
// 放大 10000 倍后再除以分母（整数除法），可得 31405，其中 3 为
// 小数点前数字，1405 为小数点后数字。
char *to_str(const BigRat *pi, int items)
{
    // 在此处补充完整
    // get a copy of pi
    BigRat *p = big_rat_copy(pi);

    p->num = big_int_mul(p->num, power10(items));

    // big_int_cancel(p->num, p->denom);

    BigInt *dummy = big_int_from_ll(0);
    BigInt *result = big_int_div(p->num, p->denom, &dummy);

    Link *ptr = result->val->head;

    char *buffer[2048];

    for (size_t i = 0; i < 2048; i++)
    {
        buffer[i] = "\0";
    }

    int i = 0;
    while (ptr)
    {
        if (i == 1)
        {
            *buffer[i] = '.';
            continue;
        }

        *buffer[i] = ptr->n + '0';
        ptr = ptr->next;
    }

    return *buffer;
}

// -----------------------------------------------------------------------------

int main(void)
{
    // 在此处补充完整
    int items = 40;
    int digits = 2 * items;
    char *buf[512];
    for (size_t i = 0; i < 512; i++)
    {
        buf[i] = '\0';
    }
    for (size_t i = 0; i < digits; i++)
    {
        // *buf[i] = *pi_string[i];
    }

<<<<<<< HEAD
    BigRat *pi = get_pi(items);
    BigRat *pi = big_rat_from_ll(5359397032, 1706489875);
    // printf("calculated= %s\n", big_rat_to_str(pi));
    printf("pi=%s\n", to_str(pi, items));
=======
    //    BigRat *pi = get_pi(items);
    BigRat *pi = big_rat_from_ll(5359397032, 1706489875);
    // printf("calculated= %s\n", big_rat_to_str(pi));
    //  printf("pi=%s\n", to_str(pi, items));
    printf("pi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089\n");
>>>>>>> 337c7052b5b5f84177c56a136bee1de0967de381
    printf("ground truth=%s", pi_string);
    getchar();
    return 0;
}

// -----------------------------------------------------------------------------

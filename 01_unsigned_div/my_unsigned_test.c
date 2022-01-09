
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "unsigned.h"

int main(int argc, char const *argv[])
{
    Unsigned *ret = get_list();
    insert_back(ret, 1, 2);  // 3
    insert_back(ret, 5, 6);  // 4
    insert_front(ret, 2, 3); // 1
    remove_front(ret);

    Unsigned *cmp1 = get_list();
    Unsigned *cmp2 = get_list();
    insert_front(cmp1, 3, 4); // 2
    insert_front(cmp1, 3, 4); // 2
    insert_front(cmp2, 4, 4); // 2
    insert_front(cmp2, 3, 4); // 2
    int x = unsigned_cmp(cmp1, cmp2);

    Unsigned *ad1 = unsigned_from_ll(12345);
    Unsigned *ad2 = unsigned_from_ll(233);

    Unsigned **remainder;
    Unsigned *r1 = unsigned_div(ad1, ad2, remainder);

    return 0;
}

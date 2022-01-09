
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "unsigned.h"

int main(int argc, char const *argv[])
{
    Unsigned *ret = get_list();
    insert_back(ret, 1, 2);  // 3
    insert_front(ret, 3, 4); // 2
    insert_back(ret, 5, 6);  // 4
    insert_front(ret, 2, 3); // 1
    remove_front(ret);
    return 0;
}

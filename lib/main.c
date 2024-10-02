#include "strings.h"

int main(void) {

    String s1;
    String s2;
    strings_init(&s1);
    strings_init(&s2);

    strings_set(&s1, "hello", strlen("hello"));
    strings_set(&s2, "hello", strlen("hello"));

    strings_concatanate(&s1, &s2);

    strings_print(&s1);

    return 0;
}





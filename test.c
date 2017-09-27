#include <stdio.h>
#include <stdlib.h>
#include "ternary.h"

int main(int argc, char *argv[])
{
    tint6 *t_1 = getTernaryInt(-1);
    tint6 *t_2 = getTernaryInt(2);
    tint6 carry = { .val = T_UNKNOWN };
    /* t_1->val = 0x0FFE; // 0000111111111110 -> - -> -1 */
    /* t_2->val = 0x0FF6; // 0000111111110110 -> +- -> 2 */

    tint6 *tsum = sum(t_1, t_2, &carry);

    printf("t_1 val: %d\n", toBinary(t_1));
    printf("t_2 val: %d\n", toBinary(t_2));
    printf("sum: %d\n", toBinary(tsum));

    free(t_1);
    free(t_2);
    return 0;
}

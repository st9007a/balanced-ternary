#include <stdio.h>
#include <stdlib.h>

#include "ternary.h"

#define T_FALSE 2
#define T_UNKNOWN 3
#define T_TRUE 1

static int t2b[3] = { 1, -1, 0 };

t_int6 *getTernaryInt(int num)
{
    if (num > 364 || num < -364) {
        printf("%d is out of range.\n", num);
        return NULL;
    }
    return NULL;
}

short toBinary(t_int6 *tint)
{
    short sum = 0;
    short exp = 1;
    unsigned short val = tint->val;
    for (int i = 0; i < 6; i++) {
        sum += t2b[(val & 3) - 1] * exp;
        exp *= 3;
        val >>= 2;
    }

    return sum;
}

/* inline void AND(trit *a, trit *b, trit *out) { */
/*     out->val = (a->val & b->val & 1) | (a->val | b->val & 2); */
/* } */
/* inline void OR(trit *a, trit *b, trit *out) { */
/*     out->val = (a->val | b->val & 1) | (a->val & b->val & 2); */
/* } */
/* inline void DECODE_FALSE(trit *num, trit *out) { */
/*     out->val = num->val << 1 | ~(num->val & 1); */
/* } */
/* inline void DECODE_TRUE(trit *num, trit *out) { */
/*     out->val = num->val & 2 | ~(num->val >> 1); */
/* } */
/* inline void DECODE_UNKNOWN(trit *num, trit *out) { */
/*     out->val = num->val & num->val >> 1 | (~(num->val & num->val >> 1)) << 1; */
/* } */

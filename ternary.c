#include <stdio.h>
#include <stdlib.h>

#include "ternary.h"


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

inline u_int16 AND(u_int16 a, u_int16 b)
{
    return (a & b & 1) | ((a | b) & 2);
}
inline u_int16 OR(u_int16 a, u_int16 b)
{
    return ((a | b) & 1) | (a & b & 2);
}
inline u_int16 NOT(u_int16 num)
{
    return (~num | num >> 1) | (num | ~num >> 1) << 1;
}
inline u_int16 DECODE_FALSE(u_int16 num)
{
    return (num << 1) | (~num & 1);
}
inline u_int16 DECODE_TRUE(u_int16 num)
{
    return (num & 2) | ((~num & 2) >> 1);
}
inline u_int16 DECODE_UNKNOWN(u_int16 num)
{
    return (~(num & ((num >> 1) & 1)) << 1) | (num & ((num >> 1) & 1));
}
u_int16 MUX(u_int16 inN, u_int16 inO, u_int16 inP, u_int16 sel)
{
    u_int16 f = AND(inN, DECODE_FALSE(sel));
    u_int16 u = AND(inO, DECODE_UNKNOWN(sel));
    u_int16 t = AND(inP, DECODE_TRUE(sel));
    return OR(f, OR(u, t));
}

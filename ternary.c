#include <stdio.h>
#include <stdlib.h>

#include "ternary.h"


static int t2b[3] = { 1, -1, 0 };

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
    return ((~num & 3) | num >> 1) | (num | (~num & 3)>> 1) << 1;
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

u_int16 multiplexer(u_int16 inN, u_int16 inO, u_int16 inP, u_int16 sel)
{
    u_int16 f = AND(inN, DECODE_FALSE(sel));
    u_int16 u = AND(inO, DECODE_UNKNOWN(sel));
    u_int16 t = AND(inP, DECODE_TRUE(sel));
    return OR(f, OR(u, t));
}

u_int16 halfAdder(u_int16 a, u_int16 b)
{
    u_int16 pinN = multiplexer(T_TRUE, T_FALSE, T_UNKNOWN, a);
    u_int16 pinP = multiplexer(T_UNKNOWN, T_TRUE, T_FALSE, a);
    return multiplexer(pinN, a, pinP, b);
}

u_int16 consensus(u_int16 a, u_int16 b)
{
    u_int16 pinN = multiplexer(T_FALSE, T_UNKNOWN, T_UNKNOWN, a);
    u_int16 pinP = multiplexer(T_UNKNOWN, T_UNKNOWN, T_TRUE, a);
    return multiplexer(pinN, T_UNKNOWN, pinP, b);
}

u_int16 fullAdder(u_int16 a, u_int16 b, u_int16 cin)
{
    return halfAdder(halfAdder(a, b), cin);
}

u_int16 checkOverflow(u_int16 a, u_int16 b, u_int16 cin)
{
    u_int16 maxCompZero = multiplexer(T_UNKNOWN, T_UNKNOWN, T_TRUE, a);
    u_int16 minCompZero = multiplexer(T_FALSE, T_UNKNOWN, T_UNKNOWN, a);
    u_int16 maxCompZeroSubOne = multiplexer(T_FALSE, T_FALSE, T_UNKNOWN, a);
    u_int16 minCompZeroAddOne = multiplexer(T_UNKNOWN, T_TRUE, T_TRUE, a);

    u_int16 pinN = multiplexer(maxCompZeroSubOne, minCompZero, T_UNKNOWN, b);
    u_int16 pinO = multiplexer(minCompZero, T_UNKNOWN, maxCompZero, b);
    u_int16 pinP = multiplexer(T_UNKNOWN, maxCompZero, minCompZeroAddOne, b);

    return multiplexer(pinN, pinO, pinP, cin);
}

t_int6 *sum(t_int6 *a, t_int6 *b, t_int6 *carry)
{
    t_int6 *sum = (t_int6 *) malloc(sizeof(t_int6));
    carry->val = T_UNKNOWN;
    sum->val = 0;

    for (int i = 0; i < 12; i += 2) {
        u_int16 tritA = (a->val & (3 << i)) >> i;
        u_int16 tritB = (b->val & (3 << i)) >> i;
        sum->val |= fullAdder(tritA, tritB, carry->val) << i;
        carry->val = checkOverflow(tritA, tritB, carry->val);
    }

    return sum;
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

t_int6 *getTernaryInt(int num)
{
    if (num > 364 || num < -364) {
        printf("%d is out of range.\n", num);
        return NULL;
    }

    int inv = 1;
    if (num < 0)
        num *= inv = -1;

    int step = 0;
    t_int6 *tnum = (t_int6 *) malloc(sizeof(t_int6));
    tnum->val = 0;
    do {
        u_int16 digit = num % 3;
        if (digit == 2) {
            digit = T_FALSE;
            ++num;
        }
        if (digit == 0) {
            digit = T_UNKNOWN;
        }
        if (inv == -1) {
            digit = NOT(digit);
        }

        tnum->val |= (digit & 3) << step;
        step += 2;
        num = ~~(num / 3);
    } while(num);

    tnum-> val |= 255 << step;
    return tnum;
}


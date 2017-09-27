#include <stdio.h>
#include <stdlib.h>

#include "ternary.h"


static int t2b[3] = { 1, -1, 0 };

inline uint16_t AND(uint16_t a, uint16_t b)
{
    return (a & b & 1) | ((a | b) & 2);
}
inline uint16_t OR(uint16_t a, uint16_t b)
{
    return ((a | b) & 1) | (a & b & 2);
}
inline uint16_t NOT(uint16_t num)
{
    return ((~num & 3) | num >> 1) | (num | (~num & 3)>> 1) << 1;
}
inline uint16_t DECODE_FALSE(uint16_t num)
{
    return (num << 1) | (~num & 1);
}
inline uint16_t DECODE_TRUE(uint16_t num)
{
    return (num & 2) | ((~num & 2) >> 1);
}
inline uint16_t DECODE_UNKNOWN(uint16_t num)
{
    return (~(num & ((num >> 1) & 1)) << 1) | (num & ((num >> 1) & 1));
}

uint16_t multiplexer(uint16_t inN, uint16_t inO, uint16_t inP, uint16_t sel)
{
    uint16_t f = AND(inN, DECODE_FALSE(sel));
    uint16_t u = AND(inO, DECODE_UNKNOWN(sel));
    uint16_t t = AND(inP, DECODE_TRUE(sel));
    return OR(f, OR(u, t));
}

uint16_t halfAdder(uint16_t a, uint16_t b)
{
    uint16_t pinN = multiplexer(T_TRUE, T_FALSE, T_UNKNOWN, a);
    uint16_t pinP = multiplexer(T_UNKNOWN, T_TRUE, T_FALSE, a);
    return multiplexer(pinN, a, pinP, b);
}

uint16_t consensus(uint16_t a, uint16_t b)
{
    uint16_t pinN = multiplexer(T_FALSE, T_UNKNOWN, T_UNKNOWN, a);
    uint16_t pinP = multiplexer(T_UNKNOWN, T_UNKNOWN, T_TRUE, a);
    return multiplexer(pinN, T_UNKNOWN, pinP, b);
}

uint16_t fullAdder(uint16_t a, uint16_t b, uint16_t cin)
{
    return halfAdder(halfAdder(a, b), cin);
}

uint16_t checkOverflow(uint16_t a, uint16_t b, uint16_t cin)
{
    uint16_t maxCompZero = multiplexer(T_UNKNOWN, T_UNKNOWN, T_TRUE, a);
    uint16_t minCompZero = multiplexer(T_FALSE, T_UNKNOWN, T_UNKNOWN, a);
    uint16_t maxCompZeroSubOne = multiplexer(T_FALSE, T_FALSE, T_UNKNOWN, a);
    uint16_t minCompZeroAddOne = multiplexer(T_UNKNOWN, T_TRUE, T_TRUE, a);

    uint16_t pinN = multiplexer(maxCompZeroSubOne, minCompZero, T_UNKNOWN, b);
    uint16_t pinO = multiplexer(minCompZero, T_UNKNOWN, maxCompZero, b);
    uint16_t pinP = multiplexer(T_UNKNOWN, maxCompZero, minCompZeroAddOne, b);

    return multiplexer(pinN, pinO, pinP, cin);
}

tint6 *sum(tint6 *a, tint6 *b, tint6 *carry)
{
    tint6 *sum = (tint6 *) malloc(sizeof(tint6));
    carry->val = T_UNKNOWN;
    sum->val = 0;

    for (int i = 0; i < 12; i += 2) {
        uint16_t tritA = (a->val & (3 << i)) >> i;
        uint16_t tritB = (b->val & (3 << i)) >> i;
        sum->val |= fullAdder(tritA, tritB, carry->val) << i;
        carry->val = checkOverflow(tritA, tritB, carry->val);
    }

    return sum;
}

short toBinary(tint6 *tnum)
{
    short sum = 0;
    short exp = 1;
    unsigned short val = tnum->val;
    for (int i = 0; i < 6; i++) {
        sum += t2b[(val & 3) - 1] * exp;
        exp *= 3;
        val >>= 2;
    }

    return sum;
}

tint6 *getTernaryInt(int num)
{
    if (num > 364 || num < -364) {
        printf("%d is out of range.\n", num);
        return NULL;
    }

    int inv = 1;
    if (num < 0)
        num *= inv = -1;

    int step = 0;
    tint6 *tnum = (tint6 *) malloc(sizeof(tint6));
    tnum->val = 0;
    do {
        uint16_t digit = num % 3;
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


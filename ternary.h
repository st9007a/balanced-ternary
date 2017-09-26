#ifndef _TERNARY_H
#define _TERNARY_H

#define T_FALSE 2
#define T_UNKNOWN 3
#define T_TRUE 1

typedef struct __TRIT {
    unsigned char val:2;
} trit;

typedef struct __TERNARY_INT {
    unsigned short val:12;
} t_int6;

t_int6 *getTernaryInt(int num);
short toBinary(t_int6 *tint);
void AND(trit *a, trit *b, trit *out);
void OR(trit *a, trit *b, trit *out);
void DECODE_FALSE(trit *num, trit *out);
void DECODE_TRUE(trit *num, trit *out);
void DECODE_UNKNOWN(trit *num, trit *out);
#endif

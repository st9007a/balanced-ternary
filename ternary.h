#ifndef _TERNARY_H
#define _TERNARY_H

typedef struct __TRIT {
    unsigned char val:2;
} trit;

typedef struct __TERNARY_INT {
    unsigned short val:12;
} t_int6;

t_int6 *getTernaryInt(int num);
short toBinary(t_int6 *tint);
// inline void AND(trit *a, trit *b, trir *out);
// inline void OR(trit *a, trit *b, trir *out);
// inline void DECODE_FALSE(trit *num, trit *out);
// inline void DECODE_TRUE(trit *num, trit *out);
// inline void DECODE_UNKNOWN(trir *num, trit *out);
#endif

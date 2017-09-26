#ifndef _TERNARY_H
#define _TERNARY_H

#define T_FALSE 2
#define T_UNKNOWN 3
#define T_TRUE 1

typedef struct __TERNARY_INT {
    unsigned short val:12;
} t_int6;

typedef unsigned short u_int16;

t_int6 *getTernaryInt(int num);
short toBinary(t_int6 *tint);
u_int16 AND(u_int16 a,u_int16 b);
u_int16 OR(u_int16 a, u_int16 b);
u_int16 NOT(u_int16 num);
u_int16 DECODE_FALSE(u_int16 num);
u_int16 DECODE_TRUE(u_int16 num);
u_int16 DECODE_UNKNOWN(u_int16 num);
u_int16 MUX(u_int16 inN, u_int16 inO, u_int16 inP, u_int16 sel);
#endif

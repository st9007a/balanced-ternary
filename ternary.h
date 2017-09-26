#ifndef _TERNARY_H
#define _TERNARY_H

#define T_FALSE 2
#define T_UNKNOWN 3
#define T_TRUE 1

typedef struct __TERNARY_INT {
    unsigned short val:12;
} t_int6;

typedef unsigned short u_int16;


u_int16 AND(u_int16 a,u_int16 b);
u_int16 OR(u_int16 a, u_int16 b);
u_int16 NOT(u_int16 num);
u_int16 DECODE_FALSE(u_int16 num);
u_int16 DECODE_TRUE(u_int16 num);
u_int16 DECODE_UNKNOWN(u_int16 num);

u_int16 multiplexer(u_int16 inN, u_int16 inO, u_int16 inP, u_int16 sel);
u_int16 halfAdder(u_int16 a, u_int16 b);
u_int16 consensus(u_int16 a, u_int16 b);
u_int16 fullAdder(u_int16 a, u_int16 b, u_int16 cin);
u_int16 checkOverflow(u_int16 a, u_int16 b, u_int16 cin);

t_int6 *getTernaryInt(int num);
short toBinary(t_int6 *tint);
t_int6 *sum(t_int6 *a, t_int6 *b, t_int6 *carry);
#endif

#ifndef _TERNARY_H
#define _TERNARY_H

#define T_FALSE 2
#define T_UNKNOWN 3
#define T_TRUE 1

#include <stdint.h>

typedef struct __TERNARY_INT {
    uint16_t val:12;
} tint6;

uint16_t AND(uint16_t a,uint16_t b);
uint16_t OR(uint16_t a, uint16_t b);
uint16_t NOT(uint16_t num);
uint16_t DECODE_FALSE(uint16_t num);
uint16_t DECODE_TRUE(uint16_t num);
uint16_t DECODE_UNKNOWN(uint16_t num);

uint16_t multiplexer(uint16_t inN, uint16_t inO, uint16_t inP, uint16_t sel);
uint16_t halfAdder(uint16_t a, uint16_t b);
uint16_t consensus(uint16_t a, uint16_t b);
uint16_t fullAdder(uint16_t a, uint16_t b, uint16_t cin);
uint16_t checkOverflow(uint16_t a, uint16_t b, uint16_t cin);

tint6 *getTernaryInt(int num);
short toBinary(tint6 *tint);
tint6 *sum(tint6 *a, tint6 *b, tint6 *carry);
#endif

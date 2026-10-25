#ifndef GF_H
#define GF_H

/* Nhan trong GF(2^4), modulo m(x) = x^4 + x + 1 (0x13). */
unsigned int nhan_gf2_4(unsigned int a, unsigned int b);

/* Nhan trong GF(2^8), modulo m(x) = x^8 + x^4 + x^3 + x + 1 (0x11B). */
unsigned int nhan_gf2_8(unsigned int a, unsigned int b);

#endif

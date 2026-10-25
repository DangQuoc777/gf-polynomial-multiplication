#include "gf.h"

/* Phep cong trong GF(2) la XOR: 1 + 1 = 0. */
unsigned int nhan_gf2_4(unsigned int a, unsigned int b)
{
    unsigned int kq = 0;
    a &= 0x0FU;
    b &= 0x0FU;

    for (unsigned int i = 0; i < 4; ++i) {
        if (b & 1U) {
            kq ^= a;
        }

        a <<= 1;              /* Nhan a voi x. */
        if (a & 0x10U) {      /* Co he so cua x^4. */
            a ^= 0x13U;       /* Lay du theo m(x) = 0x13. */
        }
        b >>= 1;
    }

    return kq & 0x0FU;
}

unsigned int nhan_gf2_8(unsigned int a, unsigned int b)
{
    unsigned int kq = 0;
    a &= 0xFFU;
    b &= 0xFFU;

    for (unsigned int i = 0; i < 8; ++i) {
        if (b & 1U) {
            kq ^= a;
        }

        a <<= 1;              /* Nhan a voi x. */
        if (a & 0x100U) {     /* Co he so cua x^8. */
            a ^= 0x11BU;      /* Lay du theo m(x) = 0x11B. */
        }
        b >>= 1;
    }

    return kq & 0xFFU;
}

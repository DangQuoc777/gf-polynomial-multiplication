#include <stdio.h>
#include "../gf.h"

/* Kiem tra doc lap: nhan da thuc thong thuong, sau do chia lay du. */
static unsigned int nhan_tham_chieu(unsigned int a, unsigned int b,
                                    unsigned int bac, unsigned int m)
{
    unsigned int tich = 0;
    unsigned int mask = (1U << bac) - 1U;
    a &= mask;
    b &= mask;

    for (unsigned int i = 0; i < bac; ++i) {
        if ((b >> i) & 1U) {
            tich ^= (a << i);
        }
    }
    for (int i = (int)(2U * bac - 2U); i >= (int)bac; --i) {
        if ((tich >> i) & 1U) {
            tich ^= (m << (i - (int)bac));
        }
    }
    return tich & mask;
}

int main(void)
{
    unsigned int dem = 0;

    if (nhan_gf2_4(0xBU, 0x7U) != 0x4U ||
        nhan_gf2_8(0x57U, 0x83U) != 0xC1U) {
        fputs("Sai ket qua vi du mau.\n", stderr);
        return 1;
    }

    for (unsigned int a = 0; a < 16; ++a) {
        for (unsigned int b = 0; b < 16; ++b) {
            unsigned int got = nhan_gf2_4(a, b);
            unsigned int expected = nhan_tham_chieu(a, b, 4, 0x13U);
            if (got != expected) {
                fprintf(stderr, "GF(2^4) sai voi a=%X, b=%X: %X != %X\n",
                        a, b, got, expected);
                return 1;
            }
            ++dem;
        }
    }

    for (unsigned int a = 0; a < 256; ++a) {
        for (unsigned int b = 0; b < 256; ++b) {
            unsigned int got = nhan_gf2_8(a, b);
            unsigned int expected = nhan_tham_chieu(a, b, 8, 0x11BU);
            if (got != expected) {
                fprintf(stderr, "GF(2^8) sai voi a=%X, b=%X: %X != %X\n",
                        a, b, got, expected);
                return 1;
            }
            ++dem;
        }
    }

    printf("PASS: %u phep nhan (256 GF(2^4) + 65536 GF(2^8)).\n", dem);
    return 0;
}

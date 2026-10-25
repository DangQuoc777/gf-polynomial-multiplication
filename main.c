#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "gf.h"

/* Doc so he 16, chi chap nhan gia tri trong [0, max]. */
static int nhap_hex(const char *loi_nhac, unsigned int max, unsigned int *gia_tri)
{
    char dong[128];
    char *cuoi;
    char *dau;
    unsigned long so;

    printf("%s", loi_nhac);
    if (!fgets(dong, sizeof(dong), stdin)) {
        return 0;
    }

    dau = dong;
    while (isspace((unsigned char)*dau)) {
        ++dau;
    }
    if (*dau == '-' || *dau == '+') {
        return 0;
    }

    errno = 0;
    so = strtoul(dau, &cuoi, 16);
    if (dau == cuoi || errno != 0) {
        return 0;
    }
    while (isspace((unsigned char)*cuoi)) {
        ++cuoi;
    }
    if (*cuoi != '\0' || so > max) {
        return 0;
    }

    *gia_tri = (unsigned int)so;
    return 1;
}

int main(void)
{
    unsigned int a4, b4, a8, b8;

    puts("=== NHAN HAI DA THUC TRONG GF(2^4) ===");
    puts("Da thuc toi gian: m(x) = x^4 + x + 1 (0x13)");
    if (!nhap_hex("Nhap A (hex, 0..F; vi du B): ", 0xFU, &a4) ||
        !nhap_hex("Nhap B (hex, 0..F; vi du 7): ", 0xFU, &b4)) {
        fputs("Loi: gia tri GF(2^4) phai la so hex tu 0 den F.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Ket qua: 0x%X * 0x%X = 0x%X\n\n", a4, b4,
           nhan_gf2_4(a4, b4));

    puts("=== NHAN HAI DA THUC TRONG GF(2^8) ===");
    puts("Da thuc toi gian: m(x) = x^8 + x^4 + x^3 + x + 1 (0x11B)");
    if (!nhap_hex("Nhap A (hex, 00..FF; vi du 57): ", 0xFFU, &a8) ||
        !nhap_hex("Nhap B (hex, 00..FF; vi du 83): ", 0xFFU, &b8)) {
        fputs("Loi: gia tri GF(2^8) phai la so hex tu 00 den FF.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Ket qua: 0x%02X * 0x%02X = 0x%02X\n", a8, b8,
           nhan_gf2_8(a8, b8));

    return EXIT_SUCCESS;
}

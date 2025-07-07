#include "util.h"
#include <stddef.h> // ou #include <stdio.h>
#include <ctype.h>

// Implementa busca sem diferenciar maiúsculas e minúsculas
char *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle)
        return NULL;

    // Percorre cada caractere de 'haystack'
    for (; *haystack; haystack++) {
        // Compara caractere atual com o início de 'needle' (sem distinguir maiúsculas)
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack, *n = needle;
            while (*h && *n &&
                   (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
                h++;
                n++;
            }
            if (!*n)
                return (char *)haystack;
        }
    }
    return NULL;
}

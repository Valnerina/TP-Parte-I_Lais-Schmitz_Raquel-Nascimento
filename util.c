#include "util.h"
#include <stddef.h> // ou #include <stdio.h>
#include <ctype.h>

char *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle)
        return NULL;

    for (; *haystack; haystack++) {
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

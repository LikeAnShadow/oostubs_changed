#include "object/uint_templates.h"

int atoi(char* str){
    int res = 0;

    for (char *buf = str; *buf != '\0'; buf++) res = res * 10 + *buf - '0';
    return res;
}
uint32_t atoui(char* str){
    uint32_t res = 0;

    for (char *buf = str; *buf != '\0'; buf++) res = res * 10 + *buf - '0';
    return res;
}
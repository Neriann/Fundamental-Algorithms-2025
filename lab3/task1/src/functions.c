#include "functions.h"

#include <stdbool.h>
#include <string.h>

void increment(uint64_t* result) {
    *result = add(*result, 1);
}

void decrement(uint64_t* result) {
    *result = sub(*result, 1);
}

uint64_t add(uint64_t a, uint64_t b) {
    while (b) {
        uint64_t rem = a & b;
        a = a ^ b;
        b = rem << 1;
    }
    return a;
}

uint64_t sub(uint64_t a, uint64_t b) {
    return add(a, add(~b, 1)); // Чтобы получить отрицательное число переводим в доп. код
}

uint64_t remainder(uint64_t a, uint64_t b) {
    return a & sub(b, 1);
}

// деление, где b = 2^n
uint64_t div(uint64_t a, uint64_t b) {
    if (b == 0) return UINT64_MAX;

    while (b != 1) {
        a >>= 1;
        b >>= 1;
    }
    return a;
}

uint64_t builtin_count(uint64_t num) {
    uint64_t count = 0;
    uint64_t val = 1;
    while (val <= num) {
        // если есть 1, то повышаем счетчик
        if (num & val) {
            increment(&count);
        }
        // иначе двигаем бит числа
        val <<= 1;
    }
    return count;
}

Code to_power_of_two_system(char** result, size_t* result_size, char* buff, size_t buff_size, int64_t num, int64_t base) {
    if (!buff || !buff_size)
        return INVALID_ARG;

    if (base < 2 || base > 36)
        return INVALID_BASE;

    uint64_t bit_count = builtin_count(base);
    if (bit_count != 1)
        return INVALID_BASE;

    if (num == 0) {
        if (buff_size < 2) return OUT_OF_RANGE;
        buff[0] = '0';
        buff[1] = 0;
        *result = buff;
        *result_size = strlen(buff);
        return SUCCESS;
    }

    bool negative = 0;
    if (num < 0) {
        negative = 1;
        num = ~sub(num, 1);
    }

    // смещение указателя на конце массива
    uint64_t shift = sub(buff_size, 1);
    /* кастуем указатель на char* к числу uint64_t - адресу и изменяем адрес на определенное количество байт */
    char* p = (char*)add((uint64_t)buff, shift);
    *p = 0;
    /* кастуем указатель на char* в указатель на uint64_t*,
         то есть по факту в декременте уменьшаем число - адрес на 1 байт */
    decrement((uint64_t*)&p);
    while (num) {
        if (p < buff)
            return OUT_OF_RANGE;
        uint64_t rem = remainder(num, base);
        *p = rem > 9 ? (char)add('A', sub(rem, 10)) : (char)add('0', rem);
        decrement((uint64_t*)&p);
        num = div(num, base);
    }
    if (negative) {
        if (p < buff) return OUT_OF_RANGE;
        *p = '-';
        decrement((uint64_t*)&p);
    }
    *result = (char*)add((uint64_t)p, 1);
    *result_size = strlen(*result);
    return SUCCESS;
}

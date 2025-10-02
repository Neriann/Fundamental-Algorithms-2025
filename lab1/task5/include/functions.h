#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LEN 50
#define BUFFER_SIZE 1024

#define IS_FLAG(a, b) strcmp(a, b) == 0

char* remove_arabic_digits(const char* buff, char* res);

char* count_latin_letters(const char* buff, char* res);

char* count_rare_symbols(const char* buff, char* res);

char* replace_except_digits(const char* buff, char* res);

#endif //FUNCTIONS_H

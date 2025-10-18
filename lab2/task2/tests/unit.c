#include "functions.h"
#include "assert_base.h"

void test_strlen() {
    printf("[...] test_strlen()\n");
    int a = my_strlen("Hello World");
    ASSERT_MSG(a == 11)

    a = my_strlen("");
    ASSERT_MSG(a == 0)
}

void test_strncmp() {
    printf("[...] test_my_strncmp()\n");
    int a = my_strncmp("Hello", "Hello World", 11);
    ASSERT_MSG(a == -1)

    a = my_strncmp("Hello", "Hello", 100);
    ASSERT_MSG(a == 0);

    a = my_strncmp("", "", 100);
    ASSERT_MSG(a == 0);

    a = my_strncmp("B", "A", 100);
    ASSERT_MSG(a == 1);

    a = my_strncmp("Hello", "Hello ", 100);
    ASSERT_MSG(a == -1);
}

void test_memchr() {
    printf("[...] test_memchr()\n");
    char* str = "Hello World";
    char* res = my_memchr(str, 'W', my_strlen(str));
    ASSERT_MSG(my_strncmp(res, "World", 5) == 0)

    res = my_memchr(str, '1', my_strlen(str));
    ASSERT_MSG(res == NULL)

    str = "";
    res = my_memchr(str, 'w', my_strlen(str));
    ASSERT_MSG(res == NULL);
}

void test_memcmp() {
    printf("[...] test_memcmp()\n");
    int a = my_memcmp("Hello", "Hello World", 11);
    ASSERT_MSG(a == -1)

    a = my_memcmp("Hello", "Hello World", 5);

    ASSERT_MSG(a == 0)

    int arr1[] = {-1, 2, 3};
    int arr2[] = {1, 2, 3};

    a = my_memcmp(arr1, arr2, 3 * sizeof(int));
    ASSERT_MSG(a == 1)
}

void test_memcpy() {
    printf("[...] test_memcpy()\n");
    char str[100];
    char* res = my_memcpy(str, "Hello World", 11);
    ASSERT_MSG(my_strncmp(res, "Hello World", 11) == 0)

    int arr1[3] = {1, 2, 3};
    int arr2[3];
    my_memcpy(arr2, arr1, 3 * sizeof(int));
    ASSERT_MSG(my_memcmp(arr2, arr1, 3 * sizeof(int)) == 0);
}


void test_memset() {
    printf("[...] test_memset()\n");
    char str[6];
    char* res = my_memset(str, 'a', 5);
    str[5] = 0;
    ASSERT_MSG(my_strncmp(res, "aaaaa", 5) == 0)

    // Тесты для Little Endian
    int32_t a = 0;
    my_memset(&a, 1, sizeof(int32_t));
    int32_t b = (1 << 0) | (1 << 8) | (1 << 16) | (1 << 24);
    ASSERT_MSG(a == b)

    int32_t arr1[3] = {1, 2, 3};
    int32_t arr2[3] = {16843009, 16843009, 16843009};
    my_memset(arr1, 1, 3 * sizeof(int32_t));

    ASSERT_MSG(my_memcmp(arr1, arr2, 3 * sizeof(int32_t)) == 0);

    a = 0;
    my_memset(&a, 1, 1);
    ASSERT_MSG(a == 1 << 0)

    a = 0;
    my_memset((char*)&a + 3, 1, 1);
    ASSERT_MSG(a == 1 << 24)

}

void test_strncat() {
    printf("[...] test_strncat()\n");
    char str[100] = "Hello ";
    char* res = my_strncat(str, "World", 5);
    ASSERT_MSG(my_strncmp(res, "Hello World", 11) == 0);

    res = my_strncat(str, "!", 0);
    ASSERT_MSG(my_strncmp(res, "Hello World", 11) == 0);

    res = my_strncat(str, "!", 100);
    ASSERT_MSG(my_strncmp(res, "Hello World!", 12) == 0);
}

void test_strchf() {
    printf("[...] test_my_strchf()\n");
    char* str = "Hello World";
    char* res = my_strchf(str, 'o');
    ASSERT_MSG(my_strncmp(res, "o World", 100) == 0)
}

void test_strcpy() {
    printf("[...] test_strcpy()\n");
    char str[100];
    char* res = my_strncpy(str, "Hello World", 1);
    ASSERT_MSG(my_strncmp(res, "H", 11) == 0)

    res = my_strncpy(str, "Hello World", 100);
    ASSERT_MSG(my_strncmp(res, "Hello World", 100) == 0)
}

void test_strcspn() {
    printf("[...] test_strcspn()\n");
    size_t len = my_strcspn("Hello", "ogol");
    ASSERT_MSG(len == 2)

    len = my_strcspn("abcde", "a");
    ASSERT_MSG(len == 0)

    len = my_strcspn("123", "456");
    ASSERT_MSG(len == 3)
}

void test_strpbrk() {
    printf("[...] test_strpbrk()\n");
    char* res = my_strpbrk("abcd", "dfgh");
    ASSERT_MSG(my_strncmp(res, "d", 100) == 0)

    res = my_strpbrk("123", "fjaja1if95bn");
    ASSERT_MSG(my_strncmp(res, "123", 100) == 0)

    res = my_strpbrk("123", "jgkajgagurieuvn");
    ASSERT_MSG(res == NULL)
}

void test_strchl() {
    printf("[...] test_my_strchl()\n");
    char* str = "Hello World";
    char* res = my_strchl(str, 'o');
    ASSERT_MSG(my_strncmp(res, "orld", 100) == 0)
}

void test_strstr() {
    printf("[...] test_strstr()\n");
    char* str = "ababa";
    char* res = my_strstr(str, "bab");
    ASSERT_MSG(my_strncmp(res, "baba", 100) == 0)

    str = "12aa52aa3gja 52 opop";
    res = my_strstr(str, "52");
    ASSERT_MSG(my_strncmp(res, "52aa3gja 52 opop", 100) == 0)

    str = "gkjqgbn nwjaqign jnqbjnbjq";
    res = my_strstr(str, "ooo");
    ASSERT_MSG(res == NULL);
}

void test_strtok() {
    printf("[...] test_strtok()\n");
    char str[] = "hello, world, from, this, example";
    char* res = my_strtok(str, " ,");

    char* answer1[] = {"hello", "world", "from", "this", "example"};
    size_t i = 0;
    while (res != NULL) {
        ASSERT_MSG(my_strncmp(res, answer1[i++], 100) == 0)
        res = my_strtok(NULL, " ,");
    }

    res = my_strtok(NULL, " ,");
    ASSERT_MSG(res == NULL);

    res = my_strtok(str, ",o ");
    char* answer2[] = {"hell", "w", "rld", "fr", "m", "this", "example"};
    i = 0;
    while (res != NULL) {
        ASSERT_MSG(my_strncmp(res, answer2[i++], 100) == 0)
        res = my_strtok(NULL, ",o ");
    }
}

void test_strerror() {
    printf("[...] test_strerror()\n");

    ASSERT_MSG(my_strncmp(my_strerror(0), "Success", 100) == 0)

    char* res = NULL;
#ifdef __linux__
    res = "No such device or address";
#elif __APPLE__
    res = "Device not configured"
#endif

    ASSERT_MSG(my_strncmp(my_strerror(6), res, 100) == 0)
}

void run_all_tests() {
    test_strlen();
    test_strncmp();
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strncat();
    test_strchf();
    test_strcpy();
    test_strcspn();
    test_strpbrk();
    test_strchl();
    test_strstr();
    test_strtok();
    test_strerror();

    printf("===All tests passed===\n");
}

int main() {
    run_all_tests();
}

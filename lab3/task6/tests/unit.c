#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "assert_base.h"


void run_tests() {
    //
    // ---- ПОЛОЖИТЕЛЬНЫЕ ТЕСТЫ ----
    //
    _ASSERT_MSG(check_brackets(""), "%s", "empty string");
    _ASSERT_MSG(check_brackets("()"), "%s", "simple parens");
    _ASSERT_MSG(check_brackets("[]"), "%s", "simple brackets");
    _ASSERT_MSG(check_brackets("{}"), "%s", "simple braces");
    _ASSERT_MSG(check_brackets("<>"), "%s", "simple angle brackets");

    _ASSERT_MSG(check_brackets("()()"), "%s", "two sequential pairs");
    _ASSERT_MSG(check_brackets("(())"), "%s", "nested parens");
    _ASSERT_MSG(check_brackets("{[()]}"), "%s", "nested different types");
    _ASSERT_MSG(check_brackets("([]{})"), "%s", "multiple nested");

    _ASSERT_MSG(check_brackets("(([]){<>})"), "%s", "complex nested");
    _ASSERT_MSG(check_brackets("()[]{}<>"), "%s", "flat sequence");

    //
    // ---- ОТРИЦАТЕЛЬНЫЕ ТЕСТЫ ----
    //
    _ASSERT_MSG(!check_brackets("("), "%s", "single open paren");
    _ASSERT_MSG(!check_brackets(")"), "%s", "single close paren");
    _ASSERT_MSG(!check_brackets("(()"), "%s", "unclosed paren");
    _ASSERT_MSG(!check_brackets("())"), "%s", "extra closing paren");
    _ASSERT_MSG(!check_brackets("(]"), "%s", "mismatched pair");

    _ASSERT_MSG(!check_brackets("([)]"), "%s", "crossed nesting");
    _ASSERT_MSG(!check_brackets("{(})"), "%s", "wrong order inside");
    _ASSERT_MSG(!check_brackets("(([])"), "%s", "missing closing bracket");
    _ASSERT_MSG(!check_brackets("([{})])"), "%s", "complex incorrect");

    _ASSERT_MSG(!check_brackets("[(])"), "%s", "bad crossing 2");

    //
    // ---- СМЕШАННЫЕ СИМВОЛЫ -----
    //
    // Если твой парсер должен игнорировать не-скобочные символы — поменяй тесты.
    _ASSERT_MSG(check_brackets("abc"), "%s", "no brackets at all");
    _ASSERT_MSG(check_brackets("(a[b{c}])"), "%s", "with chars inside");
    _ASSERT_MSG(check_brackets("[<<<bebe{`(abo)@[baba]}>()()>01234-.,{}>({})]"), "%s", "crazy test");


    // если парсер НЕ должен игнорировать символы — скажи, я перепишу
}

int main() {
    run_tests();
    return 0;
}

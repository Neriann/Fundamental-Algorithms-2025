#include <math.h>

#include "assert_base.h"
#include "functions.h"

// Макрос для сравнения double с погрешностью
#define ASSERT_DOUBLE_EQ(expected, actual, epsilon) \
    ASSERT_MSG(fabs((expected) - (actual)) < (epsilon))

// Макрос для проверки решений
#define ASSERT_SOLUTION_EQ(expected_type, sol, eps) \
    ASSERT_MSG((sol).type == (expected_type))

void test_string_to_double() {
    printf("Testing string_to_double...\n");

    // Основные случаи
    ASSERT_DOUBLE_EQ(123.45, string_to_double("123.45"), 1e-10);
    ASSERT_DOUBLE_EQ(-67.89, string_to_double("-67.89"), 1e-10);
    ASSERT_DOUBLE_EQ(0.0, string_to_double("0"), 1e-10);
    ASSERT_DOUBLE_EQ(3.14159, string_to_double("3.14159"), 1e-10);


    printf("string_to_double tests passed!\n\n");
}

void test_quadratic_equation() {
    printf("Testing quadratic equation solver...\n");
    double eps = 1e-10;

    // Два действительных корня
    Solution sol1 = get_solution_to_equation(eps, 1, -3, 2); // x² - 3x + 2 = 0
    ASSERT_SOLUTION_EQ(TWO_REAL_SOLUTIONS, sol1, eps);
    ASSERT_DOUBLE_EQ(2.0, sol1.x1, eps);
    ASSERT_DOUBLE_EQ(1.0, sol1.x2, eps);

    // Один действительный корень
    Solution sol2 = get_solution_to_equation(eps, 1, -2, 1); // x² - 2x + 1 = 0
    ASSERT_SOLUTION_EQ(ONE_REAL_SOLUTION, sol2, eps);
    ASSERT_DOUBLE_EQ(1.0, sol2.x1, eps);

    // Комплексные корни
    Solution sol3 = get_solution_to_equation(eps, 1, 0, 1); // x² + 1 = 0
    ASSERT_SOLUTION_EQ(TWO_COMPLEX_SOLUTIONS, sol3, eps);
    ASSERT_DOUBLE_EQ(0.0, sol3.re, eps);
    ASSERT_DOUBLE_EQ(1.0, sol3.im, eps);

    // Вырожденные случаи
    Solution sol4 = get_solution_to_equation(eps, 0, 2, -4); // 2x - 4 = 0
    ASSERT_SOLUTION_EQ(ONE_REAL_SOLUTION, sol4, eps);
    ASSERT_DOUBLE_EQ(2.0, sol4.x1, eps);

    Solution sol5 = get_solution_to_equation(eps, 0, 0, 5); // 5 = 0
    ASSERT_SOLUTION_EQ(ZERO_SOLUTIONS, sol5, eps);

    Solution sol6 = get_solution_to_equation(eps, 0, 0, 0); // 0 = 0
    ASSERT_SOLUTION_EQ(INFINITE_SOLUTIONS, sol6, eps);

    // Пограничные случаи
    Solution sol7 = get_solution_to_equation(eps, 1e-6, 2e-6, 1e-6); // Маленькие коэффициенты
    ASSERT_SOLUTION_EQ(ONE_REAL_SOLUTION, sol7, eps);

    printf("Quadratic equation tests passed!\n\n");
}

void test_swap() {
    printf("Testing swap...\n");

    double a = 3.14, b = 2.71;
    swap(&a, &b);
    ASSERT_MSG(a == 2.71 && b == 3.14);

    a = -5.0, b = 10.0;
    swap(&a, &b);
    ASSERT_MSG(a == 10.0 && b == -5.0);

    a = 0.0, b = 0.0;
    swap(&a, &b);
    ASSERT_MSG(a == 0.0 && b == 0.0);

    printf("swap tests passed!\n\n");
}

void test_my_abs() {
    printf("Testing my_abs...\n");

    ASSERT_MSG(my_abs(5.0) == 5.0);
    ASSERT_MSG(my_abs(-5.0) == 5.0);
    ASSERT_MSG(my_abs(0.0) == 0.0);
    ASSERT_MSG(my_abs(3.14159) == 3.14159);
    ASSERT_MSG(my_abs(-2.71828) == 2.71828);

    // Большие числа
    ASSERT_MSG(my_abs(1e6) == 1e6);
    ASSERT_MSG(my_abs(-1e6) == 1e6);

    // Малые числа
    ASSERT_MSG(my_abs(1e-6) == 1e-6);
    ASSERT_MSG(my_abs(-1e-6) == 1e-6);

    printf("my_abs tests passed!\n\n");
}

void test_string_to_int() {
    printf("Testing string_to_int...\n");

    // Десятичная система
    ASSERT_MSG(string_to_int("123", 10) == 123);
    ASSERT_MSG(string_to_int("-456", 10) == -456);
    ASSERT_MSG(string_to_int("0", 10) == 0);

    // Двоичная система
    ASSERT_MSG(string_to_int("1010", 2) == 10);
    ASSERT_MSG(string_to_int("1111", 2) == 15);

    // Шестнадцатеричная система
    ASSERT_MSG(string_to_int("FF", 16) == 255);
    ASSERT_MSG(string_to_int("1A", 16) == 26);

    // Восьмеричная система
    ASSERT_MSG(string_to_int("77", 8) == 63);
    ASSERT_MSG(string_to_int("10", 8) == 8);

    // Большие числа
    ASSERT_MSG(string_to_int("2147483647", 10) == 2147483647);

    printf("string_to_int tests passed!\n\n");
}

void test_is_divisible_by() {
    printf("Testing is_divisible_by...\n");

    ASSERT_MSG(is_divisible_by(10, 5) == 1);
    ASSERT_MSG(is_divisible_by(10, 3) == 0);
    ASSERT_MSG(is_divisible_by(0, 5) == 1);  // 0 делится на любое число
    ASSERT_MSG(is_divisible_by(7, 7) == 1);
    ASSERT_MSG(is_divisible_by(-10, 5) == 1);
    ASSERT_MSG(is_divisible_by(10, -5) == 1);

    // Отрицательные результаты
    ASSERT_MSG(is_divisible_by(10, 0) == 0);  // Деление на 0
    ASSERT_MSG(is_divisible_by(5, 10) == 0);

    printf("is_divisible_by tests passed!\n\n");
}

void test_is_rectangle() {
    printf("Testing is_rectangle...\n");
    double eps = 1e-10;

    // Прямоугольные треугольники
    ASSERT_MSG(is_rectangle(eps, 3, 4, 5) == 1);  // 3² + 4² = 5²
    ASSERT_MSG(is_rectangle(eps, 5, 12, 13) == 1); // 5² + 12² = 13²
    ASSERT_MSG(is_rectangle(eps, 6, 8, 10) == 1);  // 6² + 8² = 10²

    // Не прямоугольные треугольники
    ASSERT_MSG(is_rectangle(eps, 2, 3, 4) == 0);
    ASSERT_MSG(is_rectangle(eps, 5, 5, 5) == 0);  // Равносторонний

    // Погрешность вычислений
    ASSERT_MSG(is_rectangle(eps, 3, 4, 5.0000000001) == 1);  // В пределах погрешности
    ASSERT_MSG(is_rectangle(eps, 3, 4, 5.1) == 0);        // За пределами погрешности

    // Вырожденные случаи
    ASSERT_MSG(is_rectangle(eps, 0, 0, 0) == 0);
    ASSERT_MSG(is_rectangle(eps, 1, 1, 0) == 0);

    printf("is_rectangle tests passed!\n\n");
}

void test_print_solution() {
    printf("Testing print_solution (visual inspection)...\n");

    double eps = 1e-10;

    // Разные типы решений для визуальной проверки
    Solution sol1 = get_solution_to_equation(eps, 1, -3, 2);
    printf("Two real solutions: ");
    print_solution_to_equation(&sol1, eps, 1, -3, 2);

    Solution sol2 = get_solution_to_equation(eps, 1, -2, 1);
    printf("One real solution: ");
    print_solution_to_equation(&sol2, eps, 1, -2, 1);

    Solution sol3 = get_solution_to_equation(eps, 1, 0, 1);
    printf("Complex solutions: ");
    print_solution_to_equation(&sol3, eps, 1, 0, 1);

    Solution sol4 = get_solution_to_equation(eps, 4, 2, 1);
    printf("Complex solutions: ");
    print_solution_to_equation(&sol4, eps, 4, 2, 1);

    Solution sol5 = get_solution_to_equation(eps, 0, 0, 5);
    printf("No solutions: ");
    print_solution_to_equation(&sol5, eps, 0, 0, 5);

    printf("Print solution tests completed (check output above)\n\n");
}

void run_all_tests() {
    printf("=== Running All Tests ===\n\n");

    test_string_to_double();
    test_quadratic_equation();
    test_swap();
    test_my_abs();
    test_string_to_int();
    test_is_divisible_by();
    test_is_rectangle();
    test_print_solution();

    printf("=== All Tests Passed! ===\n");
}

int main() {
    run_all_tests();
    return 0;
}

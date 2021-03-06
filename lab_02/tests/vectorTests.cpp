#include "vectorTests.h"
#include "../inc/Vector.h"

int constructors_vector_tests()
{
    int rc = 0;
    int test_number = 1;

    printf("Constructors vector tests:\n");
    {
        // Простая инициализация
        Vector<int> v;
        rc += print_result(v.isEmpty() and v.getSize() == 0, test_number);
    }

    {
        // Инициализация с размером
        Vector<int> v(5);
        rc += print_result(not v.isEmpty() and v.getSize() == 5, test_number);
    }

    {
        // Инициализация с размером и заполняющим значением
        Vector<int> v(5, 3);
        rc += print_result(not v.isEmpty() and v.getSize() == 5 and v[0] == 3, test_number);
    }

    {
        // Инициализация с размером и заполняющим массивом
        double arr[] = {1, 2, 3};
        Vector<double> v(5, arr);
        rc += print_result(not v.isEmpty() and
                           v.getSize() == 5 and v[0] == 1 and v[1] == 2 and v[2] == 3, test_number);
    }

    {
        // Инициализация с размером и заполняющим массивом
        typedef struct test_struct
        {
            int a;
            char b;
        } test_struct_t;

        test_struct_t arr[] = {{1, 2}, {5, 6}};
        Vector<test_struct> v(5, arr);
        rc += print_result(not v.isEmpty() and v.getSize() == 5 and
                           v[0].a == 1 and v[0].b == 2 and v[1].a == 5 and v[1].b == 6, test_number);
    }
    {
        // Инициализация встроенным листом
        Vector<char> v({'a', 'b', 'c', 'd'});
        rc += print_result(not v.isEmpty() and v.getSize() == 4 and
                           v[0] == 'a' and v[1] == 'b' and v[2] == 'c' and v[3] == 'd', test_number);
    }

    {
        // Копирование
        Vector<char> v({'a', 'b'});
        Vector<char> v_copy(v);
        rc += print_result(not v.isEmpty() and v.getSize() == 2
                           and v_copy[0] == 'a' and v_copy[1] == 'b', test_number);
    }

    printf("Count tests %d, count errors: %d\n\n", test_number - 1, rc);

    return test_number;
}

static void minus_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 1 Оператор - (унарный)
        Vector<int> v = {1, -2, 3, 4, 5};
        Vector<int> neg_v(-v);
        Vector<int> perf = {-1, 2, -3, -4, -5};
        rc += print_result(neg_v == perf, test_number);
    }

    {
        // 2 Оператор - (два вектора одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 - v2);
        Vector<int> perf(5, 0);
        rc += print_result(res == perf, test_number);
    }

    {
        // 3 Оператор - (вектор и число одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 - 6);
        Vector<int> perf = {-5, -8, -3, -2, -1};
        rc += print_result(res == perf, test_number);
    }

    {
        // 4 Оператор - (два вектора разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> v2 = {7.3, 9.8};
        Vector<double> res(v1 - v2);
        Vector<double> perf = {0.7, 0.2};
        rc += print_result(res == perf, test_number);
    }

    {
        // 5 Оператор - (вектор и число разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> res(v1 - 7.9);
        Vector<double> perf = {0.1, 2.1};
        rc += print_result(res == perf, test_number);
    }

    {
        // 6 Оператор - (вектор и число, длина вектора 0)
        Vector<int> v1;
        Vector<double> res(v1 - 7.9);
        Vector<double> perf;
        rc += print_result(res == perf, test_number);
    }

    {
        // 7 Оператор - (вектор и вектор, длина вектора 0)
        Vector<int> v1;
        Vector<char> v2;
        Vector<int> res(v1 - v2);
        Vector<int> perf;
        rc += print_result(res == perf, test_number);
    }
}

static void plus_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 8 Оператор + (унарный)
        Vector<int> v = {1, -2, 3, 4, 5};
        Vector<int> res(+v);
        Vector<int> perf = {1, -2, 3, 4, 5};
        rc += print_result(res == perf, test_number);
    }

    {
        // 9 Оператор + (два вектора одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {-1, 2, -3, -4, -5};
        Vector<int> res(v1 + v2);
        Vector<int> perf(5, 0);
        rc += print_result(res == perf, test_number);
    }

    {
        // 10 Оператор + (вектор и число одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 + 6);
        Vector<int> perf = {7, 4, 9, 10, 11};
        rc += print_result(res == perf, test_number);
    }

    {
        // 11 Оператор + (два вектора разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> v2 = {0.3, 1.8};
        Vector<double> res(v1 + v2);
        Vector<double> perf = {8.3, 11.8};
        rc += print_result(res == perf, test_number);
    }

    {
        // 12 Оператор + (вектор и число разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> res(v1 + 7.9);
        Vector<double> perf = {15.9, 17.9};
        rc += print_result(res == perf, test_number);
    }

    {
        // 13 Оператор + (вектор и число, длина вектора 0)
        Vector<int> v1;
        Vector<double> res(v1 + 7.9);
        Vector<double> perf;
        rc += print_result(res == perf, test_number);
    }

    {
        // 14 Оператор + (вектор и вектор, длина вектора 0)
        Vector<int> v1;
        Vector<char> v2;
        Vector<int> res(v1 + v2);
        Vector<int> perf;
        rc += print_result(res == perf, test_number);
    }
}


static void equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 15 Оператор =
        Vector<int> v = {1, -2, 3, 4, 5};
        Vector<int> res = v;
        Vector<int> perf = {1, -2, 3, 4, 5};
        rc += print_result(res == perf, test_number);
    }

    {
        // 16 Оператор =
        Vector<int> v1 = {1, -2, 3, 4, 5};
        v1 = {1, 2, 3};
        Vector<int> perf = {1, 2, 3};
        rc += print_result(v1 == perf, test_number);
    }
}

static void minus_equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 17 Оператор -= (вектор - вектор)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        v1 -= v2;
        Vector<int> perf(5, 0);
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 18 Оператор -= (вектор - вектор, с возвратом)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        Vector<int> v3(v1 -= v2);
        Vector<int> perf(5, 0);
        rc += print_result(v3 == perf, test_number);
    }

    {
        // 19 Оператор -= (вектор - вектор, с возвратом)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        v1 -= 1;
        Vector<int> perf = {0, -3, 2, 3, 4};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 20 Оператор -= (вектор - вектор другого типа)
        Vector<int> v1 = {1, 3, 5};
        Vector<double> v2 = {1.1, 2.9, 3.4};
        v1 -= v2;
        Vector<double> perf = {0, 0, 1};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 21 Оператор -= (вектор - число другого типа)
        Vector<int> v1 = {10, 5};
        v1 -=  5.2;
        Vector<double> perf = {4, 0};
        rc += print_result(v1 == perf, test_number);
    }
}

static void plus_equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 22 Оператор += (вектор + вектор)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        v1 += v2;
        Vector<int> perf = {2, -4, 6, 8, 10};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 23 Оператор += (вектор + вектор, с возвратом)
        Vector<int> v1 = {0, 9};
        Vector<int> v2 = {1, 5};
        Vector<int> v3(v1 += v2);
        Vector<int> perf = {1, 14};
        rc += print_result(v3 == perf, test_number);
    }

    {
        // 24 Оператор += (вектор + число)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        v1 += 1;
        Vector<int> perf = {2, -1, 4, 5, 6};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 25 Оператор += (вектор + число другого типа)
        Vector<int> v1 = {1, 3, 5};
        Vector<double> v2 = {1.1, 2.9, 4.5};
        v1 += v2;
        Vector<double> perf = {2, 5, 9};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 26 Оператор += (вектор + число другого типа)
        Vector<int> v1 = {10, 5};
        v1 +=  5.2;
        Vector<double> perf = {15, 10};
        rc += print_result(v1 == perf, test_number);
    }
}

static void equal_equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 27 Оператор ==
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        rc += print_result(v1 == v2, test_number);
    }

    {
        // 28 Оператор ==
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {-1, -2, 3, 4, 5};
        rc += print_result(v1 != v2, test_number);
    }
}

static void multiply_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 29 Оператор * (вектор и число одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 * 2);
        Vector<int> perf = {2, -4, 6, 8, 10};
        rc += print_result(res == perf, test_number);
    }

    {
        // 30 Оператор * (вектор * число разных типов)
        Vector<int> v1 = {10};
        Vector<double> res(v1 * 7.9);
        Vector<double> perf = {79};
        rc += print_result(res == perf, test_number);
    }
}

static void division_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 31 Оператор / (вектор и число)
        Vector<double> v1 = {1.8};
        Vector<double> res(v1 / 2);
        Vector<double> perf = {0.9};
        rc += print_result(res == perf, test_number);
    }
    {
        // 32 Оператор / (вектор и число)
        Vector<int> v1 = {10};
        Vector<int> res(v1 / 5);
        Vector<double> perf = {2};
        rc += print_result(res == perf, test_number);
    }
}

static void multiply_equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 33 Оператор *= (вектор * число)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        v1 *= 3;
        Vector<int> perf = {3, -6, 9, 12, 15};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 34 Оператор *= (вектор * число другого типа)
        Vector<int> v1 = {10, 5};
        v1 *=  5.2;
        Vector<double> perf = {52, 26};
        rc += print_result(v1 == perf, test_number);
    }
}

static void division_equal_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 35 Оператор *= (вектор / число)
        Vector<int> v1 = {1, -2, 3};
        v1 /= 3;
        Vector<double> perf = {0, 0, 1};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 36 Оператор /=
        Vector<int> v1 = {10, 5};
        v1 /=  2;
        Vector<double> perf = {5, 2};
        rc += print_result(v1 == perf, test_number);
    }
}

static void scalar_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 37
        Vector<int> v1 = {1, -2, 3};
        Vector<int> v2 = {1, -2, 0};
        int res = v1 & v2;
        rc += print_result(res == 5, test_number);
    }

    {
        // 38
        Vector<int> v1 = {1, -2, 3};
        Vector<double> v2 = {1.5, 0, -1.5};
        double res = v1 & v2;
        rc += print_result(res == -3, test_number);
    }
}

static void vec_prod_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 39
        Vector<int> v1 = {1, 2, 3};
        Vector<int> v2 = {1, 1, 2};
        Vector<int> res(v1 ^ v2);
        Vector<int> perf = {1, 1, -1};
        rc += print_result(res == perf, test_number);
    }

    {
        // 40
        Vector<double> v1 = {1.1, 0, 3};
        Vector<int> v2 = {0, 10, 20};
        Vector<double> res(v1 ^ v2);
        Vector<int> perf = {-30, -22, 11};
        rc += print_result(res == perf, test_number);
    }

    {
        // 41
        Vector<double> v1 = {1.1, 0, 3};
        Vector<int> v2 = {0, 10, 20};
        v1 ^= v2;
        Vector<int> perf = {-30, -22, 11};
        rc += print_result(v1 == perf, test_number);
    }

    {
        // 42
        Vector<double> v1 = {1.1, 0, 3};
        Vector<double> v2 = {0, 10, 20};
        v2 ^= v1;
        Vector<int> perf = {30, 22, -11};
        rc += print_result(v2 == perf, test_number);
    }
}

int overload_vector_tests()
{
    int rc = 0;
    int test_number = 1;

    printf("Overload vector tests:\n");
    minus_overload_vector_tests(rc, test_number);
    plus_overload_vector_tests(rc, test_number);
    equal_overload_vector_tests(rc, test_number);
    minus_equal_overload_vector_tests(rc, test_number);
    plus_equal_overload_vector_tests(rc, test_number);
    equal_equal_overload_vector_tests(rc, test_number);
    multiply_overload_vector_tests(rc, test_number);
    division_overload_vector_tests(rc, test_number);
    multiply_equal_overload_vector_tests(rc, test_number);
    division_equal_overload_vector_tests(rc, test_number);
    scalar_overload_vector_tests(rc, test_number);
    vec_prod_overload_vector_tests(rc, test_number);

    printf("Count tests %d, count errors: %d\n\n", test_number - 1, rc);

    return test_number;
}

static void collinear_vector_tests(int &rc, int &test_number)
{
    {
        // 1
        Vector<int> v1 = {1, 2, 3};
        Vector<int> v2 = {1, 1, 2};
        rc += print_result(not v1.isCollinear(v2), test_number);
    }

    {
        // 2
        Vector<int> v1 = {1, 2, 3};
        Vector<int> v2 = {2, 4, 6};
        rc += print_result(v1.isCollinear(v2), test_number);
    }

    {
        // 3
        Vector<int> v1 = {1, 2};
        Vector<double> v2 = {3, 6};
        rc += print_result(v2.isCollinear(v1), test_number);
    }
}

static void orthogonal_vector_tests(int &rc, int &test_number)
{
    {
        // 4
        Vector<int> v1 = {1, 0, 0};
        Vector<int> v2 = {0, 1, 0};
        rc += print_result(v1.isOrthogonal(v2), test_number);
    }

    {
        // 5
        Vector<int> v1 = {1, 2};
        Vector<int> v2 = {2, -1};
        rc += print_result(v2.isOrthogonal(v1), test_number);
    }

    {
        // 6
        Vector<int> v1 = {1, 2, 1};
        Vector<double> v2 = {2, -1, 10};
        rc += print_result(not v2.isCollinear(v1), test_number);
    }
}

static void unit_zero_vector_tests(int &rc, int &test_number)
{
    {
        // 7
        Vector<int> v1 = {1, 0, 0};
        rc += print_result(not v1.isZero(), test_number);
    }

    {
        // 8
        Vector<int> v1 = {1, 0, 0};
        rc += print_result(v1.isUnit(), test_number);
    }

    {
        // 9
        Vector<int> v1 = {1, 2, 0};
        rc += print_result(not v1.isUnit(), test_number);
    }

    {
        // 10
        Vector<int> v1 = {0, 0, 0};
        rc += print_result(v1.isZero(), test_number);
    }

    {
        // 11
        Vector<int> v1 = {3, 4};
        Vector<double> v2(v1.getUnit<double>());
        Vector<double> v3 = {0.6, 0.8};
        rc += print_result(v2 == v3, test_number);
    }
}


int special_vector_tests()
{
    int rc = 0;
    int test_number = 1;

    printf("Special vector tests:\n");
    collinear_vector_tests(rc, test_number);
    orthogonal_vector_tests(rc, test_number);
    unit_zero_vector_tests(rc, test_number);

    printf("Count tests %d, count errors: %d\n\n", test_number - 1, rc);

    return test_number;
}

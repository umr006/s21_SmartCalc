#include <check.h>
#include <stdio.h>
#include "s21.h"


START_TEST(math_test_1) {
    char *str = "-1+2*(-2+2)";
    double x = 0;
    double res = -1.;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq(res, res1);
    ck_assert_int_eq(res, res1);
    
}

START_TEST(math_test_2) {
    char *str = "+10 + 1 * (+10 - 1)";
    double x = 0;
    double res = 19;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq(res, res1);
}

START_TEST(math_test_3) {
    char *str = "2*2+1+1+1*2^2*2+2^3+1+1";
    double x = 0;
    double res = 24;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq(res, res1);
}


START_TEST(math_test_4) {
    char *str = "2345/6.55/3/2*(9-100+(-200))";
    double x = 0;
    double res = -17363.740458;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(math_test_5) {
    char *str = "sin(123-100*8^5mod2/10+904.25)";
    double x = 0;
    double res = 0.05077588019;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(math_test_6) {
    double x = 5;
    char *str = "tan(tan(x))";
    double res = -0.2435748198;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(math_test_7) {
    double x = 5;
    char *str = "asin(0.69)-asin(0.69)";
    double res = 0;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq(res, res1);
}

START_TEST(math_test_8) {
    double x = 5;
    char *str = "sqrt(9 * 123.12312 + 324234)";
    double res = 570.387682;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq_tol(res, res1, 1e-06);
}

START_TEST(math_test_9) {
    double x = 5;
    char *str = "atan(6+77/6*(7-8-(9mod6-10)+100))";
    double res = 1.5700644;
    double res1 = 0;
    calc_proc(str, x, &res1);
    ck_assert_double_eq_tol(res, res1, 1e-7);
}


Suite *math() {
    Suite *suite = suite_create("MATH OPERATIONS");
    TCase *tCase = tcase_create("MATH");

    tcase_add_test(tCase, math_test_1);
    tcase_add_test(tCase, math_test_2);
    tcase_add_test(tCase, math_test_3);
    tcase_add_test(tCase, math_test_4);
    tcase_add_test(tCase, math_test_5);
    tcase_add_test(tCase, math_test_6);
    tcase_add_test(tCase, math_test_7);
    tcase_add_test(tCase, math_test_8);
    tcase_add_test(tCase, math_test_9);
    suite_add_tcase(suite, tCase);

    return suite;
}

START_TEST(input_test_1) {
    char *str = "2345/6.55/3/2*(9-100+(-200))";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_2) {
    char *str = "sin(123-100*5mod2/10+904.25)";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_3) {
    char *str = "tan(tan(x))";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_4) {
    char *str = "(2+2)+1)";
    int res = 1;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_5) {
    char *str = "sqrt ( x ) - 12 / 25 * sin( 22 - 21 )";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_6) {
    char *str = "2  - 3     + 2 mod 2 * sin(1 mod 2)";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_7) {
    char *str = "asin(0.69) - asin(0.69)";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(input_test_8) {
    char *str = "asin(0.69) - log(1324 * 234 / 134) * acos(3)";
    int res = 0;
    int res1 = input_check(str);
    ck_assert_int_eq(res, res1);
}



Suite *input() {
    Suite *suite = suite_create("INPUT OPERATIONS");
    TCase *tCase = tcase_create("INPUT");

    tcase_add_test(tCase, input_test_1);
    tcase_add_test(tCase, input_test_2);
    tcase_add_test(tCase, input_test_3);
    tcase_add_test(tCase, input_test_4);
    tcase_add_test(tCase, input_test_5);
    tcase_add_test(tCase, input_test_6);
    tcase_add_test(tCase, input_test_7);
    tcase_add_test(tCase, input_test_8);
    suite_add_tcase(suite, tCase);

    return suite;
}

START_TEST(credit_ann_test_1) {
    double credit = 10000;
    double rate = 12;
    double period = 12;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    annuity(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 10661.88;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_ann_test_2) {
    double credit = 123455.34;
    double rate = 35.3;
    double period = 120;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    annuity(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 449662.80;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_ann_test_3) {
    double credit = 3546565447467.23;
    double rate = 45.1233434;
    double period = 35;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    annuity(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 6435732691346.00;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_diff_test_4) {
    double credit = 3546565447467.23;
    double rate = 45.1233434;
    double period = 35;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    differentiated(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 5947058806116.81;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_diff_test_5) {
    double credit = 123455.34;
    double rate = 35.3;
    double period = 120;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    differentiated(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 343169.84;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_diff_test_6) {
    double credit = 10000;
    double rate = 12;
    double period = 12;
    double month_payment = 0, overpayment_res = 0, total_payment = 0;
    differentiated(credit, rate, period, &month_payment, &overpayment_res, &total_payment);
    
    double res = total_payment;
    double res1 = 10650.00;
    ck_assert_double_eq_tol(res, res1, 1e-7);
}

START_TEST(credit_check_7) {
    char *str = "-10000.23";
    int res = 0;
    int res1 = check_posit(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(credit_check_8) {
    char *str = "10000.12";
    int res = 1;
    int res1 = check_posit(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(credit_check_9) {
    char *str = "10000";
    int res = 1;
    int res1 = check_posit_int(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(credit_check_10) {
    char *str = "-10000";
    int res = 0;
    int res1 = check_posit_int(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(credit_check_11) {
    char *str = "-10.23";
    int res = 1;
    int res1 = graph_input(str);
    ck_assert_int_eq(res, res1);
}

START_TEST(credit_check_12) {
    char *str = "10.23";
    int res = 1;
    int res1 = graph_input(str);
    ck_assert_int_eq(res, res1);
}

Suite *credit() {
    Suite *suite = suite_create("CREDIT OPERATIONS");
    TCase *tCase = tcase_create("CREDIT");

    tcase_add_test(tCase, credit_ann_test_1);
    tcase_add_test(tCase, credit_ann_test_2);
    tcase_add_test(tCase, credit_ann_test_3);
    tcase_add_test(tCase, credit_diff_test_4);
    tcase_add_test(tCase, credit_diff_test_5);
    tcase_add_test(tCase, credit_diff_test_6);
    tcase_add_test(tCase, credit_check_7);
    tcase_add_test(tCase, credit_check_8);
    tcase_add_test(tCase, credit_check_9);
    tcase_add_test(tCase, credit_check_10);
    tcase_add_test(tCase, credit_check_11);
    tcase_add_test(tCase, credit_check_12);
    suite_add_tcase(suite, tCase);

    return suite;
}

void _runCase(Suite *suite) {
    static int count = 1;
    if (count > 1)
        putchar('\n');
    printf("%s%d%s", "CURRENT TEST: ", count, "\n");
    ++count;
    SRunner *sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);
    srunner_run_all(sRunner, CK_NORMAL);
    srunner_free(sRunner);
}

void _runSuite() {
    Suite *list[] = {
            math(),
            input(),
            credit(),
            NULL
    };
    for (Suite **current = list; *current != NULL; ++current) {
        _runCase(*current);
    }
}

int main() {
    _runSuite();
    return 0;
}

#include "../s21_calc.h"

#include <check.h>

START_TEST(calculator_1)
{
const char str[256] = "23+3";
double s21_res = s21_calculator(str);
double res = 26;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_2)
{
const char str[256] = "23(2-2)";
double s21_res = s21_calculator(str);
double res = 0;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_3)
{
const char str[256] = "3*3/9";
double s21_res = s21_calculator(str);
double res = 1;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_4)
{
const char str[256] = "(40-20)*2";
double s21_res = s21_calculator(str);
double res = 40;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_5)
{
const char str[256] = "2^3-4";
double s21_res = s21_calculator(str);
double res = 4;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_6)
{
const char str[256] = "10%5";
double s21_res = s21_calculator(str);
double res = 0;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_7)
{
const char str[256] = "sin(90)";
double s21_res = s21_calculator(str);
double res = sinl(90);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_8)
{
const char str[256] = "cos(60)";
double s21_res = s21_calculator(str);
double res = cosl(60);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_9)
{
const char str[256] = "tan(45)";
double s21_res = s21_calculator(str);
double res = tanl(45);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_10)
{
const char str[256] = "asin(1)";
double s21_res = s21_calculator(str);
double res = asinl(1);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_11)
{
const char str[256] = "acos(1)";
double s21_res = s21_calculator(str);
double res = acosl(1);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_12)
{
const char str[256] = "atan(10)";
double s21_res = s21_calculator(str);
double res = atanl(10);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_13)
{
const char str[256] = "sqrt(20)";
double s21_res = s21_calculator(str);
double res = sqrtl(20);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_14)
{
const char str[256] = "log(10)";
double s21_res = s21_calculator(str);
double res = log10l(10);
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_15)
{
const char str[256] = "ln(1)";
double s21_res = s21_calculator(str);
double res = 0;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_16)
{
const char str[256] = "cos(12-(sin(2)))";
double s21_res = s21_calculator(str);
double res = cosl(12-(sinl(2)));
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_17)
{
const char str[256] = "sqrt(6)-(34-cos(2))";
double s21_res = s21_calculator(str);
double res = sqrtl(6)-(34-cosl(2));
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(calculator_18)
{
const char str[256] = "23*-2+3*atan(0)";
double s21_res = s21_calculator(str);
double res = 23*-2+3*atanl(0);
ck_assert_double_eq(res, s21_res);


}
END_TEST

START_TEST(valid_values_1)
{
const char str[256] = "sbn(1)";
double s21_res = s21_valid_value(str);
double res = 1;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(valid_values_2)
{
const char str[256] = "cus(1)";
double s21_res = s21_valid_value(str);
double res = 1;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(valid_values_3)
{
const char str[256] = "szn(1)";
double s21_res = s21_valid_value(str);
double res = 1;
ck_assert_double_eq(res, s21_res);

}
END_TEST

START_TEST(valid_values_4)
{
const char str[256] = "12&3";
double s21_res = s21_valid_value(str);
double res = 1;
ck_assert_double_eq(res, s21_res);
}
END_TEST

START_TEST(credit_annuity)
{
credit_stack stack = {0,0,0,0};
s21_credit_annuity(100000, 24, 20, &stack);
double s21_payment = (int)stack.payment;
double payment = (int)5089.58; 
double s21_overpayment = (int)stack.overpayment;
double overpayment = (int)22149.92;
double s21_total_payment = (int)stack.total_payment;
double total_payment = (int)122149.92;
ck_assert_double_eq(payment, s21_payment);
ck_assert_double_eq(overpayment, s21_overpayment);
ck_assert_double_eq(total_payment, s21_total_payment);

}
END_TEST

START_TEST(credit_differen)
{
credit_stack stack = {0,0,0,0};
s21_credit_differ(100000, 24, 20, &stack);
double s21_first_payment = (int)stack.first_payment;
double first_payment = (int)5833.33;
double s21_payment = (int)stack.payment;
double payment = (int)4236.11; 
double s21_overpayment = (int)stack.overpayment;
double overpayment = (int)20833.33;
double s21_total_payment = (int)stack.total_payment;
double total_payment = (int)120833.33;
ck_assert_double_eq(first_payment, s21_first_payment);
ck_assert_double_eq(payment, s21_payment);
ck_assert_double_eq(overpayment, s21_overpayment);
ck_assert_double_eq(total_payment, s21_total_payment);


}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, calculator_1);
    tcase_add_test(tc1_1, calculator_2);
    tcase_add_test(tc1_1, calculator_3);
    tcase_add_test(tc1_1, calculator_4);
    tcase_add_test(tc1_1, calculator_5);
    tcase_add_test(tc1_1, calculator_6);
    tcase_add_test(tc1_1, calculator_7);
    tcase_add_test(tc1_1, calculator_8);
    tcase_add_test(tc1_1, calculator_9);
    tcase_add_test(tc1_1, calculator_10);
    tcase_add_test(tc1_1, calculator_11);
    tcase_add_test(tc1_1, calculator_12);
    tcase_add_test(tc1_1, calculator_13);
    tcase_add_test(tc1_1, calculator_14);
    tcase_add_test(tc1_1, calculator_15);
    tcase_add_test(tc1_1, calculator_16);
    tcase_add_test(tc1_1, calculator_17);
    tcase_add_test(tc1_1, calculator_18);
    tcase_add_test(tc1_1, valid_values_1);
    tcase_add_test(tc1_1, valid_values_2);
    tcase_add_test(tc1_1, valid_values_3);
    tcase_add_test(tc1_1, valid_values_4);
    tcase_add_test(tc1_1, credit_annuity);
    tcase_add_test(tc1_1, credit_differen);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}

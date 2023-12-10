#ifndef S21_CALC_H
#define S21_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_operator {
  char operat;
  int priority;
  struct stack_operator* next;
} stack_operator;

typedef struct value_stack {
  double value;
  struct value_stack* next;
} value_stack;

typedef struct credit_stack {
  double payment;
  double overpayment;
  double total_payment;
  double first_payment;
} credit_stack;

// Stack
void s21_push_value(value_stack** stack, double value);
double s21_pop_value(value_stack** stack);
int s21_peek_priority(stack_operator** stack);
void s21_push_operator(stack_operator** stack, char operat, int priority);
char s21_pop_operator(stack_operator** stack);
char s21_peek_operator(stack_operator** stack);

int s21_valid_value(const char* str);
int s21_trig_valid(int* i, const char* str);
int s21_check_value(long double* digit, int* i, const char* str);
long double s21_calculator(const char* str);
void s21_check_operator(char operand, stack_operator** stack,
                        value_stack** val_stack);
int calculate(stack_operator** oper, value_stack** val);
int s21_add_atof_value(long double* digit, int* i, const char* str,
                       value_stack** val_stack);
// Credit
void s21_credit_annuity(double sum_credit, int month, double percent,
                        credit_stack* credit_stack);
void s21_credit_differ(double sum_credit, int month, double percent,
                       credit_stack* credit_stack);
#endif

#include "s21_calc.h"

void s21_credit_annuity(double sum_credit, int month, double percent,
                        credit_stack* credit_stack) {
  double month_percent = percent / 12 / 100;
  double ann_factor = (month_percent * pow(1 + month_percent, month)) /
                      (pow(1 + month_percent, month) - 1);
  credit_stack->payment = sum_credit * ann_factor;
  credit_stack->overpayment = credit_stack->payment * month - sum_credit;
  credit_stack->total_payment = credit_stack->overpayment + sum_credit;
  credit_stack->first_payment = 0;
}
void s21_credit_differ(double sum_credit, int month, double percent,
                       credit_stack* credit_stack) {
  double month_percent = percent / 12 / 100;
  double payment = 0;
  credit_stack->first_payment =
      sum_credit / month +
      (sum_credit - (1 - 1) * (sum_credit / month)) * month_percent;
  for (int i = 1; i <= month; i++) {
    payment = sum_credit / month +
              (sum_credit - (i - 1) * (sum_credit / month)) * month_percent;
    credit_stack->total_payment += payment;
    if (i == month) credit_stack->payment = payment;
  }
  credit_stack->overpayment = credit_stack->total_payment - sum_credit;
}

int s21_check_value(long double* digit, int* i, const char* str) {
  char* buffer[256] = {0};
  int flag = 0;
  int j = 0;
  int dot_cnt = 0;
  for (; (isdigit(str[*i]) || str[*i] == '.'); j++, (*i)++) {
    if (str[*i] == '.') dot_cnt++;
    buffer[j] = (char*)&str[*i];
  }
  if (dot_cnt <= 1) {
    *digit = atof(*buffer);
  } else
    flag = 1;
  return flag;
}
int s21_add_atof_value(long double* digit, int* i, const char* str,
                       value_stack** val_stack) {
  int status = 0;
  status = s21_check_value(digit, i, str);
  if (status == 0) {
    s21_push_value(val_stack, *digit);
    (*i)--;
  } else
    status = 1;
  return status;
}

int s21_unar_minus(stack_operator** oper_stack, value_stack** val_stack, int* i,
                   long double* digit, const char* str, double value,
                   int priority) {
  int status = 0;
  s21_push_value(val_stack, value);
  (*i)++;
  s21_push_operator(oper_stack, '-', priority);
  status = s21_add_atof_value(digit, i, str, val_stack);
  return status;
}
long double s21_calculator(const char* str) {
  long double answer = 0.;
  int status = 0;
  char operand = 0;
  value_stack* stack_val = NULL;
  stack_operator* stack_oper = NULL;
  if (s21_valid_value(str) == 0) {
    for (int i = 0; str[i] != '\0' && status == 0; i++) {
      if (isdigit(str[i]) == 1) {
        status = s21_add_atof_value(&answer, &i, str, &stack_val);
      } else if (str[i] == '-' && (str[i - 1] == '/' || str[i - 1] == '*' ||
                                   str[i - 1] == '%')) {
        status =
            s21_unar_minus(&stack_oper, &stack_val, &i, &answer, str, 0, 0);
        calculate(&stack_oper, &stack_val);
      } else if ((str[i] == '-') && (str[i - 1] == '(')) {
        s21_push_value(&stack_val, 0);
        s21_check_operator('-', &stack_oper, &stack_val);
      } else if (strchr("+-*%^/", str[i])) {
        s21_check_operator(str[i], &stack_oper, &stack_val);
      } else if (str[i] == '(' && isdigit(str[i - 1]) == 1) {
        s21_check_operator('*', &stack_oper, &stack_val);
        s21_push_operator(&stack_oper, str[i], 0);
      } else if (str[i] == '(') {
        s21_push_operator(&stack_oper, str[i], 0);
      } else if (str[i] == ')') {
        operand = stack_oper->operat;
        while (operand != '(') {
          calculate(&stack_oper, &stack_val);
          operand = stack_oper->operat;
        }
        if (operand == '(') s21_pop_operator(&stack_oper);
      } else if (isalpha(str[i]) == 1 && str[i] != 'm') {
        operand = s21_trig_valid(&i, str);
        if (operand != 'R') {
          s21_push_operator(&stack_oper, operand, 4);
        } else
          status = 1;
      } else if (s21_trig_valid(&i, str) == '%') {
        s21_check_operator('%', &stack_oper, &stack_val);
      }
    }
  } else
    status = 1;
  while (stack_oper != NULL) {
    calculate(&stack_oper, &stack_val);
  }
  answer = s21_pop_value(&stack_val);
  if (status == 1) answer = NAN;
  return answer;
}
int s21_valid_value(const char* str) {
  int status = 0;
  int count = strlen(str);
  int bracket_cnt = 0;
  if (*str == '\0') status = 1;
  for (int i = 0; i < count && status == 0; i++) {
    if ((strchr("sincotaqrlmdg+-*/^%().x ", str[i]) == 0) &&
        isdigit(str[i]) == 0) {
      status = 1;
    } else if (((str[i] == '/') || (str[i + 1] == '%')) &&
               (str[i + 1] == '0')) {
      status = 1;
    } else if (str[i] == '(') {
      bracket_cnt++;
    } else if (str[i] == ')') {
      bracket_cnt--;
    }
  }
  if (bracket_cnt != 0) status = 1;
  return status;
}

int s21_trig_valid(int* i, const char* str) {
  char status = 0;
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
      str[*i + 3] == '(') {
    status = 's';
    *i += 2;
  } else if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
             str[*i + 3] == '(') {
    status = 'c';
    *i += 2;
  } else if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
             str[*i + 3] == '(') {
    status = 't';
    *i += 2;
  } else if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g' &&
             str[*i + 3] == '(') {
    status = 'l';
    *i += 2;
  } else if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
             str[*i + 3] == 's' && str[*i + 4] == '(') {
    status = 'C';
    *i += 3;
  } else if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
             str[*i + 3] == 'n' && str[*i + 4] == '(') {
    status = 'S';
    *i += 3;
  } else if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
             str[*i + 3] == 'n' && str[*i + 4] == '(') {
    status = 'T';
    *i += 3;
  } else if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
             str[*i + 3] == 't' && str[*i + 4] == '(') {
    status = 'q';
    *i += 3;
  } else if (str[*i] == 'l' && str[*i + 1] == 'n' && str[*i + 2] == '(') {
    status = 'L';
    *i += 1;
  } else if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') {
    status = '%';
    *i += 2;
  } else
    status = 'R';
  return status;
}
void s21_check_operator(char operand, stack_operator** stack,
                        value_stack** val_stack) {
  int priority = 0;
  if (operand == '+' || operand == '-')
    priority = 1;
  else if (operand == '*' || operand == '/' || operand == '%')
    priority = 2;
  else if (operand == '^')
    priority = 3;
  if (priority > s21_peek_priority(stack)) {
    s21_push_operator(stack, operand, priority);
  } else {
    if (operand == '^' && s21_peek_operator(stack) == '^') {
      s21_push_operator(stack, operand, priority);
    } else {
      calculate(stack, val_stack);
      s21_check_operator(operand, stack, val_stack);
    }
  }
}

int calculate(stack_operator** oper, value_stack** val) {
  int status = 0;
  char operand = s21_pop_operator(oper);
  long double value_1 = s21_pop_value(val);
  long double result = 0.;
  long double value_2 = 0.;
  if (operand == '-') {
    value_2 = s21_pop_value(val);
    result = value_2 - value_1;
    s21_push_value(val, result);
  } else if (operand == '+') {
    value_2 = s21_pop_value(val);
    result = value_2 + value_1;
    s21_push_value(val, result);
  } else if (operand == '^') {
    value_2 = s21_pop_value(val);
    result = powl(value_2, value_1);
    s21_push_value(val, result);
  } else if (operand == '*') {
    value_2 = s21_pop_value(val);
    result = value_2 * value_1;
    s21_push_value(val, result);
  } else if (operand == '/') {
    value_2 = s21_pop_value(val);
    result = value_2 / value_1;
    s21_push_value(val, result);
  } else if (operand == '%') {
    value_2 = s21_pop_value(val);
    result = fmodl(value_2, value_1);
    s21_push_value(val, result);
  } else if (operand == 's') {
    result = sinl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'c') {
    result = cos(value_1);
    s21_push_value(val, result);
  } else if (operand == 't') {
    result = tanl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'l') {
    result = log10l(value_1);
    s21_push_value(val, result);
  } else if (operand == 'C') {
    result = acosl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'S') {
    result = asinl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'L') {
    result = logl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'q') {
    result = sqrtl(value_1);
    s21_push_value(val, result);
  } else if (operand == 'T') {
    result = atanl(value_1);
    s21_push_value(val, result);
  } else if (operand == '(') {
    s21_push_value(val, value_1);
  } else
    status = 1;
  return status;
}

// Add value in value_stack
void s21_push_value(value_stack** stack, double value) {
  value_stack* ptr = (value_stack*)malloc(sizeof(value_stack));
  if (ptr) {
    ptr->value = value;
    ptr->next = *stack;
    *stack = ptr;
  }
}

// Get value from value_stack
double s21_pop_value(value_stack** stack) {
  value_stack* ptr = NULL;
  double res = 0.;
  if (*stack) {
    ptr = *stack;
    res = (*stack)->value;
    *stack = (*stack)->next;
    free(ptr);
  }
  return res;
}

char s21_peek_operator(stack_operator** stack) {
  char operand = '\0';
  if (*stack) {
    operand = (*stack)->operat;
  }
  return operand;
}
int s21_peek_priority(stack_operator** stack) {
  int priority = 0;
  if (*stack) {
    priority = (*stack)->priority;
  }
  return priority;
}

// Add operator in stack
void s21_push_operator(stack_operator** stack, char operat, int priority) {
  stack_operator* ptr = (stack_operator*)malloc(sizeof(stack_operator));
  if (ptr) {
    ptr->operat = operat;
    ptr->priority = priority;
    ptr->next = *stack;
    *stack = ptr;
  }
}

// Get operator from operator stack
char s21_pop_operator(stack_operator** stack) {
  stack_operator* ptr = NULL;
  char res = '\0';
  if (*stack) {
    ptr = *stack;
    res = (*stack)->operat;
    *stack = (*stack)->next;
    free(ptr);
  }
  return res;
}

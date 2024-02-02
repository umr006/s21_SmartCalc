#ifndef S21_H
#define S21_H

#include <stdio.h>
#include <math.h>

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORRECTLY 0
#define ERROR 1
#define NO 0
#define YES 1
#define BUFF 255

typedef enum typ {
  number = 1,
  s21_x,
  open_bracket,
  close_bracket,
  s21_plus,
  s21_minus,
  s21_mult,
  s21_div,
  s21_pow,
  s21_mod,
  s21_cos,
  s21_sin,
  s21_tan,
  s21_acos,
  s21_asin,
  s21_atan,
  s21_sqrt,
  s21_log,
  s21_ln,
  s21_plus_un,
  s21_minus_un
} type_t;

typedef struct list {
  double value;
  int priority;
  type_t type;
  struct list *next;
} list_t;

int check_posit(char *str);
int check_posit_int(char *str);
int graph_input(char *str);
void delete_space(char *str, char *correct_str, int len);
void annuity(double credit, double rate, double period, double *month_payment, double *overpayment_res, double *total_payment);
void differentiated (double credit, double rate, double period, double *month_payment, double *overpayment_res, double *total_payment);
int input_check(char *str);
int brackets(char *str, int len);
void calc_proc(char* str, double value_x, double *result);
void free_list(list_t *top);
int error_parser(char *str, int len) ;
int check_number(char *str, int len);
int check_x(char *str, int i);
int check_dot(char *str, int i);
int check_sign(char *str, int i);
int check_mod(char *str, int i);
int check_sign_before_func(char *str, int i);
int check_sin(char *str, int i);
int check_sqrt(char *str, int i);
int check_cos(char *str, int i);
int check_tan(char *str, int i);
int check_acos(char *str, int i);
int check_asin(char *str, int i);
int check_atan(char *str, int i);
int check_ln(char *str, int i);
int check_log(char *str, int i);
int plus_or_minus(char c);
int mul_or_div_or_pow(char c);
void parsing(char *str, list_t **list);
void create_and_add_list(list_t **list, char *num, int list_priority, type_t list_type);
list_t *create_list(char *str_value, int v_priority, type_t v_type);
void add_elem_list(list_t *head, char *str_value, int v_priority,
                   type_t v_type);
void create_stack(list_t** res, double value, int priority, type_t type);
void push_stack(list_t** res, double value, int priority, type_t type);
void create_push_stack(list_t** res, double value, int priority, type_t type);
void pop_stack(list_t **stack);
int priority_op(list_t* tmp, int priority);
void postfix_notation(list_t *list, list_t **res);
void reverse_stack(list_t **stack, double x);
void peek(list_t** stack, list_t* peek_elem);
void bi_op_calc(list_t** stack, list_t* a, list_t* b, list_t* c);
void un_op_calc(list_t** stack, list_t *a, list_t *b);
void calculate(list_t** stack);

#endif // S21_H

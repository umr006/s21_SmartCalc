#include "s21.h"

int check_posit(char *str) {
    int res = 1, dot = 0;
    for (int i = 0; str[i]; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
            res = 0;
        } else if (str[i] == '.') {
            if (dot) res = 0;
            dot = 1;
        }
    }
    return res;
}

int check_posit_int(char *str) {
    int res = 1;
    for (int i = 0; str[i]; i++)
        if ((str[i] < '0' || str[i] > '9'))
            res = 0;
    return res;
}

int graph_input(char *str) {
    int res = 1, dot = 0;
    for (int i = 0; str[i]; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-') {
            res = 0;
        } else if (str[i] == '.') {
            if (dot) res = 0;
            dot = 1;
        }
    }
    return res;
}

void annuity(double credit, double rate, double period, double *month_payment, double *overpayment_res, double *total_payment) {

    double r = 0;
    r = rate / (12 * 100);
    double pay_month = credit * ((r * pow(1 + r, period)) / (pow(1 + r, period) - 1));
    pay_month = round(pay_month * 100) / 100;
    double total_pay = pay_month * period;
    double overpayment = total_pay - credit;

    *overpayment_res = overpayment;
    *month_payment = pay_month;
    *total_payment = total_pay;
}

void differentiated (double credit, double rate, double period, double *month_payment, double *overpayment_res, double *total_payment) {
    double pay_month = 0, total_pay = 0, month_rate = 0;

    double tmp_credit = credit;

    double r = rate / (12 * 100);

    for (int i = 1; i <= period; i++) {
        month_rate = r * tmp_credit;
        pay_month = month_rate + (credit / period);
        tmp_credit -= (credit / period);
        total_pay += pay_month;
    }
    total_pay = round(total_pay * 100) / 100;
    *overpayment_res = total_pay - credit;
    *month_payment = pay_month;
    *total_payment = total_pay;

}

int input_check(char *str) {
  int error_code = 0;
  int len = strlen(str);
  char correct_str[BUFF];
  delete_space(str, correct_str, len);
  int len_correct = strlen(correct_str);
  if (len_correct > 255) {
    error_code = 1;
  } else {
    if (brackets(correct_str, len_correct))
      error_code = 1;
    else if (error_parser(correct_str, len_correct))
      error_code = 1;
  }
  return error_code;
}

void delete_space(char *str, char *correct_str, int len) {
    int y = 0;
    for(int i = 0; i <= len; i++) {
        if (str[i] == 32) {
            continue;
        } else {
            correct_str[y] = str[i];
            y++;
        }
    }
    correct_str[y] = '\0';
}

void calc_proc(char* str, double value_x, double *result) {
    list_t* list = NULL;
    list_t* res = NULL;
    int len = strlen(str);
    char correct_str[BUFF];
    delete_space(str, correct_str, len);
    input_check(correct_str);
    parsing(correct_str, &list);
    postfix_notation(list, &res);
    reverse_stack(&res, value_x);
    calculate(&res);
    *result = res->value;
    free_list(list);
    free_list(res);
}

void free_list(list_t *top) {
    while(top != NULL) {
        list_t* tmp = top;
        top = top->next;
        free(tmp);
    }
}

int brackets(char *str, int len) {
  int error_code = CORRECTLY;
  int open_brackets = 0, close_brackets = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] == '(') {
      open_brackets++;
      if (str[i + 1] == ')') {
        error_code = ERROR;
        break;
      }
    }
    if (str[i] == ')') {
      close_brackets++;
      if (close_brackets > open_brackets) {
        error_code = ERROR;
        break;
      }
    }
  }
    if (open_brackets != close_brackets)
        error_code = ERROR;
    return error_code;
}

int error_parser(char *str, int len) {
  int error_code = CORRECTLY;
  for (int i = 0; i < len; i++) {
    if (error_code)
      break;
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '(' || str[i] == ')') {
      if (check_number(str, i))
        error_code = ERROR;
    } else if (str[i] == '(' || str[i] == ')') {

    } else if (str[i] == 'x' || str[i] == 'X') {
      if (check_x(str, i))
        error_code = ERROR;
    } else if (str[i] == '.') {
      if (check_dot(str, i))
        error_code = ERROR;
    } else if (str[i] == '+' || str[i] == '-') {
      if (check_sign(str, i))
        error_code = ERROR;
    } else if (str[i] == '*' || str[i] == '/' || str[i] == '^') {
      if (i == 0 || str[i - 1] == '(' || check_sign(str, i))
        error_code = ERROR;
    } else if (str[i] == 'm') {
      int j = i + 3;
      if (j < len) {
        if (check_mod(str, i))
          error_code = ERROR;
        else
          i += 2;
      } else
        error_code = ERROR;
    } else if (str[i] == 's') {
      if (!check_sin(str, i))
        i += 3;
      else if (!check_sqrt(str, i))
        i += 4;
      else
        error_code = ERROR;
    } else if (str[i] == 'c' || str[i] == 't') {
      if (check_cos(str, i) && check_tan(str, i))
        error_code = ERROR;
      else
        i += 3;
    } else if (str[i] == 'a') {
        if (str[i + 1] == 'c') {
            error_code = check_acos(str, i);
            i += 4;
        } else if (str[i + 1] == 's') {
            error_code = check_asin(str, i);
            i += 4;
        } else if (str[i + 1] == 't') {
            error_code = check_atan(str, i);
            i += 4;
        }
    } else if (str[i] == 'l') {
      if (!check_ln(str, i))
        i += 2;
      else if (!check_log(str, i))
        i += 3;
      else
        error_code = ERROR;
    } else {
      error_code = ERROR;
    }
  }
  return error_code;
}

int check_number(char *str, int len) {
    int error_code = CORRECTLY;
    if (len == 0) {
      if (str[len] == ')')
        error_code = ERROR;
    }
    if (str[len] == '(' && str[len + 1] == ')')
        error_code = ERROR;
    if (str[len] == ')' && str[len + 1] == '(')
        error_code = ERROR;
    if (str[len + 1] == 'c' || str[len + 1] == 's')
        error_code = ERROR;
    if (str[len + 1] == 't' || str[len + 1] == 'a')
        error_code = ERROR;
    if (str[len + 1] == 'l')
        error_code = ERROR;
    return error_code;
}

int check_x(char *str, int i) {
  int error_code = CORRECTLY;
  if (i != 0) {
    if (str[i - 1] >= '0' && str[i - 1] <= '9')
      error_code = ERROR;
    if (str[i - 1] == '.' || str[i - 1] == ')')
      error_code = ERROR;
  }
  if (str[i + 1] >= '0' && str[i + 1] <= '9')
    error_code = ERROR;
  if (str[i + 1] == '.' || str[i + 1] == '(')
    error_code = ERROR;
  if (str[i + 1] == 'c' || str[i + 1] == 's')
    error_code = ERROR;
  if (str[i + 1] == 't' || str[i + 1] == 'a')
    error_code = ERROR;
  if (str[i + 1] == 'l')
    error_code = ERROR;
  return error_code;
}

int check_dot(char *str, int i) {
  int error_code = CORRECTLY;
  if (i != 0) {
    if (str[i - 1] < '0' || str[i - 1] > '9') {
      error_code = ERROR;
    } else if (str[i + 1] < '0' || str[i + 1] > '9') {
      error_code = ERROR;
    }
  } else
    error_code = ERROR;
  return error_code;
}

int check_sign(char *str, int i) {
    int res_code = CORRECTLY;
    if (str[i + 1] == ')')
        res_code = ERROR;
    if (i != 0) {
        if (plus_or_minus(str[i - 1]) || mul_or_div_or_pow(str[i + 1]))
            res_code = ERROR;
        if (plus_or_minus(str[i - 1]) || mul_or_div_or_pow(str[i + 1]))
            res_code = ERROR;
        if (str[i - 1] == 'd' || str[i + 1] == 'm')
            res_code = ERROR;
    } else {
        if (mul_or_div_or_pow(str[i + 1]))
            res_code = ERROR;
        if (plus_or_minus(str[i + 1]))
            res_code = ERROR;
        if (str[i + 1] == 'm')
            res_code = ERROR;
    }
    return res_code;
}

int check_mod(char *str, int i) {
  int error_code = CORRECTLY;
  if (i != 0) {
    if (strncmp(&str[i], "mod", 3))
      error_code = ERROR;
    if (!(str[i - 1] >= '0' && str[i - 1] <= '9'))
      error_code = ERROR;
    if (!(str[i + 3] >= '0' && str[i + 3] <= '9'))
      error_code = ERROR;
  } else {
    error_code = ERROR;
  }
  return error_code;
}

int check_sign_before_func(char *str, int i) {
  int error_code = CORRECTLY;
  if (i != 0 && str[i - 1] != '(' && str[i - 1] != 'd') {
    if (!plus_or_minus(str[i - 1]) && !mul_or_div_or_pow(str[i - 1])) {
      error_code = ERROR;
    }
  }
  return error_code;
}

int check_sin(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "sin(", 4))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_sqrt(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "sqrt(", 5))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_cos(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "cos(", 4))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_tan(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "tan(", 4))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_acos(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "acos(", 5))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_asin(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "asin(", 5))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_atan(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "atan(", 5))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_ln(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "ln(", 3))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int check_log(char *str, int i) {
  int error_code = CORRECTLY;
  if (strncmp(&str[i], "log(", 4))
    error_code = ERROR;
  if (check_sign_before_func(str, i))
    error_code = ERROR;
  return error_code;
}

int plus_or_minus(char c) {
  int a = 0;
  if (c == '+' || c == '-') {
    a = 1;
  }
  return a;
}

int mul_or_div_or_pow(char c) {
  int a = 0;
  if (c == '*' || c == '/' || c == '^') {
    a = 1;
  }
  return a;
}

void parsing(char *str, list_t **list) {
  char num[BUFF];
  int i = 0;
  int len = strlen(str);
  for (int j = 0; j < len; j++) {
    if ((str[j] >= '0' && str[j] <= '9') || str[j] == '.') {
      num[i++] = str[j];
      if ((str[j + 1] < '0' || str[j + 1] > '9') && str[j + 1] != '.') {
        num[i] = 0;
        create_and_add_list(list, num, 0, number);
        i = 0;
      }
    } else if (str[j] == 'x' || str[j] == 'X') {
      create_and_add_list(list, "0", 0, s21_x);
    } else if (str[j] == '(') {
      create_and_add_list(list, "0", 0, open_bracket);

    } else if (str[j] == ')') {
      create_and_add_list(list, "0", 0, close_bracket);
    } else if (str[j] == '+') {
      if (str[j - 1] == '(' || j == 0)
        create_and_add_list(list, "0", 1, s21_plus_un);
      else
        create_and_add_list(list, "0", 1, s21_plus);
    } else if (str[j] == '-') {
      if (str[j - 1] == '(' || j == 0)
        create_and_add_list(list, "0", 1, s21_minus_un);
      else
        create_and_add_list(list, "0", 1, s21_minus);
    } else if (str[j] == '*') {
      create_and_add_list(list, "0", 2, s21_mult);
    } else if (str[j] == '/') {
      create_and_add_list(list, "0", 2, s21_div);
    } else if (str[j] == '^') {
      create_and_add_list(list, "0", 3, s21_pow);
    } else if (str[j] == 'm') {
      create_and_add_list(list, "0", 2, s21_mod);
      j += 2;
    } else if (str[j] == 'c') {
      create_and_add_list(list, "0", 4, s21_cos);
      j += 2;
    } else if (str[j] == 's' && str[j + 1] == 'i') {
      create_and_add_list(list, "0", 4, s21_sin);
      j += 2;
    } else if (str[j] == 't') {
      create_and_add_list(list, "0", 4, s21_tan);
      j += 2;
    } else if (str[j] == 'a' && str[j + 1] == 'c') {
      create_and_add_list(list, "0", 4, s21_acos);
      j += 3;
    } else if (str[j] == 'a' && str[j + 1] == 's') {
      create_and_add_list(list, "0", 4, s21_asin);
      j += 3;
    } else if (str[j] == 'a' && str[j + 1] == 't') {
      create_and_add_list(list, "0", 4, s21_atan);
      j += 3;
    } else if (str[j] == 's' && str[j + 1] == 'q') {
      create_and_add_list(list, "0", 4, s21_sqrt);
      j += 3;
    } else if (str[j] == 'l' && str[j + 1] == 'n') {
      create_and_add_list(list, "0", 4, s21_ln);
      j += 1;
    } else if (str[j] == 'l' && str[j + 1] == 'o') {
      create_and_add_list(list, "0", 4, s21_log);
      j += 2;
    }
  }
}

void create_and_add_list(list_t **list, char *num, int list_priority,
                         type_t list_type) {
  if (*list == NULL)
    *list = create_list(num, list_priority, list_type);
  else
    add_elem_list(*list, num, list_priority, list_type);
}

list_t *create_list(char *str_value, int v_priority, type_t v_type) {
  list_t *tmp = (struct list *)malloc(sizeof(struct list));
  tmp->value = atof(str_value);
  tmp->priority = v_priority;
  tmp->type = v_type;
  tmp->next = NULL;
  return tmp;
}

void add_elem_list(list_t *head, char *str_value, int v_priority,
                   type_t v_type) {
  list_t *tmp = head;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = create_list(str_value, v_priority, v_type);
}


void create_stack(list_t** res, double value, int priority, type_t type) {
  list_t *tmp = (struct list *)malloc(sizeof(struct list));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = NULL;
  *res = tmp;
}

void push_stack(list_t** res, double value, int priority, type_t type) {
  list_t *tmp = (struct list *)malloc(sizeof(struct list));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *res;
  *res = tmp;
}

void create_push_stack(list_t** res, double value, int priority, type_t type) {
  if (*res == NULL)
    create_stack(res, value, priority, type);
  else
    push_stack(res, value, priority, type);
}

void pop_stack(list_t **stack) {
  if (*stack != NULL) {
    list_t *tmp = (*stack)->next;
    free(*stack);
    *stack = tmp;
  }
}

int priority_op(list_t* tmp, int priority) {
  int res = 0;
  if (tmp != NULL) {
    if (priority > tmp->priority)
      res = 1;
  } else
      res = 1;
  return res;
}

void postfix_notation(list_t *list, list_t **res) {
  list_t *stack_tmp = NULL;
  while (list) {
    if (list->type != 4) {
      if (list->type == 1 || list->type == 2) {
        create_push_stack(res, list->value, list->priority,
                              list->type);
      } else {
        while (1) {
          if (priority_op(stack_tmp, list->priority) || list->type == 3) {
            create_push_stack(&stack_tmp, list->value, list->priority,
                                  list->type);
            break;
          } else {
            create_push_stack(res, stack_tmp->value,
                                  stack_tmp->priority, stack_tmp->type);
            pop_stack(&stack_tmp);
          }
        }
      }
    } else {
      while (stack_tmp->type != 3) {
        create_push_stack(res, stack_tmp->value, stack_tmp->priority,
                              stack_tmp->type);
        pop_stack(&stack_tmp);
      }
      pop_stack(&stack_tmp);
    }
    list = list->next;
  }
  while (stack_tmp) {
    create_push_stack(res, stack_tmp->value, stack_tmp->priority,
                          stack_tmp->type);
    pop_stack(&stack_tmp);
  }
}

void reverse_stack(list_t **stack, double x) {
  list_t *stack_rev = NULL;
  while (*stack) {
    if ((*stack)->type == s21_x) {
      (*stack)->type = number;
      (*stack)->value = x;
    }
    create_push_stack(&stack_rev, (*stack)->value, (*stack)->priority,
                          (*stack)->type);
    pop_stack(stack);
  }
  *stack = stack_rev;
}

void peek(list_t** stack, list_t* peek_elem) {
    list_t *tmp;
    tmp = *stack;
    if (*stack == peek_elem) {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    } else {
        while (tmp->next != peek_elem) {
            tmp = tmp->next;
        }
        tmp->next = peek_elem->next;
        free(peek_elem);
    }
}


void bi_op_calc(list_t** stack, list_t* a, list_t* b, list_t* c) {
    double op1, op2, res = 0;
    op1 = a->value;
    op2 = b->value;
    if(c->type == s21_plus) {
        res = op1 + op2;
    } else if (c->type == s21_minus) {
        res = op1 - op2;
    } else if (c->type == s21_mult) {
        res = op1 * op2;
    } else if (c->type == s21_div) {
        res = op1 / op2;
    } else if (c->type == s21_pow) {
        res = pow(op1, op2);
    } else if (c->type == s21_mod) {
        res = fmod(op1, op2);
    }
    a->priority = 0;
    a->type = number;
    a->value = res;
    peek(stack, c);
    peek(stack, b);
}

void un_op_calc(list_t** stack, list_t *a, list_t *b) {
    double op1 = 0, res = 0;
    op1 = a->value;
    if (b->type == s21_plus_un) {
        res = +op1;
    } else if (b->type == s21_minus_un) {
        res = -op1;
    } else if (b->type == s21_sin) {
        res = sin(op1);
    } else if (b->type == s21_cos) {
        res = cos(op1);
    } else if (b->type == s21_tan) {
        res = tan(op1);
    } else if (b->type == s21_asin) {
        res = asin(op1);
    } else if (b->type == s21_acos) {
        res = acos(op1);
    } else if (b->type == s21_atan) {
        res = atan(op1);
    } else if (b->type == s21_sqrt) {
        res = sqrt(op1);
    } else if (b->type == s21_log) {
        res = log10(op1);
    } else if (b->type == s21_ln) {
        res = log(op1);
    }
    a->value = res;
    a->priority = 0;
    a->type = number;
    peek(stack, b);
}

void calculate(list_t** stack) {
    while((*stack)->next != NULL) {
        list_t *a, *b, *c;
        a = *stack;
        b = a->next;
        if (b->next != NULL)
            c = b->next;
        if (b->type == number) {
            while(1) {
                if (c->priority) {
                    break;
                }
                a = b;
                b = a->next;
                c = b->next;
            }
            if (c->type >= 5 && c->type <= 10) {
                bi_op_calc(stack, a, b, c);
            } else {
                un_op_calc(stack, b, c);
            }
        } else {
            un_op_calc(stack, a, b);
        }
    }
}

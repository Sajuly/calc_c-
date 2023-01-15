#include "rpn_executor.h"

#include <complex.h>

#include <cmath>
#include <iostream>
#include <list>
#include <stack>

#include "parser.h"
#include "token.h"

/*
{'_', 10, ASSOC_RIGHT, 1, eval_uminus},
{'^', 9,  ASSOC_RIGHT, 0, eval_exp},
{'*', 8,  ASSOC_LEFT,  0, eval_mul},
{'/', 8,  ASSOC_LEFT,  0, eval_div},
{'%', 8,  ASSOC_LEFT,  0, eval_mod},
{'+', 5,  ASSOC_LEFT,  0, eval_add},
{'-', 5,  ASSOC_LEFT,  0, eval_sub},
{'(', 0,  ASSOC_NONE,  0, NULL},
{')', 0,  ASSOC_NONE,  0, NULL}
 */

std::list<s21::Token> rpn(std::list<s21::Token> parsed_list) {
  // приоритет операций по типам токенов от TT_END до TT_UNKNOWN
  const int precedence[23] = {0, 0, 2, 2, 4, 4, 0, 0, 1, 1, 1, 1,
                              1, 1, 0, 1, 1, 1, 5, 4, 6, 6, 0};

  std::stack<s21::Token> stack;
  std::list<s21::Token> result;

  s21::Token top_tt;

  for (auto current_tt : parsed_list) {
    switch (current_tt.token_type) {
      case TT_DIGIT:
      case TT_X:
        result.push_back(current_tt);
        break;
      case TT_SIN:
      case TT_COS:
      case TT_TAN:
      case TT_ASIN:
      case TT_SQRT:
      case TT_LN:
      case TT_ACOS:
      case TT_ATAN:
      case TT_LOG:
        stack.push(current_tt);
        break;
      case TT_PLUS:
      case TT_MINUS:
      case TT_MUL:
      case TT_DIV:
      case TT_POW:
      case TT_MOD:
      case TT_U_MINUS:
      case TT_U_PLUS:
        if (stack.size() != 0) {
          top_tt = stack.top();
          while ((top_tt.token_type != TT_OPEN_BRACKET) &&
                 (precedence[top_tt.token_type] >=
                  precedence[current_tt.token_type])) {
            result.push_back(stack.top());
            stack.pop();
            if (stack.size() == 0) {
              break;
            }
            top_tt = stack.top();
          }
        }
        stack.push(current_tt);
        break;
      case TT_OPEN_BRACKET:
        stack.push(current_tt);
        break;
      case TT_CLOSE_BRACKET:
        top_tt = stack.top();
        if (stack.size() != 0) {
          while (top_tt.token_type != TT_OPEN_BRACKET) {
            result.push_back(stack.top());
            stack.pop();
            top_tt = stack.top();
            if (stack.size() == 0) {
              std::cout << "Absent open bracket" << std::endl;
              abort();
            }
          }
        }
        if (stack.size() != 0) {
          if (top_tt.token_type != TT_OPEN_BRACKET) {
            std::cout << "Absent open bracket" << std::endl;
            abort();
          }
        }
        stack.pop();
        if (stack.size() != 0) {
          top_tt = stack.top();
          switch (top_tt.token_type) {
            case TT_SIN:
            case TT_COS:
            case TT_TAN:
            case TT_ASIN:
            case TT_ACOS:
            case TT_ATAN:
            case TT_LOG:
            case TT_SQRT:
            case TT_LN:
              result.push_back(stack.top());
              stack.pop();
              break;
          }
        }
        break;
      default:
        break;
    }
  }

  while (stack.size() != 0) {
    result.push_back(stack.top());
    stack.pop();
  }

  return result;
}

double executor(std::list<s21::Token> rpn, double x) {
  double result = 0.0;

  std::stack<s21::Token> stack;

  s21::Token current_tt, a, b;
  s21::Token val;
  s21::Token x_tt;

  for (auto current_tt : rpn) {
    switch (current_tt.token_type) {
      case TT_DIGIT:
        stack.push(current_tt);
        break;
      case TT_X:
        stack.push(x_tt);
        break;
      case TT_SIN:
        a = stack.top();
        stack.pop();
        val.value = sin(a.value);
        stack.push(val);
        break;
      case TT_COS:
        a = stack.top();
        stack.pop();
        val.value = cos(a.value);
        stack.push(val);
        break;
      case TT_TAN:
        a = stack.top();
        stack.pop();
        val.value = tan(a.value);
        stack.push(val);
        break;
      case TT_ASIN:
        a = stack.top();
        stack.pop();
        val.value = asin(a.value);
        stack.push(val);
        break;
      case TT_ACOS:
        a = stack.top();
        stack.pop();
        val.value = acos(a.value);
        stack.push(val);
        break;
      case TT_ATAN:
        a = stack.top();
        stack.pop();
        val.value = atan(a.value);
        stack.push(val);
        break;
      case TT_SQRT:
        a = stack.top();
        stack.pop();
        val.value = sqrt(a.value);
        stack.push(val);
        break;
      case TT_LN:
        a = stack.top();
        stack.pop();
        val.value = log(a.value);
        stack.push(val);
        break;
        // operators
      case TT_LOG:
        a = stack.top();
        stack.pop();
        val.value = log10(a.value);
        stack.push(val);
        break;
        // operators
      case TT_PLUS:
        a = stack.top();
        stack.pop();
        if (stack.size() != 0) {
          b = stack.top();
          stack.pop();
          val.value = a.value + b.value;
        } else {
          val.value = 0 + a.value;
        }
        stack.push(val);
        break;
      case TT_MOD:
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();
        val.value = fmod(b.value, a.value);
        stack.push(val);
        break;
      case TT_MINUS:
        a = stack.top();
        stack.pop();
        if (stack.size() != 0) {
          b = stack.top();
          stack.pop();
          val.value = b.value - a.value;
        } else {
          val.value = 0 - a.value;
        }
        stack.push(val);
        break;
      case TT_MUL:
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();
        val.value = a.value * b.value;
        stack.push(val);
        break;
      case TT_POW:
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();
        val.value = pow(b.value, a.value);
        stack.push(val);
        break;
      case TT_U_MINUS:
        a = stack.top();
        stack.pop();
        val.value = 0 - a.value;
        stack.push(val);
        break;
      case TT_U_PLUS:
        a = stack.top();
        stack.pop();
        val.value = 0 + a.value;
        stack.push(val);
        break;
      case TT_DIV:
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();
        if (b.value != 0.0) {
          val.value = b.value / a.value;
        }
        stack.push(val);
        break;
    }
  }

  if (stack.size() != 0) {
    current_tt = stack.top();
    result = current_tt.value;
  }

  return result;
}

double proverka(std::string text) {  // for test
  std::list<s21::Token> parsed_list;
  std::list<s21::Token> rpn_list;
  double result;

  parsed_list = parse_source(text);
  bool err = check_parse_errors(parsed_list);
  if (err != 1) {
    rpn_list = rpn(parsed_list);
    result = executor(rpn_list, 0);
  } else {
    result = err;
  }
  return result;
}

double for_btnRavno(std::string text) {
  std::list<s21::Token> parsed_list;
  std::list<s21::Token> rpn_list;

  parsed_list = parse_source(text);
  rpn_list = rpn(parsed_list);
  double result = executor(rpn_list, 0);

  return result;
}

#ifndef RPN_EXECUTOR_H
#define RPN_EXECUTOR_H

#include <list>

#include "token.h"

std::list<s21::Token> rpn(std::list<s21::Token> parsed_list);

double executor(std::list<s21::Token> rpn, double x);

double proverka(std::string text);  // for test

double for_btnRavno(std::string text);

#endif  // RPN_EXECUTOR_H

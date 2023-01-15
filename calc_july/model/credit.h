#ifndef CREDIT_H
#define CREDIT_H

#include <ctime>

time_t dateToTimeT(int day, int month, int year);

long days(int d1, int m1, int y1, int d2, int m2, int y2);

void credit(double sz, double stavka, double srok, int year_Box, int type_box,
            long double &plata, long double &percent, long double &all_summ,
            long double &diff, long double &first);

bool deposit(int d1, int m1, int y1, int srok, int year_box, int capital_box,
             double sz, double stavka, long double popoln, long double spisan,
             long double &percent, long double &all_summ, long double &nalog,
             int pereodik);

#endif  // CREDIT_H

#include <cmath>
//#include <ctime>
#include <iomanip>  // точность
#include <iostream>

#include "credit.h"

time_t dateToTimeT(int day, int month, int year) {
  tm tmp = tm();
  tmp.tm_mday = day;
  tmp.tm_mon = month - 1;
  tmp.tm_year = year - 1900;
  return mktime(&tmp);
}

long days(int d1, int m1, int y1, int d2, int m2, int y2) {
  time_t date1 = dateToTimeT(d1, m1, y1);
  time_t date2 = dateToTimeT(d2, m2, y2);

  double sec = difftime(date2, date1);
  long days = static_cast<long>(sec / 86400);

  return days;
}

void credit(double sz, double stavka, double srok, int year_Box, int type_box,
            long double &plata, long double &percent, long double &all_summ,
            long double &diff, long double &first) {
  percent = 0;

  if (year_Box == 0) {
    srok *= 12;
  }
  if (type_box == 0) {
    stavka /= 1200;
    long double x = pow((1 + stavka), srok);
    plata = sz * (stavka * x / (x - 1));
    all_summ = plata * srok;
    percent = all_summ - sz;
  }

  if (type_box == 1) {
    long double osn_dolg = sz / srok;
    stavka /= 1200;   // 12 month and 100 for %
    double sz1 = sz;  // чтобы не потерять sz
    first = osn_dolg + sz1 * stavka;
    for (int i = 1; i <= srok; i++) {
      diff = osn_dolg + sz1 * stavka;
      percent += diff - osn_dolg;
      sz1 -= osn_dolg;
    }
    all_summ = percent + sz;
  }
}

bool deposit(int d1, int m1, int y1, int srok, int year_box, int capital_box,
            double sv, double stavka, long double popoln, long double spisan,
            long double &percent, long double &all_summ, long double &nalog,
            int pereodik) {
  long double rate_CB = 80000;
  int d2, m2, y2;
  bool err = 0;
  if (year_box == 0) {
    d2 = d1 + srok;
    m2 = m1;
    y2 = y1;
  } else if (year_box == 1) {
    d2 = d1;
    m2 = m1 + srok;
    y2 = y1;
  } else if (year_box == 2) {
    d2 = d1;
    m2 = m1;
    y2 = y1 + srok;
    rate_CB *= srok;
  }
  int year_days = ((y1 % 4) == 0) ? 366 : 365;
  // std::cout << d2 <<"."<< m2<<"."<< y2 << std::endl;
  int day = days(d1, m1, y1, d2, m2, y2);
  sv += popoln - spisan;
  if (capital_box == 0) {
    percent = (sv * stavka * day / year_days) / 100;
    all_summ = percent + sv;
    nalog = 0;
    long double cb = percent - rate_CB;
    if (cb > 0) {
      nalog = cb * 0.13;
    }
    all_summ -= nalog;
  }
  if (capital_box == 1) {
    long double perc;
    long double perc_sv;
    percent = 0;
    int n;
    if (pereodik == 0) {
      n = day;
    }
    if (pereodik == 1) {
      if (year_box == 1) {
        n = srok;
      } else if (year_box == 2) {
        n = srok * 12;
      } else if (year_box == 0) {
        // std::cout << "incorrect year_box, need year_box = 0";
        err = 1;
      }
    }
    if (pereodik == 2) {
      if (year_box == 2) {
        n = srok;
      } else if (year_box == 1) {
        if (srok % 12 == 0) {
          n = srok / 12;
        } else {
          // std::cout << "incorrect year_box"<< std::endl;
          err = 1;
        }
      } else {
        // std::cout << "incorrect year_box"<< std::endl;
        err = 1;
      }
    }
    if (err == 0) {
      perc_sv = sv;
      for (int i = 1; i <= n; i++) {
        // std::cout <<"  "<< perc_sv <<" * "<<stavka <<" * "
        //  << day<<" / "<< n <<" / "<< year_days << std::endl;

        perc = (perc_sv * stavka * day / n / year_days) / 100;
        percent += perc;
        perc_sv = percent + sv;
      }
      long double cb = percent - rate_CB;
      if (cb > 0) {
        nalog = cb * 0.13;
      }
      all_summ = sv + percent - nalog;
    }
  }
  return err;
}

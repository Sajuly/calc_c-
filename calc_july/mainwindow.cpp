#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model/parser.h"
#include "model/rpn_executor.h"
#include "model/credit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::token_revision() {
    int code = 0;
    QString str = ui->lineEdit->text();
    if (str.length() != 0) {
        QChar a = str[str.length()-1];
        if (a == '-' || a == '+' || a == '*' || a == '/' || a == '.') {
            code = 1;
        }
     }
    return code;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'1');
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'2');
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'3');
}


void MainWindow::on_pushButton_4_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'4');
}


void MainWindow::on_pushButton_5_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'5');
}


void MainWindow::on_pushButton_6_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'6');
}


void MainWindow::on_pushButton_7_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'7');
}


void MainWindow::on_pushButton_8_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'8');
}


void MainWindow::on_pushButton_9_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'9');
}


void MainWindow::on_pushButton_0_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+'0');
}


void MainWindow::on_pushButton_tochka_clicked()
{
    if (token_revision() == 0) {
        ui->lineEdit->setText(ui->lineEdit->text()+'.');
    }
}


void MainWindow::on_pushButton_acos_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"acos(");
}


void MainWindow::on_pushButton_asin_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text()+"asin(");
}


void MainWindow::on_pushButton_cos_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"cos(");
}


void MainWindow::on_pushButton_sin_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"sin(");
}


void MainWindow::on_pushButton_open_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'(');
}


void MainWindow::on_pushButton_close_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+')');
    }
}


void MainWindow::on_pushButton_tan_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+ "tan(");
}


void MainWindow::on_pushButton_atan_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"atan(");
}


void MainWindow::on_pushButton_ln_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"ln(");
}


void MainWindow::on_pushButton_log_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"log(");
}


void MainWindow::on_pushButton_x_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"x");
}


void MainWindow::on_pushButton_mod_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+ '%');
}


void MainWindow::on_pushButton_pow_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"^");
}


void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"sqrt(");
}


void MainWindow::on_pushButton_bs_clicked()
{
    QString old = ui->lineEdit->text();
    ui->lineEdit->setText(old.mid(0,old.length()-1));
}


void MainWindow::on_pushButton_div_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'/');
    }
}


void MainWindow::on_pushButton_plus_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'+');
    }
}


void MainWindow::on_pushButton_mul_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'*');
    }
}


void MainWindow::on_pushButton_minus_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'-');
    }
}


void MainWindow::on_pushButton_c_clicked()
{
    ui->lineEdit->setText("");
    ui->result_label->setText("");
}


void MainWindow::on_btnRavno_clicked()
{
    std::list<s21::Token> parsed_list;
    QString str1 = ui->lineEdit->text();
    QByteArray ba = str1.toLocal8Bit();
    char *func = ba.data();

    parsed_list = parse_source(func);
    bool err = check_parse_errors(parsed_list);

    if (err) {
        ui->result_label->setText("Unknown lexema");
   } else {
        double result = for_btnRavno(func);
        char res[50];
        sprintf(res, "%.6lf", result);
        ui->result_label->setText(res);
    }

}


void MainWindow::on_graphic_button_clicked()
{
    ui->graphicsView->clearGraphs();
    ui->graphicsView->xAxis->setRange(-10, 10);
    ui->graphicsView->yAxis->setRange(-2, 2);
    ui->graphicsView->addGraph();

   double x = -100;
   double y = 0;
   double delta = 0.1;

   std::list<s21::Token> parsed_list;
   std::list<s21::Token> rpn_list;
   QString str1 = ui->lineEdit->text();
   QByteArray ba = str1.toLocal8Bit();
   char *func = ba.data();

   parsed_list = parse_source(func);
   bool err = check_parse_errors(parsed_list);
   if (err == 1) {
       ui->result_label->setText("Unknown lexema");
   } else {
       rpn_list = rpn(parsed_list);
       for (int i = 0; i < 2000; i++) {
           y = executor(rpn_list, x);
           ui->graphicsView->graph(0)->addData(x, y);
           x += delta;
       }
   }
   ui->graphicsView->replot();
}


void MainWindow::on_pushButton_kredit_clicked()
{
    double sz = ui->lineEdit_sz->text().toDouble();
    double stavka = ui->lineEdit_stavka->text().toDouble();
    double srok = ui->lineEdit_srok->text().toDouble();

    int year_box = ui->year_Box->currentIndex();
    int type_box = ui->type_box->currentIndex();

    long double plata, percent, all_summ, first, diff;

    credit(sz, stavka, srok, year_box, type_box, plata, percent, all_summ, first, diff);

    char res[50];
    if (ui->type_box->currentIndex() == 0) {
        sprintf(res, "%.2Lf", plata);
        ui->result_label_month_plata->setText(res);
    }
     if (ui->type_box->currentIndex() == 1) {
        sprintf(res, "%.2Lf... %.2Lf", first, diff);
        ui->result_label_month_plata->setText(res);
     }
     sprintf(res, "%.2Lf", percent);
     ui->result_label_pereplata->setText(res);
     sprintf(res, "%.2Lf", all_summ);
     ui->result_label_allsumm->setText(res);
}


void MainWindow::on_pushButton_deposit_clicked()
{
     long double sv = ui->lineEdit_sum_vklad->text().toDouble();
     long double stavka = ui->lineEdit_procent_vklad->text().toDouble();
     int srok = ui->lineEdit_srok_vklad->text().toInt();
     long double popoln = ui->lineEdit_spisok_popolnen->text().toDouble();
     long double spisan = ui->lineEdit_spisok_spisat->text().toDouble();
     int d1 = ui->lineEdit_d1->text().toUInt();
     int m1 = ui->lineEdit_m1->text().toUInt();
     int y1 = ui->lineEdit_y1->text().toUInt();

     int year_box = ui->year_Box_2->currentIndex();
     int pereodik = ui->periodik_box->currentIndex();
     int capital_box = ui->capital_Box->currentIndex();

     long double percent, all_summ, nalog;
     char res[50];
     bool err = deposit(d1, m1, y1, srok, year_box, capital_box, sv, stavka, popoln, spisan, percent, all_summ, nalog, pereodik);
     if (err == 0) {
         sprintf(res, "%.2Lf", percent);
         ui->result_label_procent_vklad->setText(res);
         if (capital_box == 0) {
            sprintf(res, "%.2Lf", sv);
         } else {
            sprintf(res, "%.2Lf", all_summ);
         }
         ui->result_label_summ_end->setText(res);
         sprintf(res, "%.2Lf", nalog);
         ui->result_label_nalog->setText(res);
     }
}


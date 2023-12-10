#ifndef S21_CALCULATOR_H
#define S21_CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_calc.h"
#ifdef __cplusplus
}
#endif
#include <QMainWindow>
#include <QVector>
#include <iostream>

#include "credit.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Credit *window_credit;
  void remove_zero();
  int flag = 0;
  double xBegin, xEnd, h, X;
  QVector<double> x, y;

 private slots:
  void cleanall();
  void open_credit();
  void make_graph();
  void operator_remove();
  void operations();
  void dig_numbers();
  void point_clicked();
  void calc();
  void trig_func();
  void mult_div_func();
  void x_operator();
};
#endif  // S21_CALCULATOR_H

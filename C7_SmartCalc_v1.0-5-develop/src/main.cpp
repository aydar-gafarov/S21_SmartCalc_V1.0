#include <QApplication>

#include "s21_calculator.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

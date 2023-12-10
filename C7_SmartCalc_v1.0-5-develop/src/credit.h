#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QPixmap>
#ifdef __cplusplus
extern "C" {
#endif
#include "s21_calc.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private:
  Ui::Credit *ui;
  int var_credit = -1;  // 0 - Annuity, 1 - differen
 private slots:
  void annuity_button();
  void differen_button();
  void credit_calculate();
};

#endif  // CREDIT_H

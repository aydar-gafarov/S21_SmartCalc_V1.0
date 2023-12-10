#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  this->setWindowTitle("Credit Calculator");
  QPixmap pix(":/res/png_for_credit_calc.jpeg");
  pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Window, pix);
  this->setPalette(palette);
  connect(ui->calc_credit, SIGNAL(clicked()), this, SLOT(credit_calculate()));
  connect(ui->annuity, SIGNAL(clicked()), this, SLOT(annuity_button()));
  connect(ui->differen, SIGNAL(clicked()), this, SLOT(differen_button()));
  ui->sum_credit_spinbox->setRange(0, 10000000);
  ui->month_spinbox->setRange(0, 10000000);
  ui->precent_spinbox->setRange(0, 10000000);
}

Credit::~Credit() { delete ui; }
void Credit::annuity_button() { var_credit = 0; }
void Credit::differen_button() { var_credit = 1; }

void Credit::credit_calculate() {
  credit_stack stack_credit = {0, 0, 0, 0};
  double sum_credit = ui->sum_credit_spinbox->value();
  int month = ui->month_spinbox->value();
  double percent = ui->precent_spinbox->value();
  if (var_credit == 0) {
    s21_credit_annuity(sum_credit, month, percent, &stack_credit);
    ui->monthly_pay->setText(QString::number(stack_credit.payment));
    ui->overpay->setText(QString::number(stack_credit.overpayment));
    ui->total_pay->setText(QString::number(stack_credit.total_payment));
  } else if (var_credit == 1) {
    s21_credit_differ(sum_credit, month, percent, &stack_credit);
    ui->monthly_pay->setText(QString::number(stack_credit.first_payment) +
                             " ... " + QString::number(stack_credit.payment));
    ui->overpay->setText(QString::number(stack_credit.overpayment));
    ui->total_pay->setText(QString::number(stack_credit.total_payment));
  } else {
    ui->monthly_pay->setText("ERROR");
    ui->overpay->setText("ERROR");
    ui->total_pay->setText("<<<< Choose mod");
  }
}

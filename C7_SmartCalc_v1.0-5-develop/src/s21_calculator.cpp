#include "s21_calculator.h"

#include "./ui_s21_calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Calculator");
  connect(ui->zero, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(dig_numbers()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(mult_div_func()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(mult_div_func()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->l_bracket, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->r_bracket, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->degree, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->tg, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->atg, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(trig_func()));
  connect(ui->point, SIGNAL(clicked()), this, SLOT(point_clicked()));
  connect(ui->equal, SIGNAL(clicked()), this, SLOT(calc()));
  connect(ui->remove, SIGNAL(clicked()), this, SLOT(operator_remove()));
  connect(ui->button_graph, SIGNAL(clicked()), this, SLOT(make_graph()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(x_operator()));
  connect(ui->credit_open, SIGNAL(clicked()), this, SLOT(open_credit()));
  connect(ui->cleanAll, SIGNAL(clicked()), this, SLOT(cleanall()));
  ui->x_max_change->setRange(-1000000, 1000000);
  ui->x_min_change->setRange(-1000000, 1000000);
  ui->y_max_change->setRange(-1000000, 1000000);
  ui->y_min_change->setRange(-1000000, 1000000);
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::open_credit() {
  window_credit = new Credit(this);
  window_credit->show();
}
void MainWindow::cleanall() {
  flag = 0;
  remove_zero();
}
void MainWindow::make_graph() {
  double y_max_coor = ui->y_max_change->value();
  double y_min_coor = ui->y_min_change->value();
  double x_max_coor = ui->x_max_change->value();
  double x_min_coor = ui->x_min_change->value();
  ui->graphic->clearGraphs();
  ui->graphic->xAxis->setRange(x_min_coor, x_max_coor);
  ui->graphic->yAxis->setRange(y_min_coor, y_max_coor);
  h = 0.1;
  xBegin = -1000;
  xEnd = 1000 + h;
  QString str = ui->input_field->text();
  for (X = xBegin; X <= xEnd; X += h) {
    if (X > -0.01 && X < 0.01) continue;
    QString new_str = str;
    QString number_x = QString::number(X);
    new_str.replace('x', "(" + number_x + ")");
    x.push_back(X);
    double res = s21_calculator(new_str.toStdString().c_str());
    if (isnan(res)) {
      ui->input_field->setText("ERROR");
    }
    y.push_back(res);
  }
  ui->graphic->addGraph();
  ui->graphic->graph(0)->addData(x, y);
  ui->graphic->replot();
  x.clear();
  y.clear();
}
void MainWindow::mult_div_func() {
  QString temp = ui->input_field->text().back();
  if (temp == '*' || temp == '/') {
    ui->input_field->setText("ERROR");
    flag = 0;
  } else {
    QPushButton *button = (QPushButton *)sender();
    ui->input_field->setText(ui->input_field->text() + button->text());
  }
}

void MainWindow::x_operator() {
  QString str = ui->input_field->text();
  if (!(ui->input_field->text().endsWith('x'))) {
    if (str == "0" || str == "ERROR") remove_zero();
    ui->input_field->setText(ui->input_field->text() + "x");
  }
}

void MainWindow::trig_func() {
  remove_zero();
  QPushButton *button = (QPushButton *)sender();
  ui->input_field->setText(ui->input_field->text() + button->text() + "(");
}
void MainWindow::dig_numbers() {
  remove_zero();
  QPushButton *button = (QPushButton *)sender();
  QString new_text = ui->input_field->text();
  if (new_text == "0") {
    flag = 0;
    remove_zero();
  }
  ui->input_field->setText(ui->input_field->text() + button->text());
}

void MainWindow::operator_remove() {
  QString new_text = ui->input_field->text();
  new_text.chop(1);
  ui->input_field->setText(new_text);
}

void MainWindow::point_clicked() {
  if (!(ui->input_field->text().endsWith('.')))
    ui->input_field->setText(ui->input_field->text() + ".");
}

void MainWindow::operations() {
  remove_zero();
  QPushButton *button = (QPushButton *)sender();
  ui->input_field->setText(ui->input_field->text() + button->text());
}

void MainWindow::calc() {
  QString n_text = ui->input_field->text();
  ;
  if (ui->input_field->text().contains("x")) {
    QString number_x = QString::number(ui->x_value_calc->value());
    n_text.replace('x', "(" + number_x + ")");
  }
  double res = s21_calculator(n_text.toStdString().c_str());
  if (isnan(res)) {
    ui->input_field->setText("ERROR");
    flag = 0;
  } else
    ui->input_field->setText(QString::number(res, 'g', 10));
}
void MainWindow::remove_zero() {
  if (flag == 0) {
    ui->input_field->clear();
    flag = 1;
  }
}

#include "calculatorwindow.h"

#include "ui_calculatorwindow.h"

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CalculatorWindow) {
  ui_->setupUi(this);
  ui_->lineEdit->setStyleSheet("background-color: white; color: black;");
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(InputNumber()));
  connect(ui_->pushButton_left, SIGNAL(clicked()), this, SLOT(InputBracket()));
  connect(ui_->pushButton_right, SIGNAL(clicked()), this, SLOT(InputBracket()));
  connect(ui_->pushButton_X, SIGNAL(clicked()), this, SLOT(InputX()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(InputDot()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(InputOperation()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(InputOperation()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(InputOperation()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(InputOperation()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(InputOperation()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(InputOperation()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(InputFunction()));
  connect(ui_->pushButton_ac, SIGNAL(clicked()), this, SLOT(InputClear()));
  connect(ui_->pushButton_del, SIGNAL(clicked()), this, SLOT(InputClearLast()));
  connect(ui_->pushButton_equal, SIGNAL(clicked()), this, SLOT(OutputResult()));
  connect(ui_->pushButton_graph, SIGNAL(clicked()), this, SLOT(OutputGraph()));
}

void CalculatorWindow::InputNumber() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputNumber(ui_->lineEdit->text().toStdString()) ==
      0)
    return;
  ui_->lineEdit->insert(button->text());
}

void CalculatorWindow::InputDot() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputDot(ui_->lineEdit->text().toStdString()) == 0)
    return;
  ui_->lineEdit->insert(button->text());
}

void CalculatorWindow::InputX() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputX(ui_->lineEdit->text().toStdString()) == 0)
    return;
  ui_->lineEdit->insert(button->text());
}

void CalculatorWindow::InputBracket() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputBracket(button->text().toStdString(),
                                        ui_->lineEdit->text().toStdString()) ==
      0)
    return;
  ui_->lineEdit->insert(button->text());
}

void CalculatorWindow::InputOperation() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputOperation(
          button->text().toStdString(), ui_->lineEdit->text().toStdString()) ==
      0)
    return;
  ui_->lineEdit->insert(button->text());
}

void CalculatorWindow::InputFunction() {
  QPushButton *button = (QPushButton *)sender();
  if (controller_.ValidatorInputFunction(ui_->lineEdit->text().toStdString()) ==
      0)
    return;
  ui_->lineEdit->insert(button->text() + "(");
}

void CalculatorWindow::InputClear() { ui_->lineEdit->setText(""); }

void CalculatorWindow::InputClearLast() {
  if (ui_->lineEdit->text().size() == 1) {
    ui_->lineEdit->setText("");
  } else {
    ui_->lineEdit->setText(
        ui_->lineEdit->text().left(ui_->lineEdit->text().size() - 1));
  }
}

void CalculatorWindow::OutputResult() {
  if (ui_->lineEdit->text().size() == 0) {
    ui_->lineEdit->setText("");
  } else {
    if (controller_.Validator(ui_->lineEdit->text().toStdString()) == 0) {
      ui_->lineEdit->setText("invalid input");
      return;
    }
    controller_.Input(ui_->lineEdit->text().toStdString(),
                      ui_->doubleSpinBox_X->value());
    double number = controller_.Calculate();
    if (number == INFINITY || number == -INFINITY || std::isnan(number)) {
      ui_->lineEdit->setText("Oh no! Follow rules of math");
    } else {
      ui_->lineEdit->setText(QString::number(number));
    }
  }
}

void CalculatorWindow::OutputGraph() {
  if (controller_.Validator(ui_->lineEdit->text().toStdString()) == 0) {
    ui_->lineEdit->setText("invalid input");
    return;
  }
  ui_->customPlot->clearGraphs();
  controller_.Input(ui_->lineEdit->text().toStdString(),
                    ui_->doubleSpinBox_X->value());
  double x_min_num, x_max_num, range_x, range_y;
  x_min_num = ui_->doubleSpinBox_1->value();
  x_max_num = ui_->doubleSpinBox_2->value();
  range_x = ui_->doubleSpinBox_3->value();
  range_y = ui_->doubleSpinBox_4->value();
  xBegin_ = x_min_num;
  xEnd_ = x_max_num;
  ui_->customPlot->xAxis->setRange(-1 * range_x, range_x);
  ui_->customPlot->yAxis->setRange(-1 * range_y, range_y);
  h_ = 0.1;
  N_ = (xEnd_ - xBegin_) / h_ + 2;
  for (X_ = xBegin_; X_ <= xEnd_; X_ += h_) {
    x_.push_back(X_);
    controller_.Input(ui_->lineEdit->text().toStdString(), X_);
    y_.push_back(controller_.Calculate());
  }
  ui_->customPlot->addGraph();
  ui_->customPlot->graph(0)->addData(x_, y_);
  ui_->customPlot->setInteraction(QCP::iRangeZoom, true);
  ui_->customPlot->setInteraction(QCP::iRangeDrag, true);
  ui_->customPlot->replot();
  x_.clear();
  y_.clear();
}

CalculatorWindow::~CalculatorWindow() { delete ui_; }

#include "mainwindow.h"

#include "calculatorwindow.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  this->setWindowTitle("Calculator");
  ui_->stackedWidget->addWidget(new CalculatorWindow());
  ui_->stackedWidget->addWidget(new CreditWindow());
  ui_->stackedWidget->addWidget(new DepositWindow());
  this->setFixedSize(1300, 600);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_actionCalculator_triggered() {
  ui_->stackedWidget->setCurrentIndex(0);
  this->setWindowTitle("Calculator");
  ui_->stackedWidget->setStyleSheet(
      "QStackedWidget {background-image: "
      "url(:/styles/backgroundcalculator.png)}");
  this->setFixedSize(1300, 600);
}

void MainWindow::on_actionCredit_triggered() {
  ui_->stackedWidget->setCurrentIndex(1);
  this->setWindowTitle("Credit");
  ui_->stackedWidget->setStyleSheet(
      "QStackedWidget {background-image: url(:/styles/backgroundcredit.png)}");
  this->setFixedSize(1000, 500);
}

void MainWindow::on_actionDeposit_triggered() {
  ui_->stackedWidget->setCurrentIndex(2);
  this->setWindowTitle("Deposit");
  ui_->stackedWidget->setStyleSheet(
      "QStackedWidget {background-image: url(:/styles/backgrounddeposit.png)}");
  this->setFixedSize(1400, 900);
}

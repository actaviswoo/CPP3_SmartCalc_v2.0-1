#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::DepositWindow) {
  ui_->setupUi(this);
  replenishmentsBoxLayout_ = new QVBoxLayout();
  ui_->scrollReplenishments->widget()->setLayout(replenishmentsBoxLayout_);
  ui_->ReplenishmentsLayout->addWidget(ui_->scrollReplenishments);
  ui_->scrollReplenishments->setStyleSheet("background-color: transparent;");

  withdrawalsBoxLayout_ = new QVBoxLayout();
  ui_->scrollWithdrawals->widget()->setLayout(withdrawalsBoxLayout_);
  ui_->WithdrawalsLayout->addWidget(ui_->scrollWithdrawals);
  ui_->scrollWithdrawals->setStyleSheet("background-color: transparent;");

  connect(ui_->pushButton_calc, SIGNAL(clicked()), this, SLOT(OutputResult()));
  connect(ui_->pushButton_ac, SIGNAL(clicked()), this, SLOT(SetDefault()));

  connect(ui_->pushButton_addReplenishments, &QPushButton::clicked, this,
          [this]() { AddClicked(true, &replenishmentsBox_); });
  connect(ui_->pushButton_addWithdrawals, &QPushButton::clicked, this,
          [this]() { AddClicked(false, &withdrawalsBox_); });

  connect(ui_->pushButton_deleteReplenishments, &QPushButton::clicked, this,
          [this]() {
            DeleteClicked(&replenishmentsCount_, &replenishmentsBox_,
                          replenishmentsBoxLayout_);
          });
  connect(ui_->pushButton_deleteWithdrawals, &QPushButton::clicked, this,
          [this]() {
            DeleteClicked(&withdrawalsCount_, &withdrawalsBox_,
                          withdrawalsBoxLayout_);
          });
}

DepositWindow::~DepositWindow() { delete ui_; }

void DepositWindow::GetTypes() {
  depositAmount_ = ui_->doubleSpinBox_depositAmount->value();
  depositTerm_ = ui_->spinBox_depositTerm->value();
  if (ui_->radioButton_day->isChecked()) {
    lastDate_ = QDate::currentDate().addDays(depositTerm_);
  } else if (ui_->radioButton_month->isChecked()) {
    lastDate_ = QDate::currentDate().addMonths(depositTerm_);
    depositTerm_ *= 30;
  } else if (ui_->radioButton_year->isChecked()) {
    lastDate_ = QDate::currentDate().addYears(depositTerm_);
    depositTerm_ *= 365;
  }
  interestRate_ = ui_->doubleSpinBox_interestRate->value();
  taxRate_ = ui_->doubleSpinBox_taxRate->value();
  if (ui_->radioButton_everyDay->isChecked())
    period_ = 1;
  else if (ui_->radioButton_everyWeek->isChecked())
    period_ = 2;
  else if (ui_->radioButton_everyMonth->isChecked())
    period_ = 3;
  else if (ui_->radioButton_everyQuarter->isChecked())
    period_ = 4;
  else if (ui_->radioButton_everyHalf->isChecked())
    period_ = 5;
  else if (ui_->radioButton_everyYear->isChecked())
    period_ = 6;
  ui_->radioButton_capitalization->isChecked() ? capitalization_ = true
                                               : capitalization_ = false;
}

void DepositWindow::SetDefault() {
  ui_->label_accrued_interest->setText("0");
  ui_->label_tax_amount->setText("0");
  ui_->label_income_after_taxes->setText("0");
  ui_->label_deposit_amount_end_of_term->setText("0");
  while (withdrawalsCount_ != 0) {
    DeleteClicked(&withdrawalsCount_, &withdrawalsBox_, withdrawalsBoxLayout_);
  }
  while (replenishmentsCount_ != 0) {
    DeleteClicked(&replenishmentsCount_, &replenishmentsBox_,
                  replenishmentsBoxLayout_);
  }
  ui_->spinBox_depositTerm->setValue(1);
  ui_->doubleSpinBox_depositAmount->setValue(1000);
  ui_->doubleSpinBox_interestRate->setValue(1);
  ui_->doubleSpinBox_taxRate->setValue(13);
  ui_->radioButton_capitalization->setChecked(false);
  ui_->radioButton_everyWeek->setChecked(true);
  ui_->radioButton_month->setChecked(true);
}

void DepositWindow::SetNull() {
  depositAmount_ = 0;
  depositTerm_ = 0;
  interestRate_ = 0;
  taxRate_ = 0;
  period_ = 0;
  capitalization_ = false;
  replenishments_.period.clear();
  replenishments_.day.clear();
  replenishments_.deposit_amount.clear();
  withdrawals_.period.clear();
  withdrawals_.day.clear();
  withdrawals_.deposit_amount.clear();
  accruedInterest_ = 0;
  taxAmount_ = 0;
  depositEnd_ = 0;
  depositTotal_ = 0;
}

void DepositWindow::OutputResult() {
  SetNull();
  GetTypes();
  GetDepositData(&replenishments_, &replenishmentsBox_, replenishmentsCount_);
  GetDepositData(&withdrawals_, &withdrawalsBox_, withdrawalsCount_);
  controller_.DepositCalculate(depositAmount_, depositTerm_, interestRate_,
                               taxRate_, period_, capitalization_,
                               replenishments_, withdrawals_, &accruedInterest_,
                               &taxAmount_, &depositEnd_, &depositTotal_);
  ui_->label_accrued_interest->setText(QString::number(accruedInterest_));
  ui_->label_tax_amount->setText(QString::number(taxAmount_));
  ui_->label_income_after_taxes->setText(QString::number(depositEnd_));
  ui_->label_deposit_amount_end_of_term->setText(
      QString::number(depositTotal_));
}

void DepositWindow::AddClicked(bool flag, DepositWindow::DepositBox *box) {
  if (flag) {
    comboBox_ = new QComboBox(ui_->scrollReplenishments->widget());
    dateEdit_ = new QDateEdit(ui_->scrollReplenishments->widget());
    doubleSpinBox_ = new QDoubleSpinBox(ui_->scrollReplenishments->widget());
  } else {
    comboBox_ = new QComboBox(ui_->scrollWithdrawals->widget());
    dateEdit_ = new QDateEdit(ui_->scrollWithdrawals->widget());
    doubleSpinBox_ = new QDoubleSpinBox(ui_->scrollWithdrawals->widget());
  }
  Add(flag);
  box->vectorDateEdit_.push_back(dateEdit_);
  box->vectorDoubleSpinBox_.push_back(doubleSpinBox_);
  box->vectorComboBox_.push_back(comboBox_);
  if (flag) {
    replenishmentsCount_++;
  } else {
    withdrawalsCount_++;
  }
}

void DepositWindow::DeleteClicked(int *count, DepositWindow::DepositBox *box,
                                  QVBoxLayout *boxlayout) {
  if (*count) {
    QLayout *layout = boxlayout->itemAt(*count - 1)->layout();
    QWidget *widget1 = layout->itemAt(0)->widget();
    QWidget *widget2 = layout->itemAt(1)->widget();
    QWidget *widget3 = layout->itemAt(2)->widget();
    delete layout;
    delete widget1;
    delete widget2;
    delete widget3;
    box->vectorDateEdit_.pop_back();
    box->vectorDoubleSpinBox_.pop_back();
    box->vectorComboBox_.pop_back();
    (*count)--;
  }
}

void DepositWindow::Add(bool flag) {
  QHBoxLayout *layout_ = new QHBoxLayout();
  layout_->setContentsMargins(0, 0, 0, 0);
  CreateComboBox();
  layout_->addWidget(comboBox_);
  CreateDateEdit();
  layout_->addWidget(dateEdit_);
  dateEdit_->setDate(QDate::currentDate());
  CreateDoubleSpinBox();
  layout_->addWidget(doubleSpinBox_);
  layout_->setSpacing(0);
  if (flag)
    replenishmentsBoxLayout_->addLayout(layout_);
  else
    withdrawalsBoxLayout_->addLayout(layout_);
}

void DepositWindow::GetDepositData(s21::DepositData *data, DepositBox *box,
                                   int count) {
  for (int i = 0; i < count; i++) {
    QDate date = box->vectorDateEdit_[i]->date();
    double value = box->vectorDoubleSpinBox_[i]->value();
    QString every = box->vectorComboBox_[i]->currentText();
    if (date <= lastDate_) {
      data->deposit_amount.push_back(value);
      data->day.push_back(QDate::currentDate().daysTo(date));
      if (every == "1") {
        data->period.push_back(1);
      } else if (every == "1/30") {
        data->period.push_back(2);
      } else if (every == "1/60") {
        data->period.push_back(3);
      } else if (every == "1/90") {
        data->period.push_back(4);
      } else if (every == "1/180") {
        data->period.push_back(5);
      } else if (every == "1/365") {
        data->period.push_back(6);
      }
    }
  }
}

void DepositWindow::CreateComboBox() {
  comboBox_->setFixedWidth(80);
  comboBox_->setFixedHeight(80);
  comboBox_->addItem("1");
  comboBox_->addItem("1/30");
  comboBox_->addItem("1/60");
  comboBox_->addItem("1/90");
  comboBox_->addItem("1/180");
  comboBox_->addItem("1/365");
  comboBox_->setStyleSheet(
      ""
      "QComboBox::down-arrow { image: none; } QComboBox{ font-weight: bold; "
      "padding-left:25px; color: black; background-color: "
      "transparent;background-image: "
      "url(:/styles/button/frame.png);background-repeat: "
      "no-repeat;background-position: center;width: 80px;height: "
      "80px;}QComboBox::lineEdit { padding-left: 4px; color: black}"
      "");
}
void DepositWindow::CreateDateEdit() {
  dateEdit_->setCalendarPopup(true);
  dateEdit_->setFixedWidth(160);
  dateEdit_->setFixedHeight(80);
  dateEdit_->setAlignment(Qt::AlignCenter);
  dateEdit_->setStyleSheet(
      "QDateEdit{background-color: transparent;background-image: "
      "url(:/styles/button/frame_big.png);background-repeat: "
      "no-repeat;background-position: center;color: black; font-weight: "
      "bold;}");
}
void DepositWindow::CreateDoubleSpinBox() {
  doubleSpinBox_->setFixedWidth(160);
  doubleSpinBox_->setFixedHeight(80);
  doubleSpinBox_->setAlignment(Qt::AlignCenter);
  doubleSpinBox_->setMinimum(1);
  doubleSpinBox_->setMaximum(100000000);
  doubleSpinBox_->setStyleSheet(
      ""
      "QDoubleSpinBox {background-color: transparent;background-image: "
      "url(:/styles/button/frame_big.png);background-repeat: "
      "no-repeat;background-position: center;color: "
      "black;}QDoubleSpinBox::up-button, QDoubleSpinBox::down-button {width: "
      "0px;height: 0px;}"
      "");
}

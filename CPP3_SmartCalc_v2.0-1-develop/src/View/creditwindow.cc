#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreditWindow) {
  ui_->setupUi(this);
  connect(ui_->pushButton_ac, SIGNAL(clicked()), this, SLOT(SetDefault()));
  connect(ui_->pushButton_calc, SIGNAL(clicked()), this, SLOT(OutputResult()));
}

CreditWindow::~CreditWindow() { delete ui_; }

void CreditWindow::OutputResult() {
  SetNull();
  GetTypes();
  controller_->CreditCalculate(totalCreditAmount_, term_, interestRate_, type_,
                               &monthlyPayment_, &overpaymentOnCredit_,
                               &totalPayment_, &diffMonthlyPaymentMax_,
                               &diffMonthlyPaymentMin_);
  if (type_ == 1) {
    ui_->label_monthlyPayment->setText(QString::number(monthlyPayment_));
    ui_->label_overpaymentOnCredit->setText(
        QString::number(overpaymentOnCredit_));
    ui_->label_totalPayment->setText(QString::number(totalPayment_));
  } else {
    QFont font;
    font.setPointSize(9);
    if ((QString::number(diffMonthlyPaymentMin_) + "..." +
         QString::number(diffMonthlyPaymentMax_))
            .size() >= 20)
      ui_->label_monthlyPayment->setFont(font);
    ui_->label_monthlyPayment->setText(QString::number(diffMonthlyPaymentMin_) +
                                       "..." +
                                       QString::number(diffMonthlyPaymentMax_));
    ui_->label_overpaymentOnCredit->setText(
        QString::number(overpaymentOnCredit_));
    ui_->label_totalPayment->setText(QString::number(totalPayment_));
  }
}

void CreditWindow::GetTypes() {
  totalCreditAmount_ = ui_->doubleSpinBox_totalCreditAmount->value();
  term_ = (ui_->spinBox_year->value() * 12 + ui_->spinBox_month->value());
  interestRate_ = ui_->doubleSpinBox_interestRate->value();
  if (ui_->radioButton_ann->isChecked()) {
    type_ = 1;
  } else if (ui_->radioButton_diff->isChecked()) {
    type_ = 0;
  }
}

void CreditWindow::SetDefault() {
  ui_->label_monthlyPayment->setText("0");
  ui_->label_overpaymentOnCredit->setText("0");
  ui_->label_totalPayment->setText("0");
  ui_->doubleSpinBox_totalCreditAmount->setValue(1000);
  ui_->spinBox_year->setValue(0);
  ui_->spinBox_month->setValue(1);
  ui_->doubleSpinBox_interestRate->setValue(1);
  ui_->radioButton_ann->setChecked(true);
}

void CreditWindow::SetNull() {
  totalCreditAmount_ = 0;
  term_ = 0;
  interestRate_ = 0;
  type_ = 1;
  monthlyPayment_ = 0;
  overpaymentOnCredit_ = 0;
  totalPayment_ = 0;
  diffMonthlyPaymentMax_ = 0;
  diffMonthlyPaymentMin_ = 0;
}

#include "creditwindow.h"

#include "ui_creditwindow.h"

namespace s21 {
bool g_credit_dot_flag = false;

CreditWindow::CreditWindow(QWidget* parent, S21SmartCalcController* controller)
    : FinanceWindow(parent, controller), ui_(new Ui::CreditWindow) {
  ui_->setupUi(this);
  this->setStyleSheet("background-color: black;");
  if (controller != nullptr) {
    connect(this, &CreditWindow::CalculateExpression, controller,
            &S21SmartCalcController::OnCalculateExpression);
  }
  for (int i = 0; i <= 9; ++i) {
    connect(findChild<QPushButton*>(QString("pushButton_%1").arg(i)),
            SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  }
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(Signes()));
  connect(ui_->pushButton_pr, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_sum, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_time, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_del, SIGNAL(clicked()), this, SLOT(CalcFunctions()));
  connect(ui_->pushButton_ac, SIGNAL(clicked()), this, SLOT(CalcFunctions()));
  connect(ui_->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEqClicked()));
}

CreditWindow::~CreditWindow() { delete ui_; }

void CreditWindow::UpdateActiveParameter(QString& activeParam,
                                         const QString& button_text) {
  activeParam += button_text;
  UpdateInputDisplay();
}

void CreditWindow::DigitsNumbers() {
  QPushButton* button = (QPushButton*)sender();
  UpdateActiveParameter(
      (pr_is_active_ ? inputed_pr_
                     : (sum_is_active_ ? inputed_sum_ : inputed_time_)),
      button->text());
}

void CreditWindow::Signes() {
  if (!g_credit_dot_flag) {
    g_credit_dot_flag = true;
    UpdateActiveParameter(
        (pr_is_active_ ? inputed_pr_
                       : (sum_is_active_ ? inputed_sum_ : inputed_time_)),
        ".");
  }
}

void CreditWindow::Parameters() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  pr_is_active_ = button_text == "PR";
  sum_is_active_ = button_text == "SUM";
  time_is_active_ = button_text == "TIME";
}

void CreditWindow::CalcFunctions() {
  QPushButton* button = (QPushButton*)sender();
  QString calcfunc = button->text();
  QString& activeParam =
      (pr_is_active_ ? inputed_pr_
                     : (sum_is_active_ ? inputed_sum_ : inputed_time_));
  if (calcfunc == "AC") activeParam.clear();
  if (calcfunc == "DEL") activeParam.chop(1);
  UpdateInputDisplay();
}

void CreditWindow::OnPushButtonEqClicked() {
  if (ui_->radioButton_ann->isChecked()) {
    CalcAnnuity();
  } else if (ui_->radioButton_diff->isChecked()) {
    CalcDifferentiated();
  }
  g_credit_dot_flag = false;
  pr_is_active_ = false;
  sum_is_active_ = false;
  time_is_active_ = false;
}

void CreditWindow::DisplayResult(const QString& result) {
  double monthly_payment = result.toDouble();
  int total_months = ui_->input_time->text().toInt();
  double loan_amount = ui_->input_sum->text().toDouble();
  QString result_text;

  if (ui_->radioButton_ann->isChecked()) {
    double total_payment = monthly_payment * total_months;
    double overpayment = total_payment - loan_amount;
    result_text = "Аннуитетный платеж: " + QString::number(monthly_payment) +
                  "\n" + "Общая выплата: " + QString::number(total_payment) +
                  "\n" +
                  "Переплата по кредиту: " + QString::number(overpayment);
    ResultDialog dialog_ann(this);
    dialog_ann.setResultText(result_text);
    dialog_ann.exec();
  } else if (ui_->radioButton_diff->isChecked()) {
    double monthly_payment = result.toDouble();
    int current_month = diff_payment_info_.monthly_payments.size() + 1;
    diff_payment_info_.monthly_payments.append(monthly_payment);
    diff_payment_info_.total_diff_payment += monthly_payment;
    diff_payment_info_.payment_details += QString("Месяц %1: Платеж %2\n")
                                              .arg(current_month)
                                              .arg(monthly_payment);

    if (current_month == total_months) {
      double overpayment = diff_payment_info_.total_diff_payment - loan_amount;
      diff_payment_info_.payment_details +=
          QString("Общая выплата: %1\nПереплата: %2")
              .arg(diff_payment_info_.total_diff_payment)
              .arg(overpayment);
      ResultDialog dialog_diff(this);
      dialog_diff.setResultText(diff_payment_info_.payment_details);
      dialog_diff.exec();
      diff_payment_info_.monthly_payments.clear();
      diff_payment_info_.total_diff_payment = 0;
      diff_payment_info_.payment_details.clear();
    }
  }
}

void CreditWindow::CalcAnnuity() {
  QString pr_expression = ui_->input_pr->text();
  QString sum_expression = ui_->input_sum->text();
  QString time_expression = ui_->input_time->text();
  QString expression = sum_expression + "*(" + pr_expression + "/1200*(1+" +
                       pr_expression + "/1200)^" + time_expression + ")/((1+" +
                       pr_expression + "/1200)^" + time_expression + "-1)";
  emit CalculateExpression(expression);
}

void CreditWindow::CalcDifferentiated() {
  QString pr_expression = ui_->input_pr->text();
  QString sum_expression = ui_->input_sum->text();
  QString time_expression = ui_->input_time->text();
  for (int month = 0; month < time_expression.toInt(); month++) {
    QString expression = sum_expression + "/" + time_expression + "+(" +
                         sum_expression + "-(" + QString::number(month) +
                         ")*(" + sum_expression + "/" + time_expression +
                         "))*(" + pr_expression + "/1200)";
    emit CalculateExpression(expression);
  }
  diff_payment_info_.total_diff_payment = 0;
  diff_payment_info_.monthly_payments.clear();
}

void CreditWindow::UpdateInputDisplay() {
  ui_->input_pr->setText(inputed_pr_);
  ui_->input_sum->setText(inputed_sum_);
  ui_->input_time->setText(inputed_time_);
}

void CreditWindow::closeEvent(QCloseEvent* event) {
  QMainWindow::closeEvent(event);
  emit WindowClosed();
}
}  // namespace s21

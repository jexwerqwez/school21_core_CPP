#include "depositwindow.h"

#include "ui_depositwindow.h"

namespace s21 {
bool g_deposit_dot_flag = false;

DepositWindow::DepositWindow(QWidget* parent,
                             S21SmartCalcController* controller)
    : FinanceWindow(parent, controller), ui_(new Ui::DepositWindow) {
  ui_->setupUi(this);
  this->setStyleSheet("background-color: black;");
  if (controller_ != nullptr) {
    connect(this, &DepositWindow::CalculateExpression, controller_,
            &S21SmartCalcController::OnCalculateExpression);
  }
  for (int i = 0; i <= 9; ++i) {
    connect(findChild<QPushButton*>(QString("pushButton_%1").arg(i)),
            SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  }
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(Signes()));
  connect(ui_->pushButton_semicolon, SIGNAL(clicked()), this, SLOT(Signes()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_pr, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_sum, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_time, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_period, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_nalog, SIGNAL(clicked()), this, SLOT(Parameters()));
  connect(ui_->pushButton_del, SIGNAL(clicked()), this, SLOT(CalcFunctions()));
  connect(ui_->pushButton_ac, SIGNAL(clicked()), this, SLOT(CalcFunctions()));
  connect(ui_->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEqClicked()));
}

DepositWindow::~DepositWindow() { delete ui_; }

void DepositWindow::UpdateActiveParameter(QString& activeParam,
                                          const QString& button_text) {
  activeParam += button_text;
  UpdateInputDisplay();
}

void DepositWindow::DigitsNumbers() {
  QPushButton* button = (QPushButton*)sender();
  QString& activeParam = pr_is_active_      ? inputed_pr_
                         : sum_is_active_   ? inputed_sum_
                         : time_is_active_  ? inputed_time_
                         : minus_is_active_ ? inputed_minus_
                         : plus_is_active_  ? inputed_plus_
                         : nalog_is_active_ ? inputed_nalog_
                                            : inputed_period;
  UpdateActiveParameter(activeParam, button->text());
}

void DepositWindow::Signes() {
  if (!g_deposit_dot_flag) {
    g_deposit_dot_flag = true;
    QString& activeParam = pr_is_active_      ? inputed_pr_
                           : sum_is_active_   ? inputed_sum_
                           : time_is_active_  ? inputed_time_
                           : minus_is_active_ ? inputed_minus_
                           : plus_is_active_  ? inputed_plus_
                           : nalog_is_active_ ? inputed_nalog_
                                              : inputed_period;
    UpdateActiveParameter(activeParam, ".");
  }
}

void DepositWindow::Parameters() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  pr_is_active_ = button_text == "PR";
  sum_is_active_ = button_text == "SUM";
  time_is_active_ = button_text == "TIME";
  minus_is_active_ = button_text == "MINUS";
  plus_is_active_ = button_text == "PLUS";
  nalog_is_active_ = button_text == "NALOG";
  period_is_active_ = button_text == "PERIOD";
}

void DepositWindow::CalcFunctions() {
  QPushButton* button = (QPushButton*)sender();
  QString calcfunc = button->text();
  QString& activeParam = pr_is_active_      ? inputed_pr_
                         : sum_is_active_   ? inputed_sum_
                         : time_is_active_  ? inputed_time_
                         : minus_is_active_ ? inputed_minus_
                         : plus_is_active_  ? inputed_plus_
                         : nalog_is_active_ ? inputed_nalog_
                                            : inputed_period;
  if (calcfunc == "AC") activeParam.clear();
  if (calcfunc == "DEL") activeParam.chop(1);
  UpdateInputDisplay();
}

void DepositWindow::UpdateInputDisplay() {
  ui_->input_pr->setText(inputed_pr_);
  ui_->input_sum->setText(inputed_sum_);
  ui_->input_time->setText(inputed_time_);
  ui_->input_minus->setText(inputed_minus_);
  ui_->input_plus->setText(inputed_plus_);
  ui_->input_nalog->setText(inputed_nalog_);
  ui_->input_period->setText(inputed_period);
}

void DepositWindow::OnPushButtonEqClicked() {
  bool capitalization = false;
  if (ui_->radioButton_capital->isChecked()) {
    capitalization = true;
  }
  CalcAll(capitalization);
  g_deposit_dot_flag = false;
  pr_is_active_ = false;
  sum_is_active_ = false;
  time_is_active_ = false;
}

void DepositWindow::DisplayResult(const QString& result) {
  static bool is_interest_calculation = true;

  if (is_interest_calculation) {
    double interest = result.toDouble();
    double tax = interest * (inputed_nalog_.toDouble() / 100);
    double final_amount = inputed_sum_.toDouble() + interest - tax;

    QString resultText = QString(
                             "Начисленные проценты: %1\nСумма налога: "
                             "%2\nСумма на вкладе к концу срока: %3")
                             .arg(interest)
                             .arg(tax)
                             .arg(final_amount);

    ResultDialog dialog(this);
    dialog.setResultText(resultText);
    dialog.exec();

    is_interest_calculation = false;
  } else {
    is_interest_calculation = true;
  }
}

void DepositWindow::CalcAll(bool capitalization) {
  QString pr_expression = ui_->input_pr->text();
  QString sum_expression = ui_->input_sum->text();
  QString time_expression = ui_->input_time->text();

  QString minus_expression = ui_->input_minus->text();
  QString plus_expression = ui_->input_plus->text();
  QString nalog_expression = ui_->input_nalog->text();

  QString period_expression = ui_->input_period->text();

  double withdrawal_amount = SumOfList(minus_expression);
  double replenishment_amount = SumOfList(plus_expression);

  QString modified_sum_expression = sum_expression + "+" +
                                    QString::number(replenishment_amount) +
                                    "-" + QString::number(withdrawal_amount);

  QString interest_expression;
  if (capitalization) {
    interest_expression = modified_sum_expression + "*(1+" + pr_expression +
                          "/100/" + period_expression + ")^(" +
                          period_expression + "*" + time_expression + ")-" +
                          modified_sum_expression;
  } else {
    interest_expression = modified_sum_expression + "*" + pr_expression +
                          "/100*" + time_expression;
  }

  QString tax_expression =
      "(" + interest_expression + ")*" + nalog_expression + "/100";

  QString final_amount_expression = modified_sum_expression + "+" +
                                    interest_expression + "-" + tax_expression;
  emit CalculateExpression(interest_expression);
  emit CalculateExpression(tax_expression);
  emit CalculateExpression(final_amount_expression);
}

double DepositWindow::SumOfList(const QString& list) {
  double sum = 0.0;
  QStringList items = list.split(';');
  for (const QString& item : items) {
    sum += item.toDouble();
  }
  return sum;
}

void DepositWindow::closeEvent(QCloseEvent* event) {
  emit WindowClosed();
  QMainWindow::closeEvent(event);
}
}  // namespace s21
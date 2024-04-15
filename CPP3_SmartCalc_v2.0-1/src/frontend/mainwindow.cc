#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
const QStringList kOperations = {"+", "-", "*", "/", "^", "mod"};
bool g_dot_flag = false;
bool x_flag = false;
const QStringList kMsignes = {".", "(", ")"};
const QStringList kDigits = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

MainWindow::MainWindow(S21SmartCalcController* controller, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  this->setStyleSheet("background-color: black;");
  controller_ = new S21SmartCalcController(this);
  connect(this, &MainWindow::CalculateExpression, controller_,
          &S21SmartCalcController::OnCalculateExpression);

  for (int i = 0; i <= 9; ++i) {
    connect(findChild<QPushButton*>(QString("pushButton_%1").arg(i)),
            SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  }
  connectButtons({"dot", "lbr", "rbr"}, SLOT(Signes()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(Unknown()));
  connectButtons({"plus", "minus", "div", "mul", "pow", "mod"},
                 SLOT(MathOperations()));
  connectButtons({"sqrt", "ln", "log"}, SLOT(MathFunctions()));
  connectButtons({"cos", "sin", "tan", "acos", "asin", "atan"},
                 SLOT(TrigOperations()));
  connectButtons({"del", "ac"}, SLOT(CalcFunctions()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEqClicked()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this,
          SLOT(OpenCreditWindow()));
  connect(ui->pushButton_deposit, SIGNAL(clicked()), this,
          SLOT(OpenDepositWindow()));
  ui->pushButton_plus->setCheckable(true);
  ui->pushButton_minus->setCheckable(true);
  ui->pushButton_div->setCheckable(true);
  ui->pushButton_mul->setCheckable(true);
}

void MainWindow::connectButtons(const QStringList& buttons, const char* slot) {
  for (const auto& buttonName : buttons) {
    connect(findChild<QPushButton*>(QString("pushButton_%1").arg(buttonName)),
            SIGNAL(clicked()), this, slot);
  }
}

MainWindow::~MainWindow() {
  delete controller_;
  delete ui;
}

void MainWindow::DigitsNumbers() {
  QPushButton* button = (QPushButton*)sender();
  if (input_string_.right(1) != 'x' && input_string_.right(1) != ')') {
    input_string_ += button->text();
  }
  UpdateInputDisplay();
}

void MainWindow::MathOperations() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  if (input_string_.isEmpty() || input_string_.right(1) == '(') {
    if (button_text == "-" || button_text == "+" || button_text == "sqrt") {
      input_string_ += button_text;
      if (button_text == "sqrt") input_string_ += '(';
    }
  } else if (!kOperations.contains(input_string_.right(1)) ||
             input_string_.right(1) == ")") {
    if (button_text == "mod")
      input_string_ = input_string_ + " " + button_text + " ";
    else
      input_string_ += button_text;
    g_dot_flag = 0;
  }

  UpdateInputDisplay();
}

void MainWindow::Unknown() {
  x_flag = true;
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  if (CheckAroundUnknown()) {
    input_string_ += button->text();
  }
  UpdateInputDisplay();
}

bool MainWindow::CheckAroundUnknown() {
  return ((input_string_.isEmpty() || input_string_.right(1) != 'x') &&
          (!kDigits.contains(input_string_.right(1)) &&
           input_string_.right(1) != '.'));
}

bool CheckRbracket(QString* input_str, QString* button_text) {
  return (kDigits.contains(input_str->right(1)) || input_str->right(1) == "x" ||
          kMsignes.contains(input_str->right(1))) &&
         input_str->right(1) != "." && *button_text == ")";
}

bool CheckLbracket(QString* input_str, QString* button_text) {
  return (kOperations.contains(input_str->right(1)) ||
          kMsignes.contains(input_str->right(1))) &&
         input_str->right(1) != "." && *button_text == "(" &&
         input_str->right(1) != 'x';
}

void MainWindow::Signes() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  if (button_text == '.' && !g_dot_flag && input_string_.right(1) != 'x') {
    g_dot_flag = 1;
    input_string_ += button_text;
  }
  if (input_string_.isEmpty() || CheckLbracket(&input_string_, &button_text) ||
      CheckRbracket(&input_string_, &button_text)) {
    input_string_ += button->text();
  }
  UpdateInputDisplay();
}

void MainWindow::MathFunctions() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  if (input_string_.isEmpty() || kOperations.contains(input_string_.right(1)) ||
      input_string_.right(1) == '(') {
    input_string_ += button->text();
    input_string_ += '(';
  }
  UpdateInputDisplay();
}

void MainWindow::TrigOperations() {
  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();
  if (input_string_.isEmpty() || kOperations.contains(input_string_.right(1)) ||
      input_string_.right(1) == '(') {
    input_string_ += button->text();
    input_string_ += '(';
  }
  UpdateInputDisplay();
}

void MainWindow::CalcFunctions() {
  QPushButton* button = (QPushButton*)sender();
  QString calcfunc = button->text();
  g_dot_flag = 0;
  x_flag = 0;
  if (calcfunc == "AC") {
    input_string_.clear();
  }
  if (calcfunc == "DEL") {
    input_string_.chop(1);
  }
  UpdateInputDisplay();
}

void MainWindow::OnPushButtonDotClicked() {
  if (!ui->input->text().contains('.')) {
    ui->input->setText(ui->input->text() + '.');
  }
}

void MainWindow::UpdateInputDisplay() { ui->input->setText(input_string_); }

void MainWindow::OnPushButtonEqClicked() {
  QString expression = ui->input->text();
  emit CalculateExpression(expression);
  if (x_flag) {
    OpenGraphWindow(expression);
  }
  g_dot_flag = 0;
  x_flag = 0;
}

void MainWindow::DisplayResult(const QString& result) {
  if (result.startsWith("Error:"))
    ui->input->setText(result);
  else if (result == "nan" || result == "inf")
    ui->input->setText("ERROR");
  ui->input->setText(result);
}

void MainWindow::OpenGraphWindow(QString& expression) {
  if (graph_window_ != nullptr) {
    delete graph_window_;
  }
  graph_window_ = new GraphWindow(this, expression, controller_);
  connect(graph_window_, &GraphWindow::GraphWindowClosed, this,
          &MainWindow::ClearGraphInput);
  graph_window_->show();
}

void MainWindow::OpenDepositWindow() {
  if (deposit_window_ != nullptr) {
    delete deposit_window_;
  }
  deposit_window_ = new DepositWindow(this, controller_);
  connect(controller_, &S21SmartCalcController::SendCalculationResult,
          deposit_window_, &DepositWindow::DisplayResult);
  connect(deposit_window_, &DepositWindow::WindowClosed, this,
          &MainWindow::OnDepositWindowClosed);

  deposit_window_->show();
  this->hide();
}
void MainWindow::OpenCreditWindow() {
  if (credit_window_ != nullptr) {
    delete credit_window_;
  }
  credit_window_ = new CreditWindow(this, controller_);
  connect(controller_, &S21SmartCalcController::SendCalculationResult,
          credit_window_, &CreditWindow::DisplayResult);
  connect(credit_window_, &CreditWindow::WindowClosed, this,
          &MainWindow::OnCreditWindowClosed);
  credit_window_->show();
  this->hide();
}

void MainWindow::OnCreditWindowClosed() { this->show(); }

void MainWindow::OnDepositWindowClosed() { this->show(); }

void MainWindow::ClearGraphInput() {
  input_string_.clear();
  UpdateInputDisplay();
}
}  // namespace s21
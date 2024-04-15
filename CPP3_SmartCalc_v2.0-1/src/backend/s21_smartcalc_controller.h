#ifndef CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_CONTROLLER_H_
#define CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_CONTROLLER_H_

#include <QDebug>
#include <QObject>
#include <QString>

#include "s21_smartcalc_model.h"

namespace s21 {
class S21SmartCalcController : public QObject {
  Q_OBJECT

 public:
  explicit S21SmartCalcController(QObject* parent = nullptr)
      : QObject(parent), calculator_("", 0), x_(0) {}

 public slots:
  void OnCalculateExpression(const QString& expression) {
    std::string std_expression = expression.toStdString();
    Execute(std_expression, 0);
  }
  void OnGraphExpressionEvaluation(const QString& expression, double x) {
    calculator_ = S21SmartCalc(expression.toStdString(), x);
    std::string postfix = calculator_.GetPostfixExpression();
    double result = calculator_.Evaluate();
    emit SendGraphCalculationResult(QString::number(result));
  }

 signals:
  void SendCalculationResult(const QString& result);
  void SendGraphCalculationResult(const QString& result);

 private:
  void Execute(const std::string& expression, double x) {
  try {
    calculator_ = S21SmartCalc(expression, x);
    double result = calculator_.Evaluate();
    emit SendCalculationResult(QString::number(result));
  } catch (const std::runtime_error& e) {
    emit SendCalculationResult("Error: " + QString::fromStdString(e.what()));
  }
  }

 private:
  S21SmartCalc calculator_;
  double x_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_CONTROLLER_H_

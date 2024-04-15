#include "graphwindow.h"

#include <iostream>

#include "ui_graphwindow.h"

namespace s21 {
GraphWindow::GraphWindow(QWidget *parent, QString expression,
                         S21SmartCalcController *controller_)
    : QDialog(parent),
      ui_(new Ui::GraphWindow),
      controller_(controller_),
      current_expression_(expression) {
  ui_->setupUi(this);
  connect(this, &GraphWindow::requestExpressionEvaluation, controller_,
          &S21SmartCalcController::OnGraphExpressionEvaluation);
  connect(controller_, &S21SmartCalcController::SendGraphCalculationResult,
          this, &GraphWindow::onCalculationResultReceived);
  connect(this, &QDialog::finished, this, &GraphWindow::GraphWindowClosed);
  calculateYValues(expression);
}

GraphWindow::~GraphWindow() { delete ui_; }

void GraphWindow::calculateYValues(const QString &expression) {
  h_ = 0.1;
  x_begin_ = -10;
  x_end_ = 10;

  ui_->widget->xAxis->setRange(x_begin_, x_end_);
  ui_->widget->yAxis->setRange(-10, 10);
  for (current_x_ = x_begin_; current_x_ <= x_end_; current_x_ += h_) {
    QString modified_expression = expression;
    modified_expression.replace("x", "(" + QString::number(current_x_) + ")");
    emit requestExpressionEvaluation(modified_expression, current_x_);
  }
}

void GraphWindow::onCalculationResultReceived(const QString &result) {
  double y_value = result.toDouble();
  x_.push_back(current_x_);
  y_.push_back(y_value);

  if (x_.size() * h_ >= x_end_ - x_begin_) {
    ui_->widget->addGraph();
    ui_->widget->graph(0)->setData(x_, y_);
    ui_->widget->replot();
  }
}
}  // namespace s21
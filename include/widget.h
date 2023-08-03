#pragma once

#include <QWidget>

class Widget : public QWidget
{
  Q_OBJECT

public:
  /**
   * @brief Конструктор
   *
   * @param[in] parent Родитель
   */
  Widget(QWidget* parent = nullptr);
  /**
   * @brief Деструктор
   *
   */
  ~Widget();

private slots:
  
  /**
   * @brief Шаг времени
   *
   */
  void SecondTakt();

protected:
  /**
   * @brief Формирует графическое представление
   *
   * @param[in] event Событие отрисовки виджета
   */
  void paintEvent(QPaintEvent* event) override;
};
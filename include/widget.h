#pragma once

#include <cmath> // std::sin, std::cos, std::abs, std::truncf, std::fmod

#include <QColor>
#include <QLinef>
#include <QPaintEvent>
#include <QPolygon>
#include <QVector>
#include <QWidget>

/// Отступ габаритов квадрата виджета от размеров циферблата
#define OFFSET 10
/// Радиус скругления виджета
#define ROUNDING 10
/// Размер циферблата
#define CLOCK_FACE_SIZE 240
/// Размер рисок циферблата (доля от размера циферблата)
#define LABEL_SIZE 5
/// Толщина основных рисок
#define LABEL_MAIN_WIDTH 2
/// Толщина пятисекундных рисок
#define LABEL_FIFTH_WIDTH 4
/// Размер часовой стрелки (доля от размера циферблата)
#define ARROW_HOUR_SIZE 50
/// Толщина часовой стрелки
#define ARROW_HOUR_WIDTH 8
/// Размер минутной стрелки (доля от размера циферблата)
#define ARROW_MINUTE_SIZE 90
/// Толщина часовой стрелки
#define ARROW_MINUTE_WIDTH 6
/// Размер секундной стрелки (доля от размера циферблата)
#define ARROW_SECOND_SIZE 95
/// Отступ для размеки секундной стрелки
#define ARROW_SECOND_OFFSET 4
/// Длина тонкой части стрелки как отступ от центра для стрелкок (доля от размера циферблата)
#define ARROWS_OFFSET 20
/// Радиус в центре циферблата для отступа начала стрелок (доля от размера циферблата)
#define ARROWs_CENTER_OFFSET 5

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

private:
  /**
   * @brief Подготовка циферблата
   *
   */
  void Calculations();

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

private:
  QPoint m_center = QPoint((CLOCK_FACE_SIZE + OFFSET) / 2, (CLOCK_FACE_SIZE + OFFSET) / 2);
  /// Цвет рамки
  const QColor m_colorFrame = Qt::black;
  /// Цвет циферблата
  const QColor m_colorClockFace = Qt::white;
  /// Цвет рисок циферблата
  const QColor m_colorLabels = Qt::black;
  /// Цвет часовой и минутной стрелок
  const QColor m_colorHourArrow = Qt::darkBlue;
  /// Цвет часовой и минутной стрелок
  const QColor m_colorMinuteArrow = Qt::darkGreen;
  /// Цвет секундной стрелки
  const QColor m_colorSecondArrow = Qt::red;
  /// Риски циферблата секунд
  QVector<QLineF> m_labels;

  /// Полигон часовой стрелки
  QPolygon m_polygonArrowHour;
  /// Полигон минутной стрелки
  QPolygon m_polygonArrowMinute;
  // /// Полигон секундной стрелки
  // QPolygon m_polygonArrowSecond;
  /// Линия сенкундной стрелки
  QLine m_lineArrowSecond;
};
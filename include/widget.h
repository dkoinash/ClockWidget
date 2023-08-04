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
/// Размер "хвостика" часовой стрелки (доля от размера циферблата)
#define ARROW_HOUR_TAIL_SIZE 25
/// Толщина часовой стрелки
#define ARROW_HOUR_WIDTH 8
/// Толщина линии часовой стрелки
#define ARROW_HOUR_LINE_WIDTH 6
/// Радиус центрального круга стрелки
#define ARROW_HOUR_CENTER_CIRCLE 10
/// Размер минутной стрелки (доля от размера циферблата)
#define ARROW_MINUTE_SIZE 80
/// Толщина минутной стрелки
#define ARROW_MINUTE_WIDTH 6
/// Размер "хвостика" минутной стрелки (доля от размера циферблата)
#define ARROW_MINUTE_TAIL_SIZE 20
/// Толщина минутной стрелки
#define ARROW_MINUTE_WIDTH 6
/// Толщина линии минутной стрелки
#define ARROW_MINUTE_LINE_WIDTH 4
/// Радиус центрального круга стрелки
#define ARROW_MINUTE_CENTER_CIRCLE 8
/// Размер секундной стрелки (доля от размера циферблата)
#define ARROW_SECOND_SIZE 96
/// Отступ для размеки секундной стрелки
#define ARROW_SECOND_OFFSET 4
/// Толщина секундной стрелки
#define ARROW_SECOND_WIDTH 1
/// Размер "хвостика" секундной стрелки (доля от размера циферблата)
#define ARROW_SECOND_TAIL_SIZE 15
/// Толщина секундной стрелки
#define ARROW_SECOND_WIDTH 1
/// Толщина линии секундной стрелки
#define ARROW_SECOND_LINE_WIDTH 1
/// Радиус центрального круга стрелки
#define ARROW_SECOND_CENTER_CIRCLE 6
/// Радиус в центре циферблата для отступа начала стрелок (доля от размера циферблата)
#define ARROWs_CENTER_OFFSET 5

// #define ARROWS_OFFSET 5

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
  /**
   * @brief Подготовка виджета часовой стрелки
   *
   */
  void Arrow(QPainter& painter,
             int       centralCircleRadius,
             int       mainSize,
             int       tailSize,
             QColor    color = Qt::black);

  // /**
  //  * @brief Подготовка виджета минутной стрелки
  //  *
  //  */
  // void ArrowMinure();

  // /**
  //  * @brief Подготовка виджета секундной стрелки
  //  *
  //  */
  // void ArrowSecond();

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
  QPoint m_center = QPoint(CLOCK_FACE_SIZE / 2 + OFFSET, CLOCK_FACE_SIZE / 2 + OFFSET);
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

  // /// Полигон часовой стрелки
  // QPolygon m_polygonArrowHour;
  // /// Полигон минутной стрелки
  // QPolygon m_polygonArrowMinute;
  // // /// Полигон секундной стрелки
  // // QPolygon m_polygonArrowSecond;
  // /// Линия сенкундной стрелки
  // QLine m_lineArrowSecond;
  // /// Виджет часовой стрелки
  // QImage m_imgArrowHour;
  // /// Виджет минутной стрелки
  // QImage m_imgArrowMinute;
  // /// Виджет секундной стрелки
  // QImage m_imgArrowSecond;
};
#include <widget.h>

#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QSize>
#include <QTime>
#include <QTimer>

QVector<QLineF>
makeNetRays(QPoint center, int radius, int offset, int sector_count)
{
  QVector<QLineF> result;

  qreal angle = qreal(2 * 3.14159) / qreal(sector_count);
  for (int i = 0; i < sector_count; ++i) {
    result.push_back(
      QLineF(QPointF(radius * std::cos(angle * i), radius * std::sin(angle * i)) + center,
             QPointF((offset)*std::cos(angle * i), (offset)*std::sin(angle * i)) + center));
  }
  return result;
}

Widget::Widget(QWidget* parent)
  : QWidget(parent)
{
  setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  resize(QSize(CLOCK_FACE_SIZE + OFFSET, CLOCK_FACE_SIZE + OFFSET));
  Calculations();
  QTimer* timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(SecondTakt()));
  timer->start(100); // И запустим таймер
}

Widget::~Widget() {}

void
Widget::SecondTakt()
{
  Calculations();
  update();
}

void
Widget::Calculations()
{
  int labelSize       = (CLOCK_FACE_SIZE / 2) * LABEL_SIZE / 100;
  int labelFarRadius  = (CLOCK_FACE_SIZE / 2) - labelSize;
  int labelNearRadius = labelFarRadius - labelSize;
  m_labels            = makeNetRays(m_center, labelFarRadius, labelNearRadius, 60);
#pragma region "Часовая стрелка"
  m_polygonArrowHour << QPoint(-1, -1) << QPoint(1, -1)
                     << QPoint(1, -labelNearRadius * ARROW_HOUR_SIZE / 100)
                     << QPoint(-1, -labelNearRadius * ARROW_HOUR_SIZE / 100);
#pragma endregion
#pragma region "Минутная стрелка"
  m_polygonArrowMinute << QPoint(-1, -1) << QPoint(1, -1)
                       << QPoint(1, -labelNearRadius * ARROW_MINUTE_SIZE / 100)
                       << QPoint(-1, -labelNearRadius * ARROW_MINUTE_SIZE / 100);
#pragma endregion
#pragma region "Секундная стрелка"
  m_polygonArrowSecond << QPoint(0, 0) << QPoint(0, -labelNearRadius + ARROW_SECOND_OFFSET)
                       << QPoint(ARROW_SECOND_OFFSET, -labelNearRadius + ARROW_SECOND_OFFSET)
                       << QPoint(ARROW_SECOND_OFFSET, -labelFarRadius - ARROW_SECOND_OFFSET)
                       << QPoint(-ARROW_SECOND_OFFSET, -labelFarRadius - ARROW_SECOND_OFFSET)
                       << QPoint(-ARROW_SECOND_OFFSET, -labelNearRadius + ARROW_SECOND_OFFSET)
                       << QPoint(0, -labelNearRadius + ARROW_SECOND_OFFSET);
#pragma endregion
}

void
Widget::paintEvent(QPaintEvent* event)
{
  QPen     pen;
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
#pragma region "Рамка"

  painter.setBrush(m_colorFrame);
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(
    QRect(QPoint(0, 0), QSize(CLOCK_FACE_SIZE + OFFSET, CLOCK_FACE_SIZE + OFFSET)),
    qreal(ROUNDING),
    qreal(ROUNDING));
#pragma endregion
#pragma region "Циферблат"

  painter.setBrush(m_colorClockFace);
  painter.setPen(Qt::NoPen);
  painter.drawEllipse(
    QRect(QPoint(OFFSET / 2, OFFSET / 2), QSize(CLOCK_FACE_SIZE, CLOCK_FACE_SIZE)));
#pragma region "Риски"
  pen.setColor(m_colorLabels);
  pen.setStyle(Qt::SolidLine);
  for (size_t i = 0; i < 60; ++i) {
    if (i == 0 || i % 5 == 0)
      pen.setWidth(LABEL_FIFTH_WIDTH);
    else
      pen.setWidth(LABEL_MAIN_WIDTH);
    painter.setPen(pen);
    painter.drawLine(m_labels[i]);
  }

#pragma endregion
#pragma region "Цифры"
// TODO Цифры на циферблате и другие подписи? + дата?
#pragma endregion

#pragma endregion
  QTime currentTime       = QTime::currentTime();
  int   currentTimeHour   = currentTime.hour();
  int   currentTimeMinute = currentTime.minute();
  int   currentTimeSecond = currentTime.second();
  int   currentTimeMSec   = currentTime.msec();

#pragma region "Часовая стрелка"
  painter.save();
  painter.translate(m_center);
  painter.rotate(currentTimeHour * 30 + currentTimeMinute / 2);
  pen.setColor(m_colorMainArrows);
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);
  painter.setBrush(m_colorMainArrows);
  painter.drawPolygon(m_polygonArrowHour);
  painter.restore();
#pragma endregion
#pragma region "Минутная стрелка"
  painter.save();
  painter.translate(m_center);
  painter.rotate(currentTimeMinute * 6 + currentTimeSecond / 10);
  pen.setColor(m_colorMainArrows);
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);
  painter.setBrush(m_colorMainArrows);
  painter.drawPolygon(m_polygonArrowMinute);
  painter.restore();
#pragma endregion
#pragma region "Секундная стрелка"
  painter.save();
  painter.translate(m_center);
  painter.rotate(currentTimeSecond * 6 + currentTimeMSec * 6 / 1000);
  pen.setColor(m_colorSecondArrow);
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);
  painter.drawPolyline(m_polygonArrowSecond);
  painter.restore();
#pragma endregion

  painter.end();
  QWidget::paintEvent(event);
}

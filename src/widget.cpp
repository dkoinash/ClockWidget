#include <widget.h>

Widget::Widget(QWidget* parent)
  : QWidget(parent)
{}

Widget::~Widget() {}

void
Widget::SecondTakt();

void
Widget::paintEvent(QPaintEvent* event)
{}

#include "coordlabel.h"

#include <QtGui>
#include <QtCore>

CoordLabel::CoordLabel(QWidget *p) : QLabel(p) {}

CoordLabel::~CoordLabel() {}

void CoordLabel::ShowData(QMouseEvent* me)
{
    QString disp_str("X:%1  Y:%2  Button:%3  Timestamp:%4  GlobalPos: x=%5 y=%6 ");

    QPoint&& v = me->globalPos();
    setText(assemble<int, int, Qt::MouseButtons, ulong, float, float>(disp_str, me->x(), me->y(),
                                                        me->buttons(), me->timestamp(),
                                                        v.rx(), v.ry()));
}

void CoordLabel::ShowExtraInfo(QString* fmt_str)
{
    setText(*fmt_str);
}

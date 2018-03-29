#ifndef COORDLABEL_H
#define COORDLABEL_H

#include <QLabel>
#include "mainwindow.h"

template<class A>
A assemble(A s) {
    return s;
}

template<typename A, typename... Args>
QString assemble(QString s, A a, Args... args) {
    return (assemble(s.arg(a), args...));
}

struct ExtraInfoStruct {
    int val1;
    int val2;
    void* pvData;
};

class CoordLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CoordLabel(QWidget* p);
    virtual ~CoordLabel();

public slots:
    void ShowData(QMouseEvent* me);
    void ShowExtraInfo(QString* fmt);
};

#endif // COORDLABEL_H

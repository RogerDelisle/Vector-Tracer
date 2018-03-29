#ifndef DISPWIDGET_H
#define DISPWIDGET_H

#include <QWidget>
#include "coordlabel.h"
#include "timedpoint.h"
#include "mainwindow.h"
#include <vector>

using namespace std;

typedef pair<int, int> point;
typedef vector<TimedPoint> timedpointvector;
typedef vector<timedpointvector> pt_vec_vector;

class dispWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int VectorEnd READ getVectorEnd WRITE setVectorEnd)

    MainWindow*         mpOwner = nullptr;
    CoordLabel*         mpCoordWindow;
    CoordLabel*         mpExtraInfo;

    timedpointvector    mCurrVector;
    pt_vec_vector       mVectors;
    size_t              mVectorsCumulSize = 0;
    timedpointvector    mAnimationVector;
    unsigned long       mulButtonState = 0;
    bool                mbAnimate = false;
    bool                mbButtonJustPushed = false;
    QImage*             mpTestImage;

    int                 mVectorEnd = 0;
    QPropertyAnimation  mAnimation;

public:
    explicit dispWidget(QWidget *parent = nullptr);
    int  getVectorEnd(void);
    void setVectorEnd(int newVE);
    void paintEvent(QPaintEvent*e) override;
    void clear(void);
    void Undo(void);
    void Animate(void);

    void mouseMoveEvent(QMouseEvent* me) override;
    void mousePressEvent(QMouseEvent* me) override;
    void mouseReleaseEvent(QMouseEvent* me) override;
    MainWindow*& SetOwner(MainWindow* o);
    void ConnectCoordLbl(CoordLabel*);
    void ConnectExtraInfo(CoordLabel*);

signals:
    void UpdateCoords(QMouseEvent*);
    void UpdateExtraInfo(QString* fmt);

public slots:
    void AnimationFinished(void);
};

#endif // DISPWIDGET_H

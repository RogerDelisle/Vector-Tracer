#include <QtGui>
#include <QtCore>
#include "dispwidget.h"
#include <time.h>
#include <iostream>
#include <algorithm>

class MainWindow;

dispWidget::dispWidget(QWidget *parent) : QWidget(parent)
{
    QString filename("scopegrid.jpg");
    mpTestImage = new QImage(filename);
    mAnimation.setTargetObject(this);
    mAnimation.setPropertyName("VectorEnd");
    connect(&mAnimation, &QPropertyAnimation::finished, this, &dispWidget::AnimationFinished);
}

MainWindow*& dispWidget::SetOwner(MainWindow* o)
{
    return (mpOwner = o);
}

void dispWidget::ConnectCoordLbl(CoordLabel *p)
{
    mpCoordWindow = p;
    connect(this, &dispWidget::UpdateCoords, mpCoordWindow, &CoordLabel::ShowData);
}

void dispWidget::ConnectExtraInfo(CoordLabel* p)
{
    mpExtraInfo = p;
    connect(this, &dispWidget::UpdateExtraInfo, mpExtraInfo, &CoordLabel::ShowExtraInfo);
}

int dispWidget::getVectorEnd(void)
{
    return mVectorEnd;
}

void dispWidget::setVectorEnd(int newVE)
{
    mVectorEnd = newVE;
    update();
}

void dispWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if (TimedPoint::bDelay)
        p.fillRect(e->rect(), Qt::white);
    else
        p.drawImage(0,0, *mpTestImage); // , e->rect().right(), e->rect().bottom());

    QPen pen = p.pen();
    pen.setWidth(4);

    if (mbAnimate) {
        auto Draw = [&] (timedpointvector tpv) {
            QPainterPath path;
            TimedPoint& r = tpv[0];
            path.moveTo(r.x, r.y);
            for (int i = 0; i <= mVectorEnd; i++) // mVectorEnd progressively increases from 0 to tpv.back() during animation.
            {
                TimedPoint& tp = tpv.at(i);
                if (tp.mbMove)
                    path.moveTo(tp.x, tp.y);
                else
                    path.lineTo(tp.x, tp.y);
            }
            pen.setColor(QColor(0,255,190));
            p.setPen(pen);
            p.drawPath(path);
        };

        if (mAnimationVector.size())
            Draw(mAnimationVector);
    } else {
        auto Draw = [&] (timedpointvector tpv) {
            QPainterPath path;
            TimedPoint& first = tpv[0];
            path.moveTo(first.x, first.y);
            for_each(tpv.begin(), tpv.end(), [&](TimedPoint pnt) { path.lineTo(pnt.x, pnt.y); });
            p.drawPath(path);
        };

        if (mCurrVector.size())
        {
            pen.setColor(QColor(255,200,0));
            p.setPen(pen);
            Draw(mCurrVector);
        }
        if (mVectors.size()) {
            pen.setColor(QColor(120,255,255));
            p.setPen(pen);
            for (auto&& i : mVectors)
            {
                Draw(i);
            }
        }
    }
}

void dispWidget::mouseMoveEvent(QMouseEvent* me)
{
    // mCurrClock = me->timestamp();
    if (mulButtonState & Qt::LeftButton) {
        mCurrVector.push_back(TimedPoint(me->x(), me->y(), mbButtonJustPushed));
        mbButtonJustPushed = false;
        update();
    }
    emit UpdateCoords(me);

    //QString dbstr("Dir Absolute Path:%1");
    //QDir dir;
    //auto&& rstr = assemble<QString>(dbstr, dir.absolutePath());
    //emit UpdateExtraInfo(&rstr);
}

void dispWidget::mousePressEvent(QMouseEvent *me)
{
    mulButtonState = me->buttons();
    mbButtonJustPushed = true;
}

void dispWidget::mouseReleaseEvent(QMouseEvent* me)
{
    size_t s;
    if ((mulButtonState & Qt::LeftButton) && (((unsigned long)(me->buttons()) & Qt::LeftButton) == 0)
            && (s = mCurrVector.size()))
    {
        mVectors.push_back(mCurrVector);
        mVectorsCumulSize += s;
        QString dbstr("mCurrVector first/last: (%1, %2)/(%3,%4)    mVectors size: %5  mulButtonState=%6");
        auto&& rstr = assemble<int, int, int, int, int, ulong>(dbstr, mCurrVector.at(0).x, mCurrVector.at(0).y,
                                                                mCurrVector.back().x, mCurrVector.back().y, mVectors.size(),
                                                                mulButtonState);
        emit UpdateExtraInfo(&rstr);
        mCurrVector.clear();
    }
    mulButtonState = me->buttons();

}

void dispWidget::AnimationFinished(void)
{
    mbAnimate = false;
    mAnimationVector.clear();
    mVectorEnd = 0;
    QString dbstr("*** ANIMATION FINISHED!");
    emit UpdateExtraInfo(&dbstr);
}

void dispWidget::clear(void)
{
    mVectors.clear();
    mCurrVector.clear();
    mVectorsCumulSize = 0;
    update();
}

void dispWidget::Undo(void)
{
    if (mVectors.size()) {
        size_t s = mVectors.back().size();
        mVectors.pop_back();
        mVectorsCumulSize -= s;
        update();
    }
}

void dispWidget::Animate()
{
    mbAnimate = true;
    size_t ss, st;
    if ((ss = mCurrVector.size()) + (st = mVectorsCumulSize))
    {
        mAnimationVector.reserve(ss + st);
        if (ss)
            for (TimedPoint& tp : mCurrVector)
                mAnimationVector.push_back(tp);
        if (st)
            for (timedpointvector & tpv : mVectors)
                for (TimedPoint& tp : tpv)
                    mAnimationVector.push_back(tp);
    }

    if (mAnimationVector.size())
    {
        PointInTime firsttime = mAnimationVector.front().t;
        PointInTime totaltime = mAnimationVector.back().t - firsttime;
        QVariantAnimation::KeyValues kvs;
        for (int i = 0; i < mVectorEnd; i++) {
            TimedPoint& tp = mAnimationVector.at(i);
            QVariant qv(tp.t);
            double step = (tp.t - firsttime)/totaltime;
            QVariantAnimation::KeyValue kv(step, i);
            kvs.push_back(kv);
        }
        mAnimation.setKeyValues(kvs);
        lldiv_t div = lldiv(totaltime, 1000);
        mAnimation.setDuration(div.quot);
        mAnimation.setStartValue(0);
        mAnimation.setEndValue(mAnimationVector.size()-1);
        mAnimation.start();
        QString dbstr("*** STARTED ANIMATION with %1");
        auto&& rstr = assemble<unsigned long long>(dbstr, totaltime);
        emit UpdateExtraInfo(&rstr);
        update();
    }
}




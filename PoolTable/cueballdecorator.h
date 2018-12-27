#ifndef CUEBALLDECORATOR_H
#define CUEBALLDECORATOR_H
#include "balldecorator.h"

#include "dialog.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

/**
 * @brief The CueBallDecorator class is the decorator that turns a ball into a cue ball
 */
class CueBallDecorator : public BallDecorator, public QObject
{
public:
    /**
     * @brief CueBallDecorator decorates a ball to be used as a cue ball
     * @param b is the ball to be decorated
     * @param parent is the parent Dialog, this is used to connect to the signals it emits
     */
    CueBallDecorator(Ball * b, Dialog * parent);

    CueBallDecorator(CueBallDecorator const& other):BallDecorator(other),m_parent(other.parent())
    {}

    /**
     * @brief clones the balls
     * @return the new Ball
     */
    virtual CueBallDecorator* clone() const
    {
        return new CueBallDecorator(*this);
    }


    void draw(QPainter &p);

    Dialog* parent() const{ return m_parent; }

    /**
     * @brief connectSignals creates the connection between the cue Ball that has restored
     */
    void connectSignals();

public slots:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);

private:
    Dialog *m_parent;
    QVector2D endpoint;
    QVector2D mousePos;
    bool clicked;
};

#endif // CUEBALLDECORATOR_H

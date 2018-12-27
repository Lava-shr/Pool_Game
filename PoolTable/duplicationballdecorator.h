#ifndef DUPLICATIONBALLDECORATOR_H
#define DUPLICATIONBALLDECORATOR_H
#include "balldecorator.h"
#include <QDebug>

/**
 * @brief The DuplicationBallDecorator class is a little bouns decorator that duplicates when it hits things
 */
class DuplicationBallDecorator: public BallDecorator
{
public:
    DuplicationBallDecorator(Ball *b)
        :BallDecorator(b)
    {}

    DuplicationBallDecorator(DuplicationBallDecorator const& other):BallDecorator(other)
    {}
    virtual DuplicationBallDecorator* clone() const
    {
        return new DuplicationBallDecorator(*this);
    }
    /**
     * @brief changeVelocity this acts like the regular function but can also duplicate the ball whilst decreasing its size
     * @param deltaV
     * @return
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);


};

#endif // DUPLICATIONBALLDECORATOR_H

#include "stage3table.h"
#include "ball.h"
#include <QSound>

void Stage3Table::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawRect(0,0,m_width,m_height);

    for(Pocket * pocket: m_pockets)
    {
        pocket->draw(p);
    }
}

ChangeInPoolGame Stage3Table::ballCollision(Ball *b)
{
    for(Pocket * p: m_pockets)
    {
        if(p->encompassed(b->position(),b->radius()))
        {
            // Plays sound when ball goes into pocket
            QSound::play("/Users/urusha/Desktop/pooltable/sounds/goingintopocket.wav");
            return ChangeInPoolGame({b});

        }
    }

    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity
    if((b->position().x()<b->radius() && b->velocity().x()<0) || (b->position().x()>width()-b->radius() && b->velocity().x()>0))
     {
        QSound::play("/Users/urusha/Desktop/pooltable/sounds/ballhittable.wav");
        return b->changeVelocity(QVector2D(-b->velocity().x()*2,0));
    }

    //same but vertical
    if((b->position().y()<b->radius() && b->velocity().y()<0) || (b->position().y()>height()-b->radius() && b->velocity().y()>0))
    {
        QSound::play("/Users/urusha/Desktop/pooltable/sounds/ballhittable.wav");
        return b->changeVelocity(QVector2D(0,-b->velocity().y()*2));
    }

    return ChangeInPoolGame();
}


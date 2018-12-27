#include "stage3ball.h"
#include <cmath>

void Stage3Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}

CompositeBallStage3::CompositeBallStage3(const CompositeBallStage3 &other)
    :Stage3Ball(other) , m_containedBalls(other.balls()),m_containedMass(other.containedMass())
{
    for(int i = 0; i < other.balls().size(); i++)
    {
        m_containedBalls.at(i) = other.balls().at(i)->clone();
        if(other.balls().at(i)->isComposite())
        {
            deepCopy(m_containedBalls.at(i) , other.balls().at(i));
        }
    }
}

void CompositeBallStage3::deepCopy(Ball *newBall, Ball *oldBall)
{
    for(int i = 0; i < oldBall->balls().size(); i++)
    {
        newBall->balls().at(i) = oldBall->balls().at(i)->clone();
        if(oldBall->balls().at(i)->isComposite())
        {
            deepCopy(newBall->balls().at(i) , oldBall->balls().at(i));
        }
    }
}

CompositeBallStage3::~CompositeBallStage3()
{
    for(Ball * b: m_containedBalls)
    {
        delete b;
    }
}

ChangeInPoolGame CompositeBallStage3::changeVelocity(const QVector2D &deltaV)
{
    float energyOfCollision = mass()*deltaV.lengthSquared();
    if(energyOfCollision>m_strength)
    {
        float energyPerBall = energyOfCollision/m_containedBalls.size();
        QVector2D pointOfCollision((-deltaV.normalized())*m_radius);
        //for each component ball
        for(Ball * b: m_containedBalls)
        {
            b->setVelocity(m_velocity + sqrt(energyPerBall/b->mass())*(b->position()-pointOfCollision).normalized());
            b->setPosition(m_position+b->position());
        }
        ChangeInPoolGame change({this},std::move(m_containedBalls));
        m_containedBalls.clear();
        return change;
    }
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

float CompositeBallStage3::mass() const
{
    return m_mass+m_containedMass;
}

void CompositeBallStage3::draw(QPainter &p)
{
    Stage3Ball::draw(p);

    if(drawChildren)
    {
        //recursively draw children, translating the painter
        //so that the children are drawn realative to the parent
        p.translate(m_position.toPointF());
        for(Ball * b: m_containedBalls)
        {
            b->draw(p);
        }
        p.translate(-m_position.toPointF());
    }

}

void CompositeBallStage3::setRadius(float newRadius)
{
    if(m_radius==-1)
        m_radius = newRadius;
    else
    {
        float ratio = newRadius/radius();
        m_radius = newRadius;
        //recursively decrease the radius of children
        for(Ball * b: m_containedBalls)
        {
            b->setRadius(b->radius()*ratio);
            b->setPosition(b->position()*ratio);
        }
    }
}

ChangeInPoolGame SimpleStage3Ball::changeVelocity(const QVector2D &deltaV)
{
    if(mass()*deltaV.lengthSquared()>m_strength)
        return ChangeInPoolGame({this});
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

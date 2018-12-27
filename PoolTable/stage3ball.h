#ifndef STAGE3BALL_H
#define STAGE3BALL_H

#include <vector>

#include "ball.h"
#include "changeinpoolgame.h"
#include "pocket.h"

/**
 * @brief The Stage2Ball class is the component in the composite design pattern
 * it contains the general stage 2 quality strength
 */
class Stage3Ball : public Ball
{
public:
    Stage3Ball(){}

    Stage3Ball(Stage3Ball const & other):Ball(other),m_strength(other.strength())
    {}

    virtual Stage3Ball* clone() const
    {
        return new Stage3Ball(*this);
    }
    float strength() const{
        return m_strength;
    }

    void setStrength(float strength){m_strength = strength;}

public:
    void draw(QPainter &p);

protected:
    float m_strength;
};

/**
 * @brief The CompositeBall class is the composite in the composite design pattern,
 * it stores a vector of children of type Stage2Ball. It can break apart to release these balls.
 */
class CompositeBallStage3 : public Stage3Ball
{
public:
    CompositeBallStage3():m_containedMass(0)
    {
        Ball::setRadius(-1);
    }

    // Copy constructor
    CompositeBallStage3(CompositeBallStage3 const& other);

    // Cloning method for balls
    virtual CompositeBallStage3* clone() const
    {
        return new CompositeBallStage3(*this);
    }

    /**
     * @brief deepCopy copy all the composite balls
     * @param newBall composite balls that is created by copying stuff from old ball
     * @param oldBall composite balls that need to be copied
     */
    void deepCopy(Ball* newBall, Ball* oldBall);

    /**
     * @brief isComposite returns true for the composite ball
     * @return
     */
    bool isComposite() { return true; }

    virtual ~CompositeBallStage3();
    /**
     * @brief changeVelocity changes the velocity of the ball, if it changes to fast it may break apart
     * @param deltaV the change in velocity
     * @return the change to the poolgame list of balls, if the ball breaks it will be added to the remove list
     * and its children will be added to the add list
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

    /**
     * @brief mass get the total mass of the composite ball wich is the sum of its mass and the mass of its children
     * @return
     */
    float mass() const;

    /**
     * @brief draws the composite ball, if draw children is true it will also draw its children
     * @param p
     */
    void draw(QPainter &p);

    /**
     * @brief addBall to the composite
     * @param ball
     */
    void addBall(Ball* ball)
    {
        m_containedBalls.push_back(ball);
        m_containedMass += ball->mass();
    }

    /**
     * @brief setRadius sets the new radius of the ball, adjusting the radius of any children so they are stil contained
     * @param newRadius
     */
    void setRadius(float newRadius);

    std::vector<Ball*> balls() const
    {
        return m_containedBalls;
    }

    float containedMass() const
    {
        return m_containedMass;
    }

protected:
    std::vector<Ball*> m_containedBalls;
    float m_containedMass;
    //here we decide whether or not to draw children
    bool drawChildren = true;
};

/**
 * @brief The SimpleStage3Ball class is the leaf in the composite design pattern,
 * all stage 3 balls that aren't composites are leaves
 */
class SimpleStage3Ball : public Stage3Ball
{
public:
    SimpleStage3Ball(){}

    SimpleStage3Ball(SimpleStage3Ball const& other):Stage3Ball(other)
    {

    }
    virtual SimpleStage3Ball* clone() const
    {
        return new SimpleStage3Ball(*this);
    }

    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

};
#endif // STAGE3BALL_H

#ifndef ORIGINATOR_H
#define ORIGINATOR_H
#include "ball.h"
#include "memento.h"

/**
 * @brief The Originator class Creates a memento with a snapshot of its current internal state,
 *        and can use such a memento to restore its state
 */
class Originator
{
public:
    Originator();

    /**
     * @brief setState sets the state
     * @param state the state that need to be set
     */
    void setState(std::vector<Ball*> state);

    /**
     * @brief saveToMemento saves the m_state to the memento
     * @return the new Memento
     */
    Memento* saveToMemento();

    /**
     * @brief restoreFromMemento restores the save memento
     * @param saved memento is returned
     * @return
     */
    std::vector<Ball*> restoreFromMemento(Memento memento);

    ~Originator();

private:
    std::vector<Ball*> m_state;
};

#endif // ORIGINATOR_H

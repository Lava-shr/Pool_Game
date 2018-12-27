#ifndef MEMENTO_H
#define MEMENTO_H
#include "ball.h"

/**
 * @brief The Memento class stores a valid internal state of the Originator,
 *         and protects that state from access by any other objects than the Originator
 */
class Memento
{
public:
    Memento(std::vector<Ball*> state):m_state()
    {
        deepCopy(state);
    }

    /**
     * @brief getSavedState returns the saved data
     * @return
     */
    std::vector<Ball*> getSavedState();

    /**
     * @brief deepCopy does the deep copy of state. Copies all the composite balls
     * @param state
     */
    void deepCopy(std::vector<Ball*> state);

    ~Memento();

private:
    friend class Originator;
    std::vector<Ball*> m_state;

};

#endif // MEMENTO_H

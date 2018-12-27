#ifndef CARETAKER_H
#define CARETAKER_H
#include "memento.h"
#include <stack>


/**
 * @brief The Caretaker class is responsible for managing the mementos,
 *          and never inspects or operates on the memento contents
 */

class Caretaker
{
public:
    Caretaker();
    ~Caretaker();

    /**
     * @brief addState adds new memento state to the stack of memento
     * @param m Memento to add
     */
    void addState(Memento* m);

    /**
     * @brief lastState
     * @return returns the last state added in the stack of the memento
     */
    Memento* lastState();

private:
    std::stack<Memento*> m_savedState;
};

#endif // CARETAKER_H

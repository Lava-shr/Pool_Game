#include "caretaker.h"
#include <QDebug>

/**
 * @brief The Caretaker class is responsible for managing the mementos,
 *          and never inspects or operates on the memento contents
 */

Caretaker::Caretaker():m_savedState()
{

}

Caretaker::~Caretaker()
{
    while(m_savedState.size() != 0)
    {
        m_savedState.pop();
    }
}

void Caretaker::addState(Memento *m)
{
    m_savedState.push(m);
}

Memento *Caretaker::lastState()
{
    // Will always have initial state stored in it
    if(m_savedState.size() > 1)
    {
        Memento* m = new Memento(m_savedState.top()->getSavedState());
        m_savedState.pop();
        return m;
    }else{
        return new Memento(m_savedState.top()->getSavedState());
    }

}


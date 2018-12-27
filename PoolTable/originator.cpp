#include "originator.h"
#include <QDebug>

Originator::Originator():m_state()
{

}

void Originator::setState(std::vector<Ball *> state)
{
    m_state = state;
}

Memento *Originator::saveToMemento()
{
    return new Memento(m_state);

}

std::vector<Ball *> Originator::restoreFromMemento(Memento memento)
{
    return memento.getSavedState();
}

Originator::~Originator()
{
    for(Ball * b : m_state)
    {
        delete b;
    }
}


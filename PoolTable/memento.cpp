#include "memento.h"
#include <QDebug>


std::vector<Ball *> Memento::getSavedState()
{
    return m_state;
}

void Memento::deepCopy(std::vector<Ball*> state)
{
    for(int i = 0; i < state.size(); i++)
    {
        m_state.push_back(state.at(i)->clone());
    }
}

Memento::~Memento()
{
    for(Ball * b: m_state)
    {
        delete b;
    }
}

#include "dialog.h"

#include <QPainter>
#include <QSize>
#include <cmath>
#include <QSound>
#include "ckeycommand.h"
#include "bkeycommand.h"
#include "rightclickCommand.h"
#include "cueballdecorator.h"
#include "pkeycommand.h"

constexpr float fps = 60;
constexpr float timeStep = 0.01;

/**
 * @brief The Dialog class starts up and displays a poolgame
 */

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer())
{
    m_stateRecorded = false;
    m_mouseClicked = false;
}

void Dialog::start(PoolGame *game)
{
    m_game = game;
    // Check if we are in Stage3
    m_stage3 = QString::compare(m_game->table()->stage(),"stage3", Qt::CaseInsensitive);

    // Connects the keys and doubleClick to the Command design pattern;
    Command* m_keyB = new BKeycommand(this);
    Command* m_keyR = new CKeycommand(this);
    Command* m_rightCicked = new RightClickCommand(this);
    Command* m_keyP = new PKeycommand(this);

    // Store first state
    m_originator.setState(m_game->getBalls());
    m_caretaker.addState(m_originator.saveToMemento());

    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if(m_game)
    {
        if(m_stage3 == 0)
        {
            CueBallDecorator* cue = dynamic_cast<CueBallDecorator *> (m_game->getBalls().at(0));

            if(cue)
            {
                if(!m_stateRecorded && (cue->velocity().lengthSquared() < 0.001) && cue)
                {
                    // record the state
                    m_originator.setState(m_game->getBalls());
                    m_caretaker.addState(m_originator.saveToMemento());
                    setStateRecord(true);
                }
            }

            // if their is change in cue's velocity like by collision we have to store that state again.
            if(cue)
            {
                if(cue->velocity().lengthSquared() > 0.001)
                    setStateRecord(false);
            }
        }
    }

    if(m_game)
    {
        m_game->draw(p);
    }

}


void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        if(m_stage3 == 0)
        {
            CueBallDecorator* cue = dynamic_cast<CueBallDecorator *> (m_game->getBalls().at(0));
            if(cue)
            {
                if((QVector2D(event->pos())-cue->position()).length() < cue->radius())
                {
                    m_mouseClicked = true;
                }
            }
        }
    }
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_stage3 == 0)
    {
        if(m_mouseClicked)
        {
            setStateRecord(false);
            m_mouseClicked = false;
        }
    }
    emit mouseReleased(event);
}


Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::runSimulationStep()
{
    if(m_game)
        m_game->simulateTimeStep(timeStep);
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        if(m_stage3 == 0)
        {
            m_game->setBall(m_originator.restoreFromMemento(*m_caretaker.lastState()));
            CueBallDecorator* cue = dynamic_cast<CueBallDecorator *> (m_game->getBalls().at(0));

            //Plays sounds
            QSound::play("/Users/urusha/Desktop/pooltable/sounds/reversed.wav");
            if(cue)
            {
                // COnnects the signals when new cue ball is restore by pressing R
                cue->connectSignals();
            }
        }
    }

    if(m_stage3 == 0){
        // Only emit keyPressd signals if we are in Stage3
        emit keyPressed(event);
    }

}

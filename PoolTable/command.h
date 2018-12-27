#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "dialog.h"
#include <stdlib.h>
#include <time.h>

class Dialog;
class PoolGame;

/**
 * @brief The Command class is interface for executing all the commands
 */

class Command: public QObject
{
public:
    Command(Dialog *dialog) : m_dialog(dialog)
    {}

    virtual ~Command()
    {
        delete m_dialog;
    }

    Dialog * m_dialog;

    /**
     * @brief executes commands base on deerived class
     */
    virtual void execute() = 0;


public slots:
    /**
     * @brief keyPressed
     * @param event
     * Derived class inherites this methods and executes the commands bases on key event.
     */
    virtual void keyPressed(QKeyEvent *event) = 0;

    /**
     * @brief mousePressed
     * @param event Derived class inherites this methods and executes the commands bases on mouse event.
     */
    virtual void mousePressed(QMouseEvent *event) = 0;
};

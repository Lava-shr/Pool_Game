#pragma once

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "command.h"

/**
 * @brief The CKeycommand class get the signal from dialog class
 *         This class changes colour of ball randomly when C is pressed from keyboard
 *          Doesn't change the colour of CUE ball though
 */

class CKeycommand: public Command
{
public:
    CKeycommand(Dialog *dialog);

    /**
     * @brief executes the commands changings the colours of balls from randomly selected colours
     *        Doesn't change the colour of CUE ball
     */
    void execute();

    /**
     * @brief keyPressed capture the keyPressed signals from dialog class and checks if the key is C
     * @param event Key pressed Signals send from dialog
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief mousePressed doesn't do anything for this class;
     * @param event
     */
    void mousePressed(QMouseEvent *event) {}
};


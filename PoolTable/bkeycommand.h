#pragma once

#include "command.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

/**
 * @brief The BKeycommand class get the signal from dialog class
 *         This class clone more balls and put in the table when B is pressed from keyboard
 */

class BKeycommand : public Command
{
public:
    BKeycommand(Dialog *dialog);


    /**
     * @brief executes the commands of cloning the balls
     */
    void execute();

    /**
     * @brief keyPressed capture the keyPressed signals from dialog class and checks if the key is B
     * @param event Key pressed Signals send from dialog
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief mousePressed doesn't do anything for this class;
     * @param event
     */
    void mousePressed(QMouseEvent *event) {}
};


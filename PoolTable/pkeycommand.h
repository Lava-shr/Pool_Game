#ifndef PKEYCOMMAND_H
#define PKEYCOMMAND_H

#include "command.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

/**
 * @brief The PKeycommand class get the signal from dialog class
 *         This class delets the pockets from table only when there is more than 4 pockets
 *          when P is pressed from keyboard
 */

class PKeycommand : public Command
{
public:
    PKeycommand(Dialog *dialog);

    /**
     * @brief executes the commands of deleting the pockets
     */
    void execute();

    /**
     * @brief keyPressed capture the keyPressed signals from dialog class and checks if the key is P
     * @param event Key pressed Signals send from dialog
     */
    void keyPressed(QKeyEvent *event);

    /**
     * @brief mousePressed doesn't do anything for this class;
     * @param event
     */
    void mousePressed(QMouseEvent *event) {}

};

#endif // PKEYCOMMAND_H

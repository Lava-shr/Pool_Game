#ifndef RIGHTCLICKSTATE_H
#define RIGHTCLICKSTATE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "command.h"
#include "pocket.h"


/**
 * @brief The RightKeyCommand class get the signal from dialog class
 *         This class makes pocket in the position where mouse is right Clicked
 *          Doesn't overlap the pockets.
 */
class RightClickCommand: public Command
{
public:
    RightClickCommand(Dialog *dialog);

    /**
     * @brief executes the commands of making the pockets if its
     *        not overlapping with pockets that already in the table
     *        Does the check for overlapping
     */
    void execute ();

    /**
     * @brief keyPressed doesn't do anything for this class;
     * @param event
     */
    void keyPressed(QKeyEvent *event) {}

    /**
     * @brief mousePressed checks if right click is pressed and invokes the execute method
     * @param event
     */
    void mousePressed(QMouseEvent *event);

    /**
     * @brief pocketOverlaps Checks if new Pocket overlaps with already existed pockets
     * @param newPocket pocket to go in the table if not overlapped
     * @param gamePocket pocket that already existed in the pocket
     * @return
     */
    bool pocketOverlaps(Pocket* newPocket, Pocket* gamePocket);

private:
    QVector2D position;
};

#endif // RIGHTCLICKSTATE_H

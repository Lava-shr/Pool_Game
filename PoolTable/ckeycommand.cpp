#include "ckeycommand.h"
#include "ball.h"
#include <QList>
#include <QColor>
#include <QString>

/**
 * @brief The CKeycommand class get the signal from dialog class
 *         This class changes colour of ball randomly when C is pressed from keyboard
 *          Doesn't change the colour of CUE ball though
 */

CKeycommand::CKeycommand(Dialog *dialog): Command(dialog)
{
    // Connects dialog signals
    connect(dialog, &Dialog::keyPressed,this,&CKeycommand::keyPressed);
}

void CKeycommand::execute()
{
    srand (time(0));
    for(int i = 1; i < m_dialog->game()->getBalls().size(); ++i)
    {
        QList <QString> listOfColor = QColor::colorNames();
        int j = rand() % listOfColor.size();
        if(j == 0){
            // Not want to have 2 balls with white colour. Cue will only be white
            m_dialog->game()->getBalls().at(i)->setColour(listOfColor.at(j+ 11));
        }
        else
        {
            m_dialog->game()->getBalls().at(i)->setColour(listOfColor.at(j));
        }
    }
}

void CKeycommand::keyPressed(QKeyEvent *event)
{
    if( event->key() == Qt::Key_C)
    {
        execute();
    }
}


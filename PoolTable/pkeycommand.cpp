#include "pkeycommand.h"
#include "pocket.h"
#include "Stage3table.h"
#include <QSound>
#include <QDebug>

PKeycommand::PKeycommand(Dialog *dialog): Command(dialog)
{
    connect(dialog, &Dialog::keyPressed, this, &PKeycommand::keyPressed);
}

void PKeycommand::execute()
{
    // Checking if we are in stage 3
    Stage3Table *t = dynamic_cast<Stage3Table *> (m_dialog->game()->table());
    if(t)
    {
        int pocketSize = t->noOfPocket();
        if( pocketSize >4)
        {
            t->removePocket();
        }
    }
}

void PKeycommand::keyPressed(QKeyEvent *event)
{
    if(event->key() == Qt::Key_P)
    {
        execute();
    }
}

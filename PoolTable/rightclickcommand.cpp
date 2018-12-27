#include "rightclickcommand.h"
#include "Stage3table.h"
#include <QSound>


RightClickCommand::RightClickCommand(Dialog *dialog): Command(dialog)
{
    //Connects the signals
    connect(dialog, &Dialog::mousePressed,this,&RightClickCommand::mousePressed);
}

void RightClickCommand::execute()
{
    Pocket* newPocket = new Pocket(position, 20.0);
    bool toAdd = true;
    // Checking if we are in Stage 3
    Stage3Table * t = dynamic_cast<Stage3Table *> (m_dialog->game()->table());
    if(t)
    {
        std::vector <Pocket*> pockets = t->pocket();
        for(Pocket* p : pockets)
        {
            if(pocketOverlaps(newPocket,p))
            {
                toAdd = false;
                break;
            }
        }
    }else{
        // Not in Stage 3 we do nothing
        return;
    }

    if(toAdd)
        dynamic_cast<Stage3Table *> (m_dialog->game()->table())->putPocket(newPocket);
}


void RightClickCommand::mousePressed(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        // Sets the position where we want our pockets
        position.setX(event->pos().x());
        position.setY(event->pos().y());
        execute();
    }
}

bool RightClickCommand::pocketOverlaps(Pocket *newPocket, Pocket *gamePocket)
{
    return (newPocket->position() - gamePocket->position()).length() < newPocket->radius() + gamePocket->radius() ;
}

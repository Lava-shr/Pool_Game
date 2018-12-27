#include "bkeycommand.h"
#include "cueballdecorator.h"
#include "ball.h"
#include <QSound>

/**
 * @brief The BKeycommand class get the signal from dialog class
 *         This class clone more balls and put in the table when B is pressed from keyboard
 */



BKeycommand::BKeycommand(Dialog *dialog): Command(dialog)
{
    connect(dialog, &Dialog::keyPressed,this,&BKeycommand::keyPressed);

}

void BKeycommand::execute()
{
    std::vector<Ball*> newBalls;
    // Sets the random seed
    srand (time(0));

    for(int i = 0; i < m_dialog->game()->getBalls().size() ; ++i)
    {
        newBalls.push_back(m_dialog->game()->getBalls().at(i)->clone());
        int j = rand() % 300 + 150;
        int k = -1*(rand() % 300 +100);
        // sets random velocity for the new Balls
        newBalls.at(i)->changeVelocity(QVector2D(j,k));
    }
    for(int i = 0; i < newBalls.size() ; ++i)
    {
        CueBallDecorator* cue = dynamic_cast<CueBallDecorator *> (newBalls.at(i));
        // Ignore cloning cue ball and composite ball
        if(cue){
            // not cloning;
        }else if (newBalls.at(i)->isComposite()){
            // not cloning;
        }else{
            m_dialog->game()->push(newBalls.at(i)->clone());
        }
        // Plays sounds
        QSound::play("/Users/urusha/Desktop/pooltable/sounds/spawn.wav");
    }
    // Clearing the Balls arrays
    newBalls.clear();
}

void BKeycommand::keyPressed(QKeyEvent *event)
{
    if( event->key() == Qt::Key_B)
    {
        execute();
    }
}

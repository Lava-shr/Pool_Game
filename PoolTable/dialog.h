#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>
#include "poolgame.h"
#include <QDebug>
#include "originator.h"
#include "caretaker.h"
#include "command.h"


/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    /**
     * @brief starts the simulation
     */
    void start(PoolGame * game);

    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent just emits the mousePressed signal
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits the mouseMoved signal
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits a mouseReleased signal
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief setStateRecord sets the record to true if state is recorded false if state is not recorded
     * @param b
     */
    void setStateRecord(bool b) { m_stateRecorded = b;}

    /**
     * @brief keyPressEvent emits a keyPressed signals
     * @param event
     */

    void keyPressEvent(QKeyEvent *event);

    PoolGame* game(){ return m_game; }
    Originator originator() { return m_originator; }
    Caretaker caretaker() { return m_caretaker; }

signals:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);
    void keyPressed (QKeyEvent *event);

public slots:
    void runSimulationStep();


private:
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
    Originator m_originator;
    Caretaker m_caretaker;
    bool m_stateRecorded;
    bool m_mouseClicked;
    int m_stage3;
};

#endif // DIALOG_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItem>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QtMultimedia/QMediaPlayer>
#include "gameitem.h"
#include "land.h"
#include "bird.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent * event);
    QPointF pt;
    QMediaPlayer *nice;
    void res();
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<Bird *> birdlist;
    QTimer timer;
    QPushButton *exit;
    QPushButton *restart;
    int v1,v2,v3;
    int repeat;
    int b ;
    int count ;
    static QSizeF g_worldsize,g_windowsize;
};

#endif // MAINWINDOW_H

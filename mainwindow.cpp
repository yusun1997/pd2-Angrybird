#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bow.h"
#include "pig.h"
#include "wood.h"
#include <QImage>
#include <QBrush>
#include <QGraphicsScene>
#include <QtMultimedia/QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //setup background music
    nice = new QMediaPlayer();
    nice->setMedia(QUrl("qrc:/cut.mp3"));
    nice->play();

    //Enable the event Filter
    qApp->installEventFilter(this);
    repeat = 0;
    b = 0;
    count = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/background")));
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    //play background music

    // Create exit button
    exit = new QPushButton(this);
    exit->setObjectName("exit");
    exit->setGeometry(850,0,80,80);
    exit->setStyleSheet("#re{border-image:url(:/exit.png)}");
    exit->show();

    restart = new QPushButton(this);
    restart->setObjectName("restart");
    restart->setGeometry(720,0,80,80);
    restart->setStyleSheet("#re{border-image:url(:/image/restart.png)}");
    restart->show();

    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create a bow
    Bow *newbow = new Bow();
    newbow->setPos(80,210);
    newbow->setFlag(QGraphicsItem::ItemIsFocusable);
    newbow->setFocus();
    scene->addItem(newbow);
    Pig *piggy = new Pig(24.0f,10.0f,0.8f,&timer,QPixmap(":/pig1.png").scaled(height()/9.0,height()/9.0),world,scene);
    piggy->setLinearVelocity(b2Vec2(0,0));
    Wood *wood1 = new Wood(22.0f,10.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    Wood *wood2 = new Wood(22.0f,12.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    Wood *wood3 = new Wood(22.0f,14.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    Wood *wood4 = new Wood(27.0f,10.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    Wood *wood5 = new Wood(27.0f,12.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    Wood *wood6 = new Wood(27.0f,14.0f,2.0f,2.0f,&timer,QPixmap(":/wood2.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Create bird (You can edit here)
    Bird *birdie = new Bird(-5.0f,10.0f,0.8f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Setting the Velocity
    birdie->setLinearVelocity(b2Vec2(0,0));
    birdlist.push_back(birdie);
    Bird *birdie2 = new Bird(-5.0f,10.0f,0.8f,&timer,QPixmap(":/yellowbird.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Setting the Velocity
    birdie2->setLinearVelocity(b2Vec2(0,0));
    birdlist.push_back(birdie2);
    Bird *birdie3 = new Bird(-5.0f,10.0f,0.8f,&timer,QPixmap(":/blackbird.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Setting the Velocity
    birdie3->setLinearVelocity(b2Vec2(0,0));
    birdlist.push_back(birdie3);
    Bird *birdie4 = new Bird(-5.0f,10.0f,0.8f,&timer,QPixmap(":/whitebird.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Setting the Velocity
    birdie4->setLinearVelocity(b2Vec2(0,0));
    birdlist.push_back(birdie4);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
        if(event->type() == QEvent::MouseButtonPress)
        {
        /* TODO : add your code here */
            count = count +1;
            std::cout << count << std::endl ;
            if(count >= 21){
                return false ;
            }
            QMouseEvent *m = dynamic_cast<QMouseEvent *>(event);

            if(720 < m->pos().x()  &&  m->pos().x() < 800){
                if(0 <m->pos().y() && m->pos().y() < 80){
                std::cout << "restart" << std::endl ;
                res();
                }
            }
            if(850 < m->pos().x() && m->pos().x()< 930){
                if(0<m->pos().y() && m->pos().y() < 80){
                std::cout << "exit" << std::endl ;

                this->close();


                }
            }
            if(repeat==0)
            {
                std::cout << "Press !" << std::endl ;
                repeat=1;
            }

        }
        if(event->type() == QEvent::MouseMove)
        {
            /* TODO : add your code here */

            if(repeat==1)
            {
                QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
                pt.setX((me->pos().x()) * GameItem::g_worldsize.width()/GameItem::g_windowsize.width());
                pt.setY((1.0f-(me->pos().y())/GameItem::g_windowsize.height()) * GameItem::g_worldsize.height());
                birdlist[b]->g_body->SetActive(false);
                birdlist[b]->g_body->SetTransform(b2Vec2(pt.x(),pt.y()),0);
                std::cout << pt.x()<<" "<<pt.y() << std::endl ;
            }
        }
        if(event->type() == QEvent::MouseButtonRelease)
        {
            /* TODO : add your code here */
            std::cout << "Release !" << std::endl ;
            if(repeat==1)
            {
                int xn=sqrt((25-pt.x()*pt.x()));
                int yn=sqrt((81-pt.y()*pt.y()));
                birdlist[b]->g_body->SetActive(true);
                ;
                birdlist[b]->setLinearVelocity(b2Vec2(2.3*xn,2.3*yn));
                b=b+1;
                repeat = 0;
            }

        }
        return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    this->close();
    emit quitGame();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_2){
        v1 = birdlist[1]->g_body->GetLinearVelocity().Length();
        if(v1 != 0){
            std::cout<< "bird 2 skill" <<std::endl;
            birdlist[1]->skill1();
        }
    }
    if(event->key() == Qt::Key_3){
        v2 = birdlist[2]->g_body->GetLinearVelocity().Length();
        if(v2 != 0){
            std::cout<< "bird 3 skill" <<std::endl;
            birdlist[2]->skill2();
        }
    }
    if(event->key() == Qt::Key_4){
        v3 = birdlist[3]->g_body->GetLinearVelocity().Length();

        if(v3 != 0){
            std::cout<< "bird 4 skill" <<std::endl;
            birdlist[3]->g_pixmap.setPixmap(QPixmap(":/"));

        }
    }

}

void MainWindow::res()
{
   MainWindow m2;
   m2.show();
   this->close();

}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

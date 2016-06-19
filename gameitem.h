#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    static QSizeF g_worldsize, g_windowsize;
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;

public slots:
    void paint();
    // TODO virtual void collide();

protected:
    b2World *g_world;

};

#endif // GAMEITEM_H

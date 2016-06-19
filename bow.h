#ifndef BOW_H
#define BOW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Bow:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Bow(QGraphicsItem * parent = 0);
};



#endif // BOW_H



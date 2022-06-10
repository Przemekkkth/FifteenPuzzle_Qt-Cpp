#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include <QGraphicsPixmapItem>
#include <QGraphicsObject>

class PixmapItem : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT
   Q_PROPERTY(int posX READ posX WRITE setPosX NOTIFY posXChanged)
   Q_PROPERTY(int posY READ posY WRITE setPosY NOTIFY posYChanged)

public:
    PixmapItem(QObject* obj = nullptr);
signals:
    void posXChanged();
    void posYChanged();
public:
    int posX() const;
    int posY() const;
public slots:
    void setPosX(int val);
    void setPosY(int val);
private:
    int m_PosX, m_PosY;

};

#endif // PIXMAPITEM_H

#include "pixmapitem.h"

PixmapItem::PixmapItem(QObject *obj) : QObject(obj), QGraphicsPixmapItem()
{}

int PixmapItem::posX() const
{
    return m_PosX;
}

int PixmapItem::posY() const
{
    return m_PosY;
}

void PixmapItem::setPosX(int val)
{
    m_PosX = val;
    setPos(m_PosX, pos().y());
}

void PixmapItem::setPosY(int val)
{
    m_PosY = val;
    setPos(pos().x(), m_PosY);
}


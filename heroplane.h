#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QPixmap>
#include <QRect>
#include "bullet.h"
#include "config.h"

class HeroPlane {
public:
    HeroPlane();
    void shoot();
    void setPosition(int x, int y);

    QPixmap m_Plane;
    int m_x, m_y;
    QRect m_Rect;
    Bullet m_bullets[BULLET_NUM];
    int m_recorder = 0;
};

#endif // HEROPLANE_H

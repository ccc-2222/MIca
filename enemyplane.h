#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include <QPixmap>
#include <QRect>

class enemyplane {
public:
    enemyplane();
    void updatePosition();

    QPixmap m_enemy;
    int m_X, m_Y;
    QRect m_Rect;
    bool m_Free;
    int m_Speed;
};

#endif // ENEMYPLANE_H

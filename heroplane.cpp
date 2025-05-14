#include "heroplane.h"
#include "bullet.h"
#include <QPixmap>

HeroPlane::HeroPlane() {
    m_Plane.load(HERO_PATH);
    m_x = GAME_WIDTH / 2 - m_Plane.width() / 2;
    m_y = GAME_HEIGHT - m_Plane.height();
    m_Rect = QRect(m_x, m_y, m_Plane.width(), m_Plane.height());

    //初始化矩形边框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_x,m_y);
}

void HeroPlane::shoot()
{//累加时间间隔记录变量
    m_recorder++;
    //如果记录的数字 未达到发射子弹时间间隔 直接return 不发射子弹
    if(m_recorder<BULLET_INTERVAL){
        return;
    }
    //达到发射时间
    m_recorder=0;
    //发射子弹
    for(int i=0;i<BULLET_NUM;i++){
        //如果是空闲的子弹 进行发射
        if(m_bullets[i].m_Free){
            //将空闲状态改为假
            m_bullets[i].m_Free=false;
            //设置子弹的坐标
            m_bullets[i].m_X=m_x+m_Rect.width()*0.5-10;
            m_bullets[i].m_Y=m_y-25;
            break;
        }
    }

}

void HeroPlane::setPosition(int x, int y)
{
    m_x=x;
    m_y=y;
    m_Rect.moveTo(m_x,m_y);

}

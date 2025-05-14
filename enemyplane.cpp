#include "enemyplane.h"
#include "config.h"

enemyplane::enemyplane() {
    //敌机资源加载
    m_enemy.load(ENEMY_PATH);
    //敌机的位置
    m_X=0;
    m_Y=0;
    //状态
    m_Free=true;
    m_Speed=ENEMY_SPEED;
    //敌机矩形框 （碰撞检测
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void enemyplane::updatePosition()
{
//空闲状态的敌机 不计算坐标
    if(m_Free){
    return;
    }

    m_Y+=m_Speed;
    m_Rect.moveTo(m_X,m_Y);
    //如果超出了屏幕 重置状态
    if(m_Y>=GAME_HEIGHT+m_Rect.height()){
        m_Free=true;

    }

}

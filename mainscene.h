#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QSoundEffect>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter> // 添加 QPainter 头文件

#include "map.h"
#include "heroplane.h"
#include "enemyplane.h"
#include "config.h"  // 确保使用宏定义

class MainScene : public QWidget
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void initScene();
    void startGame();   // 启动游戏
    void playGame();    // 启动游戏循环
    void updatePosition();
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enemyToScene();
    void collisionDetection();
    void gameOver();
    void resetGame();

private:
    Map m_map;
    QTimer m_Timer;
    HeroPlane m_hero;
    enemyplane m_enemys[ENEMY_NUM];

    int m_recorder = 0;
    QSoundEffect *backgroundSound = nullptr;

    bool m_gameStarted = false;
    int m_heroHealth = HERO_HEALTH;
    int m_score = 0; // 添加分数变量

    QLabel *m_startLabel = nullptr;
    QPushButton *m_startButton = nullptr;
};

#endif // MAINSCENE_H

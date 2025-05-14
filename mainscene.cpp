#include "mainscene.h"
#include "config.h"
#include <QApplication>
#include <QResource>
#include <QDebug>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScene();
    //启动游戏
    playGame();
}

MainScene::~MainScene() {}

void MainScene::initScene()
{
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);  //尺寸
    setWindowTitle(GAME_TITLE);//标题
    setWindowIcon(QIcon(GAME_ICON));//图标

    //定时器
    m_Timer.setInterval(GAME_RATE);
    //敌机出场的时间间隔
    m_recorder = 0;
    //随机数种子
    srand((unsigned int)time(NULL));
    m_score = 0; // 初始化分数
}

void MainScene::playGame()
{

    backgroundSound = new QSoundEffect(this);
    backgroundSound->setSource(QUrl(SOUND_BACKGROUND));

    // 检查音频文件是否成功加载
    if (!backgroundSound->isLoaded()) {
        qDebug() << "Failed to load audio file:" << SOUND_BACKGROUND;
        qDebug() << "Error:" ;
    } else {
        qDebug() << "Audio file loaded successfully:" << SOUND_BACKGROUND;
    }

    backgroundSound->setLoopCount(QSoundEffect::Infinite);
    backgroundSound->setVolume(0.5f);

    connect(backgroundSound, &QSoundEffect::statusChanged, this, [=](){
        qDebug() << "Status changed to:" << backgroundSound->status();
        if (backgroundSound->status() == QSoundEffect::Error) {
            qDebug() << "Audio playback error:";
        }
    });

    backgroundSound->play();
    if (backgroundSound->status() == QSoundEffect::Error) {
        qDebug() << "Failed to start audio playback:" ;
    }

    m_Timer.start();
    //监听定时器发送的信号
    connect(&m_Timer, &QTimer::timeout, this, [=]() {
        //敌机出场
        enemyToScene();
        updatePosition();
        update();
        //碰撞检测
        collisionDetection();
    });
}

void MainScene::updatePosition()
{
    m_map.mapPosition();//更新地图坐标
    //发射子弹
    m_hero.shoot();
    //计算所有非空闲子弹的当前坐标
    for (int i = 0; i < BULLET_NUM; i++) {
        //如有非空闲 计算发射位置
        if (m_hero.m_bullets[i].m_Free == false) {
            m_hero.m_bullets[i].updatePosition();
        }
    }

    for (int i = 0; i < ENEMY_NUM; i++) {
        if (m_enemys[i].m_Free == false) {
            m_enemys[i].updatePosition();
            // 检查敌机是否离开屏幕且未被击中
            if (m_enemys[i].m_Y >= GAME_HEIGHT + m_enemys[i].m_Rect.height()) {
                m_enemys[i].m_Free = true;
                m_score-=2; // 分数减1
                qDebug() << "Score decreased to: " << m_score; // 调试输出分数变化
                if (m_score < 0) {
                    gameOver();
                }
            }
        }
    }
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);
    //绘制飞机
    painter.drawPixmap(m_hero.m_x, m_hero.m_y, m_hero.m_Plane);
    //绘制敌机
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (m_enemys[i].m_Free == false) {
            painter.drawPixmap(m_enemys[i].m_X, m_enemys[i].m_Y, m_enemys[i].m_enemy);
        }
    }
    //绘制子弹
    for (int i = 0; i < BULLET_NUM; i++) {
        //如有非空闲 绘制
        if (m_hero.m_bullets[i].m_Free == false) {
            painter.drawPixmap(m_hero.m_bullets[i].m_X, m_hero.m_bullets[i].m_Y, m_hero.m_bullets[i].m_Bullet);
        }
    }
    // 绘制分数
    painter.setPen(Qt::yellow); // 修改分数颜色为黄色，提高可见性
    painter.setFont(QFont("Arial", 24)); // 增大字体大小
    painter.drawText(20, 40, QString("Score: %1").arg(m_score));
    qDebug() << "Score drawn: " << m_score; // 调试输出分数绘制情况
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->position();
    int x = pos.x() - m_hero.m_Rect.width() * 0.5;
    int y = pos.y() - m_hero.m_Rect.height() * 0.5;
    //边界的检测
    if (x <= 0)
        x = 0;
    if (x >= GAME_WIDTH - m_hero.m_Rect.width())
        x = GAME_WIDTH - m_hero.m_Rect.width();
    if (y <= 0)
        y = 0;
    if (y >= GAME_HEIGHT - m_hero.m_Rect.height())
        y = GAME_HEIGHT - m_hero.m_Rect.height();

    m_hero.setPosition(x, y);
}

void MainScene::enemyToScene()
{
    m_recorder++;
    if (m_recorder < ENEMY_INTERVAL) {
        //未达到出场间隔
        return;
    }
    m_recorder = 0;
    for (int i = 0; i < ENEMY_NUM; i++) {
        //如果是空闲的敌机 出场
        if (m_enemys[i].m_Free) {
            m_enemys[i].m_Free = false;
            //坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有出场的敌机
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (m_enemys[i].m_Free) {
            continue;//如果是空闲的飞机 执行下一次的循环
        }
        //遍历所有非空闲的子弹
        for (int j = 0; j < BULLET_NUM; j++) {
            if (m_hero.m_bullets[j].m_Free) {
                continue;//空闲子弹 执行下一次循环
            }
            //如果子弹和飞机相交，发生碰撞 同时将飞机和子弹空闲状态设置为true
            if (m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect)) {
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;
                m_score++; // 分数加1
                qDebug() << "Score increased to: " << m_score; // 调试输出分数变化
            }
        }
    }
}

void MainScene::gameOver()
{
    qDebug() << "Game Over! Your score is: " << m_score;
    QApplication::quit();
}

void MainScene::resetGame()
{
    // 重置游戏状态
    m_score = 0;
    m_heroHealth = HERO_HEALTH;
    for (int i = 0; i < ENEMY_NUM; i++) {
        m_enemys[i].m_Free = true;
    }
    for (int i = 0; i < BULLET_NUM; i++) {
        m_hero.m_bullets[i].m_Free = true;
    }
}


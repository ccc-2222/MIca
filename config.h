#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH 612 //宽
#define GAME_HEIGHT 612 //高
#define GAME_TITLE "catgogo1"//标题
#define GAME_RES_PATH "./plane4.rcc"//rcc文件路径
#define GAME_ICON ":/res/res.plane/spaceship/spaceship1.png"//图标加载路径
#define GAME_RATE 10//定时器刷新时间间隔 单位毫秒

#define MAP_PATH ":/new/res2/background.jpg"  //背景图

#define MAP_SCROLL_SPEED 2//滚动速度


//飞机
#define HERO_PATH ":/new/res2/sketch-1617236724567.png"


//子弹
#define BULLET_PATH ":/new/res2/image37.png" //图片
#define BULLET_SPEED 5  //移动速度
#define BULLET_NUM 30  //弹匣中子弹总数
#define BULLET_INTERVAL 20 //发送子弹的间隔


//敌机
#define ENEMY_PATH ":/new/res2/ネズミ.png"        //图片
#define ENEMY_SPEED 7 //敌机移动速度
#define ENEMY_NUM 20 //敌机总数量
#define ENEMY_INTERVAL 30 //敌机出场时间间隔

//音频
#define SOUND_BACKGROUND "qrc:/new/res2/Catsong (online-audio-converter.com).wav"

#define HERO_HEALTH 100

#endif // CONFIG_H

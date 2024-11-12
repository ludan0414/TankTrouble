//这个文件里声明了所有用到的接口
#pragma once
#include <vector>
#include <memory>
#include <array>
#include <windows.h>
class Controller{
    public:
    char left,right,forward,backward,shoot;
    Controller(char l,char r,char f,char b,char s);
    std::array<bool,5> status();
};
class Tank;
class Wall;
class Bullet;
class Game{
    public:
    static Tank *op1,*op2;
    static std::vector<Wall*> walls;
    static std::vector<Bullet*> bullets;
    static int bulletcnt[2];
    Game();
    void runframe();
    int run();
};
class Object{
    //包含了一个物体的基本信息：位置
    public:
    double xpos,ypos;
    Object(double Xpos,double Ypos);
};
class Team{
    //包含了所属队伍的信息
    public:
    int color;
    Team(int Color);
};
class Tank:public Object,public Team{
    public:
    double dirx,diry;//单位向量(x,y)表示坦克的方向
    int hp;//血量
    int shield;//护盾
    double speed;//坦克速度
    const double size;//坦克大小
    Controller input;
    Tank(double Xpos,double Ypos,double Dirx,double Diry,int color,char l,char r,char f,char b,char s);
    void move();//坦克移动，返货0表示正常，返回-1表示似了
};
class Bullet:public Object,public Team{
    public:
    double dirx,diry;//单位向量(x,y)表示子弹的方向
    int age;//存在时间
    const int maxage;//最长存在的时间
    double speed;//子弹速度
    const double size;//子弹大小
    void move();
    void destroy();
    Bullet(double Xpos,double Ypos,double Dirx,double Diry,int color);
    ~Bullet();
};
class Wall:public Object{
    public:
    int direction;//方向，0表示横着1表示竖着
    Wall(double x0,double y0,double x1,double y1);
};
Object::Object(double Xpos,double Ypos):xpos(Xpos),ypos(Ypos){}
Team::Team(int Color):color(Color){}
Wall::Wall(double x0,double y0,double x1,double y1):Object(x0,y0){
    if (x0==x1){
        direction=1;
    }
    else if (y0==y1){
        direction=0;
    }
    else{
        throw "Invalid wall build.";
    }
}
std::vector<Wall*> Game::walls;
int Game::bulletcnt[2];
Tank *Game::op1, *Game::op2;
std::vector<Bullet*> Game::bullets;
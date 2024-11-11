//这个文件里声明了所有用到的接口
#pragma once
#include <vector>
#include <memory>
class Game{
    Tank *op1,*op2;
    Game();
    void run();
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
    Tank(double Xpos,double Ypos,double Dirx,double Diry,int color);
    bool getstat();//根据输入计算坦克的状态
};
class Bullet:public Object,public Team{
    public:
    double dirx,diry;//单位向量(x,y)表示子弹的方向
    static int count;//计算现在存在几颗子弹
    int age;//存在时间
    void move();
    Bullet(double Xpos,double Ypos,double Dirx,double Diry,int color);
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
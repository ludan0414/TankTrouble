#include "tanktrouble.hpp"
Bullet::Bullet(double Xpos,double Ypos,double Dirx,double Diry,int Color):Object(Xpos,Ypos),Team(Color),maxage(600),size(0.05){
    dirx=Dirx;
    diry=Diry;
    age=0;
    Game::bulletcnt[Color]++;
    speed=1.0/60;//每秒移动一个单位
}
void Bullet::destroy(){
    delete this;
    return;
}
void Bullet::move(){
    xpos+=speed*dirx;
    ypos+=speed*diry;
    if (++age==maxage){
        //子弹消失
        destroy();
        return;
    }
    for (auto ptr:Game::walls){
        if (ptr->direction){//竖着的
            if (ypos>ptr->ypos && ypos<ptr->ypos+1 && xpos>ptr->xpos-size && xpos<ptr->xpos+size){//撞墙
                dirx=-dirx;
            }
        }
        else{//横着的
            if (xpos>ptr->xpos && xpos<ptr->xpos+1 && ypos>ptr->ypos-size && ypos<ptr->ypos+size){//撞墙
                diry=-diry;
            }
        }
    }
}
Bullet::~Bullet(){
    Game::bulletcnt[color]--;
}
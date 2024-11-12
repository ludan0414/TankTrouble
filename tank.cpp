#include "tanktrouble.hpp"
#include <cmath>
#include <utility>
Tank::Tank(double Xpos,double Ypos,double Dirx,double Diry,int Color,char l,char r,char f,char b,char s):Object(Xpos,Ypos),Team(Color),size(0.3),input(l,r,f,b,s){
    dirx=Dirx;
    diry=Diry;
    hp=2;
    speed=1.5/60;
    shield=0;
}
double totheta(double x,double y){
    if (x>0&&y>0)   return atan(y/x)*180/3.1415926;
    if (x<0&&y>0)   return 180+atan(y/x)*180/3.1415926;
    if (x<0&&y<0)   return 180+atan(y/x)*180/3.1415926;
    if (x>0&&y<0)   return 360+atan(y/x)*180/3.1415926;
    if (x==0&&y==1) return 90;
    if (x==0&&y==-1)    return 270;
    if (y==0&&x==1) return 0;
    if (y==0&&x==-1)    return 180;
    throw "WTF?";
}
std::pair<double,double> toxy(double theta){
    return std::make_pair(cos(theta/180*3.1415926),sin(theta/180*3.1415926));
}
void Tank::move(){
    auto inp=input.status();
    if (inp[0]){
        //左转
        double theta=totheta(dirx,diry);
        theta-=6;//左转6°（一秒转完一圈）
        auto tmp=toxy(theta);
        dirx=tmp.first;
        diry=tmp.second;
    }
    if (inp[1]){
        //右转
        double theta=totheta(dirx,diry);
        theta+=6;//右转6°（一秒转完一圈）
        auto tmp=toxy(theta);
        dirx=tmp.first;
        diry=tmp.second;
    }
    if (inp[2]){
        //往前
        double tx=xpos+dirx*speed;
        double ty=ypos+diry*speed;
        bool valid=1;
        for (auto ptr:Game::walls){
            if (ptr->direction){//竖着的
                if (ty>ptr->ypos && ty<ptr->ypos+1 && tx>ptr->xpos-size && tx<ptr->xpos+size){//撞墙
                    valid=0;
                }
            }
            else{//横着的
                if (tx>ptr->xpos && tx<ptr->xpos+1 && ty>ptr->ypos-size && ty<ptr->ypos+size){//撞墙
                    valid=0;
                }
            }
        }
        if (valid)  xpos=tx,ypos=ty;
    }
    if (inp[3]){
        //往后
        double tx=xpos-dirx*speed;
        double ty=ypos-diry*speed;
        bool valid=1;
        for (auto ptr:Game::walls){
            if (ptr->direction){//竖着的
                if (ty>ptr->ypos && ty<ptr->ypos+1 && tx>ptr->xpos-size && tx<ptr->xpos+size){//撞墙
                    valid=0;
                }
            }
            else{//横着的
                if (tx>ptr->xpos && tx<ptr->xpos+1 && ty>ptr->ypos-size && ty<ptr->ypos+size){//撞墙
                    valid=0;
                }
            }
        }
        if (valid)  xpos=tx,ypos=ty;
    }
    if (inp[4]){
        //射
        if (Game::bulletcnt[color]<3){
            Game::bullets.emplace_back(new Bullet(xpos+size+0.06,ypos+size+0.06,dirx,diry,color));
        }
    }
    //判断是否被击中
    std::vector<Bullet*> newlst;
    for (auto ptr:Game::bullets){
        #define dis(x,y,a,b) sqrt((x-a)*(x-a)+(y-b)*(y-b))
        if (dis(xpos,ypos,ptr->xpos,ptr->ypos)<size+0.05){
            //被击中了
            ptr->destroy();
            hp--;
        }
        else{
            newlst.emplace_back(ptr);
        }
        #undef dis
    }
    Game::bullets.clear();
    Game::bullets.swap(newlst);
    if (hp<=0){
        throw(color-1);
    }
}
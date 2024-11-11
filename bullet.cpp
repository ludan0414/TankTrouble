#include "tanktrouble.hpp"
Bullet::Bullet(double Xpos,double Ypos,double Dirx,double Diry,int color):Object(Xpos,Ypos),Team(color){
    dirx=Dirx;
    diry=Diry;
    age=0;
    count++;
}
void Bullet::move(){
    
}
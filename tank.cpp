#include "tanktrouble.hpp"
Tank::Tank(double Xpos,double Ypos,double Dirx,double Diry,int color):Object(Xpos,Ypos),Team(color){
    dirx=Dirx;
    diry=Diry;
    hp=2;
    shield=0;
}
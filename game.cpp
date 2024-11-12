#include "tanktrouble.hpp"
#include <ctime>
Game::Game(){
    op1=new Tank(0.5,0.5,1,0,0,65,68,87,83,13);//WASD Enter
    op2=new Tank(1.5,0.5,1,0,1,37,39,38,40,32);//上下左右 Space
    int gridx=8,gridy=8;
    for (int i=0;i<gridx;i++){
        walls.emplace_back(new Wall(i,0,i+1,0));
        walls.emplace_back(new Wall(i,gridy,i+1,gridy));
    }
    for (int j=0;j<gridy;j++){
        walls.emplace_back(new Wall(0,j,0,j+1));
        walls.emplace_back(new Wall(gridx,j,gridx,j+1));
    }
}
void Game::runframe(){
    for (auto p:bullets){
        p->move();
    }
    op1->move();
    op2->move();
}
int Game::run(){
    auto lst=clock();
    auto frametime=CLOCKS_PER_SEC/60.0;
    auto endtime=lst+(10)*CLOCKS_PER_SEC/60.0;
    runframe();
    while (1){
        auto nextframe=lst+CLOCKS_PER_SEC/60.0;
        if (nextframe>endtime)  break;
        auto gap=nextframe-clock();
        Sleep(gap);
        try{
            runframe();
        }
        catch (int id){
            return id;
        }
    }
    if (op1->hp==op2->hp)   return 0;
    if (op1->hp>op2->hp)    return -2;//op1胜利
    if (op1->hp<op2->hp)    return -1;//op2胜利
    return 0;
}
#include "tanktrouble.hpp"
#include <ctime>
//#define debug
Game::Game(){
    op1=new Tank(0.5,0.5,1,0,0,'A','D','W','S',13);//WASD Enter
    op2=new Tank(1.5,0.5,1,0,1,37,39,38,40,' ');//上下左右 Space
    int gridx=8,gridy=8;
    for (int i=0;i<gridx;i++){
        walls.emplace_back(new Wall(i,0,i+1,0));
        walls.emplace_back(new Wall(i,gridy,i+1,gridy));
    }
    for (int j=0;j<gridy;j++){
        walls.emplace_back(new Wall(0,j,0,j+1));
        walls.emplace_back(new Wall(gridx,j,gridx,j+1));
    }
    //test
    bullets.emplace_back(new Bullet(1,0.2,0,-1,1));
    //
}
void Game::runframe(){
    for (auto p:bullets){
        p->move();
        fprintf(stderr,"pos %lf %lf, dir %lf %lf, age%d\n",p->xpos,p->ypos,p->dirx,p->diry,p->age);
    }
    op1->move();
    op2->move();
    //(stderr,"pos %lf %lf dir %lf %lf\n",op1->xpos,op1->ypos,op1->dirx,op1->diry);
}
int Game::run(){
    auto lst=clock();
    //auto frametime=CLOCKS_PER_SEC/60.0;
    auto frametime=CLOCKS_PER_SEC/3;
    auto endtime=lst+(100*CLOCKS_PER_SEC);
    #ifdef debug
    printf("%ld\n",endtime);
    #endif
    runframe();
    while (1){
        auto nextframe=lst+frametime;
        if (nextframe>endtime)  break;
        auto now=clock();
        #ifdef debug
        printf("now %ld lst %ld\n",now,lst);
        #endif
        if (now<nextframe)  Sleep(nextframe-now);
        try{
            runframe();
        }
        catch (int id){
            printf("terminated\n");
            return id;
        }
        lst=now;
        #ifdef debug
        printf("%lf %lf\n",op1->xpos,op1->ypos);
        #endif

    }
    if (op1->hp==op2->hp)   return 0;
    if (op1->hp>op2->hp)    return -2;//op1胜利
    if (op1->hp<op2->hp)    return -1;//op2胜利
    return 0;
}
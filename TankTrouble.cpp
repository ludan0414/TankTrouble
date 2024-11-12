#include <bits/extc++.h>
#include "tanktrouble.hpp"
#include "bullet.cpp"
#include "tank.cpp"
#include "game.cpp"
#include "controller.cpp"
#define debug
int main(){
    Game p;
    Sleep(1000);
    int result=p.run();
    std::cout<<result<<std::endl;
    return 0;
}
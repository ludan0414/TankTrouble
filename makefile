CC = g++
CFLAGS = -c -Wall 

tanktrouble: tanktrouble.o tank.o bullet.o controller.o game.o
	$(CC) -Wl,--allow-multiple-definition tanktrouble.o game.o tank.o bullet.o controller.o -o tanktrouble

tanktrouble.o: tanktrouble.cpp
	$(CC) -Wl,--allow-multiple-definition tanktrouble.cpp -c -o tanktrouble.o 

bullet.o: bullet.cpp
	$(CC) -Wl,--allow-multiple-definition bullet.cpp -c -o bullet.o

tank.o: tank.cpp
	$(CC) -Wl,--allow-multiple-definition tank.cpp -c -o tank.o

game.o: game.cpp tank.o bullet.o
	$(CC) -Wl,--allow-multiple-definition game.cpp tank.o bullet.o -c -o game.o 

controller.o: controller.cpp
	$(CC) -Wl,--allow-multiple-definition controller.cpp -c -o controller.o

clean:
	del *.o 

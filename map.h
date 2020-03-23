#include <SFML/Graphics.hpp>
#include <iostream>
const int HEIGHT_MAP = 39;//висота карти
const int WIDTH_MAP = 92;//ширина


sf::String TileMap[HEIGHT_MAP] = {
  "0000000000000000000kkkkkk00000gg0000000000kkkk0000000kkkkkkk00000000000000000000000000000000",
  "0h                 0kkkk0    0gg0        0kkkk0      0kkkkk0                 h             0",
  "0                  0kkkk0    0gg0         00000       00k00         f                      0",
  "0           f       0k00     0000                      000                               f 0",
  "0                   0k0                                                            000     0",
  "0                    0                                    f                 00000          0",
  "0   0000f                                     0000                                         0",
  "0                                0000                                                      0",
  "0            f    00000                                         00000                      0",
  "0                      f                                                                   0",
  "0                                     00000                             0000               0",
  "0000                                                                                       0",
  "0ggg0                                                                     f        h       0",
  "0000             00                                                                        0",
  "0h             00k000          000000                                         0000         0",
  "0            000k0kkk00       0k0  h 0            00000                                    0",
  "0            0000000000      0k0      0         000000000      f                  f        0",
  "0                           000      h 0                                  0               0k",
  "0    00000                 0          0                                  0                0k",
  "0         0               0       h  0                                  0                0kk",
  "0                    00000f        00                        f       000                 0kk",
  "0                   0gg0f        00                               000                   0kkk",
  "0                   0gg0ff     00        000                              f             0kkk",
  "0                   00000000            0ggg0          f                                0000",
  "0   f       00000                      0ggggg0                                 0          h0",
  "0                                     0ggg0ggg0                          f    0g0          0",
  "0              f                    00gg00000gg0         00000              0000g0         0",
  "0     0000       000              0000000   00000000      0g0                   0g0        0",
  "0                               000              0kk0     0g0   00000            0g0f      0",
  "0                               0                 00000   0g0                     0g0      0",
  "0                               0                         000                      0g0     0",
  "0       f                       0                                                   0g0    0",
  "0                               0         0       f                      0000000   f 0     0",
  "0                       000    f       0000                                                0",
  "000                                   000000                                               0",
  "0gg0              00                  00k000                       0000                    0",
  "0ggg0           00k0                 0000k00                 000000g0      f               0",
  "0gggg0        00kk00                00000000f               0g0g0g0g0h                     0",
  "0000000000000000000000000000000000000000000000000000000000000g0g0g0g000000000000000000000000",
};

void randomMapGenerate(){//рандомно розставл€ю €щики

	int randomElementX = 0;//рандомний елемент по горизонтал≥
	int randomElementY = 0;//рандомний елемент по вертиккал≥
	srand(time(0));
	int countBox = 30;//вводимо к-сть €щик≥в

	while (countBox > 0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомн≥ числа в≥д 1 (до Ўирина карти - 1) щоб не попадати на границ≥ карти
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//див коментар≥й вище
		if (TileMap[randomElementY][randomElementX] == ' ')   {//€кщо проб≥л
			TileMap[randomElementY][randomElementX] = 's'; //то ставим €щик
			countBox--;//зменшуЇм к-сть €щик≥в €к≥ ще будуть поставлен≥
		}
	}
}

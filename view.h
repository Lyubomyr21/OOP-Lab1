#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//об'явив sfml об'єкт "View", котрий представляє собою камеру

void getplayercoordinateforview(float x, float y) {
	float tempX = x; float tempY = y;//зчитую координати персонажа

	if (x < 960) tempX = 960;//блокую камеру при виїзді за ліву сторону
	if (x > 3362) tempX = 3362;//праву
	if (y < 540) tempY = 540;//верхню
	if (y > 1293) tempY = 1293;//нижню

	view.setCenter(tempX, tempY); //Слідкую за персонажем передаючи його координати

}



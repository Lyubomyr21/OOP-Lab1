#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//��'���� sfml ��'��� "View", ������ ����������� ����� ������

void getplayercoordinateforview(float x, float y) {
	float tempX = x; float tempY = y;//������ ���������� ���������

	if (x < 960) tempX = 960;//������ ������ ��� ���� �� ��� �������
	if (x > 3362) tempX = 3362;//�����
	if (y < 540) tempY = 540;//������
	if (y > 1293) tempY = 1293;//�����

	view.setCenter(tempX, tempY); //������ �� ���������� ��������� ���� ����������

}



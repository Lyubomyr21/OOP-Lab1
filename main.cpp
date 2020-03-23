#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>


using namespace sf;

class Entity { //оголошуємо клас Entity який буде містити в собі основні поля і методи
public:
	float dx, dy, x, y, speed;
	int w,h,health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, float X, float Y,int W,int H,String Name){
		x = X; y = Y; w = W; h = H; name = Name;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
};




class Character :public Entity { //унаслідуємо клас Character від класу Entity
public:
	enum { left, right, up, jump, stay } state;//всі можливі стани персонажа
	int playerScore;
	   Character(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		   playerScore = 0; state = stay;
		   if (name == "Character"){
			   sprite.setTextureRect(IntRect(0, 0, w, h));
		   }
	   }


	void update(float time)
	{

		switch (state)
		{
		case right: dx = speed;break;
		case left: dx = -speed;break;
		case up: break;
		case jump: break;
		case stay: break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//перевіряю на зіткнення по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//перевіряю на зіткнення по Y
		if (!isMove) speed = 0;
		sprite.setPosition(x+w/2, y+h/2); //задаю позицію спрайта в його центр
		interactionWithMap();
		if (health <= 0){life = false;}
		dy = dy + 0.0015*time;//реалізую гравітацію
	}

	float getplayercoordinateX(){return x;}
	float getplayercoordinateY(){return y;}

	void checkCollisionWithMap(float Dx, float Dy)//функція перевірки зіткнень з елементами карти
	{
		for (int i = y / 47; i < (y + h) / 47; i++)
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (Dy>0){ y = i * 47 - h;  dy = 0; onGround = true; }
				if (Dy<0){y = i * 47 + 47;  dy = 0;}
				if (Dx>0){x = j * 47 - w; }
				if (Dx<0){x = j * 47 + 47;}
			}
		}
	}



	void interactionWithMap()//взаємодія з елементами карти
  {

    for (int i = y / 47; i < (y + h) / 47; i++)
    for (int j = x / 47; j<(x + w) / 47; j++)
    {
        if (TileMap[i][j] == 's') {
        playerScore++;//якщо підняли ящик к-сть очків збільшиться на 1
        TileMap[i][j] = ' ';//ящик пропадає
      }

      if (TileMap[i][j] == 'f') {
        health -= 60;//якщо наступити на вогник к-сть очків здоров'я зменшиться на 60
        TileMap[i][j] = ' ';//вогник пропадає
      }

      if (TileMap[i][j] == 'h') {
        health += 30;//якщо підняти сердечко к-сть очків здоров'я збільшиться на 30
        TileMap[i][j] = ' ';//сердечко пропадає
      }
    }
  }
};




int main()
{
    randomMapGenerate();

	RenderWindow window(VideoMode(1920, 1080), "GameV1", Style::Fullscreen);//створюю вікно в якому буде генеруватися гра
	view.reset(FloatRect(0, 0, 1920, 1080));

	Font font;
    font.loadFromFile("18383.ttf");//підключаю шрифт

    Text text1("", font, 40);
    Text text2("", font, 60);

    text1.setColor(Color::White);
    text2.setColor(Color::White);


	Image map_image;
	map_image.loadFromFile("images/map3.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);


	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Character p(heroImage, 1600, 450, 83, 90 ,"Character");


	float CurrentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;
	int tempY = 0;
    Clock gameTimeClock;
    int gameTime = 0;
	float distance = 0;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();  else  {
                p.sprite.setTextureRect(IntRect(0,245,67,95));
                p.sprite.setRotation(-110.f);

        }

		clock.restart();
		time = time / 800;


		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed)
            window.close();
		}


		if (p.life) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.state = p.left;
			p.speed = 0.4;
			CurrentFrame += 0.007*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            p.sprite.setTextureRect(IntRect(83 * int(CurrentFrame), 128, 83, 96));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.state = p.right;
			p.speed = 0.4;
            CurrentFrame += 0.007*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            p.sprite.setTextureRect(IntRect(82 * int(CurrentFrame), 0, 82, 96));
        }

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (p.onGround)) {
			p.state = p.jump; p.dy = -0.9; p.onGround = false;
		}

		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}

		p.update(time);

		window.setView(view);
		window.clear();

			for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 47, 47));//фон
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(375, 0, 47, 47));//ящик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(953, 0, 47, 47));//метал
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(285, 0, 47, 47));//вогонь
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(154, 0, 47, 47));//серце
				if ((TileMap[i][j] == 'g')) s_map.setTextureRect(IntRect(587, 0, 47, 47));//цегла
				if ((TileMap[i][j] == 'k')) s_map.setTextureRect(IntRect(697, 0, 47, 47));//лід
				s_map.setPosition(j * 47, i * 47);

				window.draw(s_map);
			}

        std::ostringstream playerHealthString, playerScoreString;

        playerHealthString << p.health;
        playerScoreString << p.playerScore;

        text1.setString("Health: " + playerHealthString.str());
        text2.setString("Score:  " + playerScoreString.str());

        text1.setPosition(view.getCenter().x + 700, view.getCenter().y - 460);
        text2.setPosition(view.getCenter().x - 945, view.getCenter().y - 470);

        window.draw(text1);
        window.draw(text2);
    	window.draw(p.sprite);
		window.display();
	}
	return 0;
}

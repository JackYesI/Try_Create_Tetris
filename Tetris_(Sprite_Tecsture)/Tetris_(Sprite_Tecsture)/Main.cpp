#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <cstdlib>
using namespace sf;

const unsigned int N = 500;
const unsigned int M = 500;

int field[20][10] = { 0 };

struct Point
{
	int x;
	int y;
}a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 142 || a[i].x >= 322 || a[i].y > 360) {
			std::cout << "window size :: (" << a[i].x << ";" << a[i].y << ");\n";
			return 0;
		}
		else if (field[a[i].y / 18 - 1][(a[i].x - 142) / 18]) {
			
			return 0;
		}
	
	return 1;
}



//bool beginPosition(const int& n)
//{
//	for (size_t i = 0; i < 4; i++)
//	{
//		if (!(a[i].x == 232 + (figures[n][i] % 2) * 18 and a[i].y == (figures[n][i] / 2) * 18 + 18 - 18 and n == 0) or !(a[i].x == 232 + (figures[n][i] % 2) * 18 and a[i].y == (figures[n][i] / 2) * 18 - 18 and n != 0))
//			return 0;
//	}
//	return 1;
//}

int main()
{

	unsigned int points = 0;

	srand(time(0));
	RenderWindow window(VideoMode(N, M), "My game try 2");

	Event ev;
	Texture texture;
	texture.loadFromFile("D:\\c++\\Tetris\\Tetris_(Sprite_Tecsture)\\Images\\tiles.png");
	Sprite sprite(texture);

	int colorNum = 1;
	/*sprite.setTextureRect(IntRect(0, 0, 18, 18));*/
	sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
	float dx = 0; 
	bool rotate = false; 
	 

	float timer = 0, delay = 0.3;

	Clock clock;

	int n = rand() % 7;
	bool beginGame = true;

	// Resources
	sf::Font fonts;
	if (!fonts.loadFromFile("D:\\c++\\Game\\SFML_\\Rubik_Doodle_Triangles\\RubikDoodleTriangles-Regular.ttf"))
	{
		std::cout << "ERROR FONTS" << "\n";
	}
	// Text
	sf::Text uiText, uiText_2;

	// Lines 
	size_t lines_born = 0;

	uiText.setFont(fonts);
	uiText.setCharacterSize(25);
	uiText.setFillColor(sf::Color(39, 255, 254));
	uiText.setString("NONE");

	uiText_2.setFont(fonts);
	uiText_2.setCharacterSize(25);
	uiText_2.setFillColor(sf::Color(108, 57, 150));
	uiText_2.setString("NONE");

	// main work loop
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		// event
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
			if (ev.type == Event::KeyPressed)
				if (ev.key.code == Keyboard::Up) rotate = true;
				else if (ev.key.code == Keyboard::Left) dx = -18;
				else if (ev.key.code == Keyboard::Right) dx = 18;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		window.clear(Color(243, 98, 153));
		
		// first create tetramino
		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = 232 + (figures[n][i] % 2) * 18;
				if (n == 0)
					a[i].y = (figures[n][i] / 2) * 18 + 18;
				else
					a[i].y = (figures[n][i] / 2) * 18;
			}
		}

		// rotate
		if (rotate and n != 6)
		{
			Point p = a[1]; 
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; // y - y0
				int y = a[i].x - p.x; // x - x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		if (!check()) {
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}
		
		/*if (a[0].x == 0)
		for (int i = 0; i < 4; i++)
		{
			a[i].x = window.getSize().x / 2 - 18 + (figures[n][i] % 2) * 18;
			a[i].y = (figures[n][i] / 2) * 18;
		}*/

		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		// Draw main tetraino
		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(a[i].x, -18 + a[i].y);
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			window.draw(sprite);
		}

		// Draw field
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18 + 142, i * 18);
				window.draw(sprite);
			}
		
		/*if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 18;
			timer = 0;

		}

		dx = 0;
		rotate = 0;*/

		// pop lines
		int k = 20 - 1;
		int k_ = 0;
		for (int i = 20 - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < 10; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < 10) {
				k--;
			}
			if (count == 10)
				k_++;
			
		}

		// Lines born
		lines_born += k_;

		// count points
		if (k_ == 4) points += 1000;
		else
			points += 200 * k_;


		// update text
		std::stringstream pL, bL;

		pL << "Points: " << points << "\n";
		bL << "Lines borned: " << lines_born << "\n";

		uiText.setString(pL.str());
		uiText_2.setString(bL.str());


		//// first create tetramino
		//if (beginGame)
		//{
		//	beginGame = false;
		//	n = rand() % 7;
		//	for (int i = 0; i < 4; i++)
		//	{
		//		a[i].x = 232 + (figures[n][i] % 2) * 18;
		//		if (n == 0)
		//			a[i].y = (figures[n][i] / 2) * 18 + 18;
		//		else
		//			a[i].y = (figures[n][i] / 2) * 18;
		//	}
		//}
		
		// falling down
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 18; }
			
			
			if (!check())
			{
				for (int i = 0; i < 4; i++) field[b[i].y / 18 - 1][(b[i].x - 142) / 18] = colorNum;
				colorNum = 1 + rand() % 7;
				
				n = 1 + (rand() % 8) - 1;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = 232 + (figures[n][i] % 2) * 18;
					if (n == 0)
						a[i].y = (figures[n][i] / 2) * 18 + 18;
					else
						a[i].y = (figures[n][i] / 2) * 18;
				}

			}
			timer = 0;

		}

		dx = 0;
		rotate = 0;
		delay = 0.3;

		uiText_2.setPosition(0, 470);
		window.draw(uiText);
		window.draw(uiText_2);

		if (field[1][5] or field[1][4] or field[1][6])
		{
			// draw fild haert
			for (size_t i = 0; i < 20; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					if (i == 6 and (j == 2 or j == 3 or j == 6 or j == 7 or j == 8))
						field[i][j] = 1;
					else if (i == 7 and ((j  <= 4 and j >= 1) or (j <= 8 and j >= 6)))
						field[i][j] = 1;
					else if (i == 8 and j == 5)
						field[i][j] = 0;
					else if (i == 9 and (j == 4 or j == 5))
						field[i][j] = 0;
					else if (i <= 10 and i >= 8)
						field[i][j] = 1;
					else if (i == 11 and (j == 4 or j == 5))
						field[i][j] = 0;
					else if (i == 11 and j != 0)
						field[i][j] = 1;
					else if (i == 12 and j == 5)
						field[i][j] = 0;
					else if (i == 13 and j == 5)
						field[i][j] = 0;
					else if (i == 12 and j != 0)
						field[i][j] = 1;
					else if (i == 13 and (j >= 2 and j <= 7))
						field[i][j] = 1;
					else if (i == 14 and j == 4)
						field[i][j] = 1;
					else if (i == 15 and j == 5)
						field[i][j] = 1;
					else if (i == 10 and j == 4)
						field[i][j] = 0;
					else if (i == 14 and (j == 5 or j == 6))
						field[i][j] = 0;
					else 
						field[i][j] = 0;

					field[10][4] = 0;
				}
			}

			/*Texture textureH;
			textureH.loadFromFile("D:\\c++\\Tetris\\Tetris_(Sprite_Tecsture)\\Images\\bH.png");

			Sprite spriteH(textureH);
			spriteH.setPosition(200,190);*/

			std::stringstream pL, bL;

			pL << "Total Points: " << points << "\n";
			bL << "Total Lines: " << lines_born << "\n";

			if (points > 4000)
				uiText.setString(pL.str() + bL.str() + "\nNive try");
			else if (points > 10000)
				uiText.setString(pL.str() + bL.str() + "\nAmazing score)");
			else
				uiText.setString(pL.str() + bL.str());
			while (window.isOpen())
			{
				bool break_ = 0;
				window.clear(Color(70, 160, 212));
				while (window.pollEvent(ev))
				{
					if (ev.type == Event::Closed or ev.key.code == Keyboard::Escape)
						window.close();
					if (ev.key.code == Keyboard::Up)
					{
						for (size_t i = 0; i < 20; i++)
						{
							for (size_t j = 0; j < 10; j++)
							{
								field[i][j] = 0;
							}
						}
						points = 0;
						lines_born = 0;
						window.clear();
						break_ = true;
						break;
					}
				}

				if (break_) break;



				// Draw field
				for (int i = 0; i < 20; i++)
					for (int j = 0; j < 10; j++)
					{
						if (field[i][j] == 0) continue;
						sprite.setTextureRect(IntRect(2 * 18, 0, 18, 18));
						sprite.setPosition(j * 18 + 142, i * 18);
						window.draw(sprite);
					}

				window.draw(uiText);
				/*window.draw(spriteH);*/
				window.display();
			}
			
		}

		window.display();
	}
	std::cout << "END GAME" << std::endl;
}
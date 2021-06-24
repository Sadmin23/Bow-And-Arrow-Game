#ifndef sizesll
#define sizesll
//#include <fstream>

int highscore;

typedef struct Boxes Boxes;

struct Buttonxy
{
	int x1;
	int y1;
	int x2;
	int y2;
};

typedef struct Buttonxy Button;

Button button[12];

struct Mousexy
{
	int x;
	int y;
};

typedef struct Mousexy Mouse;

Mouse pointer;

using namespace std;

int button_pressed(Mouse pointer, Button button)
{
	if (pointer.x >= button.x1 && pointer.x <= button.x2 && pointer.y >= button.y1 && pointer.y <= button.y2)
		return 1;
	return 0;
}
void update(int score)
{
	ifstream file;

	file.open("highscore.txt");

	file >> highscore;

	if (score > highscore)
	{
		ofstream temp;
		temp.open("temp.txt");
		temp << score;
		file.close();
		temp.close();
		remove("highscore.txt");
		rename("temp.txt", "highscore.txt");
	}
	else
		file.close();

	file.open("highscore.txt");

	file >> highscore;
}
void Reset()
{
	ofstream temp;
	temp.open("temp.txt");
	temp << 0;
	temp.close();
	remove("highscore.txt");
	rename("temp.txt", "highscore.txt");

}

#endif
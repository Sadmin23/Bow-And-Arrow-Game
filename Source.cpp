#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <fstream>
#include <SDL_ttf.h>
#include <iostream>
#include "Move.h"
#include "File.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 690;
const int SCROLL_SPEED = 20;
const int F_N = 9;
const int N = 2;
const int M = 30;
const int speed1 = 10;
const int speed2 = 20;

int BOX_SPEED = speed1;
int ARROW_SPEED = speed2;
int gameover = 0;
int gamestate = 0;
int score = 0;
int index = 8;
int start;

int box_speed;// = BOX_SPEED;
int arrow_speed;// = ARROW_SPEED;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(std::string path);

SDL_Window* Window;

SDL_Renderer* Renderer;

SDL_Texture* Box_Tex[5];
SDL_Texture* Feature_Tex[F_N];
SDL_Texture* Archer_Tex;
SDL_Texture* Arrow_Tex;
SDL_Texture* Bar_Tex;
SDL_Texture* Currentscore_Font;
SDL_Texture* Arrows_tex;

SDL_Texture* MainMenu_Tex;
SDL_Texture* Background_Tex;
SDL_Texture* Gameover_Tex;
SDL_Texture* YourScore_Tex;
SDL_Texture* Instruction1_Tex;
SDL_Texture* Instruction2_Tex;
SDL_Texture* HighScore_Tex;
SDL_Texture* Highscore_Font;
SDL_Texture* Yourscore_Font;

SDL_Color black = { 0, 0, 0 };

struct Boxes
{
	SDL_Rect box[N];
	int points;
	int width, height;
	int flag[N];
};

typedef struct Boxes Boxes;

Boxes Box[5];

struct Features
{
	int width, height;
	Uint32 start;
	int flag;
	int flag_r[N];
	SDL_Rect feature[N];
	int flag_mess;
	const char* message;
};

typedef struct Features Features;

Features Feature[F_N];

bool quit = false;
SDL_Event e;

typedef struct Boxes Boxes;

void Mainmenu();
void Play();
void Gameover();
void YourScore();
void Instruction1();
void Instruction2();
void HighScore();
void Reset();

void init_Box();
void init_Feature();
void adjustspeed();
void adjustsize();
void enlarger();
void reducer();
void original();
void Play();
void loadbuttons();

int min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}
int max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		Window = SDL_CreateWindow("Bow And Arrow Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
			TTF_Init();
		}
	}

	return success;
}
bool loadMedia()
{
	bool success = true;

	Box_Tex[0] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/box2.png");
	Box_Tex[1] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/box4.png");
	Box_Tex[2] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/box1.png");
	Box_Tex[3] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/box5.png");
	Box_Tex[4] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/box6.png");

	Feature_Tex[0] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/snow2.png");
	Feature_Tex[1] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/snow1.png");
	Feature_Tex[2] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/up_speed.jpg");
	Feature_Tex[3] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/down_speed.jpg");
	Feature_Tex[4] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/right2.png");
	Feature_Tex[5] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/zoom2.png");
	Feature_Tex[6] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/zoom.png");
	Feature_Tex[7] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/2x.jpg");
	Feature_Tex[8] = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/danger.png");

	Archer_Tex = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/archer2.png");

	Arrow_Tex = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/arrow.jpg");

	Background_Tex = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/background.png");

	Bar_Tex = loadTexture("C:/Users/DOEL/Desktop/programming/test1/game images/topbar.png");

	Archer_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/archer.png");

	MainMenu_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/mainmenu.jpg");

	Background_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/background.png");

	Gameover_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/gameover.jpg");

	YourScore_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/yourscore.png");

	Instruction1_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/instruction1.jpg");

	Instruction2_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/instruction2.jpg");

	HighScore_Tex = loadTexture("C:/Users/DOEL/Desktop/Bow and Arrow game/images/highscore.jpg");

	return success;
}
void close()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

	Window = NULL;
	Renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

using namespace std;

bool Collisioncheck(int arr_x, int arr_w, int arr_y, int box_x, int box_y, int box_w, int box_h)
{
	if (arr_x + arr_w >= box_x && arr_x + arr_w <= box_x + 20 && arr_y >= box_y && arr_y <= box_y + box_h)
		return true;
	return false;
}
bool InsideScreen(SDL_Rect rect)
{
	if (rect.x + rect.w < SCREEN_WIDTH && rect.y>0 && rect.y + rect.h < SCREEN_HEIGHT)
		return true;
	return false;
}
string redefine(string num)
{
	if (num.size() == 2)
		num = "0" + num;
	else if (num.size() == 1)
		num = "00" + num;
	return num;
}
string redefine2(string num)
{
	if (num.size() == 1)
		num = "  " + num;
	else if (num.size()==2)
		num = " " + num;

	return num;
}
string redefine3(string num)
{
	if (num.size() == 1)
		num = " " + num;

	return num;
}
int main(int argc, char* args[])
{
	loadbuttons();

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			while (!quit)
			{
				if (gamestate == 0)
					Mainmenu();
				else if (gamestate == 1)
					Play();
				else if (gamestate == 2)
					Gameover();
				else if (gamestate==6)
					YourScore();
				else if (gamestate == 3)
					Instruction1();
				else if (gamestate == 4)
					Instruction2();
				else if (gamestate == 5)
					HighScore();
			}
		}
	}
	return 0;
}
void Mainmenu()
{
	gameover = 0;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			pointer.x = e.button.x;
			pointer.y = e.button.y;

			if (button_pressed(pointer, button[0]))
			{
				gameover = 0;
				gamestate = 1;
			}
			else if (button_pressed(pointer, button[1]))
				gamestate = 3;
			else if (button_pressed(pointer, button[2]))
				gamestate = 5;
		}
	}

	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, MainMenu_Tex, NULL, NULL);
	SDL_RenderPresent(Renderer);

}
void Play()
{
	index = 8;

	srand(time(0));

	init_Box();

	init_Feature();

	SDL_Rect Archer;

	int y2_pos = 0;

	Archer.x = 10;
	Archer.y = 0;
	Archer.w = 175;
	Archer.h = 197;

	SDL_Rect Arrow[M];
	int Arrow_flag[M];
	int Arrow_xpos[M];

	score = 0;

	for (int i = 0; i < M; i++)
	{
		Arrow[i].x = 48;
		Arrow[i].y = 112;
		Arrow[i].w = 125;
		Arrow[i].h = 2;
		Arrow_flag[i] = 0;
		Arrow_xpos[i] = 48;
	}

	SDL_Rect Bar;

	Bar.x = 160;
	Bar.y = 0;
	Bar.w = SCREEN_WIDTH - Bar.x;
	Bar.h = 100;;

	int shot = -1;

	box_speed = BOX_SPEED;
	arrow_speed = ARROW_SPEED;
	start = 0;

	while (!gameover && !quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
				break;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					if (Feature[0].flag == 0)
						y2_pos = max(0, y2_pos - SCROLL_SPEED);
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					if (Feature[0].flag == 0)
						y2_pos = min(SCREEN_HEIGHT - Archer.h, y2_pos + SCROLL_SPEED);
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					if (shot < M - 1)
						++shot;
				}
			}

		}

		for (int i = 0; i < F_N; i++)
		{
			if (SDL_GetTicks() - Feature[i].start >= 20000 && Feature[i].flag == 1)
			{
				Feature[i].flag = 0;
			}
		}
		if (SDL_GetTicks() - start >= 30000)
		{
			//printf("%d %d\n", BOX_SPEED, ARROW_SPEED);

			BOX_SPEED++;
			ARROW_SPEED += 2;
			start = SDL_GetTicks();
		}
		adjustspeed();

		arrow_speed = ARROW_SPEED;

		adjustsize();

			Archer.y = y2_pos;

			for (int j = shot + 1; j < M; j++)
				Arrow[j].y = y2_pos + 112;

			for (int j = 0; j <= shot; j++)
				right(&Arrow[j], arrow_speed);

			for (int i = 1; i <= 5; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (Feature[1].flag == 0)
					{
						if (Box[i - 1].box[j].x >= SCREEN_WIDTH || Box[i - 1].box[j].y + Box[i - 1].box[j].h <= 0 || Box[i - 1].flag[j] == 0)
						{
							Box[i - 1].box[j].x = (rand() % 8) * 90 + 190;
							Box[i - 1].box[j].y = (rand() % 34) * 90 + 1000;
							Box[i - 1].flag[j] = 1;
						}
						else
						{
							if (Feature[4].flag == 1 && InsideScreen(Box[i - 1].box[j]))
								right(&Box[i - 1].box[j], box_speed / 2);

							up(&Box[i - 1].box[j], box_speed);
						}
					}
				}
			}
			for (int i = 0; i < F_N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (Feature[1].flag == 0)
					{
						if (Feature[i].feature[j].y + Feature[i].feature[j].h <= 0 || Feature[i].flag_r[j] == 0)
						{
							Feature[i].feature[j].x = (rand() % 8) * 90 + 190;
							Feature[i].feature[j].y = (rand() % 34) * 90 + 1000;
							Feature[i].flag_r[j] = 1;
						}
						else
						{
							if (Feature[4].flag == 1 && InsideScreen(Feature[i].feature[j]))
								right(&Feature[i].feature[j], box_speed / 2);

							up(&Feature[i].feature[j], box_speed);

						}
					}
				}
			}

			for (int i = 0; i <= shot; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					for (int k = 0; k < N; k++)
					{
						if (Collisioncheck(Arrow[i].x, Arrow[i].w, Arrow[i].y, Box[j].box[k].x, Box[j].box[k].y, Box[j].box[k].w, Box[j].box[k].h) == true)
						{
							Box[j].flag[k] = 0;
							if (Feature[7].flag == 1)
								score += 2 * Box[j].points;
							else
								score += Box[j].points;
						}
					}
				}
				for (int j = 0; j < F_N; j++)
				{
					for (int k = 0; k < N; k++)
					{
						if (Collisioncheck(Arrow[i].x, Arrow[i].w, Arrow[i].y, Feature[j].feature[k].x, Feature[j].feature[k].y, Feature[j].feature[k].w, Feature[j].feature[k].h) == true)
						{
							Feature[j].flag_r[k] = 0;
							Feature[j].flag = 1;
							if (j == 2)
								Feature[3].flag = 0;
							else if (j == 3)
								Feature[2].flag = 0;
							if (j == 5)
								Feature[6].flag = 0;
							else if (j == 6)
								Feature[5].flag = 0;

							Feature[j].start = SDL_GetTicks();

							index = j;
						}
					}
				}
			}

		int Arrows_left = M - shot - 1;

		string CurrScore = " Score: ";
		string Arrows = "Arrows: ";

		Arrows = Arrows + redefine3(to_string(Arrows_left));
		CurrScore = CurrScore + redefine2(to_string(score));

		const char* Curr_Score = CurrScore.c_str();
		const char* ArrLeft = Arrows.c_str();

		TTF_Font* Numericfont = TTF_OpenFont("font5.ttf", 100);

		SDL_Surface* YourScorefont_surf = TTF_RenderText_Solid(Numericfont, Curr_Score, black);
		SDL_Texture* YourScorefont_tex = SDL_CreateTextureFromSurface(Renderer, YourScorefont_surf);

		TTF_Font* Textfont = TTF_OpenFont("font4.ttf", 100);

		SDL_Surface* Mess_surf = TTF_RenderText_Solid(Textfont, Feature[index].message, black);
		SDL_Texture* Mess_Tex = SDL_CreateTextureFromSurface(Renderer, Mess_surf);

		SDL_Surface* Arrows_surf = TTF_RenderText_Solid(Numericfont, ArrLeft, black);
		SDL_Texture* Arrows_tex = SDL_CreateTextureFromSurface(Renderer, Arrows_surf);

		SDL_Rect Yourscore;

		Yourscore.x = 820;
		Yourscore.y = 10;
		Yourscore.w = 120;
		Yourscore.h = 30;

		SDL_Rect ArrowL;

		ArrowL.x = 820;
		ArrowL.y = 50;
		ArrowL.w = 120;
		ArrowL.h = 30;

		SDL_Rect Message;

		int Width = 0;
		int Height = 30;

		SDL_QueryTexture(YourScorefont_tex, NULL, NULL, &Width, NULL);

		Message.x = 250;
		Message.y = 30;
		Message.w = Width;
		Message.h = Height;

		SDL_RenderClear(Renderer);

		SDL_RenderCopy(Renderer, Background_Tex, NULL, NULL);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (Box[i].flag[j] == 1)
					SDL_RenderCopy(Renderer, Box_Tex[i], NULL, &Box[i].box[j]);
			}
		}
		for (int i = 0; i < F_N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (Feature[i].flag_r[j] == 1)
					SDL_RenderCopy(Renderer, Feature_Tex[i], NULL, &Feature[i].feature[j]);
			}
		}
		for (int i = 0; i < M; i++)
			SDL_RenderCopy(Renderer, Arrow_Tex, NULL, &Arrow[i]);

		SDL_RenderCopy(Renderer, Archer_Tex, NULL, &Archer);

		SDL_RenderCopy(Renderer, Bar_Tex, NULL, &Bar);

		SDL_RenderCopy(Renderer, YourScorefont_tex, NULL, &Yourscore);

		SDL_RenderCopy(Renderer, Arrows_tex, NULL, &ArrowL);

		SDL_RenderCopy(Renderer, Mess_Tex, NULL, &Message);

		SDL_RenderPresent(Renderer);

		SDL_Delay(100);

		if (shot == M - 1 && Arrow[shot].x >= SCREEN_WIDTH || Feature[8].flag == 1)
		{
			//printf("%d %d\n", BOX_SPEED, ARROW_SPEED);
			gameover = 1;
			gamestate = 2;
			BOX_SPEED = speed1;
			ARROW_SPEED = speed2;
			break;
		}

	}

	update(score);

}
void Gameover()
{		
	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, Gameover_Tex, NULL, NULL);
	SDL_RenderPresent(Renderer);

	SDL_Delay(2000);

	gamestate = 6;
	
}
void YourScore()
{
	SDL_Rect Cartoon;

	Cartoon.x = 600;
	Cartoon.y = 150;
	Cartoon.w = 263;
	Cartoon.h = 296;

	string Score = to_string(score);
	Score = redefine(Score);
	const char* Finalscore = Score.c_str();

	TTF_Font* YourScorefont = TTF_OpenFont("font2.ttf", 250);

	SDL_Surface* YourScorefont_surf = TTF_RenderText_Solid(YourScorefont, Finalscore, black);
	SDL_Texture* YourScorefont_tex = SDL_CreateTextureFromSurface(Renderer, YourScorefont_surf);

	int Width = 0;
	int Height = 0;

	SDL_QueryTexture(YourScorefont_tex, NULL, NULL, &Width, &Height);

	SDL_Rect Yourscorefont;

	Yourscorefont.x = 170;
	Yourscorefont.y = 170;
	Yourscorefont.w = Width;
	Yourscorefont.h = Height;

	SDL_Rect fillRect = { 170, 170, Width, Height};
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	 
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			pointer.x = e.button.x;
			pointer.y = e.button.y;

			if (button_pressed(pointer, button[3]))
			{
				gamestate = 1;
				gameover = 0;
			}
			else if (button_pressed(pointer, button[5]))
				gamestate = 0;
			else if (button_pressed(pointer, button[4]))
				gamestate = 5;
		}
	}

	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, YourScore_Tex, NULL, NULL);
	SDL_RenderFillRect(Renderer, &fillRect);
	SDL_RenderCopy(Renderer, Archer_Tex, NULL, &Cartoon);
	SDL_RenderCopy(Renderer, YourScorefont_tex, NULL, &Yourscorefont);
	SDL_RenderPresent(Renderer);

}
void Instruction1()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			pointer.x = e.button.x;
			pointer.y = e.button.y;

			if (button_pressed(pointer, button[7]))
				gamestate = 4;
			else if (button_pressed(pointer, button[8]))
				gamestate = 0;
		}
	}

	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, Instruction1_Tex, NULL, NULL);
	SDL_RenderPresent(Renderer);

}
void Instruction2()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			pointer.x = e.button.x;
			pointer.y = e.button.y;

			if (button_pressed(pointer, button[9]))
				gamestate = 3;
			else if (button_pressed(pointer, button[8]))
				gamestate = 0;
		}
	}

	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, Instruction2_Tex, NULL, NULL);
	SDL_RenderPresent(Renderer);

}
void HighScore()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			pointer.x = e.button.x;
			pointer.y = e.button.y;

			if (button_pressed(pointer, button[11]))
				gamestate = 0;
			else if (button_pressed(pointer, button[10]))
				Reset();
		}
	}

	string highscore;

	highscore = redefine(to_string(get_highscore()));

	const char* Highscore = highscore.c_str();

	TTF_Font* font = TTF_OpenFont("font1.ttf", 250);
	SDL_Surface* surface = TTF_RenderText_Solid(font, Highscore, black);
	SDL_Texture* Highscorefont_tex = SDL_CreateTextureFromSurface(Renderer, surface);

	int Width = 0;
	int Height = 0;

	SDL_QueryTexture(Highscorefont_tex, NULL, NULL, &Width, &Height);

	SDL_Rect HighScore;
	
	HighScore.x = 20; 
	HighScore.y = 200;
	HighScore.w = Width;
	HighScore.h = Height;

	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, HighScore_Tex, NULL, NULL);
	SDL_RenderCopy(Renderer, Highscorefont_tex, NULL, &HighScore);
	SDL_RenderPresent(Renderer);

	TTF_CloseFont(font);
}
void init_Box()
{
	for (int i = 1; i <= 5; i++)
	{
		Box[i - 1].points = (5 - i + 1) * 3;
		Box[i - 1].width = 10 + 12 * i;
		Box[i - 1].height = 10 + 12 * i;

		for (int j = 0; j < N; j++)
		{
			Box[i - 1].flag[j] = 1;
			Box[i - 1].box[j].w = Box[i - 1].width;
			Box[i - 1].box[j].h = Box[i - 1].height;
			Box[i - 1].box[j].x = (rand() % 8) * 90 + 190;
			Box[i - 1].box[j].y = (rand() % 34) * 90 + 1000;
		}
	}
}
void init_Feature()
{
	for (int i = 0; i < F_N; i++)
	{
		Feature[i].start = 0;
		Feature[i].flag = 0;
		Feature[i].height = 46;
		Feature[i].width = 46;

		for (int j = 0; j < N; j++)
		{
			Feature[i].flag_r[j] = 1;
			Feature[i].feature[j].x = (rand() % 8) * 90 + 190;
			Feature[i].feature[j].y = (rand() % 34) * 90 + 1000;
			Feature[i].feature[j].w = Feature[i].width;
			Feature[i].feature[j].h = Feature[i].height;
			Feature[i].flag_mess = 0;
		}

		Feature[4].flag_mess = 1;
	}

	Feature[0].message = "ARCHER FROZEN";
	Feature[1].message = "BOXES FROZEN";
	Feature[2].message = "BOX SPEED INCREASED";
	Feature[3].message = "BOX SPEED DECREASED";
	Feature[4].message = "EASTWARDS MOVEMENT ENABLED";
	Feature[5].message = "BOXES SIZE INCRESED";
	Feature[6].message = "BOXES SIZE DECREASED";
	Feature[7].message = "DOUBLE POINTS ENABLED";
	Feature[8].message = "";

}
void adjustspeed()
{
	if (Feature[2].flag == 1)
		box_speed = BOX_SPEED * 1.25;
	if (Feature[3].flag == 1)
		box_speed = BOX_SPEED * 0.75;
	if (Feature[2].flag == 0 && Feature[3].flag == 0)
		box_speed = BOX_SPEED;
}
void adjustsize()
{
	if (Feature[5].flag == 1)
		enlarger();
	if (Feature[6].flag == 1)
		reducer();
	if (Feature[5].flag == 0 && Feature[6].flag == 0)
		original();
}
void enlarger()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Box[i].box[j].h = Box[i].height * 1.25;
			Box[i].box[j].w = Box[i].width * 1.25;
		}
	}
	for (int i = 0; i < F_N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Feature[i].feature[j].h = Feature[i].height * 1.25;
			Feature[i].feature[j].w = Feature[i].width * 1.25;
		}
	}
}
void reducer()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Box[i].box[j].h = Box[i].height * 0.75;
			Box[i].box[j].w = Box[i].width * 0.75;
		}
	}
	for (int i = 0; i < F_N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Feature[i].feature[j].h = Feature[i].height * 0.75;
			Feature[i].feature[j].w = Feature[i].width * 0.75;
		}
	}
}
void original()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Box[i].box[j].h = Box[i].height;
			Box[i].box[j].w = Box[i].width;
		}
	}
	for (int i = 0; i < F_N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Feature[i].feature[j].h = Feature[i].height;
			Feature[i].feature[j].w = Feature[i].width;
		}
	}
}
void loadbuttons()
{
	int a, b, cnt = 1;

	ifstream file;

	file.open("coordinates.txt");

	while (cnt <= 48 && file >> a)
	{
		b = (cnt - 1) / 4;

		if (cnt % 4 == 1)
			button[b].x1 = a;
		else if (cnt % 4 == 2)
			button[b].y1 = a;
		else if (cnt % 4 == 3)
			button[b].x2 = a;
		else if (cnt % 4 == 0)
			button[b].y2 = a;

		cnt++;
	}
}
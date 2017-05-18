#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
using namespace std;
int collision(int playerx, int playery, int playerw, int playerh,int ballx,int bally,int ballw,int ballh);

const int BallWidth = 10;
const int BallHeight = 10;
int lives = 3;
int score = 0;
class Brick {
public:
	Brick();
	void initBrick(int x, int y, int w, int h);
	void draw();
	bool isDead();
	void killBrick();
	int collision(int ball_x, int ball_y);
private:
	int xCoordinate;
	int yCoordinate;
	int width;
	int height;
	bool Dead;
};

int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2 = NULL;

	//these two variables hold the x and y positions of the player
	//initalize these variables to where you want your player to start
	float player_x = 305;
	float player_y = 430;

	bool reset = false; 

	float ball_x = 240;
	float ball_y = 350;

	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	float ball_dx = -4.0, ball_dy = 4.0;

	//the first slot represents "up", then "down", "left" and "right"
	bool key[4] = { false, false, false, false };

	//don't redraw until an event happens
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	//get the keyboard ready to use
	al_install_keyboard();

	timer = al_create_timer(.02);

	display = al_create_display(660, 480);
	ball = al_create_bitmap(BallWidth, BallHeight);

	player = al_create_bitmap(110, 20);

	font = al_load_ttf_font("OH.ttf", 50, NULL);

	al_set_target_bitmap(player);

	al_clear_to_color(al_map_rgb(0, 255, 0));

	al_set_target_bitmap(ball);

	al_clear_to_color(al_map_rgb(200, 200, 100));


	al_set_target_bitmap(al_get_backbuffer(display));


	event_queue = al_create_event_queue();

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//new! tell the event queue that it should take keyboard events, too 
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);


	//Set Bricks
	Brick b1;
	b1.initBrick(0, 0, 60, 35);

	Brick b2;
	b2.initBrick(60, 0, 60, 35);

	Brick b3;
	b3.initBrick(120, 0, 60, 35);

	Brick b4;
	b4.initBrick(180, 0, 60, 35);


	Brick b5;
	b5.initBrick(240, 0, 60, 35);

	Brick b6;
	b6.initBrick(300, 0, 60, 35);

	Brick b7;
	b7.initBrick(360, 0, 60, 35);

	Brick b8;
	b8.initBrick(420, 0, 60, 35);

	Brick b9;
	b9.initBrick(480, 0, 60, 35);

	Brick b10;
	b10.initBrick(540, 0, 60, 35);
	Brick b11;
	b11.initBrick(600, 0, 60, 35);
	Brick b12;
	b12.initBrick(0, 35, 60, 35);
	Brick b13;
	b13.initBrick(60, 35, 60, 35);
	Brick b14;
	b14.initBrick(120, 35, 60, 35);
	Brick b15;
	b15.initBrick(180, 35, 60, 35);
	Brick b16;
	b16.initBrick(240, 35, 60, 35);
	Brick b17;
	b17.initBrick(300, 35, 60, 35);
	Brick b18;
	b18.initBrick(360, 35, 60, 35);
	Brick b19;
	b19.initBrick(420, 35, 60, 35);
	Brick b20;
	b20.initBrick(480, 35, 60, 35);
	Brick b21;
	b21.initBrick(540, 35, 60, 35);
	Brick b22;
	b22.initBrick(600, 35, 60, 35);
	Brick b23;
	b23.initBrick(0, 70, 60, 35);
	Brick b24;
	b24.initBrick(60, 70, 60, 35);
	Brick b25;
	b25.initBrick(120, 70, 60, 35);
	Brick b26;
	b26.initBrick(180, 70, 60, 35);
	Brick b27;
	b27.initBrick(240, 70, 60, 35);
	Brick b28;
	b28.initBrick(300, 70, 60, 35);
	Brick b29;
	b29.initBrick(360, 70, 60, 35);
	Brick b30;
	b30.initBrick(420, 70, 60, 35);
	Brick b31;
	b31.initBrick(480, 70, 60, 35);
	Brick b32;
	b32.initBrick(540, 70, 60, 35);
	Brick b33;
	b33.initBrick(600, 70, 60, 35);
	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit)
	{
		if (reset == true) {
			al_stop_timer(timer);
			al_rest(1);
			reset = false;

			al_start_timer(timer);

		
		}

		cout << player_x << " , " << player_y << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			

			if (ball_x < 0 || ball_x > 660-10 ) {
				//flip the x direction
				ball_dx = -ball_dx;
			}

			
			//if the box hits the top wall OR the bottom wall
			if (ball_y < 0 || ball_y > 480 - 10) {
				//flip the y direction
				ball_dy = -ball_dy;
			}
			

			//really important code!
			//move the box in a diagonal
			ball_x -= ball_dx;
			ball_y += ball_dy;



			
			
			//if an event happened, you better redraw

			//if the up button is pressed AND we're still below the top wall,
			//move the box "up" by 4 pixels
			if (key[0] && player_y >= 0) {
				player_y -= 3.0;
			}


			//if the down button is pressed AND we're still above the bottom wall
			//move the box "down" by 4 pixels
			if (key[1] && player_y <= 480 - 32) {
				player_y += 4.0;
			}

			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[2] && player_x >= 0) {
				player_x -= 4.0;
			}

			//if the left button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[3] && player_x <= 660 -110) {
				player_x += 3.0;
			}
			if (collision(ball_x, ball_y, 10, 10, player_x, player_y, 110, 20) == 1) {
				ball_dy = -ball_dy;
			
			}

			
			//redraw at every tick of the timer


			if (ball_x > -3 && ball_x < 660 && ball_y >= 460 && ball_y < 482) {
				ball_x = 350;
				ball_y = 150;
				player_x = 305;
				player_y = 430;
				reset = true;
				lives--;
		
				
				
			}
			
			

			redraw = true;



			if (b1.collision(ball_x, ball_y) && b1.isDead() == false) {
				b1.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score +20 ;
			}

			if (b2.collision(ball_x, ball_y) && b2.isDead() == false) {
				b2.killBrick();
				ball_dy = -ball_dy;
				score = score + 2;
			}

			if (b3.collision(ball_x, ball_y) && b3.isDead() == false) {
				b3.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 5;
			}
			if (b4.collision(ball_x, ball_y) && b4.isDead() == false) {
				b4.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 5;
				
			}
			if (b5.collision(ball_x, ball_y) && b5.isDead() == false) {
				b5.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 5;

			}
			if (b6.collision(ball_x, ball_y) && b6.isDead() == false) {
				b6.killBrick();
				ball_dy = -ball_dy;
				score = score + 7;
			}
			if (b7.collision(ball_x, ball_y) && b7.isDead() == false) {
				b7.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 10;
			}
			if (b8.collision(ball_x, ball_y) && b8.isDead() == false) {
				b8.killBrick();
				ball_dy = -ball_dy;
				ball_dx = ball_dx;
				score = score + 10;
			}
			if (b9.collision(ball_x, ball_y) && b9.isDead() == false) {
				b9.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 1;
			}
			if (b10.collision(ball_x, ball_y) && b10.isDead() == false) {
				b10.killBrick();
				ball_dy = -ball_dy;
				score = score + 5;
			}
			if (b11.collision(ball_x, ball_y) && b11.isDead() == false) {
				b11.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 100;
			}
			if (b12.collision(ball_x, ball_y) && b12.isDead() == false) {
				b12.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 20;
			}
			if (b13.collision(ball_x, ball_y) && b13.isDead() == false) {
				b13.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score +5;
			}
			if (b14.collision(ball_x, ball_y) && b14.isDead() == false) {
				b14.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b15.collision(ball_x, ball_y) && b15.isDead() == false) {
				b15.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 7;
			}
			if (b16.collision(ball_x, ball_y) && b16.isDead() == false) {
				b16.killBrick();
				ball_dy = -ball_dy;
				score = score + 7;
			}
			if (b17.collision(ball_x, ball_y) && b17.isDead() == false) {
				b17.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 7;
			}
			if (b18.collision(ball_x, ball_y) && b18.isDead() == false) {
				b18.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b19.collision(ball_x, ball_y) && b19.isDead() == false) {
				b19.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 5;
			}
			if (b20.collision(ball_x, ball_y) && b20.isDead() == false) {
				b20.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 10;
			}
			if (b21.collision(ball_x, ball_y) && b21.isDead() == false) {
				b21.killBrick();
				ball_dy = -ball_dy;
				score = score + 2;
				
			}
			if (b22.collision(ball_x, ball_y) && b22.isDead() == false) {
				b22.killBrick();
				
				ball_dx = -ball_dx;
				score = score + 10;
			}
			if (b23.collision(ball_x, ball_y) && b23.isDead() == false) {
				b23.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 1;
			}
			if (b24.collision(ball_x, ball_y) && b24.isDead() == false) {
				b24.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b25.collision(ball_x, ball_y) && b25.isDead() == false) {
				b25.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 7;
			}
			if (b26.collision(ball_x, ball_y) && b26.isDead() == false) {
				b26.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b27.collision(ball_x, ball_y) && b27.isDead() == false) {
				b27.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 10;
			}
			if (b28.collision(ball_x, ball_y) && b28.isDead() == false) {
				b28.killBrick();
				ball_dy = -ball_dy;
				score = score + 3;
			}
			if (b29.collision(ball_x, ball_y) && b29.isDead() == false) {
				b29.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 5;
			}
			if (b30.collision(ball_x, ball_y) && b30.isDead() == false) {
				b30.killBrick();
				ball_dy = -ball_dy;
				score = score + 5;
			}
			if (b31.collision(ball_x, ball_y) && b31.isDead() == false) {
				b31.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 10;
			}
			if (b32.collision(ball_x, ball_y) && b32.isDead() == false) {
				b32.killBrick();
				ball_dy = -ball_dy;
				score = score + 5;
			}
			if (b33.collision(ball_x, ball_y) && b33.isDead() == false) {
				b33.killBrick();
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				score = score + 10;
			}



			
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the algorithm that turns key presses into events
		//a "key down" event is when a key is pushed
		//while a "key up" event is when a key is released

		//has something been pressed on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			//"keycode" holds all the different keys on the keyboard
			switch (ev.keyboard.keycode) {

				//if the up key has been pressed

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[2] = true;
				break;
				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[3] = true;
				break;
			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[2] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[3] = false;
				break;
				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}


		//RENDER SECTION
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old player dissapears
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (lives <= 0) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 255, 255), 330, 200, ALLEGRO_ALIGN_CENTRE, "Game Over NOOB!");
				
				al_flip_display();
				al_rest(1);
				return 0;
			}
			

			//Draw Bricks
			if (b1.isDead() == false)
				b1.draw();
			if (b2.isDead() == false)
				b2.draw();
			if (b3.isDead() == false)
				b3.draw();
			if (b4.isDead() == false)
				b4.draw();
			if (b5.isDead() == false)
				b5.draw();
			if (b6.isDead() == false)
				b6.draw();
			if (b7.isDead() == false)
				b7.draw();
			if (b8.isDead() == false)
				b8.draw();
			if (b9.isDead() == false)
				b9.draw();
			if (b10.isDead() == false)
				b10.draw();
			if (b11.isDead() == false)
				b11.draw();
			if (b12.isDead() == false)
				b12.draw();
			if (b13.isDead() == false)
				b13.draw();
			if (b14.isDead() == false)
				b14.draw();
			if (b15.isDead() == false)
				b15.draw();
			if (b16.isDead() == false)
				b16.draw();
			if (b17.isDead() == false)
				b17.draw();
			if (b18.isDead() == false)
				b18.draw();
			if (b19.isDead() == false)
				b19.draw();
			if (b20.isDead() == false)
				b20.draw();
			if (b21.isDead() == false)
				b21.draw();
			if (b22.isDead() == false)
				b22.draw();
			if (b23.isDead() == false)
				b23.draw();
			if (b24.isDead() == false)
				b24.draw();
			if (b25.isDead() == false)
				b25.draw();
			if (b26.isDead() == false)
				b26.draw();
			if (b27.isDead() == false)
				b27.draw();
			if (b28.isDead() == false)
				b28.draw();
			if (b29.isDead() == false)
				b29.draw();
			if (b30.isDead() == false)
				b30.draw();
			if (b31.isDead() == false)
				b31.draw();
			if (b32.isDead() == false)
				b32.draw();
			if (b33.isDead() == false)
				b33.draw();
			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			al_draw_textf(font, al_map_rgb(255, 255, 255), 330, 300, ALLEGRO_ALIGN_CENTRE, "lives = %i", lives);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 330, 400, ALLEGRO_ALIGN_CENTRE, "score = %i", score);
			al_draw_bitmap(player, player_x, player_y, 0);
			al_draw_bitmap(ball, ball_x, ball_y, 0);
			al_flip_display();
		}
	}
	al_destroy_bitmap(ball);
	al_destroy_bitmap(player);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

int collision(int playerx, int playery, int playerw, int playerh, int ballx, int bally, int ballw, int ballh) {
	//if ball is to left of paddle
	if ((playerx + playerw<ballx) ||
		//if ball is above paddle
		(playery + playerh<bally) ||
		//if ball is below paddle
		(playery >bally + ballh) ||
		//if ball is to right of paddle
		(playerx>ballx + ballw))
		return 0;
	else
		return 1;
}

Brick::Brick() {
	xCoordinate = 0;
	yCoordinate = 0;
	width = 0;
	height = 0;
	Dead = 0;

}

void Brick::initBrick(int x, int y, int w, int h) {
	xCoordinate = x;
	yCoordinate = y;
	width = w;
	height = h;
	Dead = 0;

}
int Brick::collision(int ball_x, int ball_y) {
	if ((xCoordinate > ball_x + BallWidth) || //ball is to the left
		(xCoordinate + width < ball_x) || //ball is to the right
		(yCoordinate > ball_y + BallHeight) || //ball is above

		(yCoordinate + height < ball_y)) //ball is below
	{
		return 0;
	}
	else
		cout << "collide!" << endl;
	return 1;
}


void Brick::draw() {
	al_draw_rectangle(xCoordinate, yCoordinate, xCoordinate + width, yCoordinate + height, al_map_rgb(56, 20, 152), 5);
}

bool Brick::isDead() {
	return Dead;
}

void Brick::killBrick() {
	Dead = true;

}
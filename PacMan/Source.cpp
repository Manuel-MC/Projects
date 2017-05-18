#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
using namespace std;

//global constants
const int RIGHT = 3;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 4;

int lives = 3;
/* Directions
1 = left
2 = up
3 = right
4 = down*/

const int PACSIZE = 22;

class Ghost {
public:
	Ghost();
	void initGhost(int x, int y, int w, int h);
	void draw();
	bool GetPac(int pacman_x, int pacman_y);
	void killGhost();
	int collision(int pacman_x, int pacman_y);
	void chase(int x, int y, int field[20][20]);
	void chase1(int x, int y, int field[20][20]);
	void chase3(int x, int y, int field[20][20]);
	void chase4(int x, int y, int field[20][20]);
	int setPosition(int x, int y);
private:
	int xCoordinate;
	int yCoordinate;
	int width;
	int height;
	bool Dead;
	int direction;
};
int main()
{
	int width = 640;
	int height = 480;
	bool doexit = false;
	bool key[4] = { false, false, false, false };
	int x = width / 2;
	int y = height / 2;
	bool redraw = false;

	//sprite variables////////////////////////////////////////////
	const int maxFrame = 5;     //how many pictures in your bitmap
	int curFrame = 0; //starting point
	int frameCount = 0; //what number frame you're on
	int frameDelay = 5; //speed up or slow down feet 
	int frameWidth = 33;
	int frameHeight = 30;
	///////////////////////////////////////////////////////////////

	ALLEGRO_FONT *font = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	ALLEGRO_BITMAP *WalkForward; //you need one per direction

	int wallCollide(int x, int y, int dir, int level[20][20]);



	int map[20][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,
		1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,
		1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,1,
		1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,
		0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,
		1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,
		1,0,0,0,0,1,1,0,0,0,0,0,1,0,1,0,0,0,0,1,
		1,0,1,1,0,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,
		1,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,
		1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,1,
		1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,
		1,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,1,
		1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,
		1,0,1,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,0,1,
		1,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};




	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
			cout << map[i][j];

		cout << endl;

	}




	//these two variables hold the x and y positions of the pacman
	//initalize these variables to where you want your pacman to start
	int pacman_x = 45;
	int pacman_y = 45;

	int wallCollide(int x, int y, int dir, int level[20][20]);







	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	al_init_image_addon();
	al_init_primitives_addon();
	display = al_create_display(width, height);


	//get the keyboard ready to use
	al_install_keyboard();

	timer = al_create_timer(.02);

	display = al_create_display(800, 1000);
	font = al_load_ttf_font("OH.ttf", 50, NULL);
	pacman = al_create_bitmap(22, 22);

	al_set_target_bitmap(pacman);

	al_clear_to_color(al_map_rgb(255, 255, 0));


	wall = al_create_bitmap(40, 40);
	dot = al_create_bitmap(5, 5);
	al_set_target_bitmap(wall);

	al_clear_to_color(al_map_rgb(55, 255, 0));
	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(55, 255, 0));
	al_set_target_bitmap(al_get_backbuffer(display));

	//load sprite, set transparency////////////////////////////////////////////
	WalkForward = al_load_bitmap("pacman.png");
	al_convert_mask_to_alpha(WalkForward, al_map_rgb(255, 255, 255));
	/////////////////////////////////////////////////////////////////////////

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//new! tell the event queue that it should take keyboard events, too 
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);


	Ghost blue;
	blue.initGhost(449, 445, 30, 30);

	Ghost red;
	red.initGhost(449, 445, 30, 30);

	Ghost yellow;
	yellow.initGhost(449, 445, 30, 30);

	Ghost purple;
	purple.initGhost(449, 445, 30, 30);

	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit)
	{

		cout << pacman_x << " , " << pacman_y << endl;


		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//if the up button is pressed AND we're still below the top wall,
			//move the box "up" by 4 pixels
			if (key[0] && wallCollide(pacman_x, pacman_y, UP, map) == 0) {
				pacman_y -= 4.0;
			}

			//if the down button is pressed AND we're still above the bottom wall
			//move the box "down" by 4 pixels
			if (key[1] && wallCollide(pacman_x, pacman_y, DOWN, map) == 0) {
				pacman_y += 4.0;
			}
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[2] && wallCollide(pacman_x, pacman_y, LEFT, map) == 0) {
				pacman_x -= 4.0;
			}

			//if the right button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[3] && wallCollide(pacman_x, pacman_y, RIGHT, map) == 0) {
				pacman_x += 4.0;
			}
			if (map[(pacman_y + 20) / 40][(pacman_x + 20) / 40] == 0) {
				map[(pacman_y + 20) / 40][(pacman_x + 20) / 40] = 4; //4s 

			}
			//redraw at every tick of the timer

			if (pacman_x > 774 && pacman_x < 779 && pacman_y >= 240 && pacman_y < 320) {
				pacman_x = 5;
				pacman_y = 289;

			}

			if (pacman_x > -48 && pacman_x < -24 && pacman_y >= 247 && pacman_y < 320) {
				pacman_x = 765;
				pacman_y = 289;

			}


			blue.chase(pacman_x, pacman_y, map);

			red.chase1(pacman_x, pacman_y, map);
			yellow.chase3(pacman_x, pacman_y, map);
			purple.chase4(pacman_x, pacman_y, map);

			if (blue.GetPac(pacman_x, pacman_y) == 1) {
				pacman_x = 45;
				pacman_y = 45;
				lives--;
				blue.setPosition;
			}

			redraw = true;
			if (red.GetPac(pacman_x, pacman_y) == 1) {
				pacman_x = 45;
				pacman_y = 45;
				lives--;
			}

			redraw = true;
			if (yellow.GetPac(pacman_x, pacman_y) == 1) {
				pacman_x = 45;
				pacman_y = 45;
				lives--;
			}

			redraw = true;
			if (purple.GetPac(pacman_x, pacman_y) == 1) {
				pacman_x = 45;
				pacman_y = 45;
				lives--;
			}

			//move sprite////////////////////////////////////////////////
			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
					curFrame = 0;

				frameCount = 0; //reset frame timer
			}

			if (x <= 0 - frameWidth)
				x = width;
			///////////////////////////////////////////////////////////////

			redraw = true;

		}


		//////////////////////////////////////////////////////////
		/////////////////////////////////////////////
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
			case ALLEGRO_KEY_UP:
				key[0] = true;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_DOWN:
				key[1] = true;
				break;

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
			case ALLEGRO_KEY_UP:
				key[0] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[1] = false;
				break;

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


			al_clear_to_color(al_map_rgb(0, 0, 0));

			//////////////draw bitmap REGION///////////////////////////////////
			al_draw_bitmap_region(WalkForward, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);
			//////////////////////////////////////////////////////////////////

			//paint black over the old screen, so the old pacman dissapears




			if (lives <= 0) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTRE, "Game Over NOOB!");
				al_flip_display();
				al_rest(1);
				return 0;
			}
			al_draw_textf(font, al_map_rgb(0, 0, 255), 400, 800, ALLEGRO_ALIGN_CENTRE, "lives = %i", lives);
			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			//al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (map[i][j] == 1)

						al_draw_bitmap(wall, j * 40, i * 40, NULL);

					if (map[i][j] == 0)

						al_draw_bitmap(dot, j * 40 + 20, i * 40 + 20, NULL);

				}

			blue.draw();

			red.draw();

			yellow.draw();

			purple.draw();



			al_flip_display();


		}
	}



	al_destroy_bitmap(pacman);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}
int Ghost::setPosition(int x, int y){
	xCoordinate = x;
	yCoordinate = y;
}
int wallCollide(int x, int y, int dir, int level[20][20]) {

	int new_x1, new_x2, new_x3, new_y1, new_y2, new_y3;


	if (dir == RIGHT) {         // Moving Right
								//	cout << "right branch" << endl;			// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_x1 = x + 1 + PACSIZE;
		new_x2 = x + 1 + PACSIZE;
		new_x3 = x + 1 + PACSIZE;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;


		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {

			return 1;
		}
	}

	else if (dir == LEFT) {         // Moving Right
								//	cout << "right branch" << endl;			// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_x1 = x - 24 + PACSIZE;
		new_x2 = x - 24 + PACSIZE;
		new_x3 = x - 24 + PACSIZE;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;


		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {

			return 1;
		}
	}
	else if (dir == DOWN) {         // Moving Right
									//	cout << "right branch" << endl;			// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_y1 = y + 1 + PACSIZE;
		new_y2 = y + 1 + PACSIZE;
		new_y3 = y + 1 + PACSIZE;
		// Check at three point along that edge
		new_x1 = x;
		new_x2 = x + PACSIZE / 2;
		new_x3 = x + PACSIZE;


		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {

			return 1;
		}
	}
	else if (dir == UP) {         // Moving Right
									//	cout << "right branch" << endl;			// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_y1 = y - 24 + PACSIZE;
		new_y2 = y - 24 + PACSIZE;
		new_y3 = y - 24 + PACSIZE;
		// Check at three point along that edge
		new_x1 = x;
		new_x2 = x + PACSIZE / 2;
		new_x3 = x + PACSIZE;


		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {

			return 1;
		}
	}

	return 0; //no collision
}//end function wall colide
Ghost::Ghost() {

}
void Ghost::initGhost(int x, int y, int w, int h) {
	xCoordinate = x;
	yCoordinate = y;
	width = w;
	height = h;
	Dead = 0;
	direction = LEFT;




}
void Ghost::draw() {
	al_draw_filled_rectangle(xCoordinate, yCoordinate, xCoordinate + width, yCoordinate + height, al_map_rgb(56, 20, 152));
}

bool Ghost::GetPac(int pacman_x, int pacman_y) {
	if ((xCoordinate + 30 > pacman_x&& xCoordinate < pacman_x + 30) &&
		(yCoordinate + 30 > pacman_y&&yCoordinate < pacman_y + 30)) {
		return 1;
	}
	else return 0;

}

void Ghost::killGhost() {
	Dead = true;

}

//chase function. x and y are pacman's position.
void Ghost::chase(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	/*  cout << "state is " << direction << endl;
	if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl;*/

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 4;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 4;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 2;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 2;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 2;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}
//chase function. x and y are pacman's position.
void Ghost::chase1(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	/*  cout << "state is " << direction << endl;
	if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl;*/

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 7, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 6;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 7, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 6;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 6;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 8;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 8;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 4;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 4;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 4;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}
//chase function. x and y are pacman's position.
void Ghost::chase3(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	/*  cout << "state is " << direction << endl;
	if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl;*/

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 9;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 9;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 9;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 9;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 9;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 9;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 9;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 9;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 9;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 9;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 9;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}


void Ghost::chase4(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	/*  cout << "state is " << direction << endl;
	if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl;*/

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 9;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 2;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 2;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 1;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 1;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 1;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 1;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 1;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT; 
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}



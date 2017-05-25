#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
const double CLOCK = .10;
int main() {
	cout << ".1" << endl;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
	ALLEGRO_BITMAP *snek = NULL;
	vector<int>nodes;
	vector<int>::const_iterator iter;

	int goal_y = 5;
	int goal_x = 5;
	int SnekLength = 0;
	bool gotGoal = false;
	int head_y = 8;
	int head_x = 8;
	bool doexit = false;
	bool redraw = true;
	int SNEKSIZE = 40;

	bool key[4] = { false, false, false, false };
	//Libraries
	al_init();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_reserve_samples(2);
	sample = al_load_sample("music.wav");
	//al_play_sample(sample, 1.00, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	//create game items
	timer = al_create_timer(CLOCK);
	display = al_create_display(800, 800);

	//snek = al_create_bitmap(30, 30);

	//al_set_target_bitmap(snek);

	//al_clear_to_color(al_map_rgb(70, 70, 240));
	int grid[20][20];
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			grid[i][j] = 0;

	grid[goal_x][goal_y] = 2; //setfirst goal point to 2,2

	srand(time(NULL));
	//cout << ".2" << endl;
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	al_reserve_samples(10);

	ALLEGRO_FONT *font = al_load_ttf_font("Mermaid Swash Caps.ttf", 28, 0);
	if (font == NULL)
		cout << "font is null" << endl;
	//set up event queue items for event queue to catch//
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//Start the game
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);
	//cout << ".3" << endl;
	//al_play_sample_instance(instance1);

	while (!doexit) { //game loop
					  //cout << "begin game loop" << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//cout << ".4" << endl;
		//draw map to console
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//cout << ".45" << endl;
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					if (grid[i][j] == 1)
						grid[i][j] = 0;
					//return 1;
				}

			//draw tail
			//cout << ".46" << endl;
			for (int i = 0; i < SnekLength; i += 2) {
				grid[nodes[i]][nodes[i + 1]] = 1;
				//cout<< "snek tail is at " << nodes[i] << "," << nuodes[i+1 <<
				//endl;
			}
			//cout << ".5" << endl;
			// cout << "SnekLength is " << SnekLength << endl;
			// check if  goal has been reached, set new goal true
			if (gotGoal == true) {
				//erase old goal
				grid[goal_x][goal_y] = 0;

				// generate new goal
				goal_x = rand() % 20;
				goal_y = rand() % 20;
				grid[goal_x][goal_y] = 2;
				gotGoal = false;
				//cout << "goal is at " << goal_x << " , " << goal_y << endl;
			}


			if (key[0] && head_y > -1) {
				head_y -= 1;
			}
			if (key[1] && head_y < 21) {
				cout << "trying to move down" << endl;
				head_y += 1;
			}
			if (key[2] && head_x > -1) {
				head_x -= 1;
			}
			if (key[3] && head_x > -1) {
				head_x += 1;
			}
			cout << "1" << endl;
			//Check if player got goal

			if (grid[goal_x] == grid[head_x] && grid[goal_y] == grid[head_y]) {
				gotGoal = true;
				//Beep(200, 200);
				cout << "chomp!" << endl;
				SnekLength += 2;
			}




			if (head_x > 0 &&
				head_y > 0 &&
				head_x < 20 &&
				head_y < 20) {
				grid[head_x][head_y] = 1;
			}

			cout << "snek is at " << head_x << " , " << head_y << endl;

			//put previous coordinates in vector
			nodes.insert(nodes.begin(), head_y);
			nodes.insert(nodes.begin(), head_x);

			if (head_x < 0 || head_y < 0)
				cout << "MATRIX ERROR" << endl;
			cout << "2" << endl;



			//kill snek if it hist wall
			if (head_x < 0 || head_x <= 20 || head_y < 0 || head_y >= 20) {
				cout << "hit a wall- snek is ded!" << endl;
				cout << "head was at " << head_x << " , " << head_y << endl;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(font, al_map_rgb(250, 100, 0), 0, 300, 300, NULL, "snek is dead.");
				al_flip_display();
				al_rest(2);
				cout << "2.5" << endl;
			}
			//check if you've bumped into your tail
			if (SnekLength > 2) {
				for (iter = nodes.begin() + 2; iter < nodes.end(); iter += 2) {
					cout << "head is " << head_x << " , " << head_y << endl;
					cout << "node values are " << *iter << " , " << *(iter + 1) << endl;

					if ((head_x == *iter && head_y == *(iter + 1))) {
						cout << "you bumped into tail, snek is ded!" << endl;
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font, al_map_rgb(250, 100, 0), 300, 300, NULL, "snek is ded.");
						al_flip_display();
						al_rest(2);
						return 0;
					}
				}
			}

			// cull old vector slots so it doesn't get to long
			nodes.erase(nodes.begin() + SnekLength, nodes.end());
			//cout << "3" << endl;
			redraw = true;
		}


		/////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//////////////////////////////////////////////////////
		// here's the algorithm that turns key presses into events
		// while a "key up" event iswhen a key is released

		// has something been pressed on the keyboard ?
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
				key[1] = false;
				key[2] = false;
				key[3] = false;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_DOWN:
				key[0] = false;
				key[1] = true;
				key[2] = false;
				key[3] = false;
				break;

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[0] = false;
				key[1] = false;
				key[2] = true;
				key[3] = false;
				break;

				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[0] = false;
				key[1] = false;
				key[2] = false;
				key[3] = true;
				break;
			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				//	key[0] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				//key[1] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				//	key[2] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				//key[3] = false;
				break;

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			}
		}
		//cout << "trying render section..." << endl;
		// Render Section
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			//cout << "4" << endl;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (gotGoal == false)
				grid[goal_x][goal_y] = 2;

			//draw map
			//cout<<"snek is at " << head_x << " , " << head_y << endl;
			//cout<<"grid at snek is " << grid[head_x][head_y] << endl;

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 20; j++) {
					//cout << "loops" << endl;
					if (grid[i][j] == 1) {
						//draw snek 
						//cout << "draw snek" << endl;
						al_draw_filled_rectangle(i*SNEKSIZE, j*SNEKSIZE, i*SNEKSIZE + SNEKSIZE, j*SNEKSIZE + SNEKSIZE,
							al_map_rgb(50, 250, 50));
					}
					if (grid[i][j] == 0) {
						//draw 
						//cout << " drawing background" << endl;
						al_draw_filled_rectangle(i*SNEKSIZE, j*SNEKSIZE, i*SNEKSIZE + SNEKSIZE, j*SNEKSIZE + SNEKSIZE,
							al_map_rgb(150, 250, 150));
					}
					if (grid[i][j] == 2) {
						//draw 
						//cout << "drawing fuds" << endl;
						al_draw_filled_rectangle(i*SNEKSIZE, j*SNEKSIZE, i*SNEKSIZE + SNEKSIZE, j*SNEKSIZE + SNEKSIZE,
							al_map_rgb(50, 50, 150));
					}

				}
			//cout << "shoe" << endl;
			//wipe off old goal if snek has eaten it
			if (gotGoal == true)
				grid[goal_x][goal_y] = 0;

			al_flip_display();
		}// end render






	}//While Loop
	 //al_destroy_sample_instance(instance1);
	al_destroy_sample(sample);
	al_destroy_bitmap(snek);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}// Main  
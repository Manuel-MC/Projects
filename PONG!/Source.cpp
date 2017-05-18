#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <Windows.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_ttf.h>


using namespace std;

int collision(int playerx, int playery, int playerw, int playerh, int player2x, int player2y, int player2w, int player2h);

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player = NULL;
	ALLEGRO_BITMAP *player2 = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_BITMAP *ball1 = NULL;
	ALLEGRO_SAMPLE *sample3 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance3 = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance2= NULL; 
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_SAMPLE *sample4 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance4 = NULL;
	//these two variables hold the x and y positions of the player
	//initalize these variables to where you want your player to start

	float ball_x = 300;
	float ball_y = 300;

	float player_x = 625;
	float player_y = 50;

	float player2_x = 10;
	float player2_y = 50;

	int score = 0;
	int score2 = 0;
	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	//don't redraw until an event happens
	float ball_dx = -4.0, ball_dy = 4.0;
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_reserve_samples(10);
	al_init_ttf_addon();
	//set the timer so it "ticks" at 2 milliseconds
	timer = al_create_timer(.02);

	display = al_create_display(640, 480);
	
	//create a little 32x32 square

	ball = al_create_bitmap(42, 42);
	ball1 = al_load_bitmap("Skrt_42x42.png");
	al_convert_mask_to_alpha(ball1, al_map_rgb(255, 0, 255)); //this assumes the background is bright pink!

	//use this to *draw* your own bitmaps (instead of loading them from a file)
	//before we used al_load_bitmap()
	al_set_target_bitmap(ball);

	//set the color of your bitmap
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	//register the timer as an event source so it can generate events
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	//GUESS WHAT THIS DOES
	al_start_timer(timer);

	//get the keyboard ready to use
	al_install_keyboard();

	font = al_load_ttf_font("Earth 2073.ttf", 50, NULL);

	timer = al_create_timer(.02);

	

	player = al_create_bitmap(6, 100);
	player2 = al_create_bitmap(6, 100);

	al_set_target_bitmap(player);

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(player2);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(al_get_backbuffer(display));
	
	sample3 = al_load_sample("lolo.wav");

	instance3 = al_create_sample_instance(sample3);

	sample2 = al_load_sample("quick.wav");

	instance2 = al_create_sample_instance(sample2);


	sample4 = al_load_sample("airwolf.wav");

	instance4 = al_create_sample_instance(sample4);

	al_set_sample_instance_playmode(instance4, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance4, al_get_default_mixer());

	al_play_sample_instance(instance4);
	//al_set_sample_instance_playmode(instance3, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance3, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
	
	event_queue = al_create_event_queue();

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//new! tell the event queue that it should take keyboard events, too 
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);



	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit)
	{
		cout << player_x << " , " << player_y << endl;
		ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_TIMER) {


				//if the box hits the left wall OR the right wall
				if (ball_x < 0){
					ball_dx = -ball_dx;
				score++;
			}
				if 	(ball_x > 640 - 32) {
					//flip the x direction
					ball_dx = -ball_dx;
					score2++;
				}
				//if the box hits the top wall OR the bottom wall
				if (ball_y < 0 || ball_y > 480 - 32) {
					//flip the y direction
					ball_dy = -ball_dy;
				}

				

			
				//if the up button is pressed AND we're still below the top wall,
				//move the box "up" by 4 pixels
				if (key[0] && player_y >= 0) {
					player_y -= 4.0;
				}
				if (key2[0] && player2_y >= 0) {
					player2_y -= 4.0;
				}

				//if the down button is pressed AND we're still above the bottom wall
				//move the box "down" by 4 pixels
				if (key[1] && player_y <= 480 - 42) {
					player_y += 4.0;
				}
				if (key2[1] && player2_y <= 480 - 42) {
					player2_y += 4.0;
				}

				if (ball_y > player_y ) {
					player_y += 4.0;

				}
				if (ball_y < player_y) {
					player_y -= 4.0;
				}
				//really important code!
				//move the box in a diagonal
				ball_x += ball_dx;
				ball_y += ball_dy;

				if (collision(ball_x, ball_y, 42, 42, player_x, player_y, 6, 100) == 1) {
					ball_dx = -ball_dx;
					al_play_sample_instance(instance3);
					

				}
				if (collision(ball_x, ball_y, 42, 42, player2_x, player2_y, 6, 100) == 1) {
					ball_dx *= -1;
					al_play_sample_instance(instance2);
				}
				
				
				redraw = true;
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
				case ALLEGRO_KEY_UP:
					key[0] = true;
					break;
				case ALLEGRO_KEY_W:
					key2[0] = true;
					break;
					//if the down key has been pressed
				case ALLEGRO_KEY_DOWN:
					key[1] = true;
					break;
				case ALLEGRO_KEY_S:
					key2[1] = true;
					break;


				}
			}
			//has something been released on the keyboard?
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[0] = false;
					break;
				case ALLEGRO_KEY_W:
					key2[0] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					key[1] = false;
					break;
				case ALLEGRO_KEY_S:
					key2[1] = false;
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


				
				//the algorithm above just changes the x and y coordinates
				//here's where the bitmap is actually drawn somewhere else
				al_draw_bitmap(player, player_x, player_y, 0);
				al_draw_bitmap(player2, player2_x, player2_y, 0);
				al_draw_bitmap(ball, ball_x, ball_y, 0);
				al_draw_bitmap(ball1, ball_x, ball_y, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 250, 10, ALLEGRO_ALIGN_CENTRE, "BOT = %i", score);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 250, 50, ALLEGRO_ALIGN_CENTRE, "YOU = %i", score2);
				
				al_flip_display();
			}
		}
		al_destroy_bitmap(ball);
		al_destroy_bitmap(player);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(ball1);

		return 0;
	}


	int collision(int playerx, int playery, int playerw, int playerh, int player2x, int player2y, int player2w, int player2h) {
		//if ball is to left of paddle
		if ((playerx + playerw<player2x) ||
			//if ball is above paddle
			(playery + playerh<player2y) ||
			//if ball is below paddle
			(playery >player2y + player2h) ||
			//if ball is to right of paddle
			(playerx>player2x + player2w))
			return 0;
		else
			return 1;
	}
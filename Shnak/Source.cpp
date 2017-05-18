#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

using namespace std;
int main() {
	vector<int>nodes;
	vector<int>::const_iterator iter;

	al_init();
		al_install_keyboard();
	al_install_audio();

		al_init_acodec_addon();
		al_init_primitves_addon();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();

		al_reserve_samples(2);
		sample = al_load_sample("lol.wav");
		al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

			timer = al_create_timer(CLOCK);
		display = al_create_display(800, 800);

		int grid[20][20];
		for (something with i)
			for (something with j)
				grid[i][j] = 0;

		grid[goal_x][goal_y] = 2;
		srand(time(NULL));
		al_set_target_bitmap(al_get_backbuffer(display));
		event_queue = al_create_event_queue();
		al_reserve_samples(10);

		ALLEGRO_FONT*font = al_load_ttf_font("something cool", 28, 0);
		if (font == NULL)
			cout << "font is null" << endl;

		al_register_event_source();
		al_register_event_source();
			al_register_event_source();

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
			al_start_timer(timer);


			//al_play_sample_instance(instsnce1);


			while (true) {
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue, &ev);

				//draw map to console
				//for (int i=0;)i<20;i++){
				//for (int j=0;j<20;j++)
				//cout<<grid[i][j];
				//cout<<endl;
				//}

				if (ev.type == ALLEGRO_EVENT_TIMER) {
					//wipe map
					for (int i = 0; i < 20;i++);
					for (int j = 0;j < 20;j++){
						if (grid[i][j] == 1);
							//something goes here

				}
			//draw shnak tail
					for (int i = 0; i < SnekLength; i = i + 2) {
						grid[nodes[i]][nodes[i + 1]] = 1;
						//cout<<"snek tail is at"<<nodes[i]<<","<<nodes[i+1]<< endl;
					}
					//cout<<"SkenLength is"<< SnekLength <<endl;
					//check if goal has been reached, set new goal is true
					if (gotGoal == true) {
						//erase old goal
						// grid[goal_x][goal_y]=2;
						//generate new point for goal 
						goal_x = rand() % 20;
						goal_y = rand() % 20;
						grid[goal_x][goal_y] = 2;
						gotGoal = false;
						cout << "goal is at" << goal_x << "," << goal_y << endl;
					}

					if (key[0] && head_y > -1) {
						head_y -= 1;
					}
					//something goes here

					}

				//check if player has gotten goal

				if (grid[goal_x] == grid[head_x] && grid[goal_y] == grid[head_y]) {
					gotGoal = true;
					//Beep(200,200);
					SnekLength += 2;
				}
				//shnak head into map
				if (head_x = 0 &&
					head_y = 0 &&
					head_x = 20 &&
					head_y = 20)
					grid[head_x][head_y] = 1;
				//cout<<"shnak is at"<<head_x<<","<<head_y<<endl;
				//put previous coordinates in vector
				nodes.insert(nodes.begin(), head_y);
				nodes.insert(nodes.begin(), head_x);

				if (head_x, 0 || head_y < 0)
					cout << "Matrix Error" << endl;

				//kill shnak if it hits wall

				if (somethign) {
					lol;
					 //check if you've bumbed into your tail
					//if (SnekLength > 2)
					for (iter = nodes.brgin() + 2; iter < nodes.end(); iter += 2) {
						cout << "head is" << head_x << "," << head_y << endl;
						cout << "node values are" << *iter << "," << *(iter + 1) << endl;

						if ((head_x == *iter&&head_y == *(iter + 1))) {
							cout << "you bumped into tail, shnak is ded!" << endl;
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_draw_textf(font, al_map_rgb(250, 100, 0), 300, 300, NULL, "shnak is ded.");
							al_flip_display();
							al_rest(2);
							return 0;
						}
					}
				//}
					//cull old vector slots so it doesn't get too long
					nodes.erase(nodes.begin() + SnekLength, nodes.end());

			}

}
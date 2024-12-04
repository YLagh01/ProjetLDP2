#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <allegro5/color.h>

#include "Brick.hpp"
#include "Plate.hpp"
#include "Ball.hpp"
#include "GameOrchestra.hpp"


#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int    windowWidth      = 560;
const int    windowHeight     = 900;
const double refreshPerSecond = 60;





void keyDown(int keyCode, GameOrchestra &game) {
  // Called when a key is pressed
  // Key codes are here: https://www.allegro.cc/manual/5/keyboard.html
  switch (keyCode) {
    case ALLEGRO_KEY_1:
      /* Code for key 1 pressed */
      break;
    case ALLEGRO_KEY_SPACE:
      /* Code for space pressed */
      break;
    case ALLEGRO_KEY_A:
      game.move_plate(0);
    
    case ALLEGRO_KEY_D:
      game.move_plate(1);

    default: { /* Nothing, normal. */
    }
  }
}

// *****************DONT EDIT BELOW HERE************************

void must_init(bool test, const char* description) {
  if (test) return;

  std::cerr << "couldn't initialize" << description << '\n';
  exit(1);
}

int main(int /* argc */, char** /* argv */) {
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_mouse(), "mouse");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / refreshPerSecond);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

  ALLEGRO_DISPLAY* disp = al_create_display(windowWidth, windowHeight);
  must_init(disp, "display");

  ALLEGRO_FONT* font = al_create_builtin_font();
  must_init(font, "font");

  must_init(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_init_image_addon();



  GameOrchestra game{};

  bool done = false;
  ALLEGRO_EVENT event;


  al_start_timer(timer);
  while (!done) {
    al_wait_for_event(queue, &event);
    switch (event.type) {
      case ALLEGRO_EVENT_KEY_DOWN:
        keyDown(event.keyboard.keycode, game);
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
      case ALLEGRO_EVENT_TIMER:
        al_clear_to_color(al_map_rgb(255, 255, 255));
        game.check_collisions();
        game.move_ball();
        game.draw_ball();
        game.draw_bricks();
        game.draw();
        al_flip_display();
        break;
      default: { /* Nothing, normal */
      }
    }
  }

  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}

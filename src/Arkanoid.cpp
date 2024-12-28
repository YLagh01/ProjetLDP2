#include "Common.hpp"

#include "GameOrchestra.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <cmath>
#include <iostream>

void must_init(const bool test, const char *description) {
    if (test) return;

    std::cerr << "couldn't initialize" << description << '\n';
    exit(1);
}

int main(int /* argc */, char ** /* argv */) {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / TARGET_FRAMERATE);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    must_init(event_queue, "event_queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    must_init(display, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");
    al_init_font_addon();
    al_init_ttf_addon();

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_init_image_addon();

    al_set_display_icon(display, al_load_bitmap("../res/sprites/icon.png"));

    GameOrchestra game{};

    bool running = true;
    ALLEGRO_EVENT event;

    ALLEGRO_MOUSE_STATE current_mouse_state;
    ALLEGRO_MOUSE_STATE previous_mouse_state;

    al_start_timer(timer);
    while (running) {
        al_get_mouse_state(&current_mouse_state);
        al_wait_for_event(event_queue, &event);

        game.input(current_mouse_state, previous_mouse_state, event.type, event.keyboard.keycode);

        previous_mouse_state = current_mouse_state;

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                game.update();
                game.render();
                break;
            default:
                break;
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}

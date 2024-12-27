#include "Main.hpp"

#include "GameOrchestra.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/color.h>

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

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY *disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    must_init(disp, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_init_image_addon();

    GameOrchestra game{};

    bool running = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (running) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN: case ALLEGRO_EVENT_KEY_UP:
                game.input(event.type, event.keyboard.keycode);
                break;
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
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

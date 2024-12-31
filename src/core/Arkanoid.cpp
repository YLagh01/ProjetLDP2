/*
 * INFO-F202 (2024 - 2025)
 * Written with ❤︎ by Yassir Laghmouchi & Nabil El Muhur @ ULB
 */

#include "../Common.hpp"

#include "../core/FontManager.hpp"

#include "../states/GameStateManager.hpp"
#include "../states/PlayState.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <cmath>
#include <iostream>

void must_init(const bool test, const char *description) {
    // Handling Allegro initialisations
    if (test) return;

    std::cerr << "Error: Could not initialize" << description << std::endl;
    exit(1);
}

int main(int /* argc */, char ** /* argv */) {
    // Initialising Allegro modules
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    // Setting up the timer with an arbitrary speed to keep consistent updates
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / TARGET_FRAMERATE);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    must_init(event_queue, "event_queue");

    // Setting useful Allegro settings
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Creating the window display
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    must_init(display, "display");

    // Initialising font utils
    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");
    al_init_font_addon();
    al_init_ttf_addon();

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initialising the addon to load images
    al_init_image_addon();

    // Setting the window icon
    al_set_display_icon(display, al_load_bitmap("../res/sprites/icon.png"));

    // Declaring core game variables
    // The game state manager helps us keep track of the current game state to call core functions (input, update, render) and update it if needed
    GameStateManager game_state_manager;
    SpriteManager    sprite_manager{};
    FontManager      font_manager{};
    // Making the play state the initial state on runtime
    game_state_manager.update_state(std::make_unique<PlayState>(&game_state_manager, sprite_manager));

    bool running = true;
    ALLEGRO_EVENT event;

    // Keeping track of the mouse's state
    ALLEGRO_MOUSE_STATE mouse_state;

    // Starting the timer for consistent updates
    al_start_timer(timer);

    // Main loop
    while (running) {
        al_get_mouse_state(&mouse_state);
        al_wait_for_event(event_queue, &event);

        // Handling mouse and keyboard inputs
        game_state_manager.input(mouse_state, event.type, event.keyboard.keycode);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                // Accounting for game updates
                game_state_manager.update();
            // Drawing elements to the screen
                game_state_manager.render(font_manager);
                break;
            default:
                break;
        }
    }

    // Cleaning up ALlegro modules
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}

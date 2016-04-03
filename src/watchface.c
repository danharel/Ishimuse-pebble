#include <pebble.h>

#define DELTA 20
#define STR_LEN 10

static Window *s_main_window;
static Layer *s_root_layer;
static TextLayer *s_happiness;

static int num;
static char num_str[STR_LEN];

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    num++;
    for (int i = STR_LEN - 1; i >= 0; i--) {
        if (num_str[i] == 9) {
            num_str[i] = '0';
        }
        else {
            num_str[i]++;
            break;
        }
    }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    num--;
    for (int i = STR_LEN - 1; i >= 0; i--) {
        if (num_str[i] == 0) {
            num_str[i] = '9';
        }
        else {
            num_str[i]--;
            break;
        }
    }
}

static void click_config_provider(ClickRecognizerRef recognizer, void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler)up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler)down_click_handler);
}

void init() {
    // Init window
    s_main_window = window_create();
    window_stack_push(s_main_window, true);
    window_set_background_color(s_main_window, GColorBlack);

    s_root_layer = window_get_root_layer(s_main_window);

    // Init happiness text layer
    text_layer_create(GRect(0, 18, 144, 50));
    text_layer_set_text_color(s_happiness, GColorWhite);

    //layer_add_child(s_root_layer, text_layer_get_layer(s_happiness));

    // Subscribe click provider function
    //window_set_click_config_provider(s_main_window, (ClickConfigProvider) click_config_provider);

    for (int i = 0; i < STR_LEN; i++) {
        num_str[i] = '0';
    }
}

void deinit() {
    window_destroy(s_main_window);
}

int main() {
    init();
    app_event_loop();
    deinit();
}
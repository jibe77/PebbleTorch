#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x92, 0x2A, 0x30, 0x35, 0xCB, 0x12, 0x46, 0xE1, 0x97, 0xEC, 0x3A, 0xD0, 0x92, 0x93, 0x51, 0xA8 }
PBL_APP_INFO(MY_UUID,
             "Torch", "KtoG",
             1, 1, /* App version */
             //DEFAULT_MENU_ICON,
			 RESOURCE_ID_TORCH_ICON,
             APP_INFO_STANDARD_APP);

Window window;

TextLayer textLayer;

// the light is displayed during around 2,5 seconds by default and it's not possible 
// to turn it on longer, then a timer has to switch it on every 2,5 seconds.
const int REFRESH_LIGHT_TIMEOUT = 3000; 

// Using this is a workaround as there's currently no other way to
// allocate storage for a bitmap--but the extra automatically created
// layer is useful for getting dimension information anyway.
BmpContainer image;

void handle_init(AppContextRef ctx) {

  // makes sure the light is enabled at the beginning of the app
  light_enable_interaction();
	
  window_init(&window, "Torch");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorWhite);
  // window_set_fullscreen(&window, true); // removes the clock displayed on the top of the screen.
	
  text_layer_init(&textLayer, window.layer.frame);
  text_layer_set_text(&textLayer, "Backlight is ON as long as this screen is displayed.");
  text_layer_set_font(&textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(&textLayer, GTextAlignmentCenter);
  layer_add_child(&window.layer, &textLayer.layer);
  // TODO : set text in thé midole of thé screen
	
  app_timer_send_event(ctx, REFRESH_LIGHT_TIMEOUT /* milliseconds */, 0 /* Not using a cookie value */);
}

void handle_deinit(AppContextRef ctx) {
  //bmp_deinit_container(&image);
}

// Modify these common button handlers
void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    
}

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	
}

void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
    
}
// This usually won't need to be modified

void click_config_provider(ClickConfig **config, Window *window) {
    
    config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;
    
    config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;
    
    config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
    config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;
    
    config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
	
}

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {	
	light_enable_interaction();
	app_timer_send_event(ctx, REFRESH_LIGHT_TIMEOUT /* milliseconds */, cookie /* Not using a cookie value */);
}

void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &handle_init,
		.deinit_handler = &handle_deinit,
		.timer_handler = &handle_timer // The handle_thimer fucntion manages the timer events
	};
    // Launch évents manager
	app_event_loop(params, &handlers);

	// Attach our desired button functionality
    window_set_click_config_provider(&window, 
  		(ClickConfigProvider) click_config_provider);
  
  
 	// Load pictures
  	resource_init_current_app(&APP_RESOURCES);
  
}
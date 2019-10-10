#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"

#define LCGS(code) LCTL(LGUI(LSFT(code)))
#define LCS(code) LCTL(LSFT(code))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,      // can always be here
  EPRM,           
  RGB_SLD,        
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(
    // left hand
    KC_ESC,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_LEFT,        
    KC_TAB,         KC_Q,           KC_W,           KC_D,           KC_F,           KC_K,           TG(1),          
    KC_BSPC,        KC_A,           KC_S,           KC_E,           KC_T,           KC_G,           
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_BSLS,        
    OSL(1),         KC_GRV,         KC_UP,          KC_DOWN,        KC_LCTL,        
                                                                                    KC_INS,         KC_HOME,        
                                                                                                    KC_END,         
                                                                    LSFT_T(KC_SPC), KC_LALT,        KC_LCMD,        
        // right hand
        KC_RGHT,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        
        TG(1),          KC_J,           KC_U,           KC_R,           KC_L,           KC_SCLN,        KC_DEL,         
                        KC_Y,           KC_N,           KC_I,           KC_O,           KC_H,           KC_ENT,         
        KC_EQL,         KC_P,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,        
        KC_RCTL,        KC_LBRC,        KC_RBRC,        KC_QUOT,        OSL(1),         
        KC_PGUP,        KC_RCMD,        
        KC_PGDN,        
        KC_RCMD,        KC_ALGR,        LSFT_T(KC_SPC)
    ),


  [1] = LAYOUT_ergodox(
    // left hand
    _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          
    KC_TAB,         KC_ACL2,        KC_WH_L,        KC_MS_U,        KC_WH_R,        KC_WH_U,        _______,        
    KC_ESC,         KC_ACL0,        KC_MS_L,        KC_MS_D,        KC_MS_R,        KC_WH_D,        
    KC_LSFT,        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         
    _______,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        
                                                                                    KC_LCMD,        KC_HOME,        
                                                                                                    KC_END,         
                                                                    KC_BTN1,        KC_BTN2,        KC_BTN3,        
        // right hand
        KC_NLCK,        KC_LPRN,        KC_RPRN,        KC_PSLS,        KC_PAST,        KC_EQL,         KC_DEL,         
        _______,        KC_CIRC,        KC_P7,          KC_P8,          KC_P9,          KC_PMNS,        KC_BSPC,        
                        KC_COLN,        KC_P4,          KC_P5,          KC_P6,          KC_PPLS,        KC_PENT,        
        _______,        KC_DLR,         KC_P1,          KC_P2,          KC_P3,          KC_PENT,        KC_RSFT,        
        KC_P0,          KC_COMM,        KC_PDOT,        KC_SPC,         _______,        
        KC_PGUP,        KC_RCMD,        
        KC_PGDN,        
        KC_ALGR,        KC_RCTL,        KC_RSFT
    ),


  [2] = LAYOUT_ergodox(
    // left hand
    _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          _______,        
    _______,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        _______,        
    _______,        KC_CIRC,        KC_AMPR,        KC_LPRN,        KC_RPRN,        KC_PAST,        
    _______,        KC_PPLS,        KC_TILD,        KC_LCBR,        KC_RCBR,        KC_UNDS,        KC_PIPE,        
    _______,        _______,        _______,        _______,        _______,        
                                                                                    _______,        _______,        
                                                                                                    _______,        
                                                                    _______,        _______,        _______,        
        // right hand
        _______,        KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
        _______,        _______,        _______,        _______,        _______,        _______,        KC_F12,         
                        _______,        _______,        _______,        _______,        _______,        _______,        
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        
        _______,        _______,        _______,        _______,        _______,        
        _______,        _______,        
        _______,        
        _______,        _______,        _______
    ),


};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};

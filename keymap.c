#include QMK_KEYBOARD_H

#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum keyboard_layouts {
  NORMAN,
  QWERTY,
  MOUSE
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,      // can always be here
  EPRM,           
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Norman layout
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * | Esc    |  1!  |  2@  |  3#  |  4$  |  5%  |  <-  |           |  ->  |   6, |   7. |   8; |   9( |   0) |    -_  |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * | Tab    |   Q  |   W  |   D  |   F  |   K  | L2   |           |  L3  |   J  |   U  |   R  |   L  |   ;  |  BkSp  |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * | BkSp   |   A  |   S  |   E  |   T  |   G  |------|           |------|   Y  |   N  |   I  |   O  |   H  |' / Cmd |
  * |--------+------+------+------+------+------| \|   |           |  =   |------+------+------+------+------+--------|
  * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |  L2  | `    |  Up  | Down | LCtr |                                       | Left | Right|   [  |   ]  |  \|  |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,---------------.
  *                                        | Ins  | Home |       | PgUp |  RCmd  |
  *                                 ,------|------|------|       |------+--------+------.
  *                                 |      |      | End  |       | PgDn |        |      |
  *                                 | Space| LAlt |------|       |------| Enter  | Space|
  *                                 |      |      | LCmd |       | RCmd |        |      |
  *                                 `--------------------'       `----------------------'
  */
  [NORMAN] = LAYOUT_ergodox(
    // left hand
    KC_ESC,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_LEFT,        
    KC_TAB,         KC_Q,           KC_W,           KC_D,           KC_F,           KC_K,           TG(QWERTY),
    KC_BSPC,        KC_A,           KC_S,           KC_E,           KC_T,           KC_G,
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_BSLS,
    OSL(MOUSE),     KC_GRV,         KC_UP,          KC_DOWN,        KC_LCTL,

    //left thumb block
                    KC_INS,  KC_HOME,
                             KC_END,
    LSFT_T(KC_SPC), KC_LALT, KC_LCMD,

    // right hand
    KC_RGHT,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
    TG(QWERTY),     KC_J,           KC_U,           KC_R,           KC_L,           KC_SCLN,        KC_DEL,
                    KC_Y,           KC_N,           KC_I,           KC_O,           KC_H,           KC_QUOT,
    KC_EQL,         KC_P,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
    KC_LEFT,        KC_RGHT,        KC_LBRC,        KC_RBRC,        KC_BSLS,

    //Right thumb block
    KC_PGUP,        KC_RCMD,
    KC_PGDN,
    KC_RCMD,        KC_ENT,        RSFT_T(KC_SPC)
  ),

  /* Keymap 1: QWERTY layer
  * NOTE: currently there is only symbols on this layer, everything else uses bindings of the previous layer------------
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
  * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
  * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
  *                                 ,------|------|------|       |------+--------+------.
  *                                 |      |      | Home |       | PgUp |        |      |
  *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
  *                                 |      |ace   | End  |       | PgDn |        |      |
  *                                 `--------------------'       `----------------------'
  */
  [QWERTY] = LAYOUT_ergodox(
    // left hand
    _______,                 _______,           _______,       _______,        _______,         _______,             _______,
    _______,                 KC_Q,              KC_W,          KC_E,           KC_R,            KC_T,                _______,
    _______,                 KC_A,              KC_S,          KC_D,           KC_F,            KC_G,
    _______,                 CTL_T(KC_Z),       KC_X,          KC_C,           KC_V,            KC_B,                _______,
    LT(MOUSE,KC_GRV),        _______,           _______,       _______,        _______,       

    //left thumb block
                                                                                                    _______, _______,
                                                                                                             _______,
                                                                                           _______, _______, _______,

    // right hand
    _______,                 _______,           _______,        _______,       _______,         _______,             _______,
    _______,                 KC_Y,              KC_U,           KC_I,          KC_O,            KC_P,                _______,
                             KC_H,              KC_J,           KC_K,          KC_L,            KC_SCLN,             _______,
    _______,                 KC_N,              KC_M,           KC_COMM,       KC_DOT,          CTL_T(KC_SLSH),      _______,
                                                _______,        _______,       _______,         _______,             _______,

    //right thumb block
    _______, _______,
    _______,
    _______, _______, _______
  ),


  [MOUSE] = LAYOUT_ergodox(
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
};

void eeconfig_init_user(void) {
    // set_unicode_input_mode(UC_LNX);

}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
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

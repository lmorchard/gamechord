#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default
    KEYMAP(  FN3,  FN4,  FN5,  FN6,  FN7, \
             FN8,  FN9, FN10, FN11, FN12, \
            FN13, FN14, FN15, FN16, FN17, \
              NO,   NO,  FN0,  FN1,  FN2),
    /*
    KEYMAP(    Q,    W,    E,    R,    T, \
               A,    S,    D,    F,    G, \
               Z,    X,    C,    V,    B, \
              NO,   NO,  FN0,  FN1,  FN2),
    */
    // FN0
    KEYMAP(    P,    O,    I,    U,    Y, \
            SCLN,    L,    K,    J,    H, \
            SLSH,  DOT, COMM,    M,    N, \
              NO,   NO,  FN0,  FN1,  FN2),
    // FN1 
    KEYMAP(    1,    2,    3,    4,    5, \
             ESC,  GRV, LBRC, RBRC, BSLS, \
             TAB,  EQL, MINS, QUOT,  ENT, \
              NO,   NO,  FN0,  FN1,  FN2),
    // FN0 + FN1
    KEYMAP(    0,    9,    8,    7,    6, \
             ESC, HOME,   UP,  END, PGUP, \
             TAB, LEFT, DOWN, RGHT, PGDN, \
              NO,   NO,  FN0,  FN1,  FN2),
};

/* id for user defined functions */
enum function_id {
    FN_FN0,
    FN_FN1,
    FN_FN2
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION_TAP(FN_FN0),
    [1] = ACTION_FUNCTION_TAP(FN_FN1),
    [2] = ACTION_FUNCTION_TAP(FN_FN2),
    [3] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_Q),
    [4] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_W),
    [5] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_E),
    [6] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_R),
    [7] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_T),
    [8] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_A),
    [9] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_S),
    [10] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_D),
    [11] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_F),
    [12] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_G),
    [13] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_Z),
    [14] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_X),
    [15] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_C),
    [16] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_V),
    [17] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_B),
};

bool mod_fn0 = false;
bool mod_fn1 = false;
bool mod_fn2 = false;

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if ((record->tap.count == 2) && !(record->tap.interrupted)) {
        switch (id) {
            case FN_FN0:
                // Double-tap FN0 = Left Control one shot
                if (record->event.pressed) {
                    set_oneshot_mods(MOD_LCTL);
                    return;
                }
        }
    }

    if ((record->tap.count > 0) && !(record->tap.interrupted)) {
        switch (id) {
            case FN_FN0:
                dprint("TAPPY FN0!\n");
                return;
            case FN_FN1:
                // Tap FN1 = Space
                if (record->event.pressed) { register_code(KC_SPACE); }
                else { unregister_code(KC_SPACE); }
                send_keyboard_report();
                return;
            case FN_FN2:
                // Tap FN2 = Backspace
                if (record->event.pressed) { register_code(KC_BSPACE); }
                else { unregister_code(KC_BSPACE); }
                send_keyboard_report();
                return;
        }
    }

    bool pressed = (record->tap.count == 0) && (record->event.pressed);
    switch (id) {
        case FN_FN0: mod_fn0 = pressed; break;
        case FN_FN1: mod_fn1 = pressed; break;
        case FN_FN2: mod_fn2 = pressed; break;
    }

    // FN0 held == LSHIFT
    if (mod_fn0) {
        register_mods(MOD_BIT(KC_LSHIFT));
    } else {
        unregister_mods(MOD_BIT(KC_LSHIFT));
    }

    if (mod_fn1 && mod_fn2) {
        // FN1 + FN2 held = Layer 3
        layer_move(3);
    } else if (mod_fn2) {
        // FN2 held = Layer 2
        layer_move(2);
    } else if (mod_fn1) {
        // FN1 held = Layer 1
        layer_move(1);
    } else {
        // Default = Layer 0
        layer_move(0);
    }
}

#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP( ESC,   1,    2,    3,    T, \
            TAB,   Q,    W,    E,    R, \
           LSFT,   A,    S,    D,    F, \
             NO,  NO, LCTL,  SPC,    C),
};
const uint16_t PROGMEM fn_actions[] = {};

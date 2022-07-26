/*
Copyright 2020 imchipwood

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x2289 // MD15
#define PRODUCT_ID      0x8922
#define DEVICE_VER      0x0001
#define MANUFACTURER    prasudiro
#define PRODUCT         moechanical md12

/* Column/Row IO definitions */
#define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { B1, B3, B2, B6 }
#define MATRIX_COL_PINS { D7, E6, B4, B5 }

/* Underlight configuration */
#define RGB_DI_PIN D3
#define RGBLED_NUM 18
#define RGBLIGHT_ANIMATIONS

/* Single rotary encoder */
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F6 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Reduce tapdance required taps from 5 to 2 */
#define TAPPING_TOGGLE 2

/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_UNMOD 15

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 200
#define PREVENT_STUCK_MODIFIERS
// #define PERMISSIVE_HOLD
// #define IGNORE_MOD_TAP_INTERRUPT
// #define TAPPING_FORCE_HOLD

// Enable handedness
#define EE_HANDS
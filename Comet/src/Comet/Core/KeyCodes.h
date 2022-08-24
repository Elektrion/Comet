#pragma once

#include "Comet/Core/Core.h"

namespace comet {

	using KeyCode = uint32_t;

	// GLFW keycodes (from glfw3.h)

	/* Printable keys */
	KeyCode CMT_KEY_SPACE            = 32;
	KeyCode CMT_KEY_APOSTROPHE       = 39;  /* ' */
	KeyCode CMT_KEY_COMMA            = 44;  /* , */
	KeyCode CMT_KEY_MINUS            = 45;  /* - */
	KeyCode CMT_KEY_PERIOD           = 46;  /* . */
	KeyCode CMT_KEY_SLASH            = 47;  /* / */
	KeyCode CMT_KEY_0                = 48;
	KeyCode CMT_KEY_1                = 49;
	KeyCode CMT_KEY_2                = 50;
	KeyCode CMT_KEY_3                = 51;
	KeyCode CMT_KEY_4                = 52;
	KeyCode CMT_KEY_5                = 53;
	KeyCode CMT_KEY_6                = 54;
	KeyCode CMT_KEY_7                = 55;
	KeyCode CMT_KEY_8                = 56;
	KeyCode CMT_KEY_9                = 57;
	KeyCode CMT_KEY_SEMICOLON        = 59;  /* ; */
	KeyCode CMT_KEY_EQUAL            = 61;  /* = */
	KeyCode CMT_KEY_A                = 65;
	KeyCode CMT_KEY_B                = 66;
	KeyCode CMT_KEY_C                = 67;
	KeyCode CMT_KEY_D                = 68;
	KeyCode CMT_KEY_E                = 69;
	KeyCode CMT_KEY_F                = 70;
	KeyCode CMT_KEY_G                = 71;
	KeyCode CMT_KEY_H                = 72;
	KeyCode CMT_KEY_I                = 73;
	KeyCode CMT_KEY_J                = 74;
	KeyCode CMT_KEY_K                = 75;
	KeyCode CMT_KEY_L                = 76;
	KeyCode CMT_KEY_M                = 77;
	KeyCode CMT_KEY_N                = 78;
	KeyCode CMT_KEY_O                = 79;
	KeyCode CMT_KEY_P                = 80;
	KeyCode CMT_KEY_Q                = 81;
	KeyCode CMT_KEY_R                = 82;
	KeyCode CMT_KEY_S                = 83;
	KeyCode CMT_KEY_T                = 84;
	KeyCode CMT_KEY_U                = 85;
	KeyCode CMT_KEY_V                = 86;
	KeyCode CMT_KEY_W                = 87;
	KeyCode CMT_KEY_X                = 88;
	KeyCode CMT_KEY_Y                = 89;
	KeyCode CMT_KEY_Z                = 90;
	KeyCode CMT_KEY_LEFT_BRACKET     = 91;  /* [ */
	KeyCode CMT_KEY_BACKSLASH        = 92;  /* \ */
	KeyCode CMT_KEY_RIGHT_BRACKET    = 93;  /* ] */
	KeyCode CMT_KEY_GRAVE_ACCENT     = 96;  /* ` */
	KeyCode CMT_KEY_WORLD_1          = 161; /* non-US #1 */
	KeyCode CMT_KEY_WORLD_2          = 162; /* non-US #2 */

	/* Function keys */
	KeyCode CMT_KEY_ESCAPE           = 256;
	KeyCode CMT_KEY_ENTER            = 257;
	KeyCode CMT_KEY_TAB              = 258;
	KeyCode CMT_KEY_BACKSPACE        = 259;
	KeyCode CMT_KEY_INSERT           = 260;
	KeyCode CMT_KEY_DELETE           = 261;
	KeyCode CMT_KEY_RIGHT            = 262;
	KeyCode CMT_KEY_LEFT             = 263;
	KeyCode CMT_KEY_DOWN             = 264;
	KeyCode CMT_KEY_UP               = 265;
	KeyCode CMT_KEY_PAGE_UP          = 266;
	KeyCode CMT_KEY_PAGE_DOWN        = 267;
	KeyCode CMT_KEY_HOME             = 268;
	KeyCode CMT_KEY_END              = 269;
	KeyCode CMT_KEY_CAPS_LOCK        = 280;
	KeyCode CMT_KEY_SCROLL_LOCK      = 281;
	KeyCode CMT_KEY_NUM_LOCK         = 282;
	KeyCode CMT_KEY_PRINT_SCREEN     = 283;
	KeyCode CMT_KEY_PAUSE            = 284;
	KeyCode CMT_KEY_F1               = 290;
	KeyCode CMT_KEY_F2               = 291;
	KeyCode CMT_KEY_F3               = 292;
	KeyCode CMT_KEY_F4               = 293;
	KeyCode CMT_KEY_F5               = 294;
	KeyCode CMT_KEY_F6               = 295;
	KeyCode CMT_KEY_F7               = 296;
	KeyCode CMT_KEY_F8               = 297;
	KeyCode CMT_KEY_F9               = 298;
	KeyCode CMT_KEY_F10              = 299;
	KeyCode CMT_KEY_F11              = 300;
	KeyCode CMT_KEY_F12              = 301;
	KeyCode CMT_KEY_F13              = 302;
	KeyCode CMT_KEY_F14              = 303;
	KeyCode CMT_KEY_F15              = 304;
	KeyCode CMT_KEY_F16              = 305;
	KeyCode CMT_KEY_F17              = 306;
	KeyCode CMT_KEY_F18              = 307;
	KeyCode CMT_KEY_F19              = 308;
	KeyCode CMT_KEY_F20              = 309;
	KeyCode CMT_KEY_F21              = 310;
	KeyCode CMT_KEY_F22              = 311;
	KeyCode CMT_KEY_F23              = 312;
	KeyCode CMT_KEY_F24              = 313;
	KeyCode CMT_KEY_F25              = 314;
	KeyCode CMT_KEY_KP_0             = 320;
	KeyCode CMT_KEY_KP_1             = 321;
	KeyCode CMT_KEY_KP_2             = 322;
	KeyCode CMT_KEY_KP_3             = 323;
	KeyCode CMT_KEY_KP_4             = 324;
	KeyCode CMT_KEY_KP_5             = 325;
	KeyCode CMT_KEY_KP_6             = 326;
	KeyCode CMT_KEY_KP_7             = 327;
	KeyCode CMT_KEY_KP_8             = 328;
	KeyCode CMT_KEY_KP_9             = 329;
	KeyCode CMT_KEY_KP_DECIMAL       = 330;
	KeyCode CMT_KEY_KP_DIVIDE        = 331;
	KeyCode CMT_KEY_KP_MULTIPLY      = 332;
	KeyCode CMT_KEY_KP_SUBTRACT      = 333;
	KeyCode CMT_KEY_KP_ADD           = 334;
	KeyCode CMT_KEY_KP_ENTER         = 335;
	KeyCode CMT_KEY_KP_EQUAL         = 336;
	KeyCode CMT_KEY_LEFT_SHIFT       = 340;
	KeyCode CMT_KEY_LEFT_CONTROL     = 341;
	KeyCode CMT_KEY_LEFT_ALT         = 342;
	KeyCode CMT_KEY_LEFT_SUPER       = 343;
	KeyCode CMT_KEY_RIGHT_SHIFT      = 344;
	KeyCode CMT_KEY_RIGHT_CONTROL    = 345;
	KeyCode CMT_KEY_RIGHT_ALT        = 346;
	KeyCode CMT_KEY_RIGHT_SUPER      = 347;
	KeyCode CMT_KEY_MENU             = 348;
}

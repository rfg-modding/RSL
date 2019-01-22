#pragma once
#include "RFGR_Types_Player.h"

/* 566 */
enum control_button_action
{
	CBA_BUTTON_INVALID = 0xFFFFFFFF,
	CBA_GAC_WEAPON_MENU = 0x0,
	CBA_GAC_HOLD_OBJECT = 0x1,
	CBA_GAC_SCOREBOARD = 0x2,
	CBA_GAC_SWITCH_CLASS = 0x3,
	CBA_GAC_RESPAWN = 0x4,
	CBA_GAC_TOGGLE_BACKPACK_ACTIVATION = 0x5,
	CBA_GAC_VOTE_YES = 0x6,
	CBA_GAC_VOTE_NO = 0x7,
	CBA_GAC_HELP = 0x8,
	CBA_SPECTATOR_NEXT_TARGET = 0x9,
	CBA_SPECTATOR_PREV_TARGET = 0xA,
	CBA_SPECTATOR_LOCK_CAMERA = 0xB,
	CBA_SPECTATOR_UNLOCK_CAMERA = 0xC,
	CBA_SPECTATOR_NEXT_PLAYER = 0xD,
	CBA_SPECTATOR_PREV_PLAYER = 0xE,
	CBA_SPECTATOR_MODE_CUSTOM = 0xF,
	CBA_SPECTATOR_MODE_AQUARIUM = 0x10,
	CBA_SPECTATOR_MODE_ACTION = 0x11,
	CBA_SPECTATOR_MODE_PLAYER = 0x12,
	CBA_SPECTATOR_TOGGLE_HUD = 0x13,
	CBA_OFC_ATTACK_PRIMARY = 0x14,
	CBA_OFC_ATTACK_MELEE = 0x15,
	CBA_OFC_JUMP = 0x16,
	CBA_OFC_SPRINT = 0x17,
	CBA_OFC_CROUCH = 0x18,
	CBA_OFC_RELOAD = 0x19,
	CBA_OFC_ZOOM = 0x1A,
	CBA_OFC_COVER = 0x1B,
	CBA_OFC_ACTION = 0x1C,
	CBA_OFC_CHARGE_DETONATE = 0x1D,
	CBA_VDC_ACCELERATE = 0x1E,
	CBA_VDC_BRAKE_REVERSE = 0x1F,
	CBA_VDC_HANDBRAKE = 0x20,
	CBA_VDC_FIREARM = 0x21,
	CBA_VDC_CYCLE_CAMERA_MODE = 0x22,
	CBA_VDC_LOOK_BACK = 0x23,
	CBA_VDC_MECH_MELEE1 = 0x24,
	CBA_VDC_MECH_MELEE2 = 0x25,
	CBA_VDC_MECH_MELEE3 = 0x26,
	CBA_VDC_MECH_MELEE4 = 0x27,
	CBA_VDC_MECH_CHARGE = 0x28,
	CBA_VDC_TANK_FIRE_PRIMARY = 0x29,
	CBA_VDC_TANK_FIRE_SECONDARY = 0x2A,
	CBA_VDC_ACTION = 0x2B,
	CBA_VDC_TURRET_ZOOM = 0x2C,
	CBA_VDC_CHANGE_SEAT = 0x2D,
	CBA_SAT_ZOOM = 0x2E,
	CBA_SAT_FIRE = 0x2F,
	CBA_SAT_HOLD = 0x30,
	CBA_SAT_RETURN = 0x31,
	CBA_WEAPON_MENU_UP = 0x32,
	CBA_WEAPON_MENU_UP_DPAD = 0x33,
	CBA_WEAPON_MENU_DOWN = 0x34,
	CBA_WEAPON_MENU_DOWN_DPAD = 0x35,
	CBA_WEAPON_MENU_LEFT = 0x36,
	CBA_WEAPON_MENU_LEFT_DPAD = 0x37,
	CBA_WEAPON_MENU_RIGHT = 0x38,
	CBA_WEAPON_MENU_RIGHT_DPAD = 0x39,
	CBA_MAP = 0x3A,
	CBA_MENU_UP_NO_STICK = 0x3B,
	CBA_MENU_DOWN_NO_STICK = 0x3C,
	CBA_MENU_UP = 0x3D,
	CBA_MENU_DOWN = 0x3E,
	CBA_MENU_LEFT = 0x3F,
	CBA_MENU_LEFT_NO_STICK = 0x40,
	CBA_MENU_RIGHT = 0x41,
	CBA_MENU_RIGHT_NO_STICK = 0x42,
	CBA_MENU_ALT_UP = 0x43,
	CBA_MENU_ALT_DOWN = 0x44,
	CBA_MENU_ALT_LEFT = 0x45,
	CBA_MENU_ALT_RIGHT = 0x46,
	CBA_MENU_START = 0x47,
	CBA_MENU_QUIT = 0x48,
	CBA_MENU_SELECT = 0x49,
	CBA_MENU_ABORT = 0x4A,
	CBA_MENU_PGUP = 0x4B,
	CBA_MENU_PGDN = 0x4C,
	CBA_MENU_X = 0x4D,
	CBA_MENU_Y = 0x4E,
	CBA_MENU_L1 = 0x4F,
	CBA_MENU_L2 = 0x50,
	CBA_MENU_R1 = 0x51,
	CBA_MENU_R2 = 0x52,
	CBA_MINIMAP_ZOOM_IN = 0x53,
	CBA_MINIMAP_ZOOM_OUT = 0x54,
	CBA_MENU_BACK = 0x55,
	CBA_GAMEPLAY_PAUSE = 0x56,
	CBA_GPS_MARKER = 0x57,
	CBA_TOOLTIP_RESUME = 0x58,
	CBA_START_GAME = 0x59,
	CBA_DELETE_SAVEGAME = 0x5A,
	CBA_FSM_PLACE_BEACON = 0x5B,
	CBA_MP_VIEW_GAMERCARD = 0x5C,
	CBA_CNTRL_CONFIG = 0x5D,
	CBA_CNTRL_CLEAR = 0x5E,
	CBA_CNTRL_INVERT = 0x5F,
	CBA_PUSHTOTALK = 0x60,
	CBA_SKIP_MODAL_SEQUENCE = 0x61,
	CBA_RESET_GYRO = 0x62,
	CBA_CYCLE_WEAPONS_BACK = 0x63,
	CBA_CYCLE_WEAPONS_FORWARD = 0x64,
	CBA_SCROLL_BAR_UP = 0x65,
	CBA_SCROLL_BAR_DOWN = 0x66,
	CBA_VDC_ACCELERATE_AXIS = 0x67,
	CBA_VDC_BRAKE_REVERSE_AXIS = 0x68,
	CBA_OPEN_CHAT = 0x69,
	CBA_OPEN_TEAM_CHAT = 0x6A,
	CBA_SHOULDER_SWITCH = 0x6B,
	NUM_CONTROL_BUTTON_ACTIONS = 0x6C,
	RESERVED_NUM_CONTROL_BUTTON_ACTIONS = 0xC8,
};

/* 1393 */
enum hint_type
{
	HT_SELECTION = 0x0,
	HT_ABORT = 0x1,
	HT_MISC = 0x2,
	HT_MISC_2 = 0x3,
	HT_LAST = 0x4,
};

/* 1394 */
enum control_action_type
{
	CAT_INVALID = 0xFFFFFFFF,
	CAT_BUTTON = 0x0,
	CAT_AXIS = 0x1,
	NUM_CONTROL_ACTION_TYPES = 0x2,
};

/* 9305 */
struct __declspec(align(4)) hint_info
{
	hint_type type;
	control_button_action button_action;
	char hint_text[256];
	char hint_image_name[32];
	bool is_visible;
};

struct base_array_hint_info_Vtbl;
/* 9303 */
struct base_array_hint_info
{
	base_array_hint_info_Vtbl *vfptr;
	hint_info *elt;
	int array_size;
	int num;
};

/* 9304 */
struct base_array_hint_info_Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array_hint_info *This, unsigned int);
};

/* 9306 */
struct farray_hint_info_4 : base_array_hint_info
{
	hint_info data[4];
};

/* 1380 */
enum menu_item_type
{
	MI_INVALID = 0xFFFFFFFF,
	MI_FUNCTION = 0x0,
	MI_CHAR_LIST = 0x1,
	MI_BOOL = 0x2,
	MI_INCR = 0x3,
	MI_LAST = 0x4,
};

/* 9302 */
struct document_info
{
	int needs_cleanup;
	int doc_handle;
	int data_handle_tween_on_select;
	int data_handle_title;
	int data_handle_populate_group;
	int data_handle_hint_group;
	char event_surtag[8];
	farray_int_4 data_handle_hints;
	farray_int_16 data_handle_populate_items;
};

struct ui_menuVtbl;
struct ui_menu_item_base;
/* 9298 */
struct ui_menu
{
	ui_menuVtbl *vfptr;
	bool m_surpress_accept_sounds;
	bool m_should_tween_out;
	bool m_awaiting_tween_on_select_end;
	bool m_awaiting_tween_fade_in_end;
	bool m_force_update;
	int m_choose_on_enter;
	int m_handle;
	int m_doc_handle;
	int m_input_id;
	int m_selected;
	unsigned int m_num_items;
	ui_menu_item_base *m_items[16];
	char m_title[192];
	void(__cdecl *m_selection_hint_cb)(hint_type);
	void(__cdecl *m_selection_change_cb)(int);
	document_info *m_doc_info;
	farray_hint_info_4 m_hint_info;
};

/* 9299 */
struct ui_menuVtbl
{
	void *(__thiscall *__vecDelDtor)(ui_menu *This, unsigned int);
};

struct ui_menu_item_baseVtbl;
/* 9300 */
struct ui_menu_item_base
{
	ui_menu_item_baseVtbl *vfptr;
	bool m_play_change_sound;
	bool m_selected;
	bool m_enabled;
	bool m_visible;
	int m_handle;
	menu_item_type m_type;
	char m_caption[128];
	ui_menu *m_parent;
};

/* 9301 */
struct ui_menu_item_baseVtbl
{
	void *(__thiscall *__vecDelDtor)(ui_menu_item_base *This, unsigned int);
	void(__thiscall *get_text_value)(ui_menu_item_base *This, char *, int);
};

struct base_array_ui_menu_pointer_Vtbl;
/* 9325 */
struct base_array_ui_menu_pointer
{
	base_array_ui_menu_pointer_Vtbl *vfptr;
	ui_menu **elt;
	int array_size;
	int num;
};

/* 9326 */
struct base_array_ui_menu_pointer_Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array_ui_menu_pointer *This, unsigned int);
};

/* 9327 */
struct farray_ui_menu_pointer_8 : base_array_ui_menu_pointer
{
	ui_menu *data[8];
};
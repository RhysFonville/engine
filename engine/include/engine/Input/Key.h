#include <ranges>
#include <algorithm>
#include "../util/defines.h"

enum class Key {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero,
	Minus, Equal,
	RightBracket, LeftBracket,
	Quote, Grave,
	Semicolon, Comma, Period,
	Backslash, Slash,
	KeypadDecimal, KeypadMultiply, KeypadPlus, KeypadClear, KeypadDivide, KeypadEnter, KeypadMinus, KeypadEquals,
	Keypad0, Keypad1, Keypad2, Keypad3, Keypad4, Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
	Return, Tab, Space, Delete, Escape, ForwardDelete,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
	Command, Shift, Option, Control, RightShift, RightOption, RightControl, Function,
	VolumeUp, VolumeDown, Mute,
	CapsLock, Help, Home,
	PageUp, PageDown, End,
	LeftArrow, RightArrow, DownArrow, UpArrow,
    KEYS_END
};

enum class KeyEvent {
	Down, Up, TypeHold, CurrentlyDown
};

#include <map>

#ifdef PLATFORM_APPLE

#include <Carbon/Carbon.h>

static std::map<Key, int> key_to_apple{
	{Key::A, kVK_ANSI_A}, {Key::B, kVK_ANSI_B}, {Key::C, kVK_ANSI_C}, {Key::D, kVK_ANSI_D}, {Key::E, kVK_ANSI_E}, {Key::F, kVK_ANSI_F}, {Key::G, kVK_ANSI_G}, {Key::H, kVK_ANSI_H}, {Key::I, kVK_ANSI_I}, {Key::J, kVK_ANSI_J}, {Key::K, kVK_ANSI_K}, {Key::L, kVK_ANSI_L}, {Key::M, kVK_ANSI_M}, {Key::N, kVK_ANSI_N}, {Key::O, kVK_ANSI_O}, {Key::P, kVK_ANSI_P}, {Key::Q, kVK_ANSI_Q}, {Key::R, kVK_ANSI_R}, {Key::S, kVK_ANSI_S}, {Key::T, kVK_ANSI_T}, {Key::U, kVK_ANSI_U}, {Key::V, kVK_ANSI_V}, {Key::W, kVK_ANSI_W}, {Key::X, kVK_ANSI_X}, {Key::Y, kVK_ANSI_Y}, {Key::Z, kVK_ANSI_Z},
	{Key::One, kVK_ANSI_1}, {Key::Two, kVK_ANSI_2}, {Key::Three, kVK_ANSI_3}, {Key::Four, kVK_ANSI_4}, {Key::Five, kVK_ANSI_5}, {Key::Six, kVK_ANSI_6}, {Key::Seven, kVK_ANSI_7}, {Key::Eight, kVK_ANSI_8}, {Key::Nine, kVK_ANSI_9}, {Key::Zero, kVK_ANSI_0},
	{Key::Minus, kVK_ANSI_Minus}, {Key::Equal, kVK_ANSI_Equal},
	{Key::RightBracket, kVK_ANSI_RightBracket}, {Key::LeftBracket, kVK_ANSI_LeftBracket},
	{Key::Quote, kVK_ANSI_Quote}, {Key::Grave, kVK_ANSI_Grave},
	{Key::Semicolon, kVK_ANSI_Semicolon}, {Key::Comma, kVK_ANSI_Comma}, {Key::Period, kVK_ANSI_Period},
	{Key::Backslash, kVK_ANSI_Backslash}, {Key::Slash, kVK_ANSI_Slash},
	{Key::KeypadDecimal, kVK_ANSI_KeypadDecimal}, {Key::KeypadMultiply, kVK_ANSI_KeypadMultiply}, {Key::KeypadPlus, kVK_ANSI_KeypadPlus}, {Key::KeypadClear, kVK_ANSI_KeypadClear}, {Key::KeypadDivide, kVK_ANSI_KeypadDivide}, {Key::KeypadEnter, kVK_ANSI_KeypadEnter}, {Key::KeypadMinus, kVK_ANSI_KeypadMinus}, {Key::KeypadEquals, kVK_ANSI_KeypadEquals},
	{Key::Keypad0, kVK_ANSI_Keypad0}, {Key::Keypad1, kVK_ANSI_Keypad1}, {Key::Keypad2, kVK_ANSI_Keypad2}, {Key::Keypad3, kVK_ANSI_Keypad3}, {Key::Keypad4, kVK_ANSI_Keypad4}, {Key::Keypad5, kVK_ANSI_Keypad5}, {Key::Keypad6, kVK_ANSI_Keypad6}, {Key::Keypad7, kVK_ANSI_Keypad7}, {Key::Keypad8, kVK_ANSI_Keypad8}, {Key::Keypad9, kVK_ANSI_Keypad9},
	{Key::Return, kVK_Return}, {Key::Tab, kVK_Tab}, {Key::Space, kVK_Space}, {Key::Delete, kVK_Delete}, {Key::Escape, kVK_Escape}, {Key::ForwardDelete, kVK_ForwardDelete},
	{Key::F1, kVK_F1}, {Key::F2, kVK_F2}, {Key::F3, kVK_F3}, {Key::F4, kVK_F4}, {Key::F5, kVK_F5}, {Key::F6, kVK_F6}, {Key::F7, kVK_F7}, {Key::F8, kVK_F8}, {Key::F9, kVK_F9}, {Key::F10, kVK_F10}, {Key::F11, kVK_F11}, {Key::F12, kVK_F12}, {Key::F13, kVK_F13}, {Key::F14, kVK_F14}, {Key::F15, kVK_F15}, {Key::F16, kVK_F16}, {Key::F17, kVK_F17}, {Key::F18, kVK_F18}, {Key::F19, kVK_F19}, {Key::F20, kVK_F20},
	{Key::Command, kVK_Command}, {Key::Shift, kVK_Shift}, {Key::Option, kVK_Option}, {Key::Control, kVK_Control}, {Key::RightShift, kVK_RightShift}, {Key::RightOption, kVK_RightOption}, {Key::RightControl, kVK_RightControl}, {Key::Function, kVK_Function},
	{Key::VolumeUp, kVK_VolumeUp}, {Key::VolumeDown, kVK_VolumeDown}, {Key::Mute, kVK_Mute},
	{Key::CapsLock, kVK_CapsLock}, {Key::Help, kVK_Help}, {Key::Home, kVK_Home},
	{Key::PageUp, kVK_PageUp}, {Key::PageDown, kVK_PageDown}, {Key::End, kVK_End},
	{Key::LeftArrow, kVK_LeftArrow}, {Key::RightArrow, kVK_RightArrow}, {Key::DownArrow, kVK_DownArrow}, {Key::UpArrow, kVK_UpArrow},
};

static std::map<int, Key> apple_to_key{
    key_to_apple | std::views::transform([](const std::pair<Key, int>& p) {
        return std::make_pair(p.second, p.first);
    }) | std::ranges::to<std::map<int, Key>>()
};

static std::map<KeyEvent, int> event_to_glfw{
	{KeyEvent::Down, 1}, {KeyEvent::Up, 0},
    {KeyEvent::TypeHold, 2}
};

#elifdef PLATFORM_WINDOWS

#include <Winuser.h>

static std::map<Key, int> key_to_win32{
	{Key::A, kVK_ANSI_A}, {Key::B, kVK_ANSI_B}, {Key::C, kVK_ANSI_C}, {Key::D, kVK_ANSI_D}, {Key::E, kVK_ANSI_E}, {Key::F, kVK_ANSI_F}, {Key::G, kVK_ANSI_G}, {Key::H, kVK_ANSI_H}, {Key::I, kVK_ANSI_I}, {Key::J, kVK_ANSI_J}, {Key::K, kVK_ANSI_K}, {Key::L, kVK_ANSI_L}, {Key::M, kVK_ANSI_M}, {Key::N, kVK_ANSI_N}, {Key::O, kVK_ANSI_O}, {Key::P, kVK_ANSI_P}, {Key::Q, kVK_ANSI_Q}, {Key::R, kVK_ANSI_R}, {Key::S, kVK_ANSI_S}, {Key::T, kVK_ANSI_T}, {Key::U, kVK_ANSI_U}, {Key::V, kVK_ANSI_V}, {Key::W, kVK_ANSI_W}, {Key::X, kVK_ANSI_X}, {Key::Y, kVK_ANSI_Y}, {Key::Z, kVK_ANSI_Z},
	{Key::One, kVK_ANSI_1}, {Key::Two, kVK_ANSI_2}, {Key::Three, kVK_ANSI_3}, {Key::Four, kVK_ANSI_4}, {Key::Five, kVK_ANSI_5}, {Key::Six, kVK_ANSI_6}, {Key::Seven, kVK_ANSI_7}, {Key::Eight, kVK_ANSI_8}, {Key::Nine, kVK_ANSI_9}, {Key::Zero, kVK_ANSI_0},
	{Key::Minus, kVK_ANSI_Minus}, {Key::Equal, kVK_ANSI_Equal},
	{Key::RightBracket, kVK_ANSI_RightBracket}, {Key::LeftBracket, kVK_ANSI_LeftBracket},
	{Key::Quote, kVK_ANSI_Quote}, {Key::Grave, kVK_ANSI_Grave},
	{Key::Semicolon, kVK_ANSI_Semicolon}, {Key::Comma, kVK_ANSI_Comma}, {Key::Period, kVK_ANSI_Period},
	{Key::Backslash, kVK_ANSI_Backslash}, {Key::Slash, kVK_ANSI_Slash},
	{Key::KeypadDecimal, kVK_ANSI_KeypadDecimal}, {Key::KeypadMultiply, kVK_ANSI_KeypadMultiply}, {Key::KeypadPlus, kVK_ANSI_KeypadPlus}, {Key::KeypadClear, kVK_ANSI_KeypadClear}, {Key::KeypadDivide, kVK_ANSI_KeypadDivide}, {Key::KeypadEnter, kVK_ANSI_KeypadEnter}, {Key::KeypadMinus, kVK_ANSI_KeypadMinus}, {Key::KeypadEquals, kVK_ANSI_KeypadEquals},
	{Key::Keypad0, kVK_ANSI_Keypad0}, {Key::Keypad1, kVK_ANSI_Keypad1}, {Key::Keypad2, kVK_ANSI_Keypad2}, {Key::Keypad3, kVK_ANSI_Keypad3}, {Key::Keypad4, kVK_ANSI_Keypad4}, {Key::Keypad5, kVK_ANSI_Keypad5}, {Key::Keypad6, kVK_ANSI_Keypad6}, {Key::Keypad7, kVK_ANSI_Keypad7}, {Key::Keypad8, kVK_ANSI_Keypad8}, {Key::Keypad9, kVK_ANSI_Keypad9},
	{Key::Return, kVK_Return}, {Key::Tab, kVK_Tab}, {Key::Space, kVK_Space}, {Key::Delete, kVK_Delete}, {Key::Escape, kVK_Escape}, {Key::ForwardDelete, kVK_ForwardDelete},
	{Key::F1, kVK_F1}, {Key::F2, kVK_F2}, {Key::F3, kVK_F3}, {Key::F4, kVK_F4}, {Key::F5, kVK_F5}, {Key::F6, kVK_F6}, {Key::F7, kVK_F7}, {Key::F8, kVK_F8}, {Key::F9, kVK_F9}, {Key::F10, kVK_F10}, {Key::F11, kVK_F11}, {Key::F12, kVK_F12}, {Key::F13, kVK_F13}, {Key::F14, kVK_F14}, {Key::F15, kVK_F15}, {Key::F16, kVK_F16}, {Key::F17, kVK_F17}, {Key::F18, kVK_F18}, {Key::F19, kVK_F19}, {Key::F20, kVK_F20},
	{Key::Command, kVK_Command}, {Key::Shift, kVK_Shift}, {Key::Option, kVK_Option}, {Key::Control, kVK_Control}, {Key::RightShift, kVK_RightShift}, {Key::RightOption, kVK_RightOption}, {Key::RightControl, kVK_RightControl}, {Key::Function, kVK_Function},
	{Key::VolumeUp, kVK_VolumeUp}, {Key::VolumeDown, kVK_VolumeDown}, {Key::Mute, kVK_Mute},
	{Key::CapsLock, kVK_CapsLock}, {Key::Help, kVK_Help}, {Key::Home, kVK_Home},
	{Key::PageUp, kVK_PageUp}, {Key::PageDown, kVK_PageDown}, {Key::End, kVK_End},
	{Key::LeftArrow, kVK_LeftArrow}, {Key::RightArrow, kVK_RightArrow}, {Key::DownArrow, kVK_DownArrow}, {Key::UpArrow, kVK_UpArrow},
};

static std::map<int, Key> win32_to_key{
    key_to_win32 | std::views::transform([](const std::pair<Key, int>& p) {
        return std::make_pair(p.second, p.first);
    }) | std::ranges::to<std::map<int, Key>>()
};

#endif


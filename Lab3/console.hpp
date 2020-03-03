#pragma once
#include <Windows.h>
#include <iostream>

class console {
	HANDLE out_descriptor;
	CONSOLE_SCREEN_BUFFER_INFO initial_buffer_info;
public:
	static constexpr auto foreground_blue = 1 << 0;
	static constexpr auto foreground_green = 1 << 1;
	static constexpr auto foreground_red = 1 << 2;
	static constexpr auto foreground_intensity = 1 << 3;
public:
	static constexpr auto background_blue = 1 << 0;
	static constexpr auto background_green = 1 << 1;
	static constexpr auto background_red = 1 << 2;
	static constexpr auto background_intensity = 1 << 3;
public:
	console() {
		out_descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(out_descriptor, &initial_buffer_info);
	}
	void set_color(std::uint8_t color) {
		SetConsoleTextAttribute(out_descriptor, color);
	}
	void reset_color() {
		SetConsoleTextAttribute(out_descriptor, initial_buffer_info.wAttributes);
	}
};

template<typename T>
console& operator<<(console& l, const T& r) {
	std::cout << r;
	l.reset_color();
	return l;
}
#pragma once

#include <iostream>
#include <system_error>
#include <source_location>
#include <string>
#include <unordered_map>
//#include <stacktrace>

#include "defines.h"

#define CREATE_ERROR_CATEGORY(cat_name, ...) \
class _##cat_name##_category : public std::error_category { \
public: \
	constexpr _##cat_name##_category() noexcept : std::error_category{} { } \
\
	const char* name() const noexcept override { \
		return #cat_name; \
	} \
\
	std::string message(int ev) const override { \
		static std::unordered_map<int, std::string> err_codes __VA_ARGS__; \
		auto it = err_codes.find(ev); \
		if (it != err_codes.end()) return it->second; \
		return "Unknown error"; \
	} \
};\
inline const std::error_category& cat_name##_category() { \
	static _##cat_name##_category instance; \
	return instance; \
}\

class Error : public std::error_code {
public:
	Error() { }
	explicit Error(std::error_code ec)
		: std::error_code{ ec }, location{ std::source_location::current() } { }

	NODISC std::source_location get_location() const noexcept { return location; }
	//NODISC std::stacktrace get_stacktrace() const noexcept { return stacktrace; }

private:
	std::source_location location{};
	//std::stacktrace stacktrace{std::stacktrace::current()};
};

#undef ERROR

enum class LogLevel {
	FATAL,
	ERROR,
	WARN,
	INFO,
};

inline void begin_log_level(LogLevel level) noexcept {
	if (level == LogLevel::FATAL) { std::cerr << "FATAL: "; }
	else if (level == LogLevel::ERROR) { std::cerr << "ERROR: "; }
	else if (level == LogLevel::WARN) { std::cerr << "WARN: "; }
	else if (level == LogLevel::INFO) { std::cout << "INFO: "; }
}

inline void log(LogLevel level, const auto& message) noexcept {
	begin_log_level(level);
	(level == LogLevel::INFO ? std::cout : std::cerr) << message << '\n';
}

inline void log(const auto& message) noexcept {
	log(LogLevel::INFO, message);
}

inline void log(LogLevel level, const Error& error) noexcept {
	begin_log_level(level);

	const std::source_location& loc{error.get_location()};
	(level == LogLevel::INFO ? std::cout : std::cerr) <<
		"Error code " << error.value() <<
		"(" << error.category().message(error.value()) << ")" <<
		" of category " << error.category().name() <<
		" at " <<
		std::to_string(loc.column()) + ":" +
		std::to_string(loc.line()) + ":" +
		loc.function_name() + ":" +
		loc.file_name() /*<<
		". Stacktrace:\n" << error.get_stacktrace()*/ << '\n'
	;
}
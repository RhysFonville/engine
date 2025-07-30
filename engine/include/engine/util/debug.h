#pragma once

#include <iostream>

enum class LogLevel {
	FATAL,
	ERROR,
	WARN,
	INFO,
};

inline void log(LogLevel level, const auto& message) {
	if		(level == LogLevel::FATAL)	{ std::cerr << "FATAL: "; }
	else if	(level == LogLevel::ERROR)	{ std::cerr << "ERROR: "; }
	else if	(level == LogLevel::WARN)	{ std::cerr << "WARN: "; }
	else if	(level == LogLevel::INFO)	{ std::cout << "INFO: " << message << '\n'; return; }

	std::cerr << message << '\n';
}


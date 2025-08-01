#include <cstdlib>
#include <ranges>
#include <engine/util/debug.h>
#include <system_error>

int main() {
	log(LogLevel::FATAL, "Fatal message");
	log(LogLevel::ERROR, "Error message");
	log(LogLevel::WARN, "Warn message");
	log(LogLevel::INFO, "Info message");

    for (i32 i : std::views::iota(1, 10)) {
        log(LogLevel::ERROR, Error{std::error_code{i, std::generic_category()}});
    }

	return EXIT_SUCCESS;
}

#include <cstdlib>
#include <ranges>
#include <engine/util/debug.h>
#include <system_error>

int main() {
	log(LogLevel::Fatal, "Fatal message");
	log(LogLevel::Error, "Error message");
	log(LogLevel::Warn, "Warn message");
	log(LogLevel::Info, "Info message");

    for (i32 i : std::views::iota(1, 10)) {
        log(LogLevel::Error, MK_ERROR(i, std::generic_category()));
    }

	return EXIT_SUCCESS;
}

#include <cstdlib>
#include <engine/util/debug.h>

int main() {
	log(LogLevel::FATAL, "Fatal message");
	log(LogLevel::ERROR, "Error message");
	log(LogLevel::WARN, "Warn message");
	log(LogLevel::INFO, "Info message");
	return EXIT_SUCCESS;
}

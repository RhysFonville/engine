#include "Editor/Editor.h"

int main(int argc, char* argv[]) {
	Editor editor{};
	if (auto res{editor.init(std::string{argc > 1 ? argv[1] : ""})}; res.has_value()) {
		log(LogLevel::FATAL, res.value());
		return EXIT_FAILURE;
	}
	
	editor.run();

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif

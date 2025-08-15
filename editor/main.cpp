#include "Editor/Editor.h"

int main(const int argc, const char* argv[]) {
	auto editor{Editor::init(std::string{argc > 1 ? argv[1] : ""})};
	if (!editor.has_value()) {
		log(LogLevel::FATAL, editor.error());
		return EXIT_FAILURE;
	}
	
	editor.value().run();

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int argc{2};
	//CommandLineToArgvW(GetCommandLineW(), &argc);
	//const char* argv[2] = { "editor", lpCmdLine };
	const char* argv[2] = { "editor", "G:\\Documents\\Visual Studio Code\\engine\\project" };
	main(argc, argv);
}
#endif

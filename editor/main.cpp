#include <engine/Input/InputSet.h>
#include <engine/Scene/Engine.h>

#undef ERROR

int main(int argc, char* argv[]) {
	Engine engine{};
	engine.init();

	

	engine.run();

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif

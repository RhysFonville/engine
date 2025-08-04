#include <iostream>
#include <engine/AssetManager/AssetManager.h>

#undef ERROR

int main() {
	AssetManager* am{AssetManager::get_instance()};
	std::shared_ptr<std::string> str{am->load<std::string>("test.txt")};
	std::shared_ptr<std::string> str2{am->load<std::string>("test.txt")};

    std::cout << static_cast<const void*>(str.get()) << ' ' <<
        static_cast<const void*>(str2.get()) << '\n';

    std::cout << *str << "\n\n";
    std::cout << *str2 << "\n\n";

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif

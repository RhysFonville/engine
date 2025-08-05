#include <iostream>
#include <engine/AssetManager/AssetManager.h>

#undef ERROR

int main() {
	AssetManager* am{AssetManager::get_instance()};
    auto str{am->load<std::string>("test.txt")};
    if (!str.has_value()) log(str.error());
	auto str2{am->load<std::string>("test.txt")};
    if (!str2.has_value()) log(str.error());

    std::cout << static_cast<const void*>(str.value().get()) << ' ' <<
        static_cast<const void*>(str2.value().get()) << '\n';

    std::cout << **str << "\n\n";
    std::cout << **str2 << "\n\n";

	return EXIT_SUCCESS;
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	main();
}
#endif

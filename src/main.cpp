#include <Geode/Geode.hpp>
using namespace geode::prelude;




$on_mod(Loaded) {
	auto mod = Mod::get();

	// window icon (code modified from Alphalaneous)
	auto hwnd = FindWindowW(NULL, L"Geometry Dash");

	log::info("type: {}", typeid(hwnd).name());
	auto settingPath = Mod::get()->getSettingValue<std::filesystem::path>("window-icon");

	std::string path = geode::utils::string::pathToString(settingPath);

	HICON hIcon = (HICON)LoadImage(NULL, path.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	// title text
	auto title = mod->getSettingValue<std::string>("window-title");

	auto fixedTitle = title.c_str();

	SetWindowTextA(WindowFromDC(wglGetCurrentDC()), fixedTitle);


	listenForSettingChanges<std::string>("window-title", [](std::string value) {
		auto title = value.c_str();
		SetWindowTextA(WindowFromDC(wglGetCurrentDC()), title);
	}, mod);

	listenForSettingChanges<std::filesystem::path>("window-icon", [](std::filesystem::path value) {

		auto title = Mod::get()->getSettingValue<std::string>("window-title").c_str();

		SetWindowTextA(WindowFromDC(wglGetCurrentDC()), "Geometry Dash");

		auto hwnd = FindWindowW(NULL, L"Geometry Dash");

		SetWindowTextA(WindowFromDC(wglGetCurrentDC()), title);

		auto settingPath = Mod::get()->getSettingValue<std::filesystem::path>("window-icon");

		std::string path = geode::utils::string::pathToString(settingPath);

		HICON hIcon = (HICON)LoadImage(NULL, path.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}, mod);
}


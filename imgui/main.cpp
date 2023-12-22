#include "gui/utils/Gui.h"
#include "imgui/imgui.h"
#include "gui/icons/IconsData.h"
#include "gui/fonts/Custom.h"

#include <thread>

ImFont* Font;
ImFont* CustomImFont;

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	gui::CreateHWindow("Example Ui");
	gui::CreateDevice();
	gui::CreateImGui();

	#pragma region STYLES

	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 3.f;
	style->Colors[ImGuiCol_WindowBg] = RGBtoImVec4(15, 15, 15);
	style->Colors[ImGuiCol_TitleBg] = RGBtoImVec4(124, 94, 214);
	style->Colors[ImGuiCol_TitleBgActive] = RGBtoImVec4(124, 94, 214);

	#pragma endregion    

	#pragma region ICONS
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3;
	icons_config.OversampleV = 3;

	ImFontConfig CustomFont;
	CustomFont.FontDataOwnedByAtlas = false;
	CustomImFont = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 17.5, &CustomFont);;
	Font = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 17.5f, &icons_config, icons_ranges);
	io.Fonts->AddFontDefault();
	#pragma endregion

	while (gui::isRunning)
	{
		gui::BeginRender();
		{
			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize({ gui::WIDTH, gui::HEIGHT });
			ImGui::Begin(
				"Example Ui",
				&gui::isRunning,
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove
			);

			ImGui::Text("%s Example Text with Icon!", ICON_FA_SEARCH);
			ImGui::Text("%s Another Example Text with Icon!", ICON_FA_FIRE);

		}

		ImGui::End();
		gui::EndRender();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}

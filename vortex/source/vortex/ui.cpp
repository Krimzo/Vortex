#include "vortex.h"


vtx::UI::UI(Renderer& renderer)
    : renderer(renderer)
{
	auto& window = renderer.game.system.window;
	auto& gpu = renderer.game.system.gpu;

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(HWND(window));
	ImGui_ImplDX11_Init(gpu.device().get(), gpu.context().get());
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	
	float dpi_scaling = ImGui_ImplWin32_GetDpiScaleForHwnd(HWND(window));
	load_fonts(dpi_scaling);
	load_colors();
}

void vtx::UI::update()
{
	auto& window = renderer.game.system.window;
	auto& gpu = renderer.game.system.gpu;

	gpu.bind_internal_views();
	gpu.set_viewport_size(window.size());
	gpu.clear_internal(renderer.background);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGuiDockNodeFlags_PassthruCentralNode);

	display_log_window();
	display_board_window();
	display_info_window();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void vtx::UI::display_log_window() const
{
	if (ImGui::Begin("Logs", nullptr, ImGuiWindowFlags_NoScrollbar)) {
		if (ImGui::BeginTable("table2", 5, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("Index");
			ImGui::TableNextColumn();
			ImGui::Text("Depth");
			//ImGui::TableNextColumn();
			//ImGui::Text("Calls");
			ImGui::TableNextColumn();
			ImGui::Text("Time");
			ImGui::TableNextColumn();
			ImGui::Text("Evaluation");

			for (size_t i = 0; i < renderer.game.search_results.size(); i++) {
				const auto& result = renderer.game.search_results[i];
				ImGui::TableNextRow();

				ImGui::TableNextColumn();
				ImGui::Text(kl::format(i + 1).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(result.depth).c_str());
				//ImGui::TableNextColumn();
				//ImGui::Text(kl::format(result.calls).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(result.time).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(std::fixed, std::setprecision(2), result.board.evaluation).c_str());
			}
			ImGui::EndTable();
		}

		if (ImGui::Button("Reset board", { -1.0f, 0.0f })) {
			renderer.game.reset();
		}
	}
	ImGui::End();
}

void vtx::UI::display_board_window()
{
	auto& system = renderer.game.system;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	if (ImGui::Begin("Board", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
		const ImVec2 content_region = ImGui::GetContentRegionAvail();
		system.viewport_focused = ImGui::IsWindowFocused();
		system.viewport_top_left = {
			(int) (ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x),
			(int) (ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y),
		};
		system.viewport_size = {
			(int) content_region.x,
			(int) content_region.y,
		};
		ImGui::Image(renderer.target().shader_view.get(), content_region);
	}
	ImGui::End();

	ImGui::PopStyleVar();
}

void vtx::UI::display_info_window() const
{
	auto& game = renderer.game;

	if (ImGui::Begin("Control")) {
		ImGui::Text("Search");
		ImGui::SliderInt("Search depth", &game.search_depth, 1, 7);

		ImGui::Separator();
		
		ImGui::Text("View");
		ImGui::ColorEdit3("Background", &renderer.background.x);

		ImGui::Separator();

		ImGui::Text("Board colors");
		ImGui::ColorEdit3("Default light", &renderer.default_light_color.x);
		ImGui::ColorEdit3("Default dark", &renderer.default_dark_color.x);
		ImGui::ColorEdit3("Selected light", &renderer.selected_light_color.x);
		ImGui::ColorEdit3("Selected dark", &renderer.selected_dark_color.x);
		ImGui::ColorEdit3("Last played light", &renderer.last_played_light_color.x);
		ImGui::ColorEdit3("Last played dark", &renderer.last_played_dark_color.x);
		ImGui::ColorEdit3("Game over light", &renderer.game_over_light_color.x);
		ImGui::ColorEdit3("Game over dark", &renderer.game_over_dark_color.x);

		if (ImGui::Button("Reset colors", { -1.0f, 0.0f })) {
			renderer.reset_colors();
		}
	}
	ImGui::End();
}

void vtx::UI::load_fonts(const float dpi_scaling)
{
	ImFontAtlas* atlas = ImGui::GetIO().Fonts;
	atlas->AddFontFromFileTTF("resource/fonts/roboto.ttf", 18 * dpi_scaling);
	atlas->Build();
}

void vtx::UI::load_colors()
{
	static constexpr kl::Float4 special_color = kl::Float4(1.0f);

	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

	style.Colors[ImGuiCol_Border] = ImVec4(0.45f, 0.45f, 0.45f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.60f, 0.60f, 0.60f, 0.40f);

	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);

	style.Colors[ImGuiCol_CheckMark] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_SliderGrab] = (const ImVec4&) special_color;
	style.Colors[ImGuiCol_SliderGrabActive] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_Button] = style.Colors[ImGuiCol_FrameBg];
	style.Colors[ImGuiCol_ButtonHovered] = style.Colors[ImGuiCol_FrameBgHovered];
	style.Colors[ImGuiCol_ButtonActive] = style.Colors[ImGuiCol_FrameBgActive];

	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);

	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.08f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.35f, 0.35f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_TabSelectedOverline] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_DockingPreview] = (const ImVec4&) special_color;
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.42f, 0.69f, 0.69f, 0.32f);

	style.Colors[ImGuiCol_DragDropTarget] = (const ImVec4&) special_color;

	style.Colors[ImGuiCol_NavHighlight] = (const ImVec4&) special_color;
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 7;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;
}

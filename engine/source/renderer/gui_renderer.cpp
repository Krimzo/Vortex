#include "renderer/gui_renderer.h"

#include "vortex/vortex.h"

#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>


vtx::gui_renderer::gui_renderer(vortex* vortex)
    : vortex_(vortex)
{
	// Init
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(vortex_->window_);
	ImGui_ImplDX11_Init(vortex_->gpu_.device().Get(), vortex_->gpu_.context().Get());
	ImGui::StyleColorsDark();

	// Refs
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	// IO setup
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.Fonts->AddFontFromFileTTF("fonts/JetBrainsMono.ttf", 16);

	// Style sizes
	style.WindowPadding = ImVec2(15.0f, 15.0f);
	style.WindowRounding = 2.0f;
	style.FramePadding = ImVec2(5.0f, 5.0f);
	style.FrameRounding = 2.0f;
	style.ItemSpacing = ImVec2(12.0f, 8.0f);
	style.ItemInnerSpacing = ImVec2(8.0f, 6.0f);
	style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;
	style.PopupBorderSize = 1.0f;
	style.PopupRounding = 5.0f;
	style.ChildBorderSize = 1.0f;
	style.ChildRounding = 5.0f;

	// Style colors
	const ImVec4 colorNone = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	const ImVec4 colorDark = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	const ImVec4 colorMid = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	const ImVec4 colorLight = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	const ImVec4 colorSpec = ImVec4(0.7f, 0.4f, 0.0f, 1.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = colorLight;
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.077f, 0.077f, 0.077f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = colorDark;
	style.Colors[ImGuiCol_PopupBg] = colorDark;
	style.Colors[ImGuiCol_Border] = colorLight;
	style.Colors[ImGuiCol_BorderShadow] = colorMid;
	style.Colors[ImGuiCol_FrameBg] = colorDark;
	style.Colors[ImGuiCol_FrameBgHovered] = colorMid;
	style.Colors[ImGuiCol_FrameBgActive] = colorLight;
	style.Colors[ImGuiCol_TitleBg] = colorDark;
	style.Colors[ImGuiCol_TitleBgActive] = colorDark;
	style.Colors[ImGuiCol_TitleBgCollapsed] = colorDark;
	style.Colors[ImGuiCol_MenuBarBg] = colorDark;
	style.Colors[ImGuiCol_ScrollbarBg] = colorDark;
	style.Colors[ImGuiCol_ScrollbarGrab] = colorLight;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = colorMid;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = colorLight;
	style.Colors[ImGuiCol_CheckMark] = colorSpec;
	style.Colors[ImGuiCol_SliderGrab] = colorSpec;
	style.Colors[ImGuiCol_SliderGrabActive] = colorSpec;
	style.Colors[ImGuiCol_Button] = colorMid;
	style.Colors[ImGuiCol_ButtonHovered] = colorLight;
	style.Colors[ImGuiCol_ButtonActive] = colorLight;
	style.Colors[ImGuiCol_Header] = colorMid;
	style.Colors[ImGuiCol_HeaderHovered] = colorLight;
	style.Colors[ImGuiCol_HeaderActive] = colorSpec;
	style.Colors[ImGuiCol_Separator] = colorMid;
	style.Colors[ImGuiCol_SeparatorHovered] = colorLight;
	style.Colors[ImGuiCol_SeparatorActive] = colorSpec;
	style.Colors[ImGuiCol_ResizeGrip] = colorMid;
	style.Colors[ImGuiCol_ResizeGripHovered] = colorLight;
	style.Colors[ImGuiCol_ResizeGripActive] = colorSpec;
	style.Colors[ImGuiCol_Tab] = colorMid;
	style.Colors[ImGuiCol_TabHovered] = colorSpec;
	style.Colors[ImGuiCol_TabActive] = colorSpec;
	style.Colors[ImGuiCol_TabUnfocused] = colorMid;
	style.Colors[ImGuiCol_TabUnfocusedActive] = colorLight;
	style.Colors[ImGuiCol_DockingPreview] = colorSpec;
	style.Colors[ImGuiCol_DockingEmptyBg] = colorMid;
	style.Colors[ImGuiCol_PlotLines] = colorSpec;
	style.Colors[ImGuiCol_PlotLinesHovered] = colorLight;
	style.Colors[ImGuiCol_PlotHistogram] = colorSpec;
	style.Colors[ImGuiCol_PlotHistogramHovered] = colorLight;
	style.Colors[ImGuiCol_TableHeaderBg] = colorMid;
	style.Colors[ImGuiCol_TableBorderStrong] = colorLight;
	style.Colors[ImGuiCol_TableBorderLight] = colorLight;
	style.Colors[ImGuiCol_TableRowBg] = colorDark;
	style.Colors[ImGuiCol_TableRowBgAlt] = colorMid;
	style.Colors[ImGuiCol_TextSelectedBg] = colorLight;
	style.Colors[ImGuiCol_DragDropTarget] = colorSpec;
	style.Colors[ImGuiCol_NavHighlight] = colorSpec;
	style.Colors[ImGuiCol_NavWindowingHighlight] = colorSpec;
	style.Colors[ImGuiCol_NavWindowingDimBg] = colorMid;
	style.Colors[ImGuiCol_ModalWindowDimBg] = colorMid;
}

vtx::gui_renderer::~gui_renderer()
{}

void vtx::gui_renderer::render()
{
	kl::gpu& gpu = vortex_->gpu_;

	gpu.bind_internal_views();
	gpu.set_viewport_size(vortex_->window_.size());
	gpu.clear_internal(vortex_->background);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

	display_log_window();
	display_board_window();
	display_info_window();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void vtx::gui_renderer::display_log_window()
{
	if (ImGui::Begin("Logs")) {
		if (ImGui::BeginTable("table2", 5, ImGuiTableFlags_Borders)) {
			// First row
			ImGui::TableNextColumn();
			ImGui::Text("Index");
			ImGui::TableNextColumn();
			ImGui::Text("Depth");
			ImGui::TableNextColumn();
			ImGui::Text("Calls");
			ImGui::TableNextColumn();
			ImGui::Text("Time");
			ImGui::TableNextColumn();
			ImGui::Text("Evaluation");

			// Data rows
			for (size_t i = 0; i < vortex_->search_infos_.size(); i++) {
				const search_info info = vortex_->search_infos_[i]; // Copy because of the thread safety
				ImGui::TableNextRow();

				ImGui::TableNextColumn();
				ImGui::Text(kl::format(i + 1).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(info.depth).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(info.calls).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(info.time).c_str());
				ImGui::TableNextColumn();
				ImGui::Text(kl::format(info.eval).c_str());
			}
			ImGui::EndTable();
		}

		if (ImGui::Button("Reset board", { -1.0f, 0.0f })) {
			vortex_->board_ = { default_fen };
			vortex_->search_infos_.clear();
		}
	}
	ImGui::End();
}

void vtx::gui_renderer::display_board_window()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	if (ImGui::Begin("Board", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
		// Pre-display
		const ImVec2 content_region = ImGui::GetContentRegionAvail();
		is_viewport_focused_ = ImGui::IsWindowFocused();
		viewport_top_left_ = {
			(int) (ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x),
			(int) (ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y),
		};
		viewport_size_ = {
			(int) content_region.x,
			(int) content_region.y,
		};

		// Display board
		vortex_->board_renderer_.resize(viewport_size_);
		ImGui::Image(vortex_->board_renderer_.render_texture_.shader_view.Get(), content_region);
	}
	ImGui::End();

	ImGui::PopStyleVar();
}

void vtx::gui_renderer::display_info_window()
{
	if (ImGui::Begin("Control")) {
		ImGui::Text("Search");
		ImGui::Checkbox("Parallel search", &vortex_->parallel_search);
		ImGui::SliderInt("Search depth", &vortex_->search_depth, 1, 7);

		ImGui::Separator();
		
		ImGui::Text("View");
		ImGui::Checkbox("White is bottom", &vortex_->white_is_bottom);
		ImGui::ColorEdit3("Background", vortex_->background);

		ImGui::Separator();

		ImGui::Text("Board colors");
		ImGui::ColorEdit3("Default light", vortex_->board_renderer_.default_light_color_);
		ImGui::ColorEdit3("Default dark", vortex_->board_renderer_.default_dark_color_);
		ImGui::ColorEdit3("Selected light", vortex_->board_renderer_.selected_light_color_);
		ImGui::ColorEdit3("Selected dark", vortex_->board_renderer_.selected_dark_color_);
		ImGui::ColorEdit3("Last played light", vortex_->board_renderer_.last_played_light_color_);
		ImGui::ColorEdit3("Last played dark", vortex_->board_renderer_.last_played_dark_color_);
		ImGui::ColorEdit3("Game over light", vortex_->board_renderer_.game_over_light_color_);
		ImGui::ColorEdit3("Game over dark", vortex_->board_renderer_.game_over_dark_color_);

		if (ImGui::Button("Reset colors", { -1.0f, 0.0f })) {
			vortex_->board_renderer_.reset_colors();
		}
	}
	ImGui::End();
}

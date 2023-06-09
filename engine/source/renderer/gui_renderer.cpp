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
	constexpr auto color_dark = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	constexpr auto color_mid = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	constexpr auto color_light = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	constexpr auto color_spec = ImVec4(0.7f, 0.4f, 0.0f, 1.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = color_light;
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.077f, 0.077f, 0.077f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = color_dark;
	style.Colors[ImGuiCol_PopupBg] = color_dark;
	style.Colors[ImGuiCol_Border] = color_light;
	style.Colors[ImGuiCol_BorderShadow] = color_mid;
	style.Colors[ImGuiCol_FrameBg] = color_dark;
	style.Colors[ImGuiCol_FrameBgHovered] = color_mid;
	style.Colors[ImGuiCol_FrameBgActive] = color_light;
	style.Colors[ImGuiCol_TitleBg] = color_dark;
	style.Colors[ImGuiCol_TitleBgActive] = color_dark;
	style.Colors[ImGuiCol_TitleBgCollapsed] = color_dark;
	style.Colors[ImGuiCol_MenuBarBg] = color_dark;
	style.Colors[ImGuiCol_ScrollbarBg] = color_dark;
	style.Colors[ImGuiCol_ScrollbarGrab] = color_light;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = color_mid;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = color_light;
	style.Colors[ImGuiCol_CheckMark] = color_spec;
	style.Colors[ImGuiCol_SliderGrab] = color_spec;
	style.Colors[ImGuiCol_SliderGrabActive] = color_spec;
	style.Colors[ImGuiCol_Button] = color_mid;
	style.Colors[ImGuiCol_ButtonHovered] = color_light;
	style.Colors[ImGuiCol_ButtonActive] = color_light;
	style.Colors[ImGuiCol_Header] = color_mid;
	style.Colors[ImGuiCol_HeaderHovered] = color_light;
	style.Colors[ImGuiCol_HeaderActive] = color_spec;
	style.Colors[ImGuiCol_Separator] = color_mid;
	style.Colors[ImGuiCol_SeparatorHovered] = color_light;
	style.Colors[ImGuiCol_SeparatorActive] = color_spec;
	style.Colors[ImGuiCol_ResizeGrip] = color_mid;
	style.Colors[ImGuiCol_ResizeGripHovered] = color_light;
	style.Colors[ImGuiCol_ResizeGripActive] = color_spec;
	style.Colors[ImGuiCol_Tab] = color_mid;
	style.Colors[ImGuiCol_TabHovered] = color_spec;
	style.Colors[ImGuiCol_TabActive] = color_spec;
	style.Colors[ImGuiCol_TabUnfocused] = color_mid;
	style.Colors[ImGuiCol_TabUnfocusedActive] = color_light;
	style.Colors[ImGuiCol_DockingPreview] = color_spec;
	style.Colors[ImGuiCol_DockingEmptyBg] = color_mid;
	style.Colors[ImGuiCol_PlotLines] = color_spec;
	style.Colors[ImGuiCol_PlotLinesHovered] = color_light;
	style.Colors[ImGuiCol_PlotHistogram] = color_spec;
	style.Colors[ImGuiCol_PlotHistogramHovered] = color_light;
	style.Colors[ImGuiCol_TableHeaderBg] = color_mid;
	style.Colors[ImGuiCol_TableBorderStrong] = color_light;
	style.Colors[ImGuiCol_TableBorderLight] = color_light;
	style.Colors[ImGuiCol_TableRowBg] = color_dark;
	style.Colors[ImGuiCol_TableRowBgAlt] = color_mid;
	style.Colors[ImGuiCol_TextSelectedBg] = color_light;
	style.Colors[ImGuiCol_DragDropTarget] = color_spec;
	style.Colors[ImGuiCol_NavHighlight] = color_spec;
	style.Colors[ImGuiCol_NavWindowingHighlight] = color_spec;
	style.Colors[ImGuiCol_NavWindowingDimBg] = color_mid;
	style.Colors[ImGuiCol_ModalWindowDimBg] = color_mid;
}

void vtx::gui_renderer::render()
{
	const kl::gpu& gpu = vortex_->gpu_;

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

void vtx::gui_renderer::display_log_window() const
{
	if (ImGui::Begin("Logs", nullptr, ImGuiWindowFlags_NoScrollbar)) {
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

		if (vortex_->input_handler_.lock_.try_lock()) {
			if (ImGui::Button("Reset board", { -1.0f, 0.0f })) {
				vortex_->board_ = { default_fen };
				vortex_->search_infos_.clear();
			}
			vortex_->input_handler_.lock_.unlock();
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

void vtx::gui_renderer::display_info_window() const
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

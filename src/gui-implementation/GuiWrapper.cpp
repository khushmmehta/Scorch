#include "GuiWrapper.h"
#include "imgui/imgui.h"

void ScorchGUI::DragFloat(const char* label, const char* id, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	ImGui::Text("%s", label);
	ImGui::SameLine();
	ImGui::DragFloat(id, v, v_speed, v_min, v_max, format, flags);
}

#pragma once

#include "imgui/imgui.h"

namespace ScorchGUI
{
	void DragFloat(const char* label, const char* id, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.2f", ImGuiSliderFlags flags = 0);
}

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>

class GuiHandler
{
private:
	ImFont* m_Font;

public:
	ImGuiStyle& style;
	ImGuiIO& io;

	GuiHandler(GLFWwindow* window);
	~GuiHandler();

	void SetFont(const std::string& fontLocation, unsigned int fontSize);

	void Start();
	void Render();
	void Destroy();
};

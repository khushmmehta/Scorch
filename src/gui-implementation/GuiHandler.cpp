#include "GuiHandler.h"
#include <GLFW/glfw3.h>

GuiHandler::GuiHandler(GLFWwindow* window) : m_Font(nullptr), io(ImGui::GetIO()), style(ImGui::GetStyle())
{
    io = ImGui::GetIO(); (void)io;               // Cast Dear ImGui Input/Output To Void
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Navigation Flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Navigation Flags
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Use Docking Branch
    ImGui_ImplGlfw_InitForOpenGL(window, true);           // Setup Platform/Renderer Backends
    ImGui_ImplOpenGL3_Init((char*)glGetString(460));      // Setup Platform/Renderer Backends

    style.Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.12f, 0.11f, 0.13f, 0.59f);
    style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.59f);
    style.Colors[ImGuiCol_Border]                 = ImVec4(0.20f, 0.19f, 0.22f, 0.78f);
    style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
    style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.32f, 0.31f, 0.32f, 0.59f);
    style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.40f, 0.40f, 0.40f, 0.59f);
    style.Colors[ImGuiCol_TitleBg]                = ImVec4(1.00f, 0.39f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.12f, 0.11f, 0.13f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.72f, 0.29f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Button]                 = ImVec4(1.00f, 0.47f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(1.00f, 0.39f, 0.00f, 0.78f);
    style.Colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Header]                 = ImVec4(1.00f, 0.39f, 0.00f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(1.00f, 0.39f, 0.00f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Separator]              = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(1.00f, 0.39f, 0.00f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 0.39f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 0.39f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Tab]                    = ImVec4(1.00f, 0.39f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.32f, 0.31f, 0.32f, 0.78f);
    style.Colors[ImGuiCol_TabActive]              = ImVec4(0.12f, 0.11f, 0.13f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.59f, 0.20f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(1.00f, 0.39f, 0.00f, 0.59f);
    style.Colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    style.Colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 0.39f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    style.Colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style.WindowRounding = 8;
    style.ChildRounding = 4;
    style.PopupRounding = 4;
    style.GrabRounding = 4;
    style.FrameRounding = 4;
    style.ScrollbarRounding = 4;
    style.TabRounding = 4;

    style.FrameBorderSize = 1;
    style.SeparatorTextBorderSize = 1;
}

GuiHandler::~GuiHandler()
{
}

void GuiHandler::SetFont(const std::string& fontLocation, unsigned int fontSize)
{
    m_Font = io.Fonts->AddFontFromFileTTF(fontLocation.c_str(), fontSize);
}

void GuiHandler::Start()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::PushFont(m_Font);
}

void GuiHandler::Render()
{
    ImGui::PopFont();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiHandler::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

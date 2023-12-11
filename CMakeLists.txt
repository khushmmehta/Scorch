cmake_minimum_required(VERSION 3.27)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(Scorch)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE_FILES src/Application.cpp
        src/rendering/mesh-objects/IndexBuffer.cpp
        src/rendering/mesh-objects/VertexArray.cpp
        src/rendering/mesh-objects/VertexBuffer.cpp
        src/rendering/Renderer.cpp
        src/rendering/shader-objects/Shader.cpp
        src/rendering/shader-objects/Texture.cpp
        src/glad.c
        src/gui-implementation/GuiHandler.cpp
        src/gui-implementation/GuiWrapper.cpp
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3_loader.h
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h
        src/vendor/stb_image/stb_image.cpp
        src/physics/RigidBody.cpp
        src/physics/RigidBody.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4099")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4099")

include_directories(OpenGL)
include_directories(OpenGL/include)
include_directories(src/vendor)
link_directories(OpenGL/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} glfw3 opengl32 User32 Gdi32 Shell32 ucrtd)
    target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:UCRTD)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_link_libraries(${PROJECT_NAME} glfw3 opengl32 User32 Gdi32 Shell32 ucrt)
    target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:UCRT)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    target_link_libraries(${PROJECT_NAME} glfw3 opengl32 User32 Gdi32 Shell32 ucrt)
    target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:UCRT)
endif ()

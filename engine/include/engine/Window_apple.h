#pragma once

#include "engine/util/defines.h"

#ifdef RENDERER_VULKAN

#include <GLFW/glfw3.h>
#include "engine/util/debug.h"

CREATE_ERROR_CATEGORY(glfw, {
    {1, "Unable to initialize GLFW window"},
	{0, "No error has occurred"},
	{0x00010001, "GLFW has not been initialized"},
	{0x00010002, "No context is current for this thread"},
	{0x00010003, "One of the arguments to the function was an invalid enum value"},
	{0x00010004, "One of the arguments to the function was an invalid value"},
	{0x00010005, "A memory allocation failed"},
	{0x00010006, "GLFW could not find support for the requested API on the system"},
	{0x00010007, "The requested OpenGL or OpenGL ES version is not available"},
	{0x00010008, "A platform-specific error occurred that does not match any of the more specific categories"},
	{0x00010009, "The requested format is not supported or available"},
	{0x0001000A, "The specified window does not have an OpenGL or OpenGL ES context"},
})

struct WindowImpl {
	static void error_callback(int error, const char* description) noexcept;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

	GLFWwindow* window{nullptr};
};

#endif


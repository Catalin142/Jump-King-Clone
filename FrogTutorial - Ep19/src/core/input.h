#pragma once
#include "core/core.h"

#include <unordered_map>

class Window;
struct GLFWwindow;

class Input
{
public:
	static void init(Window* window);

public:
	// true = pressed, false = released
	static std::unordered_map<u32, bool> buttons;

private:
	static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#pragma once
#include "../../imgui/imgui.h"

inline ImVec4 RGBtoImVec4(int red, int green, int blue, int alpha = 255)
{
    ImVec4 color;
    color.x = static_cast<float>(red) / 255.0f;
    color.y = static_cast<float>(green) / 255.0f;
    color.z = static_cast<float>(blue) / 255.0f;
    color.w = static_cast<float>(alpha) / 255.0f;

    return color;
}
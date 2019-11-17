#include "GuiFunctions.h"
#include "IScriptManager.h"
#include "Functions.h"
#include "IGuiManager.h"
#include "LuaGui.h"


void Lua::BindGuiFunctions(sol::state& LuaStateRef)
{
    auto ScriptManager = IocContainer->resolve<IScriptManager>();

    auto GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();
    //GetIO
    //GetStyle
    //NewFrame
    //EndFrame
    //Render
    //GetDrawData

    //ShowDemoWindow(bool* p_open = NULL);    
    //ShowAboutWindow(bool* p_open = NULL);
    //ShowMetricsWindow(bool* p_open = NULL);
    //ShowStyleEditor(ImGuiStyle * ref = NULL);
    //ShowStyleSelector(const char* label);
    //ShowFontSelector(const char* label);
    //ShowUserGuide();
    //GetVersion();

    //StyleColorsDark(ImGuiStyle* dst = NULL);   
    //StyleColorsClassic(ImGuiStyle* dst = NULL);
    //StyleColorsLight(ImGuiStyle* dst = NULL);  

    //Todo: Bind ImVec2
    //Todo: Bind all the enums used by bound functions

    GuiTable["Begin"] = sol::overload(
        [](const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, p_open, flags); },
        //[](const char* name, bool& p_open, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, &p_open, flags); },
        [](std::string& name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, p_open, flags); }//,
        //[](std::string& name, bool& p_open, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, &p_open, flags); }
    );
    GuiTable["End"] = ImGui::End;
    GuiTable["BeginChild"] = sol::overload(
        [](const char* name, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0) { ImGui::BeginChild(name, size, border, flags); },
        [](std::string& name, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0) { ImGui::BeginChild(name.c_str(), size, border, flags); }
    );
    GuiTable["EndChild"] = ImGui::EndChild;


    GuiTable["IsWindowAppearing"] = ImGui::IsWindowAppearing;
    GuiTable["IsWindowCollapsed"] = ImGui::IsWindowCollapsed;
    GuiTable["IsWindowFocused"] = ImGui::IsWindowFocused;
    GuiTable["IsWindowHovered"] = ImGui::IsWindowHovered;
    //GuiTable["GetWindowDrawList"] = ImGui::GetWindowDrawList;
    GuiTable["GetWindowDpiScale"] = ImGui::GetWindowDpiScale;
    //GuiTable["GetWindowViewport"] = ImGui::GetWindowViewport;
    GuiTable["GetWindowPos"] = ImGui::GetWindowPos;
    GuiTable["GetWindowSize"] = ImGui::GetWindowSize;
    GuiTable["GetWindowWidth"] = ImGui::GetWindowWidth;
    GuiTable["GetWindowHeight"] = ImGui::GetWindowHeight;


    GuiTable["SetNextWindowPos"] = ImGui::SetNextWindowPos;
    GuiTable["SetNextWindowSize"] = ImGui::SetNextWindowSize;
    GuiTable["SetNextWindowSizeConstraints"] = ImGui::SetNextWindowSizeConstraints;
    GuiTable["SetNextWindowContentSize"] = ImGui::SetNextWindowContentSize;
    GuiTable["SetNextWindowCollapsed"] = ImGui::SetNextWindowCollapsed;
    GuiTable["SetNextWindowFocus"] = ImGui::SetNextWindowFocus;
    GuiTable["SetNextWindowBgAlpha"] = ImGui::SetNextWindowBgAlpha;
    GuiTable["SetNextWindowViewport"] = ImGui::SetNextWindowViewport;
    GuiTable["SetWindowPos"] = sol::overload(
        [](const char* name, const ImVec2& pos, ImGuiCond cond = 0) { ImGui::SetWindowPos(name, pos, cond); },
        [](std::string& name, const ImVec2& pos, ImGuiCond cond = 0) { ImGui::SetWindowPos(name.c_str(), pos, cond); }
    );
    GuiTable["SetWindowSize"] = sol::overload(
        [](const char* name, const ImVec2& size, ImGuiCond cond = 0) { ImGui::SetWindowSize(name, size, cond); },
        [](std::string& name, const ImVec2& size, ImGuiCond cond = 0) { ImGui::SetWindowSize(name.c_str(), size, cond); }
    );
    GuiTable["SetWindowCollapsed"] = sol::overload(
        [](const char* name, bool collapsed, ImGuiCond cond = 0) { ImGui::SetWindowCollapsed(name, collapsed, cond); },
        [](std::string& name, bool collapsed, ImGuiCond cond = 0) { ImGui::SetWindowCollapsed(name.c_str(), collapsed, cond); }
    );
    GuiTable["SetWindowFocus"] = sol::overload(
        [](const char* name) { ImGui::SetWindowFocus(name); },
        [](std::string& name) { ImGui::SetWindowFocus(name.c_str()); }
    );
    GuiTable["SetWindowFontScale"] = ImGui::SetWindowFontScale;


    GuiTable["GetScrollX"] = ImGui::GetScrollX;
    GuiTable["GetScrollY"] = ImGui::GetScrollY;
    GuiTable["GetScrollMaxX"] = ImGui::GetScrollMaxX;
    GuiTable["GetScrollMaxY"] = ImGui::GetScrollMaxY;
    GuiTable["SetScrollX"] = ImGui::SetScrollX;
    GuiTable["SetScrollY"] = ImGui::SetScrollY;
    GuiTable["SetScrollHereY"] = ImGui::SetScrollHereY;
    GuiTable["SetScrollFromPosY"] = ImGui::SetScrollFromPosY;

    GuiTable["PushFont"] = ImGui::PushFont;
    GuiTable["PopFont"] = ImGui::PopFont;
    GuiTable["PushStyleColor"] = sol::overload(
        [](ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); },
        [](ImGuiCol idx, const ImVec4& col) { ImGui::PushStyleColor(idx, col); }
    );
    GuiTable["PopStyleColor"] = ImGui::PopStyleColor;
    GuiTable["PushStyleVar"] = sol::overload(
        [](ImGuiStyleVar idx, float val) { ImGui::PushStyleVar(idx, val); },
        [](ImGuiStyleVar idx, const ImVec2& val) { ImGui::PushStyleVar(idx, val); }
    );
    GuiTable["PopStyleVar"] = ImGui::PopStyleVar;
    GuiTable["GetStyleColorVec4"] = ImGui::GetStyleColorVec4;
    GuiTable["GetFont"] = ImGui::GetFont;
    GuiTable["GetFontSize"] = ImGui::GetFontSize;
    GuiTable["GetFontTexUvWhitePixel"] = ImGui::GetFontTexUvWhitePixel;
    GuiTable["GetColorU32"] = sol::overload(
        [](ImGuiCol idx, float alpha_mul = 1.0f) { ImGui::GetColorU32(idx, alpha_mul); },
        [](const ImVec4& col) { ImGui::GetColorU32(col); }
    );


    GuiTable["PushItemWidth"] = ImGui::PushItemWidth;
    GuiTable["PopItemWidth"] = ImGui::PopItemWidth;
    GuiTable["SetNextItemWidth"] = ImGui::SetNextItemWidth;
    GuiTable["CalcItemWidth"] = ImGui::CalcItemWidth;
    GuiTable["PushTextWrapPos"] = ImGui::PushTextWrapPos;
    GuiTable["PopTextWrapPos"] = ImGui::PopTextWrapPos;
    GuiTable["PushAllowKeyboardFocus"] = ImGui::PushAllowKeyboardFocus;
    GuiTable["PopAllowKeyboardFocus"] = ImGui::PopAllowKeyboardFocus;
    GuiTable["PushButtonRepeat"] = ImGui::PushButtonRepeat;
    GuiTable["PopButtonRepeat"] = ImGui::PopButtonRepeat;


    GuiTable["Separator"] = ImGui::Separator;
    GuiTable["SameLine"] = ImGui::SameLine;
    GuiTable["NewLine"] = ImGui::NewLine;
    GuiTable["Spacing"] = ImGui::Spacing;
    GuiTable["Dummy"] = ImGui::Dummy;
    GuiTable["Indent"] = ImGui::Indent;
    GuiTable["Unindent"] = ImGui::Unindent;
    GuiTable["BeginGroup"] = ImGui::BeginGroup;
    GuiTable["EndGroup"] = ImGui::EndGroup;
    GuiTable["GetCursorPos"] = ImGui::GetCursorPos;
    GuiTable["GetCursorPosX"] = ImGui::GetCursorPosX;
    GuiTable["GetCursorPosY"] = ImGui::GetCursorPosY;
    GuiTable["SetCursorPos"] = ImGui::SetCursorPos;
    GuiTable["SetCursorPosX"] = ImGui::SetCursorPosX;
    GuiTable["SetCursorPosY"] = ImGui::SetCursorPosY;
    GuiTable["GetCursorStartPos"] = ImGui::GetCursorStartPos;
    GuiTable["GetCursorScreenPos"] = ImGui::GetCursorScreenPos;
    GuiTable["SetCursorScreenPos"] = ImGui::SetCursorScreenPos;
    GuiTable["AlignTextToFramePadding"] = ImGui::AlignTextToFramePadding;
    GuiTable["GetTextLineHeight"] = ImGui::GetTextLineHeight;
    GuiTable["GetTextLineHeightWithSpacing"] = ImGui::GetTextLineHeightWithSpacing;
    GuiTable["GetFrameHeight"] = ImGui::GetFrameHeight;
    GuiTable["GetFrameHeightWithSpacing"] = ImGui::GetFrameHeightWithSpacing;


    //PushID, PopID, GetID overloads


    GuiTable["TextUnformatted"] = ImGui::TextUnformatted;
    GuiTable["Text"] = sol::overload(
        [](const char* text) { ImGui::Text(text); },
        [](std::string& text) { ImGui::Text(text.c_str()); }
    );
    GuiTable["TextColored"] = sol::overload(
        [](const char* text, ImVec4 color) { ImGui::TextColored(color, text); },
        [](const char* text, float r, float g, float b) { ImGui::TextColored(ImVec4(r, g, b, 1.0f), text); },

        [](std::string& text, ImVec4 color) { ImGui::TextColored(color, text.c_str()); },
        [](std::string& text, float r, float g, float b) { ImGui::TextColored(ImVec4(r, g, b, 1.0f), text.c_str()); }
    );
    GuiTable["TextWrapped"] = sol::overload(
        [](const char* text) { ImGui::TextWrapped(text); },
        [](std::string& text) { ImGui::TextWrapped(text.c_str()); }
    );
    GuiTable["LabelText"] = sol::overload(
        [](const char* label, const char* text) { ImGui::LabelText(text, label); },
        [](std::string& label, std::string& text) { ImGui::LabelText(text.c_str(), label.c_str()); }
    );
    GuiTable["BulletText"] = sol::overload(
        [](const char* text) { ImGui::BulletText(text); },
        [](std::string& text) { ImGui::BulletText(text.c_str()); }
    );

    //Todo: Bind button
    GuiTable["Button"] = sol::overload(
        [](const char* Label, const ImVec2& Size = {0, 0})
        { return ImGui::Button(Label, Size); },
        [](const char* Label)
        { return ImGui::Button(Label, {0, 0}); },

        [](std::string& Label, const ImVec2& Size = {0, 0})
        { return ImGui::Button(Label, Size); },
        [](std::string& Label)
        { return ImGui::Button(Label, {0, 0}); }
    );
    GuiTable["SmallButton"] = ImGui::SmallButton;
    GuiTable["InvisibleButton"] = ImGui::InvisibleButton;
    GuiTable["ArrowButton"] = ImGui::ArrowButton;
    GuiTable["Image"] = ImGui::Image;
    GuiTable["ImageButton"] = ImGui::ImageButton;
    GuiTable["Checkbox"] = ImGui::Checkbox;
    GuiTable["CheckboxFlags"] = ImGui::CheckboxFlags;
    GuiTable["RadioButton"] = sol::overload(
        [](const char* label, bool active) { ImGui::RadioButton(label, active); },
        [](const char* label, int* v, int v_button) { ImGui::RadioButton(label, v, v_button); }
    );
    GuiTable["ProgressBar"] = ImGui::ProgressBar;
    GuiTable["Bullet"] = ImGui::Bullet;


    //Combo


    GuiTable["DragFloat"] = sol::overload(
        [](const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, power); },

        [](std::string& label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat(label.c_str(), v, v_speed, v_min, v_max, format, power); }//,

        //[](const char* label, float& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, power); }//,

        //[](std::string& label, float& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max, format, power); }
    );
    GuiTable["DragFloat2"] = sol::overload(
        [](const char* label, vector2* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat2(label, (float*)v, v_speed, v_min, v_max, format, power); },

        [](std::string& label, vector2* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat2(label.c_str(), (float*)v, v_speed, v_min, v_max, format, power); }//,

        //[](const char* label, vector2& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat2(label, (float*)&v, v_speed, v_min, v_max, format, power); },

        //[](std::string& label, vector2& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power); }
    );
    GuiTable["DragFloat3"] = sol::overload(
        [](const char* label, vector* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat3(label, (float*)v, v_speed, v_min, v_max, format, power); },

        [](std::string& label, vector* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        { ImGui::DragFloat3(label.c_str(), (float*)v, v_speed, v_min, v_max, format, power); }//,

        //[](const char* label, vector& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat3(label, (float*)&v, v_speed, v_min, v_max, format, power); },

        //[](std::string& label, vector& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power); }
    );
    ////DragFloat4
    ////DragFloatRange2
    GuiTable["DragInt"] = sol::overload(
        [](const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d")
        { ImGui::DragInt(label, v, v_speed, v_min, v_max, format); },

        [](std::string& label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d")
        { ImGui::DragInt(label.c_str(), v, v_speed, v_min, v_max, format); }//,

        //[](const char* label, int& v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d")
        //{ ImGui::DragInt(label, &v, v_speed, v_min, v_max, format); },

        //[](std::string& label, int& v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d")
        //{ ImGui::DragInt(label.c_str(), &v, v_speed, v_min, v_max, format); }
    );
    //DragInt2
    //DragInt3
    //DragInt4
    //DragIntRange2
    //DragScalar
    //DragScalarN


    GuiTable["SliderFloat"] = sol::overload(
        [](const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat(label, v, v_min, v_max, format, power); },

        [](std::string& label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat(label.c_str(), v, v_min, v_max, format, power); }//,

        //[](const char* label, float& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat(label, &v, v_min, v_max, format, power); },

        //[](std::string& label, float& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat(label.c_str(), &v, v_min, v_max, format, power); }
    );
    GuiTable["SliderFloat2"] = sol::overload(
        [](const char* label, vector2* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat2(label, (float*)v, v_min, v_max, format, power); },

        [](std::string& label, vector2* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat2(label.c_str(), (float*)v, v_min, v_max, format, power); }//,

        //[](const char* label, vector2& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat2(label, (float*)&v, v_min, v_max, format, power); },

        //[](std::string& label, vector2& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat2(label.c_str(), (float*)&v, v_min, v_max, format, power); }
    );
    GuiTable["SliderFloat3"] = sol::overload(
        [](const char* label, vector* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat3(label, (float*)v, v_min, v_max, format, power); },

        [](std::string& label, vector* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        { ImGui::SliderFloat3(label.c_str(), (float*)v, v_min, v_max, format, power); }//,

        //[](const char* label, vector& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat3(label, (float*)&v, v_min, v_max, format, power); },

        //[](std::string& label, vector& v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f)
        //{ ImGui::SliderFloat3(label.c_str(), (float*)&v, v_min, v_max, format, power); }
    );
    GuiTable["SliderAngle"] = sol::overload(
        [](const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg")
        { ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max, format); },

        [](std::string& label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg")
        { ImGui::SliderAngle(label.c_str(), v_rad, v_degrees_min, v_degrees_max, format); }
    );
    GuiTable["SliderInt"] = sol::overload(
        [](const char* label, int* v, int v_min, int v_max, const char* format = "%d")
        { ImGui::SliderInt(label, v, v_min, v_max, format); },

        [](std::string& label, int* v, int v_min, int v_max, const char* format = "%d")
        { ImGui::SliderInt(label.c_str(), v, v_min, v_max, format); }
    );
    //SliderInt2
    //SliderInt3
    //SliderInt4
    //SliderScalar
    //SliderScalarN
    //VSliderFloat
    //VSliderInt
    //VSliderScalar


    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;
    //GuiTable[""] = ImGui::;

    GuiTable["MakeGui"] = [](std::string& GuiName, const sol::function& DrawFunc)
    {
        static auto GuiManager = IocContainer->resolve<IGuiManager>();
        auto NewGui = new LuaGui(GuiName, DrawFunc);
        GuiManager->AddChildGui(NewGui);
        return NewGui;
    };
}

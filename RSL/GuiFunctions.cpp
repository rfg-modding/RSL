#include "GuiFunctions.h"
#include "IScriptManager.h"
#include "Functions.h"
#include "IGuiManager.h"
#include "LuaGui.h"


void Lua::BindGuiFunctions(sol::state& LuaStateRef)
{
#if LUA_ENABLED
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
    //Todo: See if all the std::string overloads are necessary at all
    //Todo: Figure out when to use ptrs and when to use references for edit gui elements

    //GuiTable["Begin"] = sol::overload(
    //    [](const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, p_open, flags); },
    //    //[](const char* name, bool& p_open, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, &p_open, flags); },
    //    [](std::string& name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, p_open, flags); }//,
    //    //[](std::string& name, bool& p_open, ImGuiWindowFlags flags = 0) { ImGui::Begin(name, &p_open, flags); }
    //);
    //GuiTable["End"] = ImGui::End;
    GuiTable["BeginChild"] = sol::overload(
        [](std::string& name) 
        { ImGui::BeginChild(name.c_str()); },
        [](std::string& name, const ImVec2& size) 
        { ImGui::BeginChild(name.c_str(), size); },
        [](std::string& name, const ImVec2& size, bool border) 
        { ImGui::BeginChild(name.c_str(), size, border); },
        [](std::string& name, const ImVec2& size, bool border, ImGuiWindowFlags flags) 
        { ImGui::BeginChild(name.c_str(), size, border, flags); }
    );
    GuiTable["EndChild"] = ImGui::EndChild;


    GuiTable["IsWindowAppearing"] = ImGui::IsWindowAppearing;
    GuiTable["IsWindowCollapsed"] = ImGui::IsWindowCollapsed;
    GuiTable["IsWindowFocused"] = sol::overload(
        []() { ImGui::IsWindowFocused(); },
        [](ImGuiFocusedFlags flags) { ImGui::IsWindowFocused(flags); }
    );
    GuiTable["IsWindowHovered"] = sol::overload(
        []() { ImGui::IsWindowHovered(); },
        [](ImGuiHoveredFlags flags) { ImGui::IsWindowHovered(flags); }
    );
    //GuiTable["GetWindowDrawList"] = ImGui::GetWindowDrawList;
    GuiTable["GetWindowDpiScale"] = ImGui::GetWindowDpiScale;
    //GuiTable["GetWindowViewport"] = ImGui::GetWindowViewport;
    GuiTable["GetWindowPos"] = ImGui::GetWindowPos;
    GuiTable["GetWindowSize"] = ImGui::GetWindowSize;
    GuiTable["GetWindowWidth"] = ImGui::GetWindowWidth;
    GuiTable["GetWindowHeight"] = ImGui::GetWindowHeight;


    GuiTable["SetNextWindowPos"] = sol::overload(
        [](const ImVec2& pos) { ImGui::SetNextWindowPos(pos); },
        [](float x, float y) { ImGui::SetNextWindowPos(ImVec2(x, y)); },

        [](const ImVec2& pos, ImGuiCond cond) { ImGui::SetNextWindowPos(pos, cond); },
        [](float x, float y, ImGuiCond cond) { ImGui::SetNextWindowPos(ImVec2(x, y), cond); },

        [](const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot)
        { ImGui::SetNextWindowPos(pos, cond, pivot); },
        [](float posx, float posy, ImGuiCond cond, float pivotx, float pivoty)
        { ImGui::SetNextWindowPos(ImVec2(posx, posy), cond, ImVec2(pivotx, pivoty)); }
    );
    GuiTable["SetNextWindowSize"] = sol::overload(
        [](const ImVec2& size) { ImGui::SetNextWindowSize(size); },
        [](float x, float y) { ImGui::SetNextWindowSize(ImVec2(x, y)); },

        [](const ImVec2& size, ImGuiCond cond) { ImGui::SetNextWindowSize(size, cond); },
        [](float x, float y, ImGuiCond cond) { ImGui::SetNextWindowSize(ImVec2(x, y), cond); }
    );
    GuiTable["SetNextWindowSizeConstraints"] = sol::overload(
        [](const ImVec2& size_min, const ImVec2& size_max) 
        { ImGui::SetNextWindowSizeConstraints(size_min, size_max); },
        [](float minx, float miny, const ImVec2& size_max) 
        { ImGui::SetNextWindowSizeConstraints(ImVec2(minx, miny), size_max); },
        [](const ImVec2& size_min, float maxx, float maxy) 
        { ImGui::SetNextWindowSizeConstraints(size_min, ImVec2(maxx, maxy)); },
        [](float minx, float miny, float maxx, float maxy) 
        { ImGui::SetNextWindowSizeConstraints(ImVec2(minx, miny), ImVec2(maxx, maxy)); }

    );
    GuiTable["SetNextWindowContentSize"] = ImGui::SetNextWindowContentSize;
    GuiTable["SetNextWindowCollapsed"] = sol::overload(
        [](bool collapsed) {ImGui::SetNextWindowCollapsed(collapsed); },
        [](bool collapsed, ImGuiCond cond) {ImGui::SetNextWindowCollapsed(collapsed, cond); }
    );
    GuiTable["SetNextWindowFocus"] = ImGui::SetNextWindowFocus;
    GuiTable["SetNextWindowBgAlpha"] = ImGui::SetNextWindowBgAlpha;
    GuiTable["SetNextWindowViewport"] = ImGui::SetNextWindowViewport;
    GuiTable["SetWindowPos"] = sol::overload(
        [](std::string& name, const ImVec2& pos, ImGuiCond cond) { ImGui::SetWindowPos(name.c_str(), pos, cond); },
        [](std::string& name, const ImVec2& pos) { ImGui::SetWindowPos(name.c_str(), pos); }
    );
    GuiTable["SetWindowSize"] = sol::overload(
        [](std::string& name, const ImVec2& size) { ImGui::SetWindowSize(name.c_str(), size); },
        [](std::string& name, const ImVec2& size, ImGuiCond cond) { ImGui::SetWindowSize(name.c_str(), size, cond); }
    );
    GuiTable["SetWindowCollapsed"] = sol::overload(
        [](std::string& name, bool collapsed) { ImGui::SetWindowCollapsed(name.c_str(), collapsed); },
        [](std::string& name, bool collapsed, ImGuiCond cond) { ImGui::SetWindowCollapsed(name.c_str(), collapsed, cond); }
    );
    GuiTable["SetWindowFocus"] = [](std::string& name) { ImGui::SetWindowFocus(name.c_str()); };
    GuiTable["SetWindowFontScale"] = ImGui::SetWindowFontScale;


    GuiTable["GetScrollX"] = ImGui::GetScrollX;
    GuiTable["GetScrollY"] = ImGui::GetScrollY;
    GuiTable["GetScrollMaxX"] = ImGui::GetScrollMaxX;
    GuiTable["GetScrollMaxY"] = ImGui::GetScrollMaxY;
    GuiTable["SetScrollX"] = ImGui::SetScrollX;
    GuiTable["SetScrollY"] = ImGui::SetScrollY;
    GuiTable["SetScrollHereY"] = sol::overload(
        []() { ImGui::SetScrollHereY(); },
        [](float center_y_ration) { ImGui::SetScrollHereY(center_y_ration); }
    );
    GuiTable["SetScrollFromPosY"] = sol::overload(
        [](float local_y) { ImGui::SetScrollFromPosY(local_y); },
        [](float local_y, float center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); }
    );

    //Todo: Add FontManager and way for lua to get/add/remove/use different fonts
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
        [](ImGuiCol idx, float alpha_mul) { ImGui::GetColorU32(idx, alpha_mul); },
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
    GuiTable["SameLine"] = sol::overload(
        []() { ImGui::SameLine(); },
        [](float offset_from_start_x) { ImGui::SameLine(offset_from_start_x); },
        [](float offset_from_start_x, float spacing) { ImGui::SameLine(offset_from_start_x, spacing); }
    );
    GuiTable["NewLine"] = ImGui::NewLine;
    GuiTable["Spacing"] = ImGui::Spacing;
    GuiTable["Dummy"] = ImGui::Dummy;
    GuiTable["Indent"] = sol::overload(
        []() {ImGui::Indent(); },
        [](float indent_w) {ImGui::Indent(indent_w); }
    );
    GuiTable["Unindent"] = sol::overload(
        []() {ImGui::Unindent(); },
        [](float indent_w) {ImGui::Unindent(indent_w); }
    );
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
    GuiTable["Text"] = [](std::string& text) { ImGui::Text(text.c_str()); };
    GuiTable["TextColored"] = sol::overload(
        [](std::string& text, ImVec4 color) { ImGui::TextColored(color, text.c_str()); },
        [](std::string& text, float r, float g, float b) { ImGui::TextColored(ImVec4(r, g, b, 1.0f), text.c_str()); }
    );
    GuiTable["TextWrapped"] = [](std::string& text) { ImGui::TextWrapped(text.c_str()); };
    GuiTable["LabelText"] = [](std::string& label, std::string& text) { ImGui::LabelText(text.c_str(), label.c_str()); };
    GuiTable["BulletText"] = [](std::string& text) { ImGui::BulletText(text.c_str()); };

    //Todo: Bind button
    GuiTable["Button"] = sol::overload(
        [](std::string& Label, const ImVec2& Size = {0, 0})
        { return ImGui::Button(Label, Size); },
        [](std::string& Label)
        { return ImGui::Button(Label, {0, 0}); }
    );
    GuiTable["SmallButton"] = ImGui::SmallButton;
    GuiTable["InvisibleButton"] = ImGui::InvisibleButton;
    GuiTable["ArrowButton"] = ImGui::ArrowButton;
    //Todo: Add way to load/manage/select textures with lua. Ideally could use a Image + transparent window for additions to game hud
    GuiTable["Image"] = ImGui::Image;
    GuiTable["ImageButton"] = ImGui::ImageButton;
    GuiTable["Checkbox"] = [](std::string& label, bool* v) { ImGui::Checkbox(label.c_str(), v); };
    GuiTable["CheckboxFlags"] = ImGui::CheckboxFlags; //Todo: Make sure this is working
    GuiTable["RadioButton"] = sol::overload(
        [](std::string& label, bool active) { ImGui::RadioButton(label.c_str(), active); },
        [](std::string& label, int v, int v_button)
        {
            ImGui::RadioButton(label.c_str(), &v, v_button);
            return v;
        }
    );
    GuiTable["ProgressBar"] = sol::overload(
        [](float fraction)
        { ImGui::ProgressBar(fraction); },

        [](float fraction, const ImVec2& size_arg)
        { ImGui::ProgressBar(fraction, size_arg); },
        [](float fraction, float size_x, float size_y)
        { ImGui::ProgressBar(fraction, ImVec2(size_x, size_y)); },

        [](float fraction, float size_x, float size_y, const char* overlay)
        { ImGui::ProgressBar(fraction, ImVec2(size_x, size_y), overlay); }
    );
    GuiTable["Bullet"] = ImGui::Bullet;


    //Combo

    GuiTable["DragFloat"] = [](std::string& label, float v)
    {
        ImGui::DragFloat(label.c_str(), &v);
        return v;
    };

    GuiTable["DragFloat"] = sol::overload(
        [](std::string& label, float v)
        {
            ImGui::DragFloat(label.c_str(), &v);
            return v;
        },
        [](std::string& label, float v, float v_speed)
        {
            ImGui::DragFloat(label.c_str(), &v, v_speed);
            return v;
        },
        [](std::string& label, float v, float v_speed, float v_min)
        {
            ImGui::DragFloat(label.c_str(), &v, v_speed, v_min);
            return v;
        },
        [](std::string& label, float v, float v_speed, float v_min, float v_max)
        {
            ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max);
            return v;
        },        
        [](std::string& label, float v, float v_speed, float v_min, float v_max, const char* format)
        {
            ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max, format);
            return v;
        },
        [](std::string& label, float v, float v_speed, float v_min, float v_max, const char* format, float power)
        {
            ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max, format, power);
            return v;
        }
    );
    GuiTable["DragFloat2"] = sol::overload(
        [](std::string& label, vector2& v)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v);
        },
        [](std::string& label, vector2& v, float v_speed)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed);
        },
        [](std::string& label, vector2& v, float v_speed, float v_min)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min);
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max);
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max, const char* format)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max, format);
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max, const char* format, float power)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power);
        }
    );
    GuiTable["DragFloat3"] = sol::overload(
        [](std::string& label, vector& v)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v);
        },
        [](std::string& label, vector& v, float v_speed)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed);
        },
        [](std::string& label, vector& v, float v_speed, float v_min)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min);
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max);
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max, const char* format)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max, format);
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max, const char* format, float power)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power);
        }
    );
    ////DragFloat4
    ////DragFloatRange2
    GuiTable["DragInt"] = sol::overload(
        [](std::string& label, int v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d")
        {
            ImGui::DragInt(label.c_str(), &v, v_speed, v_min, v_max, format);
            return v;
        }
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
#endif
}

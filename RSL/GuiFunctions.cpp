#include "GuiFunctions.h"
#include "IScriptManager.h"
#include "Functions.h"
#include "IGuiManager.h"
#include "LuaGui.h"


void Lua::BindImVec2(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    auto GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();

    auto Utype = GuiTable.create_simple_usertype<ImVec2>();
    Utype.set("new", sol::constructors <ImVec2(), ImVec2(float, float), ImVec2(const ImVec2&), ImVec2(ImVec2&&)>());
    Utype.set("x", &ImVec2::x);
    Utype.set("y", &ImVec2::y);
    GuiTable.set_usertype("ImVec2", Utype);
#endif
}

void Lua::BindImVec4(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    auto GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();

    auto Utype = GuiTable.create_simple_usertype<ImVec4>();
    Utype.set("new", sol::constructors <ImVec4(), ImVec4(float, float, float, float), ImVec4(const ImVec4&), ImVec4(ImVec4&&)>());
    Utype.set("x", &ImVec4::x);
    Utype.set("y", &ImVec4::y);
    Utype.set("z", &ImVec4::z);
    Utype.set("w", &ImVec4::w);
    GuiTable.set_usertype("ImVec4", Utype);
#endif
}

//Todo: Bind all the enums used by bound functions
//Todo: Check ImGui bindings return values and make sure they're correct
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
    GuiTable["PopStyleColor"] = sol::overload(
        []()
        {
            ImGui::PopStyleColor(1);
        },
        [](int count)
        {
            ImGui::PopStyleColor(count);
        }
    );
    GuiTable["PushStyleVar"] = sol::overload(
        [](ImGuiStyleVar idx, float val) { ImGui::PushStyleVar(idx, val); },
        [](ImGuiStyleVar idx, const ImVec2& val) { ImGui::PushStyleVar(idx, val); }
    );
    GuiTable["PopStyleVar"] = sol::overload(
        []()
        {
            ImGui::PopStyleVar(1);
        },
        [](int count)
        {
            ImGui::PopStyleVar(count);
        }
    );
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
        [](std::string& text, ImVec4& color) { ImGui::TextColored(color, text.c_str()); },
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
    GuiTable["Checkbox"] = [](std::string& label, bool v)
    {
        ImGui::Checkbox(label.c_str(), &v);
        return v;
    };
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
            return v;
        },
        [](std::string& label, vector2& v, float v_speed)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed);
            return v;
        },
        [](std::string& label, vector2& v, float v_speed, float v_min)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min);
            return v;
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max);
            return v;
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max, const char* format)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max, format);
            return v;
        },
        [](std::string& label, vector2& v, float v_speed, float v_min, float v_max, const char* format, float power)
        {
            ImGui::DragFloat2(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power);
            return v;
        }
    );
    GuiTable["DragFloat3"] = sol::overload(
        [](std::string& label, vector& v)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v);
            return v;
        },
        [](std::string& label, vector& v, float v_speed)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed);
            return v;
        },
        [](std::string& label, vector& v, float v_speed, float v_min)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min);
            return v;
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max);
            return v;
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max, const char* format)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max, format);
            return v;
        },
        [](std::string& label, vector& v, float v_speed, float v_min, float v_max, const char* format, float power)
        {
            ImGui::DragFloat3(label.c_str(), (float*)&v, v_speed, v_min, v_max, format, power);
            return v;
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
        [](std::string& label, float v, float v_min, float v_max)
        {
            ImGui::SliderFloat(label.c_str(), &v, v_min, v_max);
            return v;
        },
        [](std::string& label, float v, float v_min, float v_max, std::string& format)
        {
            ImGui::SliderFloat(label.c_str(), &v, v_min, v_max, format.c_str());
            return v;
        },
        [](std::string& label, float v, float v_min, float v_max, std::string& format, float power)
        {
            ImGui::SliderFloat(label.c_str(), &v, v_min, v_max, format.c_str(), power);
            return v;
        }
    );
    GuiTable["SliderFloat2"] = sol::overload(
        [](std::string& label, vector2& v, float v_min, float v_max)
        {
            ImGui::SliderFloat2(label.c_str(), (float*)&v, v_min, v_max);
            return v;
        },
        [](std::string& label, vector2& v, float v_min, float v_max, std::string& format)
        {
            ImGui::SliderFloat2(label.c_str(), (float*)&v, v_min, v_max, format.c_str());
            return v;
        },
        [](std::string& label, vector2& v, float v_min, float v_max, std::string& format, float power)
        {
            ImGui::SliderFloat2(label.c_str(), (float*)&v, v_min, v_max, format.c_str(), power);
            return v;
        }
    );
    GuiTable["SliderFloat3"] = sol::overload(
        [](std::string& label, vector& v, float v_min, float v_max)
        {
            ImGui::SliderFloat3(label.c_str(), (float*)&v, v_min, v_max);
            return v;
        },
        [](std::string& label, vector& v, float v_min, float v_max, std::string& format)
        {
            ImGui::SliderFloat3(label.c_str(), (float*)&v, v_min, v_max, format.c_str());
            return v;
        },
        [](std::string& label, vector& v, float v_min, float v_max, std::string& format, float power)
        {
            ImGui::SliderFloat3(label.c_str(), (float*)&v, v_min, v_max, format.c_str(), power);
            return v;
        }
    );
    GuiTable["SliderAngle"] = sol::overload(
        [](std::string& label, float v_rad)
        {
            ImGui::SliderAngle(label.c_str(), &v_rad);
            return v_rad;
        },
        [](std::string& label, float v_rad, float v_degrees_min)
        {
            ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min);
            return v_rad;
        },
        [](std::string& label, float v_rad, float v_degrees_min, float v_degrees_max)
        {
            ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min, v_degrees_max);
            return v_rad;
        },
        [](std::string& label, float v_rad, float v_degrees_min, float v_degrees_max, std::string& format)
        {
            ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min, v_degrees_max, format.c_str());
            return v_rad;
        }
    );
    GuiTable["SliderInt"] = sol::overload(
        [](std::string& label, int v, int v_min, int v_max, std::string& format)
        {
            ImGui::SliderInt(label.c_str(), &v, v_min, v_max, format.c_str());
            return v;
        },
        [](std::string& label, int v, int v_min, int v_max)
        {
            ImGui::SliderInt(label.c_str(), &v, v_min, v_max);
            return v;
        }
    );
    //Todo: Don't need to implement int2/int3 types quite yet since they aren't used much by rfg
    //SliderInt2
    //SliderInt3
    //SliderInt4
    //SliderScalar
    //SliderScalarN
    //VSliderFloat
    //VSliderInt
    //VSliderScalar

    //Todo: Implement these InputText variants
    //GuiTable["InputText"] = sol::overload(
    //    [](std::string& label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL)
    //    {
    //        
    //    }
    //);
    //InputTextMultiline
    //InputTextWithHint

    GuiTable["InputFloat"] = sol::overload(
        [](std::string& label, float v)
        {
            ImGui::InputFloat(label.c_str(), &v, 0.01f, 0.1, 3);
            return v;
        },
        [](std::string& label, float v, float step)
        {
            ImGui::InputFloat(label.c_str(), &v, step, 0.1, 3);
            return v;
        },
        [](std::string& label, float v, float step, float step_fast)
        {
            ImGui::InputFloat(label.c_str(), &v, step, step_fast, 3);
            return v;
        },
        [](std::string& label, float v, float step, float step_fast, int decimal_precision)
        {
            ImGui::InputFloat(label.c_str(), &v, step, step_fast, decimal_precision);
            return v;
        },
        [](std::string& label, float v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags flags)
        {
            ImGui::InputFloat(label.c_str(), &v, step, step_fast, decimal_precision, flags);
            return v;
        }
    );
    GuiTable["InputFloat2"] = sol::overload(
        [](std::string& label, vector2& v)
        {
            ImGui::InputFloat2(label.c_str(), (float*)&v);
            return v;
        },
        [](std::string& label, vector2& v, std::string& format)
        {
            ImGui::InputFloat2(label.c_str(), (float*)&v, format.c_str());
            return v;
        },
        [](std::string& label, vector2& v, std::string& format, ImGuiInputTextFlags flags)
        {
            ImGui::InputFloat2(label.c_str(), (float*)&v, format.c_str(), flags);
            return v;
        }
    );
    GuiTable["InputFloat3"] = sol::overload(
        [](std::string& label, vector& v)
        {
            ImGui::InputFloat3(label.c_str(), (float*)&v);
            return v;
        },
        [](std::string& label, vector& v, std::string& format)
        {
            ImGui::InputFloat3(label.c_str(), (float*)&v, format.c_str());
            return v;
        },
        [](std::string& label, vector& v, std::string& format, ImGuiInputTextFlags flags)
        {
            ImGui::InputFloat3(label.c_str(), (float*)&v, format.c_str(), flags);
            return v;
        }
    );
    //InputFloat4

    GuiTable["InputInt"] = sol::overload(
        [](std::string& label, int v)
        {
            ImGui::InputInt(label.c_str(), &v);
            return v;
        },
        [](std::string& label, int v, int step)
        {
            ImGui::InputInt(label.c_str(), &v, step);
            return v;
        },
        [](std::string& label, int v, int step, int step_fast)
        {
            ImGui::InputInt(label.c_str(), &v, step, step_fast);
            return v;
        },
        [](std::string& label, int v, int step, int step_fast, ImGuiInputTextFlags flags)
        {
            ImGui::InputInt(label.c_str(), &v, step, step_fast, flags);
            return v;
        }
    );
    //InputInt2
    //InputInt3
    //InputInt4
    //InputDouble
    GuiTable["InputDouble"] = sol::overload(
        [](std::string& label, double v)
        {
            ImGui::InputDouble(label.c_str(), &v);
            return v;
        },
        [](std::string& label, double v, float step)
        {
            ImGui::InputDouble(label.c_str(), &v, step);
            return v;
        },
        [](std::string& label, double v, float step, float step_fast)
        {
            ImGui::InputDouble(label.c_str(), &v, step, step_fast);
            return v;
        },
        [](std::string& label, double v, float step, float step_fast, std::string& format)
        {
            ImGui::InputDouble(label.c_str(), &v, step, step_fast, format.c_str());
            return v;
        },
        [](std::string& label, double v, float step, float step_fast, std::string& format, ImGuiInputTextFlags flags)
        {
            ImGui::InputDouble(label.c_str(), &v, step, step_fast, format.c_str(), flags);
            return v;
        }
    );
    //InputScalar
    //InputScalarN

    GuiTable["ColorEdit3"] = sol::overload(
        [](std::string& label, vector& col)
        {
            ImGui::ColorEdit3(label.c_str(), (float*)&col);
            return col;
        },
        [](std::string& label, vector& col, ImGuiColorEditFlags flags)
        {
            ImGui::ColorEdit3(label.c_str(), (float*)&col, flags);
            return col;
        }
    );
    GuiTable["ColorEdit4"] = sol::overload(
        [](std::string& label, ImVec4& col)
        {
            ImGui::ColorEdit4(label.c_str(), (float*)&col);
            return col;
        },
        [](std::string& label, ImVec4& col, ImGuiColorEditFlags flags)
        {
            ImGui::ColorEdit4(label.c_str(), (float*)&col, flags);
            return col;
        }
    );
    GuiTable["ColorPicker3"] = sol::overload(
        [](std::string& label, vector& col)
        {
            ImGui::ColorPicker3(label.c_str(), (float*)&col);
            return col;
        },
        [](std::string& label, vector& col, ImGuiColorEditFlags flags)
        {
            ImGui::ColorPicker3(label.c_str(), (float*)&col, flags);
            return col;
        }
    );
    GuiTable["ColorPicker4"] = sol::overload(
        [](std::string& label, ImVec4& col)
        {
            ImGui::ColorPicker4(label.c_str(), (float*)&col);
            return col;
        },
        [](std::string& label, ImVec4& col, ImGuiColorEditFlags flags)
        {
            ImGui::ColorPicker4(label.c_str(), (float*)&col, flags);
            return col;
        }
    );
    GuiTable["ColorButton"] = sol::overload(
        [](std::string& desc_id, ImVec4& col)
        {
            ImGui::ColorButton(desc_id.c_str(), col);
            return col;
        },
        [](std::string& desc_id, ImVec4& col, ImGuiColorEditFlags flags)
        {
            ImGui::ColorButton(desc_id.c_str(), col, flags);
            return col;
        },
        [](std::string& desc_id, ImVec4& col, ImGuiColorEditFlags flags, ImVec2 size)
        {
            ImGui::ColorButton(desc_id.c_str(), col, flags, size);
            return col;
        }
    );
    GuiTable["SetColorEditOptions"] = ImGui::SetColorEditOptions;


    GuiTable["TreeNode"] = sol::overload(
        [](std::string& label)
        {
            ImGui::TreeNode(label.c_str());
        }
    );
    GuiTable["TreeNodeEx"] = sol::overload(
        [](std::string& label)
        {
            ImGui::TreeNodeEx(label.c_str());
        },
        [](std::string& label, ImGuiTreeNodeFlags flags)
        {
            ImGui::TreeNodeEx(label.c_str(), flags);
        }
    );
    GuiTable["TreePush"] = sol::overload(
        [](std::string& label)
        {
            ImGui::TreePush(label.c_str());
        }
    );
    GuiTable["TreePop"] = ImGui::TreePop;
    GuiTable["TreeAdvanceToLabelPos"] = ImGui::TreeAdvanceToLabelPos; 
    GuiTable["GetTreeNodeToLabelSpacing"] = ImGui::GetTreeNodeToLabelSpacing;
    GuiTable["CollapsingHeader"] = sol::overload(
        [](std::string& label)
        {
            ImGui::CollapsingHeader(label.c_str());
        },
        [](std::string& label, ImGuiTreeNodeFlags flags)
        {
            ImGui::CollapsingHeader(label.c_str(), flags);
        },

        [](std::string& label, bool p_open)
        {
            ImGui::CollapsingHeader(label.c_str(), &p_open);
            return p_open;
        },
        [](std::string& label, bool p_open, ImGuiTreeNodeFlags flags)
        {
            ImGui::CollapsingHeader(label.c_str(), &p_open, flags);
            return p_open;
        }
    );
    GuiTable["SetNextItemOpen"] = sol::overload(
        [](bool is_open)
        {
            ImGui::SetNextItemOpen(is_open);
        },
        [](bool is_open, ImGuiCond cond)
        {
            ImGui::SetNextItemOpen(is_open, cond);
        }
    );


    //ListBox -- 2 overloads
    //ListBoxHeader -- 2 overloads
    //ListBoxFooter
    
    //PlotLines -- 2 overloads
    //PlotLinesHistogram -- 2 overloads

    GuiTable["Value"] = sol::overload(
        [](std::string& prefix, bool val)
        {
            ImGui::Value(prefix.c_str(), val);
        },
        [](std::string& prefix, int val)
        {
            ImGui::Value(prefix.c_str(), val);
        },
        [](std::string& prefix, uint val)
        {
            ImGui::Value(prefix.c_str(), val);
        },
        [](std::string& prefix, float val)
        {
            ImGui::Value(prefix.c_str(), val);
        },
        [](std::string& prefix, float val, std::string& float_format)
        {
            ImGui::Value(prefix.c_str(), val, float_format.c_str());
        },
        [](std::string& prefix, vector2& val)
        {
            ImGui::Text("%s: x: %.2f, y: %.2f", prefix, val.x, val.y);
        },
        [](std::string& prefix, vector& val)
        {
            ImGui::Text("%s: x: %.2f, y: %.2f, z: %.2f", prefix, val.x, val.y, val.z);
        },
        [](std::string& prefix, ImVec2& val)
        {
            ImGui::Text("%s: x: %.2f, y: %.2f", prefix, val.x, val.y);
        },
        [](std::string& prefix, ImVec4& val)
        {
            ImGui::Text("%s: x: %.2f, y: %.2f, z: %.2f, w: %.2f", prefix, val.x, val.y, val.z, val.w);
        }
    );


    GuiTable["BeginMainMenuBar"] = ImGui::BeginMainMenuBar;
    GuiTable["EndMainMenuBar"] = ImGui::EndMainMenuBar; //Only call if begin returns true
    GuiTable["EndMainMenuBar"] = ImGui::BeginMenuBar;
    GuiTable["EndMainMenuBar"] = ImGui::EndMenuBar; //Only call if begin returns true
    GuiTable["BeginMenu"] = sol::overload(
        [](std::string& label)
        {
            ImGui::BeginMenu(label.c_str());
        },
        [](std::string& label, bool enabled)
        {
            ImGui::BeginMenu(label.c_str(), enabled);
        }
    );
    GuiTable["EndMenu"] = ImGui::EndMenu; //Only call if begin returns true
    GuiTable["MenuItem"] = sol::overload(
        [](std::string& label)
        {
            ImGui::MenuItem(label.c_str());
        },
        [](std::string& label, std::string& shortcut)
        {
            ImGui::MenuItem(label.c_str(), shortcut.c_str());
        },
        [](std::string& label, std::string& shortcut, bool selected)
        {
            ImGui::MenuItem(label.c_str(), shortcut.c_str(), selected);
        },
        [](std::string& label, std::string& shortcut, bool selected, bool enabled)
        {
            ImGui::MenuItem(label.c_str(), shortcut.c_str(), selected, enabled);
        }
    );

    GuiTable["TooltipOnPrevious"] = [](std::string& tooltip)
    {
        if (!Globals::FontNormal)
            return;

        Util::Gui::TooltipOnPrevious(tooltip, Globals::FontNormal);
    };
    GuiTable["ShowHelpMarker"] = sol::overload(
        [](std::string& Description)
        {
            Util::Gui::ShowHelpMarker(Description.c_str());
        },
        [](std::string& Description, std::string& Label)
        {
            Util::Gui::ShowHelpMarker(Description.c_str(), Label.c_str());
        }
    );
    GuiTable["BeginTooltip"] = ImGui::BeginTooltip;
    GuiTable["EndTooltip"] = ImGui::EndTooltip;


    GuiTable["OpenPopup"] = [](std::string& str_id)
    {
        ImGui::OpenPopup(str_id.c_str());
    };
    GuiTable["BeginPopup"] = sol::overload(
        [](std::string& str_id)
        {
            return ImGui::BeginPopup(str_id.c_str());
        },
        [](std::string& str_id, ImGuiWindowFlags flags)
        {
            return ImGui::BeginPopup(str_id.c_str(), flags);
        }
    );
    GuiTable["BeginPopupContextItem"] = sol::overload(
        []()
        {
            return ImGui::BeginPopupContextItem();
        },
        [](std::string& str_id)
        {
            return ImGui::BeginPopupContextItem(str_id.c_str());
        },
        [](std::string& str_id, int mouse_button)
        {
            return ImGui::BeginPopupContextItem(str_id.c_str(), mouse_button);
        }
    );
    GuiTable["BeginPopupContextWindow"] = sol::overload(
        []()
        {
            return ImGui::BeginPopupContextWindow();
        },
        [](std::string& str_id)
        {
            return ImGui::BeginPopupContextWindow(str_id.c_str());
        },
        [](std::string& str_id, int mouse_button)
        {
            return ImGui::BeginPopupContextWindow(str_id.c_str(), mouse_button);
        },
        [](std::string& str_id, int mouse_button, bool also_over_items)
        {
            return ImGui::BeginPopupContextWindow(str_id.c_str(), mouse_button, also_over_items);
        }
    );
    GuiTable["BeginPopupContextVoid"] = sol::overload(
        []()
        {
            return ImGui::BeginPopupContextVoid();
        },
        [](std::string& str_id)
        {
            return ImGui::BeginPopupContextVoid(str_id.c_str());
        },
        [](std::string& str_id, int mouse_button)
        {
            return ImGui::BeginPopupContextVoid(str_id.c_str(), mouse_button);
        }
    );
    GuiTable["BeginPopupModal"] = sol::overload(
        [](std::string& name)
        {
            return ImGui::BeginPopupModal(name.c_str());
        },
        [](std::string& name, bool p_open)
        {
            ImGui::BeginPopupModal(name.c_str(), &p_open);
            return p_open;
        },
        [](std::string& name, bool p_open, ImGuiWindowFlags flags)
        {
            ImGui::BeginPopupModal(name.c_str(), &p_open, flags);
            return p_open;
        }
    );
    GuiTable["EndPopup"] = ImGui::EndPopup;
    GuiTable["OpenPopupOnItemClick"] = sol::overload(
        []()
        {
            return ImGui::OpenPopupOnItemClick();
        },
        [](std::string& str_id)
        {
            return ImGui::OpenPopupOnItemClick(str_id.c_str());
        },
        [](std::string& str_id, int mouse_button)
        {
            return ImGui::OpenPopupOnItemClick(str_id.c_str(), mouse_button);
        }
    );
    GuiTable["IsPopupOpen"] = [](std::string& str_id)
    {
        return ImGui::IsPopupOpen(str_id.c_str());
    };
    GuiTable["CloseCurrentPopup"] = ImGui::CloseCurrentPopup;


    GuiTable["Columns"] = sol::overload(
        []()
        {
            ImGui::Columns();
        },
        [](int count)
        {
            ImGui::Columns(count);
        },
        [](int count, std::string& id)
        {
            ImGui::Columns(count, id.c_str());
        },
        [](int count, std::string& id, bool border)
        {
            ImGui::Columns(count, id.c_str(), border);
        }
    );
    GuiTable["NextColumn"] = ImGui::NextColumn;
    GuiTable["GetColumnIndex"] = ImGui::GetColumnIndex;
    GuiTable["GetColumnWidth"] = sol::overload(
        []()
        {
            return ImGui::GetColumnWidth();
        },
        [](int column_index)
        {
            return ImGui::GetColumnWidth(column_index);
        }
    );
    GuiTable["SetColumnWidth"] = [](int column_index, float width)
    {
        ImGui::SetColumnWidth(column_index, width);
    };
    GuiTable["GetColumnOffset"] = sol::overload(
        []()
        {
            return ImGui::GetColumnOffset();
        },
        [](int column_index)
        {
            return ImGui::GetColumnOffset(column_index);
        }
    );
    GuiTable["SetColumnOffset"] = [](int column_index, float offset_x)
    {
        ImGui::SetColumnOffset(column_index, offset_x);
    };
    GuiTable["GetColumnsCount"] = ImGui::GetColumnsCount;

    //BeginTabBar
    //EndTabBar
    //BeginTabItem
    //EndTabItem
    //SetTabItemClosed

    GuiTable["IsItemHovered"] = sol::overload(
        []()
        {
            return ImGui::IsItemHovered();
        },
        [](ImGuiHoveredFlags flags)
        {
            return ImGui::IsItemHovered(flags);
        }
    );
    GuiTable["IsItemActive"] = ImGui::IsItemActive;
    GuiTable["IsItemFocused"] = ImGui::IsItemFocused;
    GuiTable["IsItemClicked"] = sol::overload(
        []()
        {
            return ImGui::IsItemClicked();
        },
        [](int mouse_button)
        {
            return ImGui::IsItemClicked(mouse_button);
        }
    );
    GuiTable["IsItemVisible"] = ImGui::IsItemVisible;
    GuiTable["IsItemEdited"] = ImGui::IsItemEdited;
    GuiTable["IsItemActivated"] = ImGui::IsItemActivated;
    GuiTable["IsItemDeactivated"] = ImGui::IsItemDeactivated;
    GuiTable["IsItemDeactivatedAfterEdit"] = ImGui::IsItemDeactivatedAfterEdit;
    GuiTable["IsAnyItemHovered"] = ImGui::IsAnyItemHovered;
    GuiTable["IsAnyItemActive"] = ImGui::IsAnyItemActive;
    GuiTable["IsAnyItemFocused"] = ImGui::IsAnyItemFocused;
    GuiTable["GetItemRectMin"] = ImGui::GetItemRectMin;
    GuiTable["GetItemRectMax"] = ImGui::GetItemRectMax;
    GuiTable["GetItemRectSize"] = ImGui::GetItemRectSize;
    GuiTable["SetItemAllowOverlap"] = ImGui::SetItemAllowOverlap;


    GuiTable["ColorConvertRGBtoHSV"] = sol::overload(
        [](float r, float g, float b)
        {
            float h, s, v;
            ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
            return vector(h, s, v);
        },
        [](vector& color)
        {
            float h, s, v;
            ImGui::ColorConvertRGBtoHSV(color.x, color.y, color.z, h, s, v);
            return vector(h, s, v);
        }
    );
    GuiTable["ColorConvertHSVtoRGB"] = sol::overload(
        [](float h, float s, float v)
        {
            float r, g, b;
            ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
            return vector(r, g, b);
        },
        [](vector& color)
        {
            float r, g, b;
            ImGui::ColorConvertHSVtoRGB(color.x, color.y, color.z, r, g, b);
            return vector(r, g, b);
        }
    );

    GuiTable["LabelAndValue"] = Util::Gui::LabelAndValue;


    GuiTable["MakeGui"] = [](std::string& GuiName, const sol::function& DrawFunc)
    {
        static auto GuiManager = IocContainer->resolve<IGuiManager>();
        auto NewGui = new LuaGui(GuiName, DrawFunc);
        GuiManager->AddChildGui(NewGui);
        return NewGui;
    };
#endif
}

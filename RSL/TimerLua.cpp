#include "TimerLua.h"
#include "Functions.h"

void Lua::BindTimer(sol::state& LuaState)
{
    auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
    RslTable.new_usertype<Timer>
    (
        "Timer",
        "new", sol::constructors<Timer(), Timer(bool StartNow), Timer(const Timer&)>(),
        "Start", &Timer::Start,
        "Reset", &Timer::Reset,
        "ElapsedHours", &Timer::ElapsedHours,
        "ElapsedMinutes", &Timer::ElapsedMinutes,
        "ElapsedSeconds", &Timer::ElapsedSeconds,
        "ElapsedMilliseconds", &Timer::ElapsedMilliseconds,
        "ElapsedMicroseconds", &Timer::ElapsedMicroseconds,
        "ElapsedNanoseconds", &Timer::ElapsedNanoseconds
    );
}
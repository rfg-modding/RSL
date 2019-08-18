#include "TimerLua.h"
#include "Functions.h"

void Lua::BindTimer(sol::state& LuaState)
{
    auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
    auto Utype = RslTable.create_simple_usertype<Timer>();
    Utype.set("new", sol::constructors<Timer(), Timer(bool StartNow), Timer(const Timer&)>());
    Utype.set("Start", &Timer::Start);
    Utype.set("Reset", &Timer::Reset);
    Utype.set("ElapsedHours", &Timer::ElapsedHours);
    Utype.set("ElapsedMinutes", &Timer::ElapsedMinutes);
    Utype.set("ElapsedSeconds", &Timer::ElapsedSeconds);
    Utype.set("ElapsedMilliseconds", &Timer::ElapsedMilliseconds);
    Utype.set("ElapsedMicroseconds", &Timer::ElapsedMicroseconds);
    Utype.set("ElapsedNanoseconds", &Timer::ElapsedNanoseconds);
    RslTable.set_usertype("Timer", Utype);
}

local function MyEvent()
        rsl.Log("Per frame event triggered!\n")
end

rfg.RegisterEvent("FrameUpdate", MyEvent)
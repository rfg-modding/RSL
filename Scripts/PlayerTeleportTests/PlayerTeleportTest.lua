
a = rfg.ActivePlayer.Position -- Make an alias variable to rfg.ActivePlayer.Position for convenience
rsl.Log("Player position: {}", a:GetDataString()) -- All vectors support GetDataString for convenience

rfg.TeleportPlayer(rfg.Vector:new(1434.0, 15.0, 693.3)) --Teleport to Oasis safehouse
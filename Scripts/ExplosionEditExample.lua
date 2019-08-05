
-- Get a pointer to the remote charge ExplosionInfo instance
RemoteChargeExp = rfg.GetExplosionInfo("remote_charge")
RemoteChargeExp.Radius = 12.0 --Change the remote charge damage radius
RemoteChargeExp.SecondaryRadius = 15.0

-- If you don't want to edit the actual explosion values you need to make a copy
RemoteChargeExpCopy = rfg.ExplosionInfo:new(RemoteChargeExp)
-- Now we can edit the values of RemoteChargeExpCopy without changing the global
-- remote charge explosion values.
RemoteChargeExpCopy.AiSoundRadius = 2.0
RemoteChargeExpCopy.Radius = 25.0
RemoteChargeExpCopy.SecondaryRadius = 30.0
RemoteChargeExpCopy.ImpulseMagnitude = -100000.0

SpawnPosition = rfg.Vector:new(rfg.ActivePlayer.Position)
SpawnPosition.y = SpawnPosition.y + 10.0
-- Note that here we're not exactly spawning a remote charge explosion
-- But a modified version of it
rfg.ExplosionCreate(RemoteChargeExpCopy, SpawnPosition) 
-- ^^ Also has an overload with many more args. Check the docs for more info on that.

-- You can also iterate through the games explosion list, as shown with the func below:

-- Normally it's good practice to stick console commands like this func 
-- in their own file and to label them as such. Placing it here for examples sake.
function ListExplosionInfoNames()
    for i = 0, rfg.ExplosionInfos:Size(), 1 do
        rsl.Log("{}: {}\n", i, rfg.ExplosionInfos[i].Name)
    end
end







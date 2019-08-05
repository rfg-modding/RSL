
Multiplier = 2.0

for i = 0, rfg.ExplosionInfos:Size(), 1 do
    IndexExp = rfg.ExplosionInfos[i];
    IndexExp.Radius = IndexExp.Radius * Multiplier
    IndexExp.SecondaryRadius = IndexExp.SecondaryRadius * Multiplier
    IndexExp.ImpulseMagnitude = IndexExp.ImpulseMagnitude * Multiplier
end


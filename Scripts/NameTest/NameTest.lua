
-- A test of a rfg.GetObject
-- Has two overloads, one takes the objects name, as shown below,
-- and one takes an objects handle (a uint) which are much more common.
-- All objects have a handle, almost none have names except a few squads (like sam) or sectors.

Sam = rfg.GetObject("Samanya") 
SamName = Sam:GetName() -- Interestingly enough the named sam object is a squad and not a human. The human object for sam is unnamed.
rsl.Log("{}\n", SamName)
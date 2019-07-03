local rfg = {}

rfg.ObjectTypes = require("rfg.ObjectTypes")
rfg.HumanTeams = require("rfg.HumanTeams")
rfg.PropTypes = require("rfg.PropTypes")
rfg.ObjectHitLocations = require("rfg.ObjectHitLocations")
rfg.HumanRotateDirections = require("rfg.HumanRotateDirections")
rfg.BlockMovementTypes = require("rfg.BlockMovementTypes")
rfg.HumanStates = require("rfg.HumanStates")
rfg.HumanMovementStates = require("rfg.HumanMovementStates")
rfg.HumanStances = require("rfg.HumanStances")
rfg.HumanMoveModes = require("rfg.HumanMoveModes")
rfg.HumanMoveSubmodes = require("rfg.HumanMoveSubmodes")
rfg.AnimationActions = require("rfg.AnimationActions")
rfg.HumanRagdollStates = require("rfg.HumanRagdollStates")
rfg.IkTypes = require("rfg.IkTypes")
rfg.FootPlant = require("rfg.FootPlant")
rfg.VehicleSeatIndex = require("rfg.VehicleSeatIndex")
rfg.ObjectImportanceLevels = require("rfg.ObjectImportanceLevels")
rfg.VoiceLineHandle = require("rfg.VoiceLineHandle")
rfg.VoiceLines = require("rfg.VoiceLines")
rfg.VoiceLinePriorities = require("rfg.VoiceLinePriorities")
rfg.AudiolibCuePriorities = require("rfg.AudiolibCuePriorities")
rfg.LipsyncDataHandle = require("rfg.LipsyncDataHandle")
rfg.GeneralActionTypes = require("rfg.GeneralActionTypes")
rfg.UseObjectIcon = require("rfg.UseObjectIcon")
rfg.TaggingSequences = require("rfg.TaggingSequences")
rfg.HudMessageHandle = require("rfg.HudMessageHandle")
rfg.PlayerZoomState = require("rfg.PlayerZoomState")
rfg.PlayerScriptModes = require("rfg.PlayerScriptModes")
rfg.PlayerCoverTest = require("rfg.PlayerCoverTest")
rfg.InterfaceModes = require("rfg.InterfaceModes")
rfg.AlertLevels = require("rfg.AlertLevels")
rfg.WorldDeserializeStates = require("rfg.WorldDeserializeStates")
rfg.WorldZoneStates = require("rfg.WorldZoneStates")
rfg.WorldStateModes = require("rfg.WorldStateModes")

-- Takes the ObjectType integer value and returns it's string name or nil.
function rfg.GetObjectTypeByValue(ObjectTypeValue)
    for key, value in rfg.ObjectType do
        if value == ObjectTypeValue then
            return key
        end
    end
    return nil
end

return rfg
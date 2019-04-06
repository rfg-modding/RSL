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
rfg.IkTypes = require("rfg.IkType")
rfg.FootPlant = require("rfg.FootPlant")
rfg.VehicleSeatIndex = require("rfg.VehicleSeatIndex")
rfg.ObjectImportanceLevels = require("rfg.ObjectImportanceLevels")
rfg.VoiceLineHandle = require("rfg.VoiceLineHandle")
rfg.VoiceLines = require("rfg.VoiceLines")
rfg.VoiceLinePriorities = require("rfg.VoiceLinePriorities")
rfg.AudiolibCuePriorities = require("rfg.AudiolibCuePriorities")
rfg.LipsyncDataHandle = require("rfg.LipsyncDataHandle")

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
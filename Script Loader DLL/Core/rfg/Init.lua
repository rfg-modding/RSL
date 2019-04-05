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
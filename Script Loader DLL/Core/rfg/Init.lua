local rfg = {}

rfg.ObjectType = require("rfg.ObjectType")
rfg.LogType = require("rfg.LogType")

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
#include "ObjectLua.h"
#include "Functions.h"

void Lua::BindObjectContactInfo(sol::state & LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<ObjectContactInfo>
    (
        "ObjectContactInfo",
        "new", sol::constructors<ObjectContactInfo(), ObjectContactInfo(const ObjectContactInfo&)>(),
        "ContactList", &ObjectContactInfo::m_contact_list
    );
}

void Lua::BindObject(sol::state& LuaState)
{
    //Todo: Add formatting to the casting exceptions and make note of the actual type of the object, and the casting function that should be used, if that type is supported yet.
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<Object>
    (
        "Object",
        "new", sol::constructors<Object(), Object(const Object&)>(),
        "Position", &Object::Position,
        "Orientation", &Object::Orientation,
        "Child", &Object::ChildPtr,
        "ChildNext", &Object::ChildNext,
        "ChildPrevious", &Object::ChildPrevious,
        "AttachInfo", &Object::AttachInfo,
        "HavokHandle", &Object::HavokHandle,
        "ContactInfo", &Object::ContactInfo,
        "ObjFlags", &Object::ObjFlags,
        "RemoteObjFlags", &Object::RemoteObjFlags,
        "MPDcmoIndex", &Object::MPDcmoIndex, //Note: Use a sol::property if you bind this to avoid char<->int comparison issues
        "CheckingReset", &Object::CheckingReset,
        "NameIndex", &Object::NameIndex,
        "FlaggedNext", &Object::FlaggedNext,
        "FlaggedPrevious", &Object::FlaggedPrevious,
        "Handle", &Object::Handle,
        "Parent", &Object::Parent,
        "BPOHandle", &Object::BPOHandle,
        "AllIndex", &Object::AllIndex,
        "TypeIndex", &Object::TypeIndex,
        "SubtypeIndex", &Object::SubtypeIndex,
        "Type", sol::property([](Object& Self) -> int {return static_cast<int>(Self.ObjectType); }, [](Object& Self, int Value) {Self.ObjectType = static_cast<char>(Value); }),
        "SubType", sol::property([](Object& Self) -> int {return static_cast<int>(Self.SubType); }, [](Object& Self, int Value) {Self.SubType = static_cast<char>(Value); }),
        "LastKnownBMin", &Object::LastKnownBMin,
        "LastKnownBMax", &Object::LastKnownBMax,
        "SRID", &Object::SRID,
        "CastToHuman", [](Object& Self) ->Human *
        {
            if (Self.ObjectType != OT_HUMAN) throw std::exception("Cannot cast to a human, since the object is not a human object. Check that YourObject.Type == rfg.ObjectTypes.Human before casting.");
            return static_cast<Human*>(&Self);
        },
        "CastToPlayer", [](Object& Self) ->Player*
        {
            if (Self.ObjectType != OT_HUMAN && Self.SubType == OT_SUB_HUMAN_PLAYER) throw std::exception("Cannot cast to a player, since the object is not a player object. Check that YourObject.Type == rfg.ObjectTypes.Human and that Object.SubType == rfg.ObjectSubTypes.HumanPlayer before casting.");
            return static_cast<Player*>(&Self);
        },
        "CastToSquad", [](Object& Self) ->object_squad*
        {
            if (Self.ObjectType != OT_SQUAD) throw std::exception("Cannot cast to a squad, since the object is not a squad object. Check that YourObject.Type == rfg.ObjectTypes.Squad before casting.");
            return static_cast<object_squad*>(&Self);
        },
        "CastToZone", [](Object& Self) ->obj_zone*
        {
            if (Self.ObjectType != OT_ZONE) throw std::exception("Cannot cast to a zone, since the object is not a zone object. Check that YourObject.Type == rfg.ObjectTypes.Zone before casting.");
            return static_cast<obj_zone*>(&Self);
        },
        "CastToTriggerRegion", [](Object& Self) ->trigger_region*
        {
            if (Self.ObjectType != OT_TRIGGER_REGION) throw std::exception("Cannot cast to a trigger region, since the object is not a trigger region object. Check that YourObject.Type == rfg.ObjectTypes.TriggerRegion before casting.");
            return static_cast<trigger_region*>(&Self);
        },
        "CastToMarauderAmbushRegion", [](Object& Self) ->marauder_ambush_region*
        {
            if (Self.ObjectType != OT_MARAUDER_AMBUSH_REGION) throw std::exception("Cannot cast to a marauder ambush region, since the object is not a marauder ambush region object. Check that YourObject.Type == rfg.ObjectTypes.MarauderAmbushRegion before casting.");
            return static_cast<marauder_ambush_region*>(&Self);
        },
        "CastToSquadSpawnNode", [](Object& Self) ->object_squad_spawn_node*
        {
            if (Self.ObjectType != OT_SQUAD_SPAWN_NODE) throw std::exception("Cannot cast to a squad spawn node, since the object is not a squad spawn node object. Check that YourObject.Type == rfg.ObjectTypes.SquadSpawnNode before casting.");
            return static_cast<object_squad_spawn_node*>(&Self);
        },
        "CastToDistrict", [](Object& Self) ->district*
        {
            if (Self.ObjectType != OT_DISTRICT) throw std::exception("Cannot cast to a district, since the object is not a district object. Check that YourObject.Type == rfg.ObjectTypes.District before casting.");
            return static_cast<district*>(&Self);
        },
        "GetName", [](Object& Self) -> const char*
        {
            if (Globals::RfgWorldPtr)
            {
                return WorldGetObjectName(Globals::RfgWorldPtr, nullptr, &Self);
            }
            return nullptr;
        }
    );

    //Todo: convert these to the new_usertype syntax and bind them as necessary
    //Casting functions
    //Utype.set("CastToItem", [](Object& Self) ->Human* {return static_cast<Item*>(&Self); });
    //Utype.set("CastToMover", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToVehicle", [](Object& Self) ->Human* {return static_cast<vehicle*>(&Self); });
    //Utype.set("CastToEffect", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToDebris", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToTurret", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToLight", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToPlayerStart", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToCoverNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToNavPoint", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToConvoy", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToConvoyEnd", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToPatrol", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToGuardNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToSkybox", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToLadder", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToConstraint", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToRestrictedArea", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToSpawnRegion", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToAmbientSpawnRegion", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToVehicleSpawnNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToNpcSpawnNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToTurretSpawnNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToActionNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToRoadblockNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToShapeCutter", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToMultiMarker", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToPathRoad", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToLightParams", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToDummy", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToActivitySpawn", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToRaidNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToSubzone", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToHouseArrestNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToDemolitionsMasterNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToRidingShotgunNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToDeliveryNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToBoundingBox", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToMissionStartNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToCourier", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToCourierEnd", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToSafehouse", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToBftpNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToAirstrikeDefenseNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToUpgradeNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
    //Utype.set("CastToAreaDefenseNode", [](Object& Self) ->Human* {return static_cast<Human*>(&Self); });
}

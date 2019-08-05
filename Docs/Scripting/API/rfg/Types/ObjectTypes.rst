
ObjectTypes
========================================================
These values are used to differentiate each object type from each other. These are defined in ``./Core/rfg/ObjectTypes.lua``. You can get an objects type via ``Object.Type``. So, for example, you could loop through the global object list and count the number of human objects: 

.. code-block:: lua

    HumanCount = 0
    for i=0, rfg.ActiveWorld.AllObjects:Size(), 1 do
        Object = rfg.ActiveWorld.AllObjects[i]
        if Object.Type == rfg.ObjectTypes.Human then
            HumanCount = HumanCount + 1
        end
    end
    rsl.Log("Number of human objects found: {}\n", HumanCount)

====================== ========================================= ==========
Object Type            Access Variable                           Value     
====================== ========================================= ==========
`Human`_               ``rfg.ObjectTypes.Human``                 0
Item                   ``rfg.ObjectTypes.Item``                  1
Mover                  ``rfg.ObjectTypes.Mover``                 2
Vehicle                ``rfg.ObjectTypes.Vehicle``               3 
Effect                 ``rfg.ObjectTypes.Effect``                4 
Debris                 ``rfg.ObjectTypes.Debris``                5 
Turret                 ``rfg.ObjectTypes.Turret``                6
Light                  ``rfg.ObjectTypes.Light``                 7
PlayerStart            ``rfg.ObjectTypes.PlayerStart``           8  
CoverNode              ``rfg.ObjectTypes.CoverNode``             9    
NavPoint               ``rfg.ObjectTypes.NavPoint``              10 
Squad                  ``rfg.ObjectTypes.Squad``                 11
Convoy                 ``rfg.ObjectTypes.Convoy``                12
ConvoyEnd              ``rfg.ObjectTypes.ConvoyEnd``             13
Patrol                 ``rfg.ObjectTypes.Patrol``                14 
GuardNode              ``rfg.ObjectTypes.GuardNode``             15 
Skybox                 ``rfg.ObjectTypes.Skybox``                16 
Ladder                 ``rfg.ObjectTypes.Ladder``                17   
Constraint             ``rfg.ObjectTypes.Constraint``            18     
`Zone`_                ``rfg.ObjectTypes.Zone``                  19
TriggerRegion          ``rfg.ObjectTypes.TriggerRegion``         20       
MarauderAmbushRegion   ``rfg.ObjectTypes.MarauderAmbushRegion``  21    
RestrictedArea         ``rfg.ObjectTypes.RestrictedArea``        22      
SpawnRegion            ``rfg.ObjectTypes.SpawnRegion``           23
AmbientSpawnRegion     ``rfg.ObjectTypes.AmbientSpawnRegion``    24         
VehicleSpawnRegion     ``rfg.ObjectTypes.VehicleSpawnRegion``    25         
NpcSpawnNode           ``rfg.ObjectTypes.NpcSpawnNode``          26   
TurretSpawnNode        ``rfg.ObjectTypes.TurretSpawnNode``       27      
ActionNode             ``rfg.ObjectTypes.ActionNode``            28 
SquadSpawnNode         ``rfg.ObjectTypes.SquadSpawnNode``        29     
RoadblockNode          ``rfg.ObjectTypes.RoadblockNode``         30    
ShapeCutter            ``rfg.ObjectTypes.ShapeCutter``           31  
District               ``rfg.ObjectTypes.District``              32
MultiMarker            ``rfg.ObjectTypes.MultiMarker``           33  
PathRoad               ``rfg.ObjectTypes.PathRoad``              34 
LightParams            ``rfg.ObjectTypes.LightParams``           35  
Dummy                  ``rfg.ObjectTypes.Dummy``                 36
ActivitySpawn          ``rfg.ObjectTypes.ActivitySpawn``         37    
RaidNode               ``rfg.ObjectTypes.RaidNode``              38
Subzone                ``rfg.ObjectTypes.Subzone``               39
HouseArrestNode        ``rfg.ObjectTypes.HouseArrestNode``       40      
DemolitionsMasterNode  ``rfg.ObjectTypes.DemolitionsMasterNode`` 41            
RidingShotgunNode      ``rfg.ObjectTypes.RidingShotgunNode``     42        
DeliveryNode           ``rfg.ObjectTypes.DeliveryNode``          43   
BoundingBox            ``rfg.ObjectTypes.BoundingBox``           44  
MissionStartNode       ``rfg.ObjectTypes.MissionStartNode``      45       
Courier                ``rfg.ObjectTypes.Courier``               46
CourierEnd             ``rfg.ObjectTypes.CourierEnd``            47 
Safehouse              ``rfg.ObjectTypes.Safehouse``             48
BftpNode               ``rfg.ObjectTypes.BftpNode``              49
AirstrikeDefenseNode   ``rfg.ObjectTypes.AirstrikeDefenseNode``  50           
UpgradeNode            ``rfg.ObjectTypes.UpgradeNode``           51  
AreaDefenseNode        ``rfg.ObjectTypes.AreaDefenseNode``       52      
N/A                    ``rfg.ObjectTypes.Undefined``             4294967295          
====================== ========================================= ==========

.. _`Object`: ./Object.html
.. _`Human`: ./Human.html
.. _`Zone`: ./Zone.html

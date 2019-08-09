
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.
last updated: 09.08.2019  - added several descriptions for variables.

hkpSolverInfo
********************************************************
Values used by the physics solver. Mostly untested and unresearched for now. Should be able to look at open source physics engines and research papers to determine what these values do and their purposes. You generally shouldn't change these much if you want a stable game experience.

Variables
========================================================

**Tau** (`float`_)
    Vanilla Value: 0.600
    Angular Velocity and rotational force (Torque) 
    (Vanilla is recommended)

**Damping** (`float`_)
    (Vanilla Value: 1.000 )  (Max recommended Value: 1.520)
    Damping is based on how bouncy a rigid object will behave when falling onto the ground.

**FrictionTau** (`float`_)
    (Vanilla Value: 0.300) (Recommended Value: 1.780) -- For a more realistic vision.
    Friction is a part of collision resolution. Friction always applies a force upon objects. 
    In RedFactionGuerilla, it will make buildings and objects harder to break, and buildings will fall in bigger pieces.

**DampDivTau** (`float`_)
    (Vanilla Value: 0.600)
    Torque and Damp Stress Values - !! - do not touch this. Editing this will not yeld any beneficial results .

**TauDivDamp** (`float`_)
    (Vanilla Value: 3.333)
    Effect is Unknown for now. 

**DampDivFrictionTau** (`float`_)
    (Vanilla Value: 0.300)
    Friction and Damp Stress Values - !! - do not touch this. Editing this will not yeld any beneficial results .

**FrictionTauDivDamp** (`float`_)
    Unknown value.
    Friction and Damp Stress Values - !! - do not touch this. Editing this will not yeld any beneficial results .

**ContactRestingVelocity** (`float`_)
   Friction and Damp Stress Values - !! - do not touch this. Editing this will not yeld any beneficial results 

**DeltaTime** (`float`_)
    Unknown value. ``ReadOnly``. Set by the game manually each frame/physics update based on the amount of time passed (educated guess).

**InvDeltaTime** (`float`_)
    Unknown value. ``ReadOnly``. Equals ``1 / DeltaTime``.

**NumSteps** (`int`_)
     "Step" is a process of calculating system's next state. 
    Timestep is the time interval for which simulation will progress during next "step". 
    It works simliar to Timestep multiplier.

**NumMicroSteps** (`int`_)
    Half the Numstep value for better percision when editing values.

**InvNumMicroSteps** (`float`_)
    Unknown value. ``readonly``. Equals ``1 / NumMicroSteps``.

**InvNumSteps** (`float`_)
    Unknown value. ``readonly``. Equals ``1 / NumSteps``.

**ForceCoherentConstraintOrderinginSolver** (`bool`_)
    Unknown value.

.. _`float`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`bool`: ./PrimitiveTypes.html

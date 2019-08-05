
.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.


hkpSolverInfo
********************************************************
Values used by the physics solver. Mostly untested and unresearched for now. Should be able to look at open source physics engines and research papers to determine what these values do and their purposes. You generally shouldn't change these much if you want a stable game experience.

Variables
========================================================

**Tau** (`float`_)
    Unknown value.

**Damping** (`float`_)
    Unknown value.

**FrictionTau** (`float`_)
    Unknown value.

**DampDivTau** (`float`_)
    Unknown value.

**TauDivDamp** (`float`_)
    Unknown value.

**DampDivFrictionTau** (`float`_)
    Unknown value.

**FrictionTauDivDamp** (`float`_)
    Unknown value.

**ContactRestingVelocity** (`float`_)
    Unknown value.

**DeltaTime** (`float`_)
    Unknown value. ``readonly``. Set by the game manually each frame/physics update based on the amount of time passed (educated guess).

**InvDeltaTime** (`float`_)
    Unknown value. ``readonly``. Equals ``1 / DeltaTime``.

**NumSteps** (`int`_)
    Unknown value.

**NumMicroSteps** (`int`_)
    Unknown value.

**InvNumMicroSteps** (`float`_)
    Unknown value. ``readonly``. Equals ``1 / NumMicroSteps``.

**InvNumSteps** (`float`_)
    Unknown value. ``readonly``. Equals ``1 / NumSteps``.

**ForceCoherentConstraintOrderinginSolver** (`bool`_)
    Unknown value.

.. _`float`: ./PrimitiveTypes.html
.. _`int`: ./PrimitiveTypes.html
.. _`bool`: ./PrimitiveTypes.html

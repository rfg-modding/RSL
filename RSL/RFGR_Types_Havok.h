#pragma once
#include "RFGR_Types_StateManager.h"

enum hkcdShapeType_ShapeTypeEnum
{
	SPHERE = 0x0,
	CYLINDER = 0x1,
	TRIANGLE = 0x2,
	BOX = 0x3,
	CAPSULE = 0x4,
	CONVEX_VERTICES = 0x5,
	TRI_SAMPLED_HEIGHT_FIELD_COLLECTION = 0x6,
	TRI_SAMPLED_HEIGHT_FIELD_BV_TREE = 0x7,
	LIST = 0x8,
	MOPP = 0x9,
	CONVEX_TRANSLATE = 0xA,
	CONVEX_TRANSFORM = 0xB,
	SAMPLED_HEIGHT_FIELD = 0xC,
	EXTENDED_MESH = 0xD,
	TRANSFORM = 0xE,
	COMPRESSED_MESH = 0xF,
	STATIC_COMPOUND = 0x10,
	BV_COMPRESSED_MESH = 0x11,
	COLLECTION = 0x12,
	USER0 = 0x13,
	USER1 = 0x14,
	USER2 = 0x15,
	BV_TREE = 0x16,
	CONVEX = 0x17,
	CONVEX_PIECE = 0x18,
	MULTI_SPHERE = 0x19,
	CONVEX_LIST = 0x1A,
	TRIANGLE_COLLECTION = 0x1B,
	HEIGHT_FIELD = 0x1C,
	SPHERE_REP = 0x1D,
	BV = 0x1E,
	PLANE = 0x1F,
	PHANTOM_CALLBACK = 0x20,
	MULTI_RAY = 0x21,
	INVALID = 0x22,
	FIRST_SHAPE_TYPE = 0x0,
	MAX_SPU_SHAPE_TYPE = 0x16,
	MAX_PPU_SHAPE_TYPE = 0x23,
	ALL_SHAPE_TYPES = 0xFFFFFFFF,
};

enum hkcdShapeInfoCodecType_ShapeInfoCodecTypeEnum
{
	NULL_CODEC = 0x0,
	UFM358 = 0x1,
	MAX_NUM_CODECS = 0x10,
};

enum hkpSimulation_LastProcessingStep
{
	INTEGRATE = 0x0,
	COLLIDE = 0x1,
};

enum hkpConstraintAtom_AtomType
{
	TYPE_INVALID = 0x0,
	TYPE_BRIDGE = 0x1,
	TYPE_SET_LOCAL_TRANSFORMS = 0x2,
	TYPE_SET_LOCAL_TRANSLATIONS = 0x3,
	TYPE_SET_LOCAL_ROTATIONS = 0x4,
	TYPE_BALL_SOCKET = 0x5,
	TYPE_STIFF_SPRING = 0x6,
	TYPE_LIN = 0x7,
	TYPE_LIN_SOFT = 0x8,
	TYPE_LIN_LIMIT = 0x9,
	TYPE_LIN_FRICTION = 0xA,
	TYPE_LIN_MOTOR = 0xB,
	TYPE_2D_ANG = 0xC,
	TYPE_ANG = 0xD,
	TYPE_ANG_LIMIT = 0xE,
	TYPE_TWIST_LIMIT = 0xF,
	TYPE_CONE_LIMIT = 0x10,
	TYPE_ANG_FRICTION = 0x11,
	TYPE_ANG_MOTOR = 0x12,
	TYPE_RAGDOLL_MOTOR = 0x13,
	TYPE_PULLEY = 0x14,
	TYPE_RACK_AND_PINION = 0x15,
	TYPE_COG_WHEEL = 0x16,
	TYPE_SETUP_STABILIZATION = 0x17,
	TYPE_3D_ANG = 0x18,
	TYPE_DEFORMABLE_3D_LIN = 0x19,
	TYPE_DEFORMABLE_3D_ANG = 0x1A,
	TYPE_OVERWRITE_PIVOT = 0x1B,
	TYPE_WHEEL_FRICTION = 0x1C,
	TYPE_ELLIPTICAL_LIMIT = 0x1D,
	TYPE_CONTACT = 0x1E,
	FIRST_MODIFIER_TYPE = 0x1F,
	TYPE_MODIFIER_SOFT_CONTACT = 0x1F,
	TYPE_MODIFIER_MASS_CHANGER = 0x20,
	TYPE_MODIFIER_VISCOUS_SURFACE = 0x21,
	TYPE_MODIFIER_MOVING_SURFACE = 0x22,
	TYPE_MODIFIER_IGNORE_CONSTRAINT = 0x23,
	TYPE_MODIFIER_CENTER_OF_MASS_CHANGER = 0x24,
	LAST_MODIFIER_TYPE = 0x24,
	TYPE_MAX = 0x25,
};

enum hkpAgentNnTrackType
{
	HK_AGENT3_INVALID_TRACK = 0x0,
	HK_AGENT3_MIDPHASE_TRACK = 0x1,
	HK_AGENT3_NARROWPHASE_TRACK = 0x2,
};

enum hkpMaterial_ResponseType
{
	RESPONSE_INVALID = 0x0,
	RESPONSE_SIMPLE_CONTACT = 0x1,
	RESPONSE_REPORTING = 0x2,
	RESPONSE_NONE = 0x3,
	RESPONSE_MAX_ID = 0x4,
};

enum hkpConstraintInstance_ConstraintPriority
{
	PRIORITY_INVALID = 0x0,
	PRIORITY_PSI = 0x1,
	PRIORITY_SIMPLIFIED_TOI_UNUSED = 0x2,
	PRIORITY_TOI = 0x3,
	PRIORITY_TOI_HIGHER = 0x4,
	PRIORITY_TOI_FORCED = 0x5,
	NUM_PRIORITIES = 0x6,
};

enum hkpConstraintInstance_AddReferences
{
	DO_NOT_ADD_REFERENCES = 0x0,
	DO_ADD_REFERENCES = 0x1,
};

enum hkpConstraintInstance_CloningMode
{
	CLONE_SHALLOW_IF_NOT_CONSTRAINED_TO_WORLD = 0x0,
	CLONE_DATAS_WITH_MOTORS = 0x1,
	CLONE_FORCE_SHALLOW = 0x2,
};

enum hkpConstraintInstance_OnDestructionRemapInfo
{
	ON_DESTRUCTION_REMAP = 0x0,
	ON_DESTRUCTION_REMOVE = 0x1,
	ON_DESTRUCTION_RESET_REMOVE = 0x2,
};

enum hkClassMember_FlagValues
{
	FLAGS_NONE = 0x0,
	ALIGN_8 = 0x80,
	ALIGN_16 = 0x100,
	NOT_OWNED = 0x200,
	SERIALIZE_IGNORED = 0x400,
	ALIGN_32 = 0x800,
	ALIGN_REAL = 0x100,
};

enum hkpConstraintInstance_InstanceType
{
	TYPE_NORMAL = 0x0,
	TYPE_CHAIN = 0x1,
	TYPE_DISABLE_SPU = 0x2,
};

enum hkpEntity_SpuCollisionCallbackEventFilter
{
	SPU_SEND_NONE = 0x0,
	SPU_SEND_CONTACT_POINT_ADDED = 0x1,
	SPU_SEND_CONTACT_POINT_PROCESS = 0x2,
	SPU_SEND_CONTACT_POINT_REMOVED = 0x4,
	SPU_SEND_CONTACT_POINT_ADDED_OR_PROCESS = 0x3,
};

enum hkpMotion_MotionType
{
	MOTION_INVALID = 0x0,
	MOTION_DYNAMIC = 0x1,
	MOTION_SPHERE_INERTIA = 0x2,
	MOTION_BOX_INERTIA = 0x3,
	MOTION_KEYFRAMED = 0x4,
	MOTION_FIXED = 0x5,
	MOTION_THIN_BOX_INERTIA = 0x6,
	MOTION_CHARACTER = 0x7,
	MOTION_MAX_ID = 0x8,
};

enum hkpWorldCinfo_SolverType
{
	SOLVER_TYPE_INVALID = 0x0,
	SOLVER_TYPE_2ITERS_SOFT = 0x1,
	SOLVER_TYPE_2ITERS_MEDIUM = 0x2,
	SOLVER_TYPE_2ITERS_HARD = 0x3,
	SOLVER_TYPE_4ITERS_SOFT = 0x4,
	SOLVER_TYPE_4ITERS_MEDIUM = 0x5,
	SOLVER_TYPE_4ITERS_HARD = 0x6,
	SOLVER_TYPE_8ITERS_SOFT = 0x7,
	SOLVER_TYPE_8ITERS_MEDIUM = 0x8,
	SOLVER_TYPE_8ITERS_HARD = 0x9,
	SOLVER_TYPE_MAX_ID = 0xA,
};

enum hkpWorldCinfo_SimulationType
{
	SIMULATION_TYPE_INVALID = 0x0,
	SIMULATION_TYPE_DISCRETE = 0x1,
	SIMULATION_TYPE_CONTINUOUS = 0x2,
	SIMULATION_TYPE_MULTITHREADED = 0x3,
};

enum hkpWorldCinfo_ContactPointGeneration
{
	CONTACT_POINT_ACCEPT_ALWAYS = 0x0,
	CONTACT_POINT_REJECT_DUBIOUS = 0x1,
	CONTACT_POINT_REJECT_MANY = 0x2,
};

enum hkpWorldCinfo_BroadPhaseType
{
	BROADPHASE_TYPE_SAP = 0x0,
	BROADPHASE_TYPE_TREE = 0x1,
	BROADPHASE_TYPE_HYBRID = 0x2,
};

enum hkpWorldCinfo_BroadPhaseBorderBehaviour
{
	BROADPHASE_BORDER_ASSERT = 0x0,
	BROADPHASE_BORDER_FIX_ENTITY = 0x1,
	BROADPHASE_BORDER_REMOVE_ENTITY = 0x2,
	BROADPHASE_BORDER_DO_NOTHING = 0x3,
};

enum hkpVelocityAccumulator_hkpAccumulatorType
{
	HK_RIGID_BODY = 0x0,
	HK_KEYFRAMED_RIGID_BODY = 0x1,
	HK_NO_GRAVITY_RIGID_BODY = 0x2,
	HK_END = 0x3,
};

enum hkpVelocityAccumulator_hkpAccumulatorContext
{
	ACCUMULATOR_CONTEXT_BUILD_JACOBIANS = 0x0,
	ACCUMULATOR_CONTEXT_SOLVER = 0x1,
};

enum hkpCollisionFilter_hkpFilterType
{
	HK_FILTER_UNKNOWN = 0x0,
	HK_FILTER_NULL = 0x1,
	HK_FILTER_GROUP = 0x2,
	HK_FILTER_LIST = 0x3,
	HK_FILTER_CUSTOM = 0x4,
	HK_FILTER_PAIR = 0x5,
	HK_FILTER_CONSTRAINT = 0x6,
};

enum hkpBodyOperation_ExecutionState
{
	EXECUTE_SINGLE_THREADED = 0x0,
	EXECUTE_MULTI_THREADED = 0x1,
};

/* 1949 */
enum hkWorldOperation_Type
{
	OPERATION_ID_ANY = 0x0,
	OPERATION_ID_INVALID = 0x0,
	ENTITY_ADD = 0x1,
	ENTITY_REMOVE = 0x2,
	ENTITY_UPDATE_BROAD_PHASE = 0x3,
	RIGIDBODY_SET_MOTION_TYPE = 0x4,
	WORLD_OBJECT_SET_SHAPE = 0x5,
	WORLD_OBJECT_UPDATE_SHAPE = 0x6,
	ENTITY_BATCH_ADD = 0x7,
	ENTITY_BATCH_REMOVE = 0x8,
	CONSTRAINT_ADD = 0x9,
	CONSTRAINT_REMOVE = 0xA,
	ACTION_ADD = 0xB,
	ACTION_REMOVE = 0xC,
	ISLAND_MERGE = 0xD,
	PHANTOM_ADD = 0xE,
	PHANTOM_REMOVE = 0xF,
	PHANTOM_BATCH_ADD = 0x10,
	PHANTOM_BATCH_REMOVE = 0x11,
	PHANTOM_UPDATE_BROAD_PHASE = 0x12,
	UPDATE_FILTER_ENTITY = 0x13,
	UPDATE_FILTER_ENTITY_PAIR = 0x14,
	UPDATE_FILTER_PHANTOM = 0x15,
	UPDATE_FILTER_WORLD = 0x16,
	UPDATE_MOVED_BODY_INFO = 0x17,
	ENTITY_BATCH_REINTEGRATE_AND_RECOLLIDE = 0x18,
	RIGIDBODY_SET_POSITION_AND_ROTATION = 0x19,
	RIGIDBODY_SET_LINEAR_VELOCITY = 0x1A,
	RIGIDBODY_SET_ANGULAR_VELOCITY = 0x1B,
	RIGIDBODY_APPLY_LINEAR_IMPULSE = 0x1C,
	RIGIDBODY_APPLY_POINT_IMPULSE = 0x1D,
	RIGIDBODY_APPLY_ANGULAR_IMPULSE = 0x1E,
	WORLD_OBJECT_ADD_REFERENCE = 0x1F,
	WORLD_OBJECT_REMOVE_REFERENCE = 0x20,
	ACTIVATE_REGION = 0x21,
	ACTIVATE_ENTITY = 0x22,
	REQUEST_DEACTIVATE_ENTITY = 0x23,
	DEACTIVATE_ENTITY = 0x24,
	CONSTRAINT_FILTER_BROKEN_EVENT = 0x25,
	USER_CALLBACK = 0x26,
};

enum hkpSimulation_ResetCollisionInformation
{
	RESET_TOI = 0x1,
	RESET_TIM = 0x2,
	RESET_AABB = 0x4,
	RESET_ALL = 0x7,
};

enum hkpSimulation_FindContacts
{
	FIND_CONTACTS_DEFAULT = 0x0,
	FIND_CONTACTS_EXTRA = 0x1,
};

enum hkpDynamicsJob_JobSubType
{
	DYNAMICS_JOB_INTEGRATE = 0x0,
	DYNAMICS_JOB_BUILD_ACCUMULATORS = 0x1,
	DYNAMICS_JOB_CREATE_JACOBIAN_TASKS = 0x2,
	DYNAMICS_JOB_FIRE_JACOBIAN_SETUP_CALLBACK = 0x3,
	DYNAMICS_JOB_BUILD_JACOBIANS = 0x4,
	DYNAMICS_JOB_SPLIT_ISLAND = 0x5,
	DYNAMICS_JOB_SOLVE_CONSTRAINTS = 0x6,
	DYNAMICS_JOB_SOLVE_APPLY_GRAVITY = 0x7,
	DYNAMICS_JOB_SOLVE_CONSTRAINT_BATCH = 0x8,
	DYNAMICS_JOB_SOLVE_INTEGRATE_VELOCITIES = 0x9,
	DYNAMICS_JOB_SOLVE_EXPORT_RESULTS = 0xA,
	DYNAMICS_JOB_INTEGRATE_MOTION = 0xB,
	DYNAMICS_JOB_BROADPHASE = 0xC,
	DYNAMICS_JOB_AGENT_SECTOR = 0xD,
	DYNAMICS_JOB_POST_COLLIDE = 0xE,
	DYNAMICS_JOB_AGENT_NN_ENTRY = 0xF,
	DYNAMICS_JOB_DUMMY = 0x10,
	DYNAMICS_JOB_END = 0x11,
};

enum hkpDynamicsJob_NoJob
{
	NO_SRC_JOB = 0x0,
};

enum $A4F4501B2362594B85846B5580AE3763
{
	ACCUMULATORS_PER_JOB = 0x80,
};

enum hkpPhysicsCommand_TYPE
{
	TYPE_ADD_CONSTRAINT_TO_LOCKED_ISLAND = 0x0,
	TYPE_REMOVE_CONSTRAINT_FROM_LOCKED_ISLAND = 0x1,
	TYPE_END = 0x2,
};

enum hkpStepResult
{
	HK_STEP_RESULT_SUCCESS = 0x0,
	HK_STEP_RESULT_MEMORY_FAILURE_BEFORE_INTEGRATION = 0x1,
	HK_STEP_RESULT_MEMORY_FAILURE_DURING_COLLIDE = 0x2,
	HK_STEP_RESULT_MEMORY_FAILURE_DURING_TOI_SOLVE = 0x3,
};

template <class T>
class hkArrayBase
{
	const T& operator[](int Index)
	{
		return Elements[Index];
	}
	int Size() { return ArraySize; }
	int Capacity() { return CapacityAndFlags; }

private:
	T* Elements;
	int ArraySize;
	int CapacityAndFlags;
};

template <class T, class U>
class hkArray : hkArrayBase<T>
{

};

template <class T, class U>
class hkEnum
{
public:
	U m_storage;
};

template <class T>
class hkRefPtr
{
public:
	T* Pointer;
};

template <class T>
class hkSmallArray
{
public:
	const T& operator[](int Index)
	{
		return Elements[Index];
	}
	int Size() { return ArraySize; }
	int Capacity() { return CapacityAndFlags; }

private:
	T* Elements;
	unsigned __int16 ArraySize;
	unsigned __int16 CapacityAndFlags;
};

template <class T, class U>
class hkFlags
{
public:
	U Storage;
};

template <class T>
class hkViewPtr
{
public:
	T* Pointer;
};

template <class T, unsigned int InitialSize, class U>
class hkInplaceArray : hkArray<T, U>
{
public:
	T Storage[InitialSize];
};

template <class T>
class hkPadSpu
{
public:
	T Storage;
};

struct hkMultiThreadCheck
{
	unsigned int m_threadId;
	int m_stackTraceId;
	unsigned __int16 m_markCount;
	unsigned __int16 m_markBitStack;
};

struct hkContainerHeapAllocator
{

};

struct  hkBool
{
	char m_bool;
};

struct  hkVector4f
{
	__m128 m_quad;
};

struct hkBaseObjectVtbl;
struct hkBaseObject
{
	hkBaseObjectVtbl* vfptr;
};

struct hkBaseObjectVtbl
{
	void*(__thiscall *__vecDelDtor)(hkBaseObject* This, unsigned int);
	void(__thiscall *__first_virtual_table_function__)(hkBaseObject* This);
};

struct hkReferencedObject : hkBaseObject
{
	unsigned int m_memSizeAndRefCount;
};

typedef hkcdShapeType_ShapeTypeEnum hkcdShapeDispatchType_ShapeDispatchTypeEnum;
const struct hkcdShape : hkReferencedObject
{
	hkEnum<hkcdShapeType_ShapeTypeEnum, unsigned char> m_type;
	hkEnum<hkcdShapeDispatchType_ShapeDispatchTypeEnum, unsigned char> m_dispatchType;
	char m_bitsPerKey;
	hkEnum<hkcdShapeInfoCodecType_ShapeInfoCodecTypeEnum, unsigned char> m_shapeInfoCodecType;
};

struct hkpShapeBase : hkcdShape
{

};

const struct hkpShape : hkpShapeBase
{
	unsigned int m_userData;
};

struct hkHalf
{
	__int16 m_value;
};

struct hkSimdFloat32
{
	__m128 m_real;
};

struct hkAabbUint32
{
	unsigned int m_min[3];
	char m_expansionMin[3];
	char m_expansionShift;
	unsigned int m_max[3];
	char m_expansionMax[3];
	char m_shapeKeyByte;
};

struct  hkpCollidable_BoundingVolumeData
{
	unsigned int m_min[3];
	char m_expansionMin[3];
	char m_expansionShift;
	unsigned int m_max[3];
	char m_expansionMax[3];
	char m_padding;
	unsigned __int16 m_numChildShapeAabbs;
	unsigned __int16 m_capacityChildShapeAabbs;
	hkAabbUint32 *m_childShapeAabbs;
	unsigned int *m_childShapeKeys;
};

/*
struct hkpBroadPhaseHandle
{
	unsigned int m_id;
};*/

struct hkpTypedBroadPhaseHandle : hkpBroadPhaseHandle
{
	char m_type;
	char m_ownerOffset;
	char m_objectQualityType;
	unsigned int m_collisionFilterInfo;
};

const struct  hkpCdBody
{
	hkpShape *m_shape;
	unsigned int m_shapeKey;
	const void *m_motion;
	hkpCdBody *m_parent;
};

const struct hkpCollidable : hkpCdBody
{
	char m_ownerOffset;
	char m_forceCollideOntoPpu;
	unsigned __int16 m_shapeSizeOnSpu;
	hkpTypedBroadPhaseHandle m_broadPhaseHandle;
	hkpCollidable_BoundingVolumeData m_boundingVolumeData;
	float m_allowedPenetrationDepth;
};

struct hkpAgentEntry
{
	char m_streamCommand;
	char m_agentType;
	char m_numContactPoints;
	char m_size;
};

typedef hkpConstraintAtom_AtomType hkpContactMgr_Type;
struct hkpContactMgr : hkReferencedObject
{
	hkpContactMgr_Type m_type;
};

struct hkpLinkedCollidable;
struct hkpAgentNnEntry : hkpAgentEntry
{
	unsigned __int16 m_agentIndexOnCollidable[2];
	hkpContactMgr *m_contactMgr;
	char m_collisionQualityIndex;
	char m_forceCollideOntoPpu;
	hkEnum<enum hkpAgentNnTrackType, unsigned char> m_nnTrackType;
	char m_padding;
	hkpLinkedCollidable *m_collidable[2];
};

struct hkpLinkedCollidable_CollisionEntry
{
	hkpAgentNnEntry *m_agentEntry;
	hkpLinkedCollidable *m_partner;
};

struct hkStringPtr
{
	const char* m_stringAndFlag;
};

struct hkpLinkedCollidable : hkpCollidable
{
	hkArray<hkpLinkedCollidable_CollisionEntry, hkContainerHeapAllocator> m_collisionEntries;
};

struct  hkSimplePropertyValue
{
	unsigned __int64 m_data;
};

struct  hkSimpleProperty
{
	unsigned int m_key;
	unsigned int m_alignmentPadding;
	hkSimplePropertyValue m_value;
};

struct hkpWorld;
const struct  hkpWorldObject : hkReferencedObject
{
	hkpWorld *m_world;
	unsigned int m_userData;
	hkpLinkedCollidable m_collidable;
	hkMultiThreadCheck m_multiThreadCheck;
	hkStringPtr m_name;
	hkArray<hkSimpleProperty, hkContainerHeapAllocator> m_properties;
};

struct hkpMaterial
{
	hkEnum<hkpMaterial_ResponseType, signed char> m_responseType;
	hkHalf m_rollingFrictionMultiplier;
	float m_friction;
	float m_restitution;
};

struct  hkpBreakableBody_Controller : hkReferencedObject
{
	float m_breakingImpulse;
};

struct hkRefCountedProperties_Entry
{
	hkRefPtr<hkReferencedObject> m_object;
	unsigned __int16 m_key;
	unsigned __int16 m_flags;
};

struct hkRefCountedProperties
{
	hkArray<hkRefCountedProperties_Entry, hkContainerHeapAllocator> m_entries;
};

struct hkpBreakableMaterial : hkReferencedObject
{
	float m_strength;
	int m_typeAndFlags;
	hkRefCountedProperties* m_properties;
};

const struct hkpBreakableShape : hkReferencedObject
{
	hkRefPtr<hkcdShape const > m_physicsShape;
	hkRefPtr<hkpBreakableMaterial> m_material;
};

struct hkpBreakableBody : hkReferencedObject
{
	hkRefPtr<hkpBreakableBody_Controller> m_controller;
	hkRefPtr<hkpBreakableShape const > m_breakableShape;
	char m_bodyTypeAndFlags;
	hkHalf m_constraintStrength;
};

struct hkpConstraintData : hkReferencedObject
{
	unsigned int m_userData;
};

struct  hkpConstraintAtom
{
	hkEnum<hkpConstraintAtom_AtomType, unsigned short> m_type;
};

struct hkpModifierConstraintAtom : hkpConstraintAtom
{
	__declspec(align(16)) unsigned __int16 m_modifierAtomSize;
	unsigned __int16 m_childSize;
	hkpConstraintAtom *m_child;
	unsigned int m_pad[2];
};

const struct hkClassEnum_Item
{
	int m_value;
	const char *m_name;
};

struct hkClass;
struct hkVariant
{
	void *m_object;
	hkClass *m_class;
};

const struct hkCustomAttributes_Attribute
{
	const char *m_name;
	hkVariant m_value;
};

struct hkCustomAttributes
{
	hkCustomAttributes_Attribute *m_attributes;
	int m_numAttributes;
};

typedef hkpConstraintAtom_AtomType hkClassMember_Type;
typedef hkClassMember_FlagValues hkClassEnum_FlagValues;
const struct hkClassEnum
{
	const char *m_name;
	hkClassEnum_Item *m_items;
	int m_numItems;
	hkCustomAttributes *m_attributes;
	hkFlags<hkClassEnum_FlagValues, unsigned int> m_flags;
};

const struct hkClassMember
{
	const char *m_name;
	hkClass *m_class;
	hkClassEnum *m_enum;
	hkEnum<hkClassMember_Type, unsigned char> m_type;
	hkEnum<hkClassMember_Type, unsigned char> m_subtype;
	__int16 m_cArraySize;
	hkFlags<enum hkClassMember_FlagValues, unsigned short> m_flags;
	unsigned __int16 m_offset;
	hkCustomAttributes *m_attributes;
};

typedef hkClassMember_FlagValues hkClass_FlagValues;
const struct hkClass
{
	const char *m_name;
	hkClass *m_parent;
	int m_objectSize;
	int m_numImplementedInterfaces;
	hkClassEnum *m_declaredEnums;
	int m_numDeclaredEnums;
	hkClassMember *m_declaredMembers;
	int m_numDeclaredMembers;
	const void *m_defaults;
	hkCustomAttributes *m_attributes;
	hkFlags<hkClass_FlagValues, unsigned int> m_flags;
	int m_describedVersion;
};

struct hkpConstraintTrackerData : hkReferencedObject
{

};

struct hkpConstraintInstance;
const struct  hkpConstraintRepairedEvent
{
	hkpWorld *m_world;
	hkpConstraintInstance *m_constraintInstance;
	hkClass *m_eventSource;
	hkpConstraintTrackerData *m_eventSourceDetails;
};

const struct  hkpConstraintBrokenEvent
{
	hkpWorld *m_world;
	hkpConstraintInstance *m_constraintInstance;
	hkClass *m_eventSource;
	hkpConstraintTrackerData *m_eventSourceDetails;
	float m_actualImpulse;
	float m_impulseLimit;
};

struct hkpConstraintOwner;
struct hkpConstraintListenerVtbl;
struct hkpConstraintListener
{
	hkpConstraintListenerVtbl *vfptr;
};

struct hkpConstraintListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpConstraintListener *This, unsigned int);
	void(__thiscall *constraintAddedCallback)(hkpConstraintListener *This, hkpConstraintInstance *);
	void(__thiscall *constraintRemovedCallback)(hkpConstraintListener *This, hkpConstraintInstance *);
	void(__thiscall *constraintDeletedCallback)(hkpConstraintListener *This, hkpConstraintInstance *);
	void(__thiscall *constraintViolatedCallback)(hkpConstraintListener *This, hkpConstraintInstance *);
	void(__thiscall *constraintBreakingCallback)(hkpConstraintListener *This, hkpConstraintBrokenEvent *);
	void(__thiscall *constraintRepairedCallback)(hkpConstraintListener *This, hkpConstraintRepairedEvent *);
};

struct hkConstraintInternal;
struct hkpEntity;
struct hkpConstraintInstance : hkReferencedObject
{
	hkpConstraintOwner *m_owner;
	hkpConstraintData *m_data;
	hkpModifierConstraintAtom *m_constraintModifiers;
	hkpEntity *m_entities[2];
	hkEnum<hkpConstraintInstance_ConstraintPriority, unsigned char> m_priority;
	hkBool m_wantRuntime;
	hkEnum<hkpConstraintInstance_OnDestructionRemapInfo, unsigned char> m_destructionRemapInfo;
	hkSmallArray<hkpConstraintListener *> m_listeners;
	hkStringPtr m_name;
	unsigned int m_userData;
	hkConstraintInternal *m_internal;
	unsigned int m_uid;
};

struct  __declspec(align(8)) hkConstraintInternal
{
	hkpConstraintInstance *m_constraint;
	hkpEntity *m_entities[2];
	hkpConstraintAtom *m_atoms;
	unsigned __int16 m_atomsSize;
	char m_callbackRequest;
	hkEnum<hkpConstraintInstance_ConstraintPriority, unsigned char> m_priority;
	unsigned __int16 m_numSolverResults;
	unsigned int m_sizeOfSchemas;
	unsigned int m_numSolverElemTemps;
	char m_whoIsMaster;
	hkEnum<hkpConstraintInstance_InstanceType, unsigned char> m_constraintType;
	struct hkpConstraintRuntime *m_runtime;
	unsigned __int16 m_runtimeSize;
	unsigned __int16 m_slaveIndex;
};

struct hkpEntity_SpuCollisionCallback
{
	struct hkSpuCollisionCallbackUtil *m_util;
	unsigned __int16 m_capacity;
	char m_eventFilter;
	char m_userFilter;
};

struct hkMatrix3f
{
	hkVector4f m_col0;
	hkVector4f m_col1;
	hkVector4f m_col2;
};

struct hkRotationf : hkMatrix3f
{

};

struct hkTransformf
{
	hkRotationf m_rotation;
	hkVector4f m_translation;
};

struct hkQuaternionf
{
	hkVector4f m_vec;
};

struct hkSweptTransformf
{
	hkVector4f m_centerOfMass0;
	hkVector4f m_centerOfMass1;
	hkQuaternionf m_rotation0;
	hkQuaternionf m_rotation1;
	hkVector4f m_centerOfMassLocal;
};

struct  hkUFloat8
{
	char m_value;
};

struct  __declspec(align(4)) hkMotionState
{
	hkTransformf m_transform;
	hkSweptTransformf m_sweptTransform;
	hkVector4f m_deltaAngle;
	float m_objectRadius;
	hkHalf m_linearDamping;
	hkHalf m_angularDamping;
	hkHalf m_timeFactor;
	hkUFloat8 m_maxLinearVelocity;
	hkUFloat8 m_maxAngularVelocity;
	char m_deactivationClass;
};

struct hkpMaxSizeMotion;
struct hkpMotion : hkReferencedObject
{
	hkEnum<hkpMotion_MotionType, unsigned char> m_type;
	char m_deactivationIntegrateCounter;
	unsigned __int16 m_deactivationNumInactiveFrames[2];
	hkMotionState m_motionState;
	hkVector4f m_inertiaAndMassInv;
	hkVector4f m_linearVelocity;
	hkVector4f m_angularVelocity;
	hkVector4f m_deactivationRefPosition[2];
	unsigned int m_deactivationRefOrientation[2];
	hkpMaxSizeMotion *m_savedMotion;
	unsigned __int16 m_savedQualityTypeIndex;
	hkHalf m_gravityFactor;
};

struct  hkpKeyframedRigidMotion : hkpMotion
{

};

struct hkpMaxSizeMotion : hkpKeyframedRigidMotion
{

};

struct hkpContactListenerVtbl;
struct  hkpContactListener
{
	void* vfptr; //hkpContactListenerVtbl *vfptr;
};

/*union $20C0711F3BD00BFDA4FDF4C04305F6AC
{
	void(__thiscall *hkpContactListener)(hkpContactListener *This);
	void *(__thiscall *__vecDelDtor)(hkpContactListener *This, unsigned int);
};

struct hkpContactListenerVtbl
{
	void(__thiscall *contactPointCallback)(hkpContactListener *This, hkpContactPointEvent *);
	void(__thiscall *collisionAddedCallback)(hkpContactListener *This, hkpCollisionEvent *);
	void(__thiscall *collisionRemovedCallback)(hkpContactListener *This, hkpCollisionEvent *);
	$20C0711F3BD00BFDA4FDF4C04305F6AC ___u3;
	void(__thiscall *contactPointAddedCallback)(hkpContactListener *This, hkpContactPointAddedEvent *);
	void(__thiscall *contactPointRemovedCallback)(hkpContactListener *This, hkpContactPointRemovedEvent *);
	void(__thiscall *contactProcessCallback)(hkpContactListener *This, hkpContactProcessEvent *);
};*/

struct hkLocalFrame : hkReferencedObject
{

};

struct hkpEntityActivationListenerVtbl;
struct  hkpEntityActivationListener
{
	hkpEntityActivationListenerVtbl *vfptr;
};

struct hkpEntityActivationListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpEntityActivationListener *This, unsigned int);
	void(__thiscall *entityDeactivatedCallback)(hkpEntityActivationListener *This, hkpEntity *);
	void(__thiscall *entityActivatedCallback)(hkpEntityActivationListener *This, hkpEntity *);
};

struct hkpEntityListenerVtbl;
struct  hkpEntityListener
{
	hkpEntityListenerVtbl *vfptr;
};

struct hkpEntityListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpEntityListener *This, unsigned int);
	void(__thiscall *entityAddedCallback)(hkpEntityListener *This, hkpEntity *);
	void(__thiscall *entityRemovedCallback)(hkpEntityListener *This, hkpEntity *);
	void(__thiscall *entityShapeSetCallback)(hkpEntityListener *This, hkpEntity *);
	void(__thiscall *entitySetMotionTypeCallback)(hkpEntityListener *This, hkpEntity *);
	void(__thiscall *entityDeletedCallback)(hkpEntityListener *This, hkpEntity *);
};

struct hkpEntity_ExtendedListeners
{
	hkSmallArray<hkpEntityActivationListener *> m_activationListeners;
	hkSmallArray<hkpEntityListener *> m_entityListeners;
};

struct hkpAction;
struct hkpSimulationIsland;
struct __declspec(align(8)) hkpEntity : hkpWorldObject
{
	hkpMaterial m_material;
	void* m_limitContactImpulseUtilAndFlag;
	float m_damageMultiplier;
	hkpBreakableBody* m_breakableBody;
	unsigned int m_solverData;
	unsigned __int16 m_storageIndex;
	unsigned __int16 m_contactPointCallbackDelay;
	hkSmallArray<hkConstraintInternal> m_constraintsMaster;
	hkArray<hkViewPtr<hkpConstraintInstance>, hkContainerHeapAllocator> m_constraintsSlave;
	hkArray<unsigned char, hkContainerHeapAllocator> m_constraintRuntime;
	hkpSimulationIsland* m_simulationIsland;
	char m_autoRemoveLevel;
	char m_numShapeKeysInContactPointProperties;
	char m_responseModifierFlags;
	unsigned int m_uid;
	hkpEntity_SpuCollisionCallback m_spuCollisionCallback;
	hkpMaxSizeMotion m_motion;
	hkSmallArray<hkpContactListener*> m_contactListeners;
	hkSmallArray<hkpAction*> m_actions;
	hkRefPtr<hkLocalFrame> m_localFrame;
	hkpEntity_ExtendedListeners *m_extendedListeners;
	unsigned int m_npData;
};

struct hkpRigidBody : hkpEntity
{

};

struct hkpConstraintInfo
{
	int m_maxSizeOfSchema;
	int m_sizeOfSchemas;
	int m_numSolverResults;
	int m_numSolverElemTemps;
};

struct hkpConstraintOwner : hkReferencedObject
{
	hkpConstraintInfo m_constraintInfo;
};

struct hkpAction : hkReferencedObject
{
	hkpWorld* m_world;
	hkpSimulationIsland* m_island;
	unsigned int m_userData;
	hkStringPtr m_name;
};

struct hkpAgentNnSector
{
	char m_data[512];
};

struct hkpAgentNnTrack
{
	unsigned __int16 m_bytesUsedInLastSector;
	hkEnum<hkpAgentNnTrackType, unsigned char> m_nnTrackType;
	char m_padding;
	hkInplaceArray<hkpAgentNnSector*, 1, hkContainerHeapAllocator> m_sectors;
};

struct  hkpWorldMaintenanceMgr : hkReferencedObject
{

};

struct  hkWorldMemoryAvailableWatchDog : hkReferencedObject
{

};

/*
struct hkpBroadPhaseHandle
{
	unsigned int m_id;
};*/

struct hkCriticalSection
{
	_RTL_CRITICAL_SECTION m_section;
};

struct hkpBroadPhaseHandlePair
{
	hkpBroadPhaseHandle *m_a;
	hkpBroadPhaseHandle *m_b;
};

struct hkpTypedBroadPhaseHandlePair : hkpBroadPhaseHandlePair
{

};

struct hkpBroadPhaseListenerVtbl;
struct  hkpBroadPhaseListener
{
	hkpBroadPhaseListenerVtbl *vfptr;
};

struct hkpBroadPhaseListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpBroadPhaseListener* This, unsigned int);
	void(__thiscall *addCollisionPair)(hkpBroadPhaseListener* This, hkpTypedBroadPhaseHandlePair *);
	void(__thiscall *removeCollisionPair)(hkpBroadPhaseListener* This, hkpTypedBroadPhaseHandlePair *);
};

struct hkpBroadPhaseListener;
struct hkpWorld;
struct hkpEntityEntityBroadPhaseListener : hkReferencedObject, hkpBroadPhaseListener
{
	hkpWorld *m_world;
};

struct hkpNullBroadPhaseListener : hkReferencedObject, hkpBroadPhaseListener
{

};

struct hkpPhantomBroadPhaseListener : hkReferencedObject, hkpBroadPhaseListener
{

};

struct hkpBroadPhaseBorderListener : hkReferencedObject, hkpBroadPhaseListener
{

};

const struct hkpConvexListFilter : hkReferencedObject
{

};

struct hkpBodyOperation : hkReferencedObject
{

};

struct hkpViolatedConstraintArray
{
	unsigned int m_nextFreeElement;
	hkpConstraintInstance *m_constraints[128];
};

struct  __declspec(align(8)) hkpConstraintQueryStepInfo
{
	hkPadSpu<float> m_subStepDeltaTime;
	hkPadSpu<float> m_microStepDeltaTime;
	hkPadSpu<float> m_subStepInvDeltaTime;
	hkPadSpu<float> m_frameDeltaTime;
	hkPadSpu<float> m_frameInvDeltaTime;
	hkPadSpu<float> m_invNumSteps;
	hkPadSpu<float> m_invNumStepsTimesMicroSteps;
	hkPadSpu<float> m_maxConstraintViolationSqrd;
	hkPadSpu<float> m_rhsFactor;
	hkPadSpu<float> m_virtMassFactor;
	hkPadSpu<float> m_frictionRhsFactor;
};

struct  hkpVelocityAccumulator
{
	hkEnum<hkpVelocityAccumulator_hkpAccumulatorType, unsigned char> m_type;
	hkEnum<hkpVelocityAccumulator_hkpAccumulatorContext, unsigned char> m_context;
	unsigned int m_deactivationClass;
	float m_gravityFactor;
	hkVector4f m_linearVel;
	hkVector4f m_angularVel;
	hkVector4f m_invMasses;
	hkVector4f m_scratch0;
	hkVector4f m_scratch1;
	hkVector4f m_scratch2;
	hkVector4f m_scratch3;
};

struct  hkpJacobianSchema
{

};

struct hkpConstraintQueryOut
{
	hkPadSpu<hkpJacobianSchema *> m_jacobianSchemas;
	hkPadSpu<void*> m_constraintRuntime; //hkPadSpu<hkpConstraintRuntime *> m_constraintRuntime;
	hkPadSpu<void*> m_instanceRuntime; //hkPadSpu<hkpConstraintRuntime *> m_instanceRuntime;
};

struct hkpSolverResults
{
	float m_impulseApplied;
	float m_internalSolverData;
};

struct __declspec(align(16)) hkpConstraintQueryIn : hkpConstraintQueryStepInfo
{
	hkPadSpu<hkpVelocityAccumulator const *> m_bodyA;
	hkPadSpu<hkpVelocityAccumulator const *> m_bodyB;
	hkPadSpu<hkTransformf const *> m_transformA;
	hkPadSpu<hkTransformf const *> m_transformB;
	hkPadSpu<float> m_tau;
	hkPadSpu<float> m_damping;
	hkSimdFloat32 m_maxConstraintViolationSqrd;
	hkPadSpu<hkpConstraintInstance *> m_constraintInstance;
	hkPadSpu<hkpViolatedConstraintArray *> m_violatedConstraints;
	hkPadSpu<unsigned int> m_accumulatorAIndex;
	hkPadSpu<unsigned int> m_accumulatorBIndex;
	void(__cdecl *m_beginConstraints)(hkpConstraintQueryIn *, hkpConstraintQueryOut *, hkpSolverResults *, int);
};

/*struct hkpCollisionInput
{
	hkPadSpu<hkpCollisionDispatcher *> m_dispatcher;
	hkPadSpu<unsigned int> m_weldClosestPoints;
	hkPadSpu<unsigned int> m_forceAcceptContactPoints;
	hkPadSpu<float> m_tolerance;
	hkPadSpu<hkpCollisionFilter const *> m_filter;
	hkPadSpu<hkpConvexListFilter const *> m_convexListFilter;
	hkPadSpu<unsigned int> m_createPredictiveAgents;
	hkpCollisionInput::Aabb32Info m_aabb32Info;
};

const struct __declspec(align(16)) hkpProcessCollisionInput : hkpCollisionInput
{
	hkStepInfo m_stepInfo;
	hkPadSpu<hkpCollisionQualityInfo *> m_collisionQualityInfo;
	hkpAgent1nSector *m_spareAgentSector;
	void *m_dynamicsInfo;
	hkBool m_enableDeprecatedWelding;
	hkBool m_allowToSkipConfirmedCallbacks;
	hkpCollisionAgentConfig *m_config;
};

struct hkpMtThreadStructure
{
	hkpWorld *m_world;
	hkpConstraintQueryIn m_constraintQueryIn;
	hkpProcessCollisionInput m_collisionInput;
	hkPadSpu<hkpMultiThreadedSimulation *> m_simulation;
	hkPadSpu<hkpWorldDynamicsStepInfo *> m_dynamicsStepInfo;
	hkPadSpu<float> m_tolerance;
	hkPadSpu<void *> m_weldingTable;
};*/

struct  hkpShapeCollectionFilter
{
	void* vfptr; //hkpShapeCollectionFilterVtbl *vfptr;
};

/*union $DB708AFE12D2077C3C966BBE2FB79F55
{
	void(__thiscall *~hkpShapeCollectionFilter)(hkpShapeCollectionFilter *this);
	void *(__thiscall *__vecDelDtor)(hkpShapeCollectionFilter *this, unsigned int);
};

struct hkpShapeCollectionFilterVtbl
{
	hkBool *(__thiscall *isCollisionEnabled)(hkpShapeCollectionFilter *this, hkBool *result, hkpCollisionInput *, hkpCdBody *, hkpCdBody *, hkpShapeContainer *, hkpShapeContainer *, unsigned int, unsigned int);
	hkBool *(__thiscall *isCollisionEnabled)(hkpShapeCollectionFilter *this, hkBool *result, hkpCollisionInput *, hkpCdBody *, hkpCdBody *, hkpShapeContainer *, unsigned int);
	int(__thiscall *numShapeKeyHitsLimitBreached)(hkpShapeCollectionFilter *this, hkpCollisionInput *, hkpCdBody *, hkpCdBody *, hkpBvTreeShape *, hkAabb *, unsigned int *, int);
	$DB708AFE12D2077C3C966BBE2FB79F55 ___u3;
};*/

struct  hkpRayCollidableFilter
{
	void* vfptr; //hkpRayCollidableFilterVtbl *vfptr;
};

/*struct hkpRayCollidableFilterVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpRayCollidableFilter *this, unsigned int);
	hkBool *(__thiscall *isCollisionEnabled)(hkpRayCollidableFilter *this, hkBool *result, hkpWorldRayCastInput *, hkpCollidable *);
};*/

struct  hkpRayShapeCollectionFilter
{
	void* vfptr; //hkpRayShapeCollectionFilterVtbl *vfptr;
};

/*union $0F6C60C68858AB00AD8D78AF440D4A68
{
	void(__thiscall *~hkpRayShapeCollectionFilter)(hkpRayShapeCollectionFilter *this);
	void *(__thiscall *__vecDelDtor)(hkpRayShapeCollectionFilter *this, unsigned int);
};

struct hkpRayShapeCollectionFilterVtbl
{
	hkBool *(__thiscall *isCollisionEnabled)(hkpRayShapeCollectionFilter *this, hkBool *result, hkpShapeRayCastInput *, hkpShapeContainer *, unsigned int);
	$0F6C60C68858AB00AD8D78AF440D4A68 ___u1;
};*/

struct hkpCollidableCollidableFilterVtbl;
struct  hkpCollidableCollidableFilter
{
	hkpCollidableCollidableFilterVtbl *vfptr;
};

struct hkpCollidableCollidableFilterVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpCollidableCollidableFilter* This, unsigned int);
	hkBool *(__thiscall *isCollisionEnabled)(hkpCollidableCollidableFilter* This, hkBool *result, hkpCollidable *, hkpCollidable *);
};

const struct hkpCollisionFilter : hkReferencedObject, hkpCollidableCollidableFilter, hkpShapeCollectionFilter, hkpRayShapeCollectionFilter, hkpRayCollidableFilter
{
	unsigned int m_prepad[2];
	hkEnum<hkpCollisionFilter_hkpFilterType, unsigned int> m_type;
	unsigned int m_postpad[3];
};

struct hkpTypedBroadPhaseDispatcher
{
	hkpBroadPhaseListener* m_broadPhaseListeners[8][8];
	hkpNullBroadPhaseListener m_nullBroadPhaseListener;
};

struct hkWorldOperation_BaseOperation
{
	hkEnum<hkWorldOperation_Type, unsigned char> m_type;
};

struct hkpBodyOperationEntry
{
	hkpEntity *m_entity;
	hkpBodyOperation *m_operation;
	int m_priority;
	hkpBodyOperation_ExecutionState m_hint;
};

struct  hkWorldOperation_BiggestOperation : hkWorldOperation_BaseOperation
{
	unsigned int dummy[7];
};

struct hkpWorldOperationQueue
{
	hkArray<hkWorldOperation_BiggestOperation, hkContainerHeapAllocator> m_pending;
	hkpWorld* m_world;
	hkArray<hkWorldOperation_BiggestOperation, hkContainerHeapAllocator> m_islandMerges;
	hkArray<hkpBodyOperationEntry, hkContainerHeapAllocator> m_pendingBodyOperations;
};

struct hkpDebugInfoOnPendingOperationQueues
{
	hkArray<hkWorldOperation_BiggestOperation, hkContainerHeapAllocator> *m_pending;
	int m_nextPendingOperationIndex;
	hkpDebugInfoOnPendingOperationQueues *m_nextQueue;
	hkpDebugInfoOnPendingOperationQueues *m_prevQueue;
};

struct hkpActionListenerVtbl;
struct hkpActionListener
{
	hkpActionListenerVtbl *vfptr;
};

struct hkpActionListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpActionListener* This, unsigned int);
	void(__thiscall *actionAddedCallback)(hkpActionListener* This, hkpAction *);
	void(__thiscall *actionRemovedCallback)(hkpActionListener* This, hkpAction *);
};

struct hkpIslandActivationListener
{
	void* vfptr; //hkpIslandActivationListenerVtbl *vfptr;
};

struct hkpWorldPostSimulationListener
{
	void* vfptr; //hkpWorldPostSimulationListenerVtbl *vfptr;
};

struct hkpWorldPostIntegrateListener
{
	void* vfptr; //hkpWorldPostIntegrateListenerVtbl *vfptr;
};

struct hkpWorldPostCollideListener
{
	void* vfptr; //hkpWorldPostCollideListenerVtbl *vfptr;
};

struct hkpIslandPostIntegrateListener
{
	void* vfptr; //hkpIslandPostIntegrateListenerVtbl *vfptr;
};

struct hkpIslandPostCollideListener
{
	void* vfptr; //hkpIslandPostCollideListenerVtbl *vfptr;
};

struct  hkpContactImpulseLimitBreachedListener
{
	void* vfptr; //hkpContactImpulseLimitBreachedListenerVtbl *vfptr;
};

/*
struct hkpContactImpulseLimitBreachedListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpContactImpulseLimitBreachedListener *this, unsigned int);
	void(__thiscall *contactImpulseLimitBreachedCallback)(hkpContactImpulseLimitBreachedListener *this, hkpContactImpulseLimitBreachedListenerInfo *, int);
};*/

struct  __declspec(align(4)) hkpWorldExtension : hkReferencedObject
{
	hkpWorld *m_world;
	int m_id;
	unsigned __int16 m_attachmentCount;
};

/*
struct hkpIslandActivationListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpIslandActivationListener *this, unsigned int);
	void(__thiscall *islandActivatedCallback)(hkpIslandActivationListener *this, hkpSimulationIsland *);
	void(__thiscall *islandDeactivatedCallback)(hkpIslandActivationListener *this, hkpSimulationIsland *);
};

struct hkpWorldPostSimulationListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpWorldPostSimulationListener *this, unsigned int);
	void(__thiscall *postSimulationCallback)(hkpWorldPostSimulationListener *this, hkpWorld *);
	void(__thiscall *inactiveEntityMovedCallback)(hkpWorldPostSimulationListener *this, hkpEntity *);
};

struct hkpWorldPostIntegrateListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpWorldPostIntegrateListener *this, unsigned int);
	void(__thiscall *postIntegrateCallback)(hkpWorldPostIntegrateListener *this, hkpWorld *, hkStepInfo *);
};

struct hkpWorldPostCollideListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpWorldPostCollideListener *this, unsigned int);
	void(__thiscall *postCollideCallback)(hkpWorldPostCollideListener *this, hkpWorld *, hkStepInfo *);
};

struct hkpIslandPostIntegrateListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpIslandPostIntegrateListener *this, unsigned int);
	void(__thiscall *postIntegrateCallback)(hkpIslandPostIntegrateListener *this, hkpSimulationIsland *, hkStepInfo *);
};

struct hkpIslandPostCollideListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpIslandPostCollideListener *this, unsigned int);
	void(__thiscall *postCollideCallback)(hkpIslandPostCollideListener *this, hkpSimulationIsland *, hkStepInfo *);
};*/

struct  hkpWorldDeletionListener
{
	void* vfptr; //hkpWorldDeletionListenerVtbl *vfptr;
};

/*
struct hkpWorldDeletionListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpWorldDeletionListener *this, unsigned int);
	void(__thiscall *worldDeletedCallback)(hkpWorldDeletionListener *this, hkpWorld *);
	void(__thiscall *worldRemoveAllCallback)(hkpWorldDeletionListener *this, hkpWorld *);
};*/

struct  hkpPhantomOverlapListener
{
	void* vfptr; //hkpPhantomOverlapListenerVtbl *vfptr;
};

/*union $93E351A694271900E797B5F48EF9CD61
{
	void(__thiscall *~hkpPhantomOverlapListener)(hkpPhantomOverlapListener *this);
	void *(__thiscall *__vecDelDtor)(hkpPhantomOverlapListener* This, unsigned int);
};

struct hkpPhantomOverlapListenerVtbl
{
	void(__thiscall *collidableAddedCallback)(hkpPhantomOverlapListener *this, hkpCollidableAddedEvent *);
	void(__thiscall *collidableRemovedCallback)(hkpPhantomOverlapListener *this, hkpCollidableRemovedEvent *);
	$93E351A694271900E797B5F48EF9CD61 ___u2;
};*/

struct hkpPhantomListener
{
	void* vfptr; //hkpPhantomListenerVtbl *vfptr;
};

/*struct hkpPhantomListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpPhantomListener *this, unsigned int);
	void(__thiscall *phantomAddedCallback)(hkpPhantomListener *this, hkpPhantom *);
	void(__thiscall *phantomRemovedCallback)(hkpPhantomListener *this, hkpPhantom *);
	void(__thiscall *phantomShapeSetCallback)(hkpPhantomListener *this, hkpPhantom *);
	void(__thiscall *phantomDeletedCallback)(hkpPhantomListener *this, hkpPhantom *);
};*/

// struct hkpIslandActivationListener
// {
// 	void* vfptr; //hkpIslandActivationListenerVtbl *vfptr;
// };

/*
struct hkpIslandActivationListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(hkpIslandActivationListener *this, unsigned int);
	void(__thiscall *islandActivatedCallback)(hkpIslandActivationListener *this, hkpSimulationIsland *);
	void(__thiscall *islandDeactivatedCallback)(hkpIslandActivationListener *this, hkpSimulationIsland *);
};*/

struct hkpPhantom : hkpWorldObject
{
	hkArray<hkpPhantomOverlapListener*, hkContainerHeapAllocator> m_overlapListeners;
	hkArray<hkpPhantomListener*, hkContainerHeapAllocator> m_phantomListeners;
};

struct hkpBroadPhaseBorder : hkReferencedObject, hkpWorldDeletionListener, hkpPhantomOverlapListener, hkpWorldPostSimulationListener
{
	hkpWorld* m_world;
	hkpPhantom* m_phantoms[6];
	hkpWorldCinfo_BroadPhaseBorderBehaviour m_type;
	hkBool m_postponeAndSortCallbacks;
	hkArray<hkpEntity*, hkContainerHeapAllocator> m_entitiesExitingBroadPhase;
};

struct havok_bpo : hkpBroadPhaseHandle
{
	char flags;
	char state;
	__int16 bpo_index;
	__int16 state_index;
	unsigned __int16 owner;
	unsigned __int16 next;
	unsigned __int16 prev;
	void *user_data;
};

struct hkpBroadPhase : hkReferencedObject
{
	const unsigned __int16 m_type;
	const unsigned __int16 m_size;
	const unsigned int m_caps;
	hkMultiThreadCheck m_multiThreadCheck;
	hkCriticalSection* m_criticalSection;
};

struct hkpSimulationIsland : hkpConstraintOwner
{
	hkpWorld* m_world;
	int m_numConstraints;
	unsigned __int16 m_storageIndex;
	unsigned __int16 m_dirtyListIndex;
	char m_splitCheckFrameCounter;
	__int8 m_splitCheckRequested : 2;
	__int8 m_isSparse : 2;
	__int8 m_actionListCleanupNeeded : 2;
	__int8 m_allowIslandLocking : 2;
	__int8 m_isInActiveIslandsArray : 2;
	__int8 m_activeMark : 2;
	__int8 m_tryToIncreaseIslandSizeMark : 2;
	__int8 m_inIntegrateJob : 2;
	hkMultiThreadCheck m_multiThreadCheck;
	float m_timeSinceLastHighFrequencyCheck;
	float m_timeSinceLastLowFrequencyCheck;
	hkArray<hkpAction*, hkContainerHeapAllocator> m_actions;
	float m_timeOfDeactivation;
	hkInplaceArray<hkpEntity *, 1, hkContainerHeapAllocator> m_entities;
	hkpAgentNnTrack m_midphaseAgentTrack;
	hkpAgentNnTrack m_narrowphaseAgentTrack;
};

struct hkStepInfo
{
	hkPadSpu<float> m_startTime;
	hkPadSpu<float> m_endTime;
	hkPadSpu<float> m_deltaTime;
	hkPadSpu<float> m_invDeltaTime;
};

struct hkpSolverInfo_DeactivationInfo
{
	float m_linearVelocityThresholdInv;
	float m_angularVelocityThresholdInv;
	float m_slowObjectVelocityMultiplier;
	float m_relativeSleepVelocityThreshold;
	float m_maxDistSqrd[2];
	float m_maxRotSqrd[2];
};

struct  __declspec(align(16)) hkpSolverInfo
{
	float m_padding;
	float m_tau;
	float m_damping;
	float m_frictionTau;
	hkVector4f m_globalAccelerationPerSubStep;
	hkVector4f m_globalAccelerationPerStep;
	hkVector4f m_integrateVelocityFactor;
	hkVector4f m_invIntegrateVelocityFactor;
	float m_dampDivTau;
	float m_tauDivDamp;
	float m_dampDivFrictionTau;
	float m_frictionTauDivDamp;
	float m_contactRestingVelocity;
	hkpSolverInfo_DeactivationInfo m_deactivationInfo[6];
	float m_deltaTime;
	float m_invDeltaTime;
	int m_numSteps;
	int m_numMicroSteps;
	float m_invNumMicroSteps;
	float m_invNumSteps;
	hkBool m_forceCoherentConstraintOrderingInSolver;
	char m_deactivationNumInactiveFramesSelectFlag[2];
	char m_deactivationIntegrateCounter;
	float m_maxConstraintViolationSqrd;
};

struct hkpWorldDynamicsStepInfo
{
	hkStepInfo m_stepInfo;
	hkpSolverInfo m_solverInfo;
};

struct hkpSimulation : hkReferencedObject
{
	unsigned int m_determinismCheckFrameCounter;
	hkpWorld *m_world;
	hkEnum<hkpSimulation_LastProcessingStep, unsigned char> m_lastProcessingStep;
	float m_currentTime;
	float m_currentPsiTime;
	float m_physicsDeltaTime;
	float m_simulateUntilTime;
	float m_frameMarkerPsiSnap;
	unsigned int m_previousStepResult;
};

struct __declspec(align(16)) hkpWorld : hkReferencedObject
{
	hkpSimulation* m_simulation;
	hkVector4f m_gravity;
	hkpSimulationIsland* m_fixedIsland;
	hkpRigidBody* m_fixedRigidBody;
	hkArray<hkpSimulationIsland*, hkContainerHeapAllocator> m_activeSimulationIslands;
	hkArray<hkpSimulationIsland*, hkContainerHeapAllocator> m_inactiveSimulationIslands;
	hkArray<hkpSimulationIsland*, hkContainerHeapAllocator> m_dirtySimulationIslands;
	hkpWorldMaintenanceMgr* m_maintenanceMgr;
	hkRefPtr<hkWorldMemoryAvailableWatchDog> m_memoryWatchDog;
	hkBool m_assertOnRunningOutOfSolverMemory;
	hkEnum<hkpWorldCinfo_BroadPhaseType, signed char> m_broadPhaseType;
	hkpBroadPhase* m_broadPhase;
	hkpTypedBroadPhaseDispatcher* m_broadPhaseDispatcher;
	hkpPhantomBroadPhaseListener* m_phantomBroadPhaseListener;
	hkpEntityEntityBroadPhaseListener* m_entityEntityBroadPhaseListener;
	hkpBroadPhaseBorderListener* m_broadPhaseBorderListener;
	void* m_multithreadedSimulationJobData; //hkpMtThreadStructure* m_multithreadedSimulationJobData;
	void* m_collisionInput; //hkpProcessCollisionInput* m_collisionInput;
	hkpCollisionFilter* m_collisionFilter;
	void* m_collisionDispatcher;//hkpCollisionDispatcher* m_collisionDispatcher;
	hkpConvexListFilter* m_convexListFilter;
	hkpWorldOperationQueue* m_pendingOperations;
	int m_pendingOperationsCount;
	int m_pendingBodyOperationsCount;
	int m_criticalOperationsLockCount;
	int m_criticalOperationsLockCountForPhantoms;
	hkBool m_blockExecutingPendingOperations;
	hkBool m_criticalOperationsAllowed;
	hkpDebugInfoOnPendingOperationQueues* m_pendingOperationQueues;
	int m_pendingOperationQueueCount;
	hkMultiThreadCheck m_multiThreadCheck;
	hkBool m_processActionsInSingleThread;
	hkBool m_allowIntegrationOfIslandsWithoutConstraintsInASeparateJob;
	unsigned int m_minDesiredIslandSize;
	hkCriticalSection* m_modifyConstraintCriticalSection;
	int m_isLocked;
	hkCriticalSection* m_islandDirtyListCriticalSection;
	hkCriticalSection* m_propertyMasterLock;
	hkBool m_wantSimulationIslands;
	float m_snapCollisionToConvexEdgeThreshold;
	float m_snapCollisionToConcaveEdgeThreshold;
	hkBool m_enableToiWeldRejection;
	hkBool m_wantDeactivation;
	hkBool m_shouldActivateOnRigidBodyTransformChange;
	float m_deactivationReferenceDistance;
	float m_toiCollisionResponseRotateNormal;
	int m_maxSectorsPerMidphaseCollideTask;
	int m_maxSectorsPerNarrowphaseCollideTask;
	hkBool m_processToisMultithreaded;
	int m_maxEntriesPerToiMidphaseCollideTask;
	int m_maxEntriesPerToiNarrowphaseCollideTask;
	int m_maxNumToiCollisionPairsSinglethreaded;
	hkEnum<hkpWorldCinfo_SimulationType, int> m_simulationType;
	float m_numToisTillAllowedPenetrationSimplifiedToi;
	float m_numToisTillAllowedPenetrationToi;
	float m_numToisTillAllowedPenetrationToiHigher;
	float m_numToisTillAllowedPenetrationToiForced;
	unsigned int m_lastEntityUid;
	unsigned int m_lastIslandUid;
	unsigned int m_lastConstraintUid;
	hkArray<hkpPhantom*, hkContainerHeapAllocator> m_phantoms;
	hkArray<hkpActionListener*, hkContainerHeapAllocator> m_actionListeners;
	hkArray<hkpEntityListener*, hkContainerHeapAllocator> m_entityListeners;
	hkArray<hkpPhantomListener*, hkContainerHeapAllocator> m_phantomListeners;
	hkArray<hkpConstraintListener*, hkContainerHeapAllocator> m_constraintListeners;
	hkArray<hkpWorldDeletionListener*, hkContainerHeapAllocator> m_worldDeletionListeners;
	hkArray<hkpIslandActivationListener*, hkContainerHeapAllocator> m_islandActivationListeners;
	hkArray<hkpWorldPostSimulationListener*, hkContainerHeapAllocator> m_worldPostSimulationListeners;
	hkArray<hkpWorldPostIntegrateListener*, hkContainerHeapAllocator> m_worldPostIntegrateListeners;
	hkArray<hkpWorldPostCollideListener*, hkContainerHeapAllocator> m_worldPostCollideListeners;
	hkArray<hkpIslandPostIntegrateListener*, hkContainerHeapAllocator> m_islandPostIntegrateListeners;
	hkArray<hkpIslandPostCollideListener*, hkContainerHeapAllocator> m_islandPostCollideListeners;
	hkArray<hkpContactListener*, hkContainerHeapAllocator> m_contactListeners;
	hkArray<hkpContactImpulseLimitBreachedListener*, hkContainerHeapAllocator> m_contactImpulseLimitBreachedListeners;
	hkArray<hkpWorldExtension*, hkContainerHeapAllocator> m_worldExtensions;
	hkpViolatedConstraintArray* m_violatedConstraintArray;
	hkpBroadPhaseBorder* m_broadPhaseBorder;
	struct hkdWorld* m_destructionWorld;
	struct hknpWorld* m_npWorld;
	hkpWorldDynamicsStepInfo m_dynamicsStepInfo;
	hkVector4f m_broadPhaseExtents[2];
	int m_broadPhaseNumMarkers;
	int m_sizeOfToiEventQueue;
	int m_broadPhaseQuerySize;
	int m_broadPhaseUpdateSize;
	hkEnum<hkpWorldCinfo_ContactPointGeneration, signed char> m_contactPointGeneration;
	hkBool m_useCompoundSpuElf;
};
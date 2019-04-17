#pragma once
#include "RFGR_Containers.h"

struct rl_base_objectVtbl;
struct rl_base_object;
struct rl_3d_entity;
//struct __declspec(align(16)) rl_scene_entity;
//struct rl_camera;
struct rl_renderer_metrics;
struct rl_hdr_state;
class vector;
class matrix;
struct matrix23;
class matrix43;
struct vector2;
struct rl_bvolume;
struct rl_sphere;
class Player;
//struct rl_partition_system;
//struct rl_partition_sector;
//struct rl_partition_sector_entry;
//struct linked_list_p;// <rl_partition_sector_entry>;

enum rl_light_light_type
{
	LIGHT_TYPE_DIRECTIONAL = 0x0,
	LIGHT_TYPE_POINT = 0x1,
	LIGHT_TYPE_SPOT_LIGHT = 0x2,
	LIGHT_TYPE_FORCE_SIZEOF_INT = 0xFFFFFFFF,
};

enum voice_line_handle
{
	INVALID_VOICE_LINE_HANDLE = 0xFFFFFFFF,
	VOICE_LINE_HANDLE_IS_DLC = 0x8000,
	VOICE_LINE_HANDLE_FORCE_TO_32_BIT = 0x7FFFFFFF,
};

enum game_clock_time_of_day
{
	GC_INVALID = 0xFFFFFFFF,
	GC_DAY = 0x0,
	GC_NIGHT = 0x1,
	GC_TIME_OF_DAY_COUNT = 0x2,
};

enum game_clock_tod_partitioned
{
	GC_EARLY_DAY = 0x0,
	GC_MID_DAY = 0x1,
	GC_LATE_DAY = 0x2,
	GC_EARLY_NIGHT = 0x3,
	GC_MID_NIGHT = 0x4,
	GC_LATE_NIGHT = 0x5,
	NUM_TOD_PARTITIONS = 0x6,
};

enum vint_res_offset
{
	VINT_RES_OFFSET_INHERIT = 0x0,
	VINT_RES_OFFSET_START = 0x1,
	VINT_RES_OFFSET_CENTER = 0x2,
	VINT_RES_OFFSET_END = 0x3,
	VINT_RES_OFFSET_NEG_START = 0x4,
	VINT_RES_OFFSET_NEG_START_TWICE = 0x5,
	VINT_RES_OFFSET_NEG_START_X = 0x6,
	VINT_RES_OFFSET_NEG_START_Y = 0x7,
	NUM_VINT_RES_OFFSET = 0x8,
};

enum vint_res_scale
{
	VINT_RES_SCALE_INHERIT = 0x0,
	VINT_RES_SCALE_MAINTAIN_RATIO = 0x1,
	VINT_RES_SCALE_FILL = 0x2,
	VINT_RES_SCALE_CUTOFF = 0x3,
	VINT_RES_SCALE_CUTOFF_X = 0x4,
	VINT_RES_SCALE_CUTOFF_Y = 0x5,
	NUM_VINT_RES_SCALE = 0x6,
};

/* 617 */
enum HumanTeams
{
	HUMAN_TEAM_NONE = 0xFFFFFFFF,
	HUMAN_TEAM_GUERILLA = 0x0,
	HUMAN_TEAM_EDF = 0x1,
	HUMAN_TEAM_CIVILIAN = 0x2,
	HUMAN_TEAM_MP_NEUTRAL = 0x2,
	HUMAN_TEAM_MARAUDER = 0x3,
	HUMAN_TEAM_MP_SPECTATOR = 0x3,
	NUM_HUMAN_TEAMS = 0x4,
};

enum xray_effect_types
{
	XET_VISION_BACKPACK = 0x0,
	XET_RAIL_DRIVER = 0x1,
	NUM_XRAY_EFFECT_TYPES = 0x2,
};

enum debug_text_posn
{
	DT_TOP_LEFT = 0x0,
	DT_TOP_RIGHT = 0x1,
	DT_BOT_LEFT = 0x2,
	DT_BOT_RIGHT = 0x3,
	DT_CENTER_LEFT = 0x4,
	DT_CENTER_RIGHT = 0x5,
	DT_LAST = 0x6,
};

enum SalvageMaterialType
{
	INVALID_SALVAGE_MATERIAL = 0xFFFFFFFF,
	SALVAGE_MATERIAL_METAL = 0x0,
	SALVAGE_MATERIAL_ORE = 0x1,
	SALVAGE_MATERIAL_CHEMICAL = 0x2,
	NUM_SALVAGE_MATERIAL_TYPES = 0x3,
};

/* 600 */
enum GeneralActionTypes
{
	GENERAL_ACTION_TYPE_INVALID = 0xFFFFFFFF,
	GENERAL_ACTION_MP_USE_DISARM = 0x0,
	GENERAL_ACTION_MP_SWAP_BACKPACK = 0x1,
	GENERAL_ACTION_MP_MODE_SPECIFIC = 0x2,
	GENERAL_ACTION_DIALOGUE = 0x3,
	GENERAL_ACTION_USE_TURRET = 0x4,
	GENERAL_ACTION_USE_EQUIPPED_ITEM = 0x5,
	GENERAL_ACTION_USE_NEAREST_OBJECT = 0x6,
	GENERAL_ACTION_USE_VEHICLE = 0x7,
	GENERAL_ACTION_USE_LADDER = 0x8,
	GENERAL_ACTION_USE_AMMO_BOX = 0x9,
	GENERAL_ACTION_RELEASE_HOSTAGE = 0xA,
	GENERAL_ACTION_USE_BASE = 0xB,
	GENERAL_ACTION_START_MISSION = 0xC,
	GENERAL_ACTION_START_DEMOLITIONS_MASTER = 0xD,
	GENERAL_ACTION_START_RIDING_SHOTGUN = 0xE,
	GENERAL_ACTION_START_HOUSE_ARREST = 0xF,
	GENERAL_ACTION_START_OFFENSIVE_RAID = 0x10,
	GENERAL_ACTION_UPGRADE = 0x11,
	GENERAL_ACTION_START_AREA_DEFENSE = 0x12,
	NUM_GENERAL_ACTION_TYPES = 0x13,
};

enum UseObjectIcon
{
	USE_OBJECT_ICON_INVALID = 0xFFFFFFFF,
	USE_OBJECT_ICON_SWAP = 0x0,
	USE_OBJECT_ICON_DEFAULT = 0x1,
	USE_OBJECT_ICON_HYDROGEN_TANK = 0x2,
	USE_OBJECT_ICON_LADDER = 0x3,
	USE_OBJECT_ICON_VEHICLE = 0x4,
	USE_OBJECT_ICON_MISSION = 0x5,
	USE_OBJECT_ICON_DEMOLITION_GUERRILLA = 0x6,
	USE_OBJECT_ICON_DEMOLITION_EDF = 0x7,
	USE_OBJECT_ICON_BAGMAN_GUERRILLA = 0x8,
	USE_OBJECT_ICON_BAGMAN_EDF = 0x9,
	USE_OBJECT_ICON_UPGRADE = 0xA,
	NUM_PAOI_TYPES = 0xB,
};

enum HumanRagdollState
{
	HUMAN_RAGDOLL_STATE_NONE = 0x0,
	HUMAN_RAGDOLL_STATE_ACTIVE = 0x1,
	HUMAN_RAGDOLL_STATE_BLEND_OUT = 0x2,
	HUMAN_RAGDOLL_STATE_FLINCH = 0x3,
	HUMAN_RAGDOLL_STATE_ACTIVE_ON_IMPACT = 0x4,
	HUMAN_RAGDOLL_STATE_DEACTIVATED = 0x5,
	HUMAN_RAGDOLL_STATE_POSE_SAVED = 0x6,
	NUM_HUMAN_RAGDOLL_STATES = 0x7,
};

enum TaggingSequence
{
	TAGGING_SEQUENCE_NONE = 0xFFFFFFFF,
	TAGGING_SEQUENCE_START = 0x0,
	TAGGING_SEQUENCE_TAG = 0x1,
	TAGGING_SEQUENCE_DONE = 0x2,
	NUM_TAGGING_SEQUENCES = 0x3,
};

enum PlayerZoomState
{
	PZS_OFF = 0x0,
	PZS_SPRINT = 0x1,
	PZS_FINE_AIM = 0x2,
	PZS_SCOPE = 0x3,
};

enum HudMessageHandle
{
	INVALID_HUD_MESSAGE_HANDLE = 0xFFFFFFFF,
	HUD_MESSAGE_HANDLE_FORCE_TO_32_BIT = 0x7FFFFFFF,
};

enum PlayerScriptMode
{
	PSM_NONE = 0x0,
	PSM_VEHICLE_ENTER = 0x1,
	NUM_PLAYER_SCRIPT_MODES = 0x2,
};

enum PlayerCoverTest
{
	PCT_CHECK_COVER_NORMAL = 0x0,
	PCT_THREE_FRAME_DELAY = 0x1,
	PCT_TWO_FRAME_DELAY = 0x2,
	PCT_ONE_FRAME_DELAY = 0x3,
	PCT_CROUCH = 0x4,
	PCT_VERIFY_COVER = 0x5,
	PCT_DONE = 0x6,
};

enum InterfaceModes
{
	INT_MODE_NONE = 0xFFFFFFFF,
	INT_MODE_NORMAL = 0x0,
	INT_MODE_NO_CONTROL = 0x1,
	INT_MODE_MULTIPLAYER_REMOTE_CLIENT = 0x2,
	INT_MODE_PDA = 0x3,
	INT_MODE_PRE_RACING_IN_VEHICLE = 0x4,
	INT_MODE_RACING_WO_COMBAT_IN_VEHICLE = 0x5,
	INT_MODE_RACING_WO_COMBAT_STANDING = 0x6,
	INT_MODE_MULTI_PRE_RACING = 0x7,
	INT_MODE_MULTI_RACING = 0x8,
	INT_MODE_MULTI_RACING_GUNNER = 0x9,
	NUM_INT_MODES = 0xA,
};

enum cf_search_types
{
	CF_SEARCH_NONE = 0xFFFFFFFF,
	CF_SEARCH_STANDARD = 0x0,
	CF_SEARCH_PACKFILE = 0x1,
	CF_SEARCH_VDIR = 0x2,
	CF_SEARCH_NUM_TYPES = 0x3,
};

enum cf_io_media_types
{
	CF_IO_MEDIA_NONE = 0xFFFFFFFF,
	CF_IO_MEDIA_HDD = 0x0,
	CF_IO_MEDIA_DVD = 0x1,
	CF_IO_MEDIA_HOST = 0x2,
	CF_IO_MEDIA_MEMORY = 0x5,
	CF_IO_MEDIA_NUM_TYPES = 0x6,
};

enum cf_io_access_types
{
	CF_IO_ACCESS_NONE = 0xFFFFFFFF,
	CF_IO_ACCESS_STANDARD = 0x0,
	CF_IO_ACCESS_PACKFILE = 0x1,
	CF_IO_ACCESS_MEMORY = 0x2,
	CF_IO_ACCESS_UNKNOWN = 0x3,
	CF_IO_ACCESS_NUM_TYPES = 0x4,
};

enum cfmode_type
{
	CF_MODE_NONE = 0x0,
	CF_MODE_READ = 0x1,
	CF_MODE_WRITE = 0x2,
};

enum cf_error_codes
{
	CF_ERROR_NONE = 0x0,
	CF_ERROR_READ = 0x1,
	CF_ERROR_WRITE = 0x2,
	CF_ERROR_ABORT = 0x3,
	CF_ERROR_NUM_CODES = 0x4,
};

struct timestamp_realtime
{
	int value;
};

/* 5492 */
struct MultiTimestamp //4
{
	int Value;
};

/* 5493 */
struct MultiTimestampPercent : MultiTimestamp //8
{
	int SetMilliseconds; //4
};

struct Timestamp //4
{
	int value;
};

struct TimestampPercent : Timestamp //8
{
	int set_milliseconds;
};

namespace keen
{
	struct GraphicsMatrix43
	{
		float row0[4];
		float row1[4];
		float row2[4];
	};

	struct GraphicsMatrix44
	{
		float row0[4];
		float row1[4];
		float row2[4];
		float row3[4];
	};

	struct String
	{
		const char* pStart;
		const char* pEnd;
	};

	struct float2
	{
		float x;
		float y;
	};

	struct float3
	{
		float x;
		float y;
		float z;
	};

	struct float4
	{
		float x;
		float y;
		float z;
		float w;
	};
};


class vector
{
public:
	vector() 
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};
	vector(const vector& CopyVector)
	{
		x = CopyVector.x;
		y = CopyVector.y;
		z = CopyVector.z;
	}
	vector(float InitialValue) : x(InitialValue), y(InitialValue), z(InitialValue) { }
	vector(float x_, float y_, float z_) : x(x_), y(y_), z(z_) { }
	vector operator+(const vector& B)
	{
		return vector(x + B.x, y + B.y, z + B.z);
	}
	vector operator-(const vector& B)
	{
		return vector(x - B.x, y - B.y, z - B.z);
	}
	float operator*(const vector& B)
	{
		return (x * B.x) + (y * B.y) + (z * B.z);
	}
	bool operator==(const vector& B)
	{
		return (x == B.x && y == B.y && z == B.z);
	}
	bool operator!=(const vector& B)
	{
		return !(*this == B);
	}
	vector& operator=(const vector& B)
	{
		x = B.x;
		y = B.y;
		z = B.z;
		return *this;
	}
	vector Cross(const vector& B)
	{
		vector C;
		C.x = (y * B.z) - (B.y * z);
		C.y = (B.x * z) - (y * B.z);
		C.z = (x * B.y) - (B.x * y);
		return C;
	}
	float Magnitude()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	void SetAll(float Value)
	{
		x = Value;
		y = Value;
		z = Value;
	}
	std::string GetDataString(bool Parentheses, bool Labels)
	{
		std::string String;
		if(Parentheses)
		{
			String += "(";
		}
		if (Labels)
		{
			String += "x: ";

		}
		String += std::to_string(x);
		String += ", ";
		if (Labels)
		{
			String += "y: ";

		}
		String += std::to_string(y);
		String += ", ";
		if(Labels)
		{
			String += "z: ";
		}
		String += std::to_string(z);
		if (Parentheses)
		{
			String += ")";
		}
		return String;
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

class matrix //3x3
{
public:
	matrix() 
	{
		rvec.SetAll(0.0f);
		uvec.SetAll(0.0f);
		fvec.SetAll(0.0f);
	}
	matrix(const matrix& CopyMatrix)
	{
		rvec = CopyMatrix.rvec;
		uvec = CopyMatrix.uvec;
		fvec = CopyMatrix.fvec;
	}
	matrix(float InitialValue)
	{
		rvec.SetAll(InitialValue);
		uvec.SetAll(InitialValue);
		fvec.SetAll(InitialValue);
	}
	matrix(vector Right, vector Up, vector Forward)
	{
		rvec = Right;
		uvec = Up;
		fvec = Forward;
	}
	matrix operator+(const matrix& B)
	{
		return matrix(rvec + B.rvec, uvec + B.uvec, fvec + B.fvec);
	}
	matrix operator-(const matrix& B)
	{
		return matrix(rvec - B.rvec, uvec - B.uvec, fvec - B.fvec);
	}
	bool operator==(const matrix& B)
	{
		return(rvec == B.rvec && uvec == B.uvec && fvec == B.fvec);
	}
	bool operator!=(const matrix& B)
	{
		return !(*this == B);
	}
	matrix operator=(const matrix& B)
	{
		rvec = B.rvec;
		uvec = B.uvec;
		fvec = B.fvec;
		return *this;
	}
	void SetAll(float Value)
	{
		rvec.SetAll(Value);
		uvec.SetAll(Value);
		fvec.SetAll(Value);
	}

	vector rvec;
	vector uvec;
	vector fvec;
};

struct matrix23
{
	matrix23() { }
	float elem[2][3];
};

class matrix43
{
public:
public:
	matrix43()
	{
		m_rotation.SetAll(0.0f);
		m_translation.SetAll(0.0f);
	}
	matrix43(const matrix43& CopyMatrix)
	{
		m_rotation = CopyMatrix.m_rotation;
		m_translation = CopyMatrix.m_translation;
	}
	matrix43(float InitialValue)
	{
		m_rotation.SetAll(InitialValue);
		m_translation.SetAll(InitialValue);
	}
	matrix43(matrix Rotation, vector Translation)
	{
		m_rotation = Rotation;
		m_translation = Translation;
	}
	matrix43 operator+(const matrix43& B)
	{
		return matrix43(m_rotation + B.m_rotation, m_translation + B.m_translation);
	}
	matrix43 operator-(const matrix43& B)
	{
		return matrix43(m_rotation - B.m_rotation, m_translation - B.m_translation);
	}
	bool operator==(const matrix43& B)
	{
		return(m_rotation == B.m_rotation && m_translation == B.m_translation);
	}
	bool operator!=(const matrix43& B)
	{
		return !(*this == B);
	}
	void SetAll(float Value)
	{
		m_rotation.SetAll(Value);
		m_translation.SetAll(Value);
	}
	matrix m_rotation;
	vector m_translation;
};

struct matrix44
{
	matrix44() {}
	float elem[4][4];
	//$EFBF005ED9B80EDE8789D61FAD0B4E5B ___u0;
};

class vector2
{
public:
	vector2() 
	{
		x = 0.0f;
		y = 0.0f;
	}
	vector2(const vector2& Copy)
	{
		x = Copy.x;
		y = Copy.y;
	}
	vector2(float InitialValue) : x(InitialValue), y(InitialValue) { }
	vector2(float x_, float y_) : x(x_), y(y_) { }
	vector2 operator+(const vector2& B)
	{
		return vector2(x + B.x, y + B.y);
	}
	vector2 operator-(const vector2& B)
	{
		return vector2(x - B.x, y - B.y);
	}
	float operator*(const vector2& B)
	{
		return (x * B.x) + (y * B.y);
	}
	bool operator==(const vector2& B)
	{
		return (x == B.x && y == B.y);
	}
	bool operator!=(const vector2& B)
	{
		return !(*this == B);
	}
	void operator=(const vector2& B)
	{
		x = B.x;
		y = B.y;
	}
	float Magnitude()
	{
		return sqrtf((x * x) + (y * y));
	}
	void SetAll(float Value)
	{
		x = Value;
		y = Value;
	}
	std::string GetDataString(bool Parentheses, bool Labels)
	{
		std::string String;
		if (Parentheses)
		{
			String += "(";
		}
		if (Labels)
		{
			String += "x: ";

		}
		String += std::to_string(x);
		String += ", ";
		if (Labels)
		{
			String += "y: ";

		}
		String += std::to_string(y);
		if (Parentheses)
		{
			String += ")";
		}
		return String;
	}

	float x;
	float y;
};

/* 3928 */
struct cf_keen_open_file
{
	unsigned int Gandle;
	void* FileSystem;///keen::FileSystem *m_pFileSystem;
	unsigned int m_flags;
	unsigned int m_async_num_bytes_to_transfer;
	unsigned int m_async_pad_bytes;
	unsigned int m_async_num_pad_bytes_to_transfer;
	unsigned int m_async_num_bytes_read;
};

struct v_packfile;

/* 3929 */
struct v_packfile_entry
{
	char* name;
	unsigned int sector;
	unsigned int start;
	unsigned int hash;
	unsigned int size;
	unsigned int compressed_size;
	v_packfile* parent;
};

/* 5329 */
struct PackfileEntrySerializedPointerOffset
{
	int m_offset;
};

/* 3931 */
struct PackfileEntrySerializedParentOffset
{
	int m_offset;
};

/* 3932 */
struct v_packfile_entry_serialized
{
	PackfileEntrySerializedPointerOffset name;
	unsigned int sector;
	unsigned int start;
	unsigned int hash;
	unsigned int size;
	unsigned int compressed_size;
	PackfileEntrySerializedParentOffset parent;
};

/* 3933 */
struct v_packfile
{
	unsigned int descriptor;
	unsigned int version;
	char short_name[65];
	char pathname[256];
	unsigned int flags;
	unsigned int sector;
	unsigned int num_files;
	unsigned int file_size;
	unsigned int dir_size;
	unsigned int filename_size;
	unsigned int data_size;
	unsigned int compressed_data_size;
	v_packfile_entry *dir;
	v_packfile_entry_serialized *dir_serialized;
	char *filenames;
	char *data;
};

/* 3934 */
struct keen_cf_packfile_handle
{
	cf_keen_open_file *file_handle;
	v_packfile_entry *packfile_entry;
};

/* 3935 */
struct cf_memory_handle
{
	char *buf;
	unsigned int size;
	bool compressed;
	unsigned int compressed_size;
};

/* 3936 */
union FileObjectPointers
{
	cf_keen_open_file *m_standard_fp;
	keen_cf_packfile_handle *m_packfile_fp;
	cf_memory_handle *_m_memory_fp;
};

/* 3937 */
struct FileObject
{
	char name[65];
	char full_pathname[257];
	cf_search_types m_searched_system;
	cf_io_access_types m_access_type;
	FileObjectPointers Pointers;
	cf_io_media_types m_media_type;
	cfmode_type mode;
	cf_error_codes m_error_code;
	unsigned int pos;
	unsigned int size;
	unsigned int max_write_size;
	unsigned int m_flags;
};

/* 5472 */
struct CustomVehicleFlags //8 Bytes
{
	unsigned __int32 IsTotaled : 1; //4
	unsigned __int32 IsInGarage : 1; //4
};

/* 5471 */
struct CustomVehicle //20 Bytes
{
	CustomVehicle* Previous; //4
	CustomVehicle* Next; //4
	int TypeIndex; //4
	CustomVehicleFlags Flags; //8
};

/* 5464 */
struct VehicleControlFlags //3
{
	__int8 BrakeReverse : 1; //1
	__int8 Handbrake : 1; //1
	__int8 Honk : 1; //1
};

/* 5465 */
union VehicleControlContainer //4
{
	VehicleControlFlags Flags; //3
	char Controls; //1
};

/* 5466 */
struct VehicleControls //12
{
	VehicleControlContainer Controls; //4
	float Accelerate; //4
	float Steering; //4
};

/* 5468 */
struct UseableObject //24 Bytes
{
	unsigned int handle; //4
	GeneralActionTypes action_type; //4
	UseObjectIcon action_icon; //4
	float dot_prod; //4
	float dist_squared; //4
	bool(__cdecl* action_callback)(Player*, bool); //4
};

/* 5470 */
struct PlayerFlags //176 Bytes
{
	unsigned __int32 ActionNodeAnimStarted : 1; //4
	unsigned __int32 CustomMesh : 1; //4
	unsigned __int32 IsLoaded : 1; //4
	unsigned __int32 ScriptControlled : 1; //4
	unsigned __int32 NeverDie : 1; //4
	unsigned __int32 MissionNeverDie : 1; //4
	unsigned __int32 DoSprint : 1; //4
	unsigned __int32 DisableControls : 1; //4
	unsigned __int32 JetpackStarted : 1; //4
	unsigned __int32 JetpackReady : 1; //4
	unsigned __int32 MovingToAStop : 1; //4
	unsigned __int32 QuickTurn : 1; //4
	unsigned __int32 CrouchingState : 1; //4
	unsigned __int32 WeaponHidden : 1; //4
	unsigned __int32 IsStuck : 1; //4
	unsigned __int32 CoverFiring : 1; //4
	unsigned __int32 CoverLeanup : 1; //4
	unsigned __int32 UseCover : 1; //4
	unsigned __int32 NoReticule : 1; //4
	unsigned __int32 NoFineaim : 1; //4
	unsigned __int32 CoverSearchForEdge : 1; //4
	unsigned __int32 CoverAgainstVehicle : 1; //4
	unsigned __int32 InCommTowerRange : 1; //4
	unsigned __int32 CommRangeChecked : 1; //4
	unsigned __int32 PassengerBrake : 1; //4
	unsigned __int32 LocalPlayerHitSomeoneThisFrame : 1; //4
	unsigned __int32 WeaponSwapLock : 1; //4
	unsigned __int32 UnlimitedAmmo : 1; //4
	unsigned __int32 InRadiation : 1; //4
	unsigned __int32 RagdollOnNextExplosion : 1; //4
	unsigned __int32 LeavingSquadMemberBehind : 1; //4
	unsigned __int32 IsWaitingForHostageVehicleExit : 1; //4
	unsigned __int32 BackpackFadeOut : 1; //4
	unsigned __int32 BackpackFadeIn : 1; //4
	unsigned __int32 MP_DisplayRespawnMsg : 1; //4
	unsigned __int32 MP_RemotePlayerFiredThisFrame : 1; //4
	unsigned __int32 MP_IgnorePlayerForRespawnCollisions : 1; //4
	unsigned __int32 MP_LostHP : 1; //4
	unsigned __int32 MP_HitSomeoneThisNetworkFrame : 1; //4
	unsigned __int32 MP_RemotePlayerChargedThisFrame : 1; //4
	unsigned __int32 MP_LocalPlayerCanSeeMe : 1; //4
	unsigned __int32 MP_HasReloaded : 1; //4
	unsigned __int32 MP_RemovingPlayer : 1; //4
	unsigned __int32 WaitingForLockerExit : 1; //4
};

/* 5412 */
struct ControlFlagsContainer//100 Bytes
{
	unsigned __int32 DoStop : 1; //4
	unsigned __int32 DoSprint : 1; //4
	unsigned __int32 DesiredWeaponSlot : 4; //4
	unsigned __int32 AttackType : 2; //4
	unsigned __int32 Jump : 1; //4
	unsigned __int32 Climb : 1; //4
	unsigned __int32 Accelerate : 8; //4
	unsigned __int32 BrakeReverse : 1; //4
	unsigned __int32 Handbrake : 1; //4
	unsigned __int32 Honk : 1; //4
	unsigned __int32 Action : 1; //4
	unsigned __int32 Pickup : 1; //4
	unsigned __int32 Reload : 1; //4
	unsigned __int32 Zoomed : 1; //4
	unsigned __int32 IsCrouching : 1; //4
	unsigned __int32 IsTakingMPDrug : 1; //4
	unsigned __int32 Ragdolled : 1; //4
	unsigned __int32 DoPant : 1; //4
	unsigned __int32 IsCombatBlocking : 1; //4
	unsigned __int32 Taunt : 2; //4
};

/* 5413 */
union ControlFlagsObject //104
{
	ControlFlagsContainer Flags; //100
	unsigned int Data; //4
};

/* 5414 */
struct ControlFlags //104
{
	ControlFlagsObject Flags; //104
};

/* 5487 */
struct GameCommand //268
{
	unsigned __int16 CommandID; //2
	float Forward; //4
	float Sideways;//4
	bool DoStop; //1
	bool DoSprint; //1 
	bool IsCrouching; //1
	matrix CameraOrient; //36
	vector CameraPos; //12
	unsigned int NetworkTime; //4
	int EquippedWeaponSlot; //4
	char EquippedWeaponIndex; //1
	char EquippedWeaponMagazineRounds; //1
	unsigned __int16 EquippedWeaponRoundsInReserve; //2
	bool Jump; //1
	bool StartJump; //1
	bool Climb; //1
	bool Action; //1
	bool Pickup; //1
	bool Reload; //1
	bool IsCombatBlocking; //1
	VehicleControls VControls; //12
	bool SetTurnToTarget; //1
	float ThrowPitch; //4
	float ThrowStrength; //4
	ControlFlags Flags; //104
	vector Position; //12
	vector LinearVelocity; //12
	vector AngularVelocity; //12
	vector2 LocalXZVelocity; //8
	bool InCar; //1
	bool ReceivedVehicleControlThisFrame; //1
	bool Correcting; //1
	Player* TargetedPlayer; //4
	vector MovementDirection; //12
};

/* 5420 */
struct __declspec(align(4)) VehicleEnterStruct //8
{
	unsigned int VehicleHandle; //4
	bool Run; //1
};

/* 5473 */
union ScriptSpecificData //8 Bytes
{
	VehicleEnterStruct VehicleEnterData; //8
};

/* 5488 */
struct PlayerStateMPFlags //21 * 4 = 84 Bytes
{
	unsigned __int32 EquipWeaponSlot : 3;
	unsigned __int32 DoSprint : 1;
	unsigned __int32 JumpID : 2;
	unsigned __int32 IsOnLadder : 1;
	unsigned __int32 Reload : 1;
	unsigned __int32 Jetpack : 1;
	unsigned __int32 IsZoomed : 1;
	unsigned __int32 DontDeformBones : 1;
	unsigned __int32 InAirDetonate : 1;
	unsigned __int32 RunningAttack : 1;
	unsigned __int32 DetonatedCharges : 1;
	unsigned __int32 ChargeWeapon : 2;
	unsigned __int32 MeleePrimaryID : 2;
	unsigned __int32 MeleeSecondaryID : 2;
	unsigned __int32 MeleeTertiaryID : 2;
	unsigned __int32 MeleeFirearmID : 2;
	unsigned __int32 FirearmTriggerDownID : 2;
	unsigned __int32 FirearmTriggerUpID : 2;
	unsigned __int32 ThrowAttackID : 2;
	unsigned __int32 IsCrouched : 1;
	unsigned __int32 PadBits : 1;
};

/* 5489 */
union PlayerStateMP //85
{
	PlayerStateMPFlags Flags; //84 
	unsigned int Data; //1
};

/* 5174 */
struct MultiObjectState //78
{
	vector Position; //12
	vector LinearVelocity; //12
	vector AngularVelocity; //12
	matrix Orientation; //36
	unsigned int NetworkTime; //4
};

/* 5424 */
struct MPLadderStateContainer //2
{
	char State; //1
	char Rung; //1
};

/* 5425 */
union MPLadderStateObject //4
{
	MPLadderStateContainer Flags; //2
	unsigned __int16 Data; //2
};

/* 5426 */
struct MPLadderState //4
{
	MPLadderStateObject Flags; //4
};

/* 5406 */
struct NetworkToGameHandle
{
	unsigned __int16 NetworkHandle;
	unsigned int GameHandle;
};

/* 5490 */
struct MultiplayerState : MultiObjectState // 170 + 78 = 248
{
	matrix CameraOrient; //36
	vector2 CameraAngularVelocity; //8
	float Forward; //4
	float Sideways; //4
	float HitPointsPercent; //4
	unsigned int LadderHandle; //4
	HumanRagdollState RagdollState; //4
	int KnockdownTimestamp; //4
	NetworkToGameHandle TurretHandle; //6
	NetworkToGameHandle VehicleHandle; //6
	char VehicleSeat; //1
	MPLadderState LadderState; //4
	PlayerStateMP State; //85
	unsigned __int16 WeaponMagazineAmmo; //2
	unsigned __int16 WeaponReserveAmmo; //2
};

/* 5491 */
struct MultiSimStateMP
{
	int StatesUsed;
	MultiplayerState States[25];
	Timestamp ApplyCorrectionTimestamp;
};

/* 5424 */
struct PlayerLadderStateContainer
{
	char State;
	char Rung;
};

/* 5425 */
union PlayerLadderStateObject
{
	PlayerLadderStateContainer Flags;
	unsigned __int16 Data;
};

/* 5494 */
struct PlayerLadderState //12
{
	PlayerLadderStateObject Flags; //4
	Timestamp RemoteLadderMountDelay; //4
	Timestamp LocalLadderMountDelay; //4
};

/* 5495 */
struct MultiplayerEdgeCorrectionInfo //8
{
	int IncreasingVelocityCount; //4
	float VerticalVelocity; //4
};

/* 5496 */
struct MultiplayerBlockedInfo //4
{
	int RaycastBlockedCount; //4
};

/* 5497 */
struct __declspec(align(8)) PathfindNavInfo //16
{
	unsigned __int64 LastVisitedVehicleNavCellHandle; //8
	Timestamp LastVisitedVehicleNavCellUpdateTimer; //4
};

/* 5498 */
struct DecalFadeData //8
{
	unsigned int Handle; //4
	float Opacity; //4
};

/* 5499 */
struct CircArrayDecalFadeData10 //88
{
	DecalFadeData Data[10]; //8 * 10 = 80
	int Num; //4
	int Offset; //4
};

/* 5500 */
struct DecalCircArrayQueue10 //92
{
	CircArrayDecalFadeData10 Array; //88
	int Num; //4
};

/* 5503 */
struct UpgradeItem //7 Bytes
{
	char current_level; //1
	unsigned __int16 availability_bitfield; //2
	unsigned __int16 unlocked_notified_bitfield; //2
	unsigned __int16 new_notified_bitfield; //2
};

struct PlayerMetadata //928 Bytes
{
	void* PlayerMetadataVtbl;//player_meta_dataVtbl* vfptr; //4
	int Salvage; //4
	int MiningCount; //4
	int SupplyCrateCount; //4
	unsigned int DistrictHash; //4
	int DistrictTime; //4
	UpgradeItem upgrades[128]; //896
	int PlayTime; //4
	int LastDeathTime; //4
};

struct PlayerPositionalRecord //16 Bytes
{
	vector pos; //12
	int period_ms; //4
};

const struct CameraViewTableEntry //82 Bytes?
{
	char *Name; //8 bytes
	int ChangeViewTime;
	int OutTimeOverride;
	int TargetFocusSpeed;
	int TerrainFocusSpeed;
	float FOVMin;
	float FOVMinSP;
	float FOVMax;
	float FovZoomPercent;
	float FocalDistanceMin;
	float FocalDistanceMax;
	float FocalRangeNear;
	float FocalRangeFar;
	float FocusedDistanceNormal;
	float FocusedDistanceZoom;
	float FocusedDistanceTargetMultiplier;
	float CameraDistance;
	bool UseDOF;
	bool UseWeaponFOV;
	bool UseFarValues;
	bool UseFOVZoom;
	bool OverrideWeaponZoom;
	bool OverrideWeaponMaxRange;
	unsigned int EffectHandle;
};

/* 6290 */
struct CameraViewData //117 Bytes
{
	float CameraDistance; //0x0
	float m_focused_distance; //0x4
	float m_focal_distance; //0x8
	float m_focal_range_near; //0xC
	float m_focal_range_far; //0x10
	float m_fov; //0x14
	bool m_dof_enable; //0x18
	CameraViewTableEntry* m_last_view;  //0x1C
	CameraViewTableEntry* m_current_view;  //0x20
	TimestampPercent m_transition_timestamp;  //0x24
	TimestampPercent m_target_zoom_timestamp;  //0x2C
	Timestamp m_lost_target;  //0x34
	unsigned int m_current_target; //0x38
	float m_temp_distance_override; //0x3C
	float m_last_camera_distance; //0x40
	float m_target_camera_distance; //0x44
	float m_last_focal_distance; //0x48
	float m_target_focal_distance; //0x4C
	float m_last_focused_distance; //0x50
	float m_target_focused_distance; //0x54
	float m_last_range_near; //0x58
	float m_target_range_near; //0x5C
	float m_last_range_far; //0x60
	float m_target_range_far; //0x64
	float m_last_fov; //0x68
	float m_target_fov; //0x6C
	float m_min_zoom; //0x70
	float m_max_zoom; //0x74
	float m_max_range; //0x78
	unsigned int m_effect_info_handle; //0x7C
	unsigned int m_effect_handle; //0x80
};

/*struct GraphicsStateObjectPool<BlendState>
{
	PoolAllocator<BlendState> m_allocator;
	GraphicsStateObjectCache m_cache;
	unsigned int m_peakSize;
	unsigned int m_cacheHits;
	unsigned int m_cacheRequests;
};

struct StockObjects;
{
	ShaderPipeline m_shaderPipelines[3];
	VertexShader* m_pStockVertexShaders[2];
	FragmentShader* m_pStockFragmentShaders[3];
	VertexFormat* m_pFormats[3];
	TextureData m_textures[1];
};

struct CombinedGraphicsStateObjectPool;
{
	GraphicsStateObjectPool<BlendState> m_blendStatePool;
	GraphicsStateObjectPool<RasterizerState> m_rasterizerStatePool;
	GraphicsStateObjectPool<SamplerState> m_samplerStatePool;
	GraphicsStateObjectPool<DepthStencilState> m_depthStencilStatePool;
	GraphicsStateObjectPool<VertexFormat> m_vertexFormatPool;
	GraphicsStateObjectPool<VertexInputBinding> m_vertexInputBindingPool;
};

struct GraphicsSystemBase
{
	void* pShaderFactory; //keen::ShaderFactory *pShaderFactory;
	void* pSystemAllocator; //keen::MemoryAllocator *pSystemAllocator;
	CombinedGraphicsStateObjectPool stateObjectPool;
	StockObjects stockObjects;
};

struct KeenGraphicsSystem : GraphicsSystemBase //Todo: Make Keen namespace eventually if it'll help organization.
{
	ID3D11Device *pDevice;
	ID3D11DeviceContext *pImmediateContext;
	float screenAspectRatio;
	HWND__* createdWindowHandle;
	bool isWindowDestroyed;
	SkinningD3D11 skinningBuffer;
	unsigned int ownerThreadId;
	unsigned int frontThreadId;
	GraphicsCommandBuffer immediateCommandBuffer;
	GraphicsCommandBuffer deferredCommandBuffer;
	FragmentShader emptyFragmentShader;
	RenderSwapChain* pDefaultSwapChain;
	RenderSwapChain* pCurrentSwapChain;
	unsigned int currentFrameNumber;
	ScreenCapture* pScreenCapture;
	WindowMode previousFullscreenMode;
	WindowMode fullscreenMode;
	unsigned int exclusiveModeWidth;
	unsigned int exclusiveModeHeight;
	unsigned int exclusiveModeRefreshRateNumerator;
	unsigned int exclusiveModeRefreshRateDenominator;
	unsigned int windowModeWidth;
	unsigned int windowModeHeight;
};*/

struct vector4 //16
{
	float x;
	float y;
	float z;
	float w;
};

/* 5181 */
const struct __declspec(align(4)) explosion_info //340 Bytes
{
	char m_name[32]; //32
	int m_unique_id; //4
	unsigned int m_name_crc_str; //4
	unsigned int flags; //4
	float m_radius; //4
	float m_secondary_radius; //4
	float m_knockdown_radius; //4
	float m_flinch_radius; //4
	float m_ai_sound_radius; //4
	unsigned int m_human_min_damage_hitpoints; //4
	unsigned int m_human_max_damage_hitpoints; //4
	unsigned int m_vehicle_min_damage_hitpoints; //4
	unsigned int m_vehicle_max_damage_hitpoints; //4
	float player_damage_mult; //4
	float player_veh_damage_mult; //4
	float player_vehicle_impulse_mult; //4
	float m_impulse_magnitude; //4
	int m_structural_damage; //4
	unsigned int expanding_explosion_duration; //4
	unsigned int expanding_explosion_delay; //4
	unsigned int m_num_effects; //4
	unsigned int m_effects[4]; //16
	unsigned int m_num_material_effects; //4
	unsigned int m_material_effects[8];  //32
	char m_material_referenece[8]; //8
	SalvageMaterialType salvage_material; //4
	int salvage_max_pieces; //4
	float salvage_probability; //4
	int time_between_breaks; //4
	float half_angle_dot; //4
	float blast_decal_radius; //4
	char camera_shake_type[32]; //128
	float camera_shake_multiplier; //4
	float camera_shake_falloff; //4
	bool ignore_orientation; //4
	bool always_ragdoll; //4
};

/* 5191 */
/*const struct weapon_info
{
	char *name;
	checksum_stri name_crc;
	int unique_id;
	weapon_info_flags flags;
	weapon_class_type weapon_class;
	item_info *weapon_obj_item_info;
	inv_item_info *weapon_inv_item_info;
	human_teams default_team;
	char *icon_name;
	char *small_icon_name;
	char *reticule_name;
	char *fine_aim_reticule_name;
	char *mp_kill_phrase;
	animation_group weapon_anim_group;
	unsigned int muzzle_flash_effect;
	unsigned int muzzle_smoke_effect;
	unsigned int special_hit_effect;
	unsigned int special_effect;
	unsigned int secondary_special_effect;
	unsigned int overheated_effect;
	unsigned int tracer_effect;
	camera_shake *fire_camera_shake;
	bool fire_camera_shake_ignore_disabled;
	camera_shake *secondary_camera_shake;
	camera_shake *player_hit_camera_shake;
	char attachment_point[32];
	int fire_sound;
	int secondary_sound;
	int upgrade_sound;
	int reload_sound;
	int reload_sound_delay;
	int no_ammo_sound;
	int special_sound;
	int flyby_sound;
	int num_weapon_personas;
	int npc_fire_sounds[16];
	float max_range;
	float red_range;
	float max_engagement_dist;
	float min_engagement_dist;
	float max_ai_penetrating_dist;
	weapon_firing_pattern *npc_firing_pattern;
	aim_drift_profile *npc_aim_drift_profile;
	weapon_trigger_type trigger_type;
	weapon_ammo_type ammo_type;
	unsigned __int16 magazine_size;
	unsigned __int16 magazine_start_num;
	unsigned __int16 max_rounds;
	unsigned __int16 max_rounds_upgrade;
	unsigned __int16 ammo_box_restock;
	unsigned __int16 to_min_spread;
	unsigned __int16 to_max_spread;
	char melee_group_index;
	char bullet_group_index;
	char tracer_frequency;
	char shots_per_round;
	float firing_sound_radius;
	float npc_refire_delay;
	float default_refire_delay;
	float prefire_delay;
	int default_reload_delay;
	damage_scaling_info low_scale_damage;
	damage_scaling_info high_scale_damage;
	explosion_info *m_explosion_info;
	explosion_info *m_ai_explosion_info;
	float fire_cone_dot;
	float even_spread_accuracy_dot;
	float max_spread;
	float min_spread;
	float fine_aim_max_spread;
	float fine_aim_min_spread;
	float npc_max_spread;
	float npc_min_spread;
	float spread_multiplier_run;
	float ragdoll_force_shoot;
	float ragdoll_chance;
	float recoil_camera_kick;
	float recoil_impulse;
	int out_of_ammo_reload_delay;
	float overheat_cool_down_time;
	float overheat_percent_per_shot;
	float dropped_ammo_scale;
	float bullet_hole_scale;
	float headshot_multiplier;
	float zoom_magnification;
	float autoaim_override;
	float npc_autoaim;
	float aim_assist;
	float player_move_speed_multiplier;
	float npc_move_speed_multiplier;
	float alert_multiplier;
	$F54F3887FFD77A00286D402304E8BC36 projectile_info;
	human_melee_combat_move_id standing_primary_melee_attack;
	human_melee_combat_move_id standing_secondary_melee_attack;
	human_melee_combat_move_id standing_tertiary_melee_attack;
	human_melee_combat_move_id crouching_primary_melee_attack;
	human_melee_combat_move_id crouching_secondary_melee_attack;
	human_melee_combat_move_id crouching_tertiary_melee_attack;
};*/



/*struct __unaligned __declspec(align(4)) constraint
{
	unsigned int host_handle;
	unsigned int child_handle;
	int host_attach_index;
	int child_attach_index;
	int host_alt_hk_body_index;
	int child_alt_hk_body_index;
	constraint_template constraint_info;
	hkpConstraintInstance *hk_constraint;
	constraint *child_constraint_prev;
	constraint *child_constraint_next;
	constraint *host_constraint_prev;
	constraint *host_constraint_next;
};

struct object
{
	void* vfptr;//objectVtbl *vfptr;
	vector pos;
	matrix orient;
	object *child_ptr;
	object *child_next;
	object *child_prev;
	constraint *child_constraint_ptr;
	constraint *host_constraint_ptr;
	void* attach_info_data;//attach_info_data *attach_info;
	unsigned int havok_handle;
	object_contact_info contact_info;
	object_flags obj_flags;
	remote_object_flags remote_obj_flags;
	char mp_dcmo_index;
	int checking_reset;
	unsigned __int16 name_index;
	object *flagged_next;
	object *flagged_prev;
	unsigned int handle;
	unsigned int parent;
	havok_bpo *bp_handle;
	unsigned __int16 all_index;
	unsigned __int16 type_index;
	unsigned __int16 subtype_index;
	char obj_type;
	char sub_type;
	vector last_known_bmin;
	vector last_known_bmax;
	unsigned int srid;
};*/




/*struct rl_sphere
{
	vector m_position;
	float m_radius;
};

struct rl_bvolume
{
	rl_sphere m_sphere;
	vector m_half_vec;
	float m_pad;
};*/

/*struct rl_partition_sector_entry
{
	rl_partition_sector *m_sector_p;
	rl_scene_entity *m_entity_p;
	rl_partition_sector_entry *next;
	rl_partition_sector_entry *prev;
};

struct rl_partition_sector : rl_base_object
{
	linked_list_p<rl_partition_sector_entry> m_entries;
	int m_child_count;
	rl_partition_sector **m_children;
	vector m_position;
	__declspec(align(16)) rl_bvolume m_world_bvolume;
};

struct linked_list_p<rl_partition_sector_entry>
{
	rl_partition_sector_entry *m_head_p;
	int m_elem_count;
};

struct rl_partition_system : rl_base_object
{
	rl_partition_sector* m_root_sector_p;
};*/

/*struct rl_base_objectVtbl
{
	void *(__thiscall* __vecDelDtor)(rl_base_object* ThisBaseObject, unsigned int); //ThisBaseObject = this
	void (__thiscall* release)(rl_base_object* ThisBaseObject); //ThisBaseObject = this
};

struct rl_base_object
{
	rl_base_objectVtbl *vfptr;
	unsigned int m_leaf_class_id;
};

struct rl_3d_entity : rl_base_object
{
	matrix43 m_world_matrix;
};*/

/*struct __declspec(align(16)) rl_scene_entity : rl_3d_entity
{
	rl_scene_entity *prev;
	rl_scene_entity *next;
	unsigned __int16 m_flags;
	unsigned __int16 m_pass_flags;
	float m_lod_off_distance;
	int m_gpu_vis_index;
	__declspec(align(8)) rl_bvolume m_world_bvolume;
	rl_bvolume m_local_bvolume;
	unsigned int m_vis_pass_flags;
	float m_camera_distance_squared;
	unsigned __int16 m_visibility_list_index;
	char m_category_id;
	char m_last_visibility_pass;
	rl_partition_system *m_partition_system_p;
	rl_partition_sector_entry m_partition_sector_entry;
	rl_scene *m_scene_p;
};*/

/*struct rl_camera : rl_scene_entity
{
	matrix44 m_projection_transform;
	matrix44 m_view_transform;
	float m_fov;
	__declspec(align(16)) rl_view_frustum m_frustum;
	rl_view_frustum m_high_lod_frustum;
	float m_near_clip;
	float m_far_clip;
	float m_high_lod_far_clip;
	rl_camera::rl_camera_type m_type;
	bool m_use_pixel_aspect_ratio;
	bool m_depth_of_field_enabled;
	float m_focus_start_A;
	float m_focus_start_B;
	float m_focus_end_A;
	float m_focus_end_B;
	bool m_motion_blur_enabled;
	rl_camera::motion_blur_type m_motion_blur_type;
	float m_motion_blur_amount;
	float m_radial_blur_radius;
	vector2 m_radial_blur_position;
	float m_frame_override_blur;
	float m_signal_noise_scale;
	float m_signal_noise_frequency;
};*/

struct rl_renderer_metrics
{
	unsigned int m_warning_flags;
	int m_particle_batches;
	int m_particle_batch_average;
	volatile unsigned int m_num_dps_per_group_vals;
	volatile unsigned int m_max_dps_per_group;
	volatile unsigned int m_total_dps_per_group;
	float m_cpu_render_time;
	float m_gpu_render_time;
	float m_cpu_scene_render_time;
	int m_num_draw_calls;
	int m_num_dynamic_indices;
	int m_num_dynamic_vert_bytes;
	int m_num_dynamic_inst_bytes;
	unsigned int m_num_entities_in_frustum;
	unsigned int m_num_entities_occluded;
	unsigned int m_num_entities_lod_offed;
	unsigned int m_occlusion_accuracy_total_insts;
	unsigned int m_occlusion_accuracy_visible_insts;
	volatile unsigned int m_num_clone_mesh_widgets;
	volatile unsigned int m_num_clone_mesh_vertices;
	volatile unsigned int m_num_occlusion_queries;
	volatile unsigned int m_num_gpu_vis_entries;
};

struct rl_hdr_state
{
	rl_hdr_state()
	{
		m_enable = true;
		m_lum_range = 0.5f;
		m_lum_offset = 0.1f;
		m_bloom_exposure = 0.1f;
		m_luminance_conversion = vector(0.5f, 0.5f, 0.5f); //vec
		m_iris_rate = 0.1f;
		m_luminance_max = 1.0f;
		m_luminance_min = 0.2f;
		m_luminance_mask_max = 0.5f;
		m_brightpass_threshold = 0.27f;
		m_brightpass_offset = 0.45f;
		m_bloom_soft = true; //bool
		m_bloom_alternate = false; //bool
		m_tone_mapped_bloom = false; //bool
		m_use_hdr_level = true; //bool
		m_eye_adaption_base = 0.2f;
		m_eye_adaption_amount = 0.2f;
		m_eye_fade_min = 0.2f;
		m_eye_fade_max = 0.2f;
		m_bloom_amount = 0.2f;
		m_bloom_new = false; //bool
		m_bloom_theta = 0.2f;
		m_bloom_slope_A = 0.2f;
		m_bloom_slope_B = 0.2f;
		m_sun_shafts_position = vector(0.0f, 200.0f, 0.0f);//vec
	};
	bool m_enable;
	float m_lum_range;
	float m_lum_offset;
	float m_bloom_exposure;
	vector m_luminance_conversion;
	float m_iris_rate;
	float m_luminance_max;
	float m_luminance_min;
	float m_luminance_mask_max;
	float m_brightpass_threshold;
	float m_brightpass_offset;
	bool m_bloom_soft;
	bool m_bloom_alternate;
	bool m_tone_mapped_bloom;
	bool m_use_hdr_level;
	float m_eye_adaption_base;
	float m_eye_adaption_amount;
	float m_eye_fade_min;
	float m_eye_fade_max;
	float m_bloom_amount;
	bool m_bloom_new;
	float m_bloom_theta;
	float m_bloom_slope_A;
	float m_bloom_slope_B;
	vector m_sun_shafts_position;
};

struct base_array_int_Vtbl;
/* 6026 */
struct base_array_int
{
	base_array_int_Vtbl *vfptr;
	int *elt;
	int array_size;
	int num;
};

/* 6027 */
struct base_array_int_Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array_int *This, unsigned int);
};

/* 6028 */
struct farray_int_4 : base_array_int
{
	int data[4];
};

/* 9049 */
struct farray_int_16 : base_array_int
{
	int data[16];
};

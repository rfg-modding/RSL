//#pragma once

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

namespace keen
{
	struct IniVariableBaseVtbl;
	struct MemoryAllocatorVtbl;
	struct FileDeviceInterfaceVtbl;
	struct ResourceFactoryVtbl;
	struct FileSystemMountPoint;
	struct FileSystemDeviceEntry;
	struct ISteamLobbyDataListener;
	struct ISteamLobbyDataListenerVtbl;
	struct ISteamStatsCallback;
	struct ISteamStatsCallbackVtbl;
	struct ISteamLobbyCallback;
	struct ISteamLobbyCallbackVtbl;
	struct ISteamNetworkingCallback;
	struct ISteamNetworkingCallbackVtbl;
	struct SoundSystem::SoundProviderVtbl;
	struct SoundSystem::TemporarySoundDefinition;
	struct SoundSystem::SoundTriggerMemory;
	struct SoundSystem::SoundVoiceXAudio2;
	struct SoundSystem::SystemXaudio2;
	struct SoundDeviceChangedCallback;
	struct SoundDeviceChangedCallbackVtbl;
	struct ISteamLeaderboardsCallback;
	struct ISteamLeaderboardsCallbackVtbl;
	struct ISteamFriendsCallback;
	struct ISteamFriendsCallbackVtbl;
	struct ISteamAchievementsCallback;
	struct ISteamAchievementsCallbackVtbl;
	struct ISteamMatchmakingCallback;
	struct ISteamMatchmakingCallbackVtbl;
	struct SaveData::SaveDataProviderWin32InterfaceVtbl;
	struct ShaderFactory;
	//*** Needs Fix ***//
	struct PoolAllocator<HashMap<unsigned int, GraphicsStateObject *, DefaultHashmapTraits<unsigned int, GraphicsStateObject *> >::Entry>;
	struct InternalList<HashMap<unsigned int, GraphicsStateObject *, DefaultHashmapTraits<unsigned int, GraphicsStateObject *> >::Entry>::Iterator;
	struct VertexFormat;
	struct SkinningD3D11;
	struct SkinnedGeometryInstance;
	struct SoftwareSkinningJointMatrixData;
	struct WorkerThreadContext;
	struct TaskQueue;
	struct TaskQueueContext;
	struct Task;
	struct TaskContext;
	struct RenderTarget;
	struct DownsampleDepthContext;
	struct RenderSwapChain;
	struct ScreenCapture;
	struct RenderCommands;
	struct RenderContext;
	struct RenderEffectSystem;
	struct AnimationCommandBuffer;
	struct NetworkSystem;
	struct GameApplicationVtbl;
	struct TerminationHandlerVtbl;
	struct DebugCommandBrokerVtbl;

	/* 41 */
	enum Float32WriteFormat
	{
	  Float32WriteFormat_Hex = 0x0,
	  Float32WriteFormat_HexShort = 0x1,
	  Float32WriteFormat_Float = 0x2,
	  Float32WriteFormat_FloatShort = 0x3,
	};

	/* 42 */
	enum AchievementId
	{
	  AchievementId_red_faction_guerrilla = 0x0,
	  AchievementId_welcoming_comitte = 0x1,
	  AchievementId_martian_tea_party = 0x2,
	  AchievementId_spread_the_word = 0x3,
	  AchievementId_death_from_above = 0x4,
	  AchievementId_friendly_skies = 0x5,
	  AchievementId_dont_tread_on_me = 0x6,
	  AchievementId_d_etat = 0x7,
	  AchievementId_red_dawn = 0x8,
	  AchievementId_insurgent = 0x9,
	  AchievementId_guerrilla = 0xA,
	  AchievementId_freedom_fighter = 0xB,
	  AchievementId_revolutionary = 0xC,
	  AchievementId_clean_and_righteous = 0xD,
	  AchievementId_warp_speed = 0xE,
	  AchievementId_got_any_fingers_left = 0xF,
	  AchievementId_lost_memories = 0x10,
	  AchievementId_working_the_land = 0x11,
	  AchievementId_free_your_mind = 0x12,
	  AchievementId_one_man_army = 0x13,
	  AchievementId_disaster_area = 0x14,
	  AchievementId_broken_supply_line = 0x15,
	  AchievementId_power_to_the_people = 0x16,
	  AchievementId_tank_buster = 0x17,
	  AchievementId_best_friends_forever = 0x18,
	  AchievementId_coming_down = 0x19,
	  AchievementId_freed_space = 0x1A,
	  AchievementId_just_the_beginning = 0x1B,
	  AchievementId_start_of_something_special = 0x1C,
	  AchievementId_doing_your_part = 0x1D,
	  AchievementId_juggernaut = 0x1E,
	  AchievementId_doozer = 0x1F,
	  AchievementId_grab_some_popcorn = 0x20,
	  AchievementId_try_anything_once = 0x21,
	  AchievementId_check_your_map = 0x22,
	  AchievementId_tools_of_the_trade = 0x23,
	  AchievementId_field_tested = 0x24,
	  AchievementId_battle_scarred = 0x25,
	  AchievementId_war_veteran = 0x26,
	  AchievementId_a_winner_is_you = 0x27,
	  AchievementId_topher_would_be_proud = 0x28,
	  AchievementId_courier_of_pain = 0x29,
	  AchievementId_experimenter = 0x2A,
	  AchievementId_detective = 0x2B,
	  AchievementId_mad_genius = 0x2C,
	  AchievementId_jack_of_all_trades = 0x2D,
	  AchievementId_the_high_and_mighty = 0x2E,
	  AchievementId_party_time = 0x2F,
	  AchievementId_cant_get_enough = 0x30,
	  AchievementId_wrecking_ball = 0x31,
	  AchievementId_red_faction_member = 0x32,
	  AchievementId_bound_by_blood = 0x33,
	  AchievementId_family_vengeance = 0x34,
	  AchievementId_a_greater_purpose = 0x35,
	  AchievementId_deliverance_defender = 0x36,
	  AchievementId_tumbling_down = 0x37,
	  AchievementId_mobile_bombs = 0x38,
	  AchievementId_structural_integrity = 0x39,
	  AchievementId_purge_the_valley = 0x3A,
	  AchievementId_ares_bloodlust = 0x3B,
	  AchievementId_the_power_of_one = 0x3C,
	  AchievementId_Count = 0x3D,
	};

	/* 49 */
	enum MemoryType
	{
	  MemoryType_MainMemory = 0x0,
	  MemoryType_Ps3_RsxLocal = 0x1,
	  MemoryType_Ps3_RsxMain = 0x2,
	  MemoryType_Xb360_Physical = 0x3,
	  MemoryType_Xb360_Physical_WriteCombined = 0x4,
	  MemoryType_WiiU_Mem1 = 0x5,
	  MemoryType_Garlic = 0x6,
	  MemoryType_Onion = 0x7,
	  MemoryType_PsV_VRAM = 0x8,
	  MemoryType_GPU_Mapped = 0x9,
	  MemoryType_XBone_APU = 0xA,
	  MemoryType_Switch_AudioBuffers = 0xB,
	  MemoryType_Count = 0xC,
	};

	/* 50 */
	enum Endianness
	{
	  Endianness_Little = 0x0,
	  Endianness_Big = 0x1,
	  Endianness_Count = 0x2,
	};

	/* 51 */
	enum FileAccessMode
	{
	  FileAccessMode_Read = 0x0,
	  FileAccessMode_Write = 0x1,
	  FileAccessMode_Append = 0x2,
	  FileAccessMode_ReadWrite = 0x3,
	  FileAccessMode_Count = 0x4,
	};

	//*** Needs fix ***//
	/* 52 */
	enum Sequence::PlaybackFlagMask
	{
	  PlaybackFlagMask_NoFlags = 0x0,
	  PlaybackFlagMask_Looped = 0x1,
	  PlaybackFlagMask_Invalid = 0xFFFFFFFF,
	};

	/* 55 */
	enum IoError
	{
	  IoError_Ok = 0x0,
	  IoError_Generic = 0x1,
	  IoError_CompressionError = 0x2,
	  IoError_DecompressionError = 0x3,
	  IoError_ReadError = 0x4,
	  IoError_WriteError = 0x5,
	  IoError_NotImplemented = 0x6,
	  IoError_EofReached = 0x7,
	  IoError_InvalidState = 0x8,
	  IoError_FileNotFound = 0x9,
	  IoError_InvalidPosition = 0xA,
	  IoError_NoPermission = 0xB,
	  IoError_NoConnection = 0xC,
	  IoError_TimeOut = 0xD,
	  IoError_InvalidArgument = 0xE,
	  IoError_OutOfMemory = 0xF,
	  IoError_AlreadyExists = 0x10,
	  IoError_NotSupported = 0x11,
	  IoError_Count = 0x12,
	};

	//*** Needs fix ***//
	/* 61 */
	enum File::State
	{
	  State_Ready = 0x0,
	  State_Error = 0x1,
	  State_Count = 0x2,
	};

	/* 63 */
	enum VertexAttributeId
	{
	  VertexAttributeId_Position = 0x0,
	  VertexAttributeId_Normal = 0x1,
	  VertexAttributeId_Tangent = 0x2,
	  VertexAttributeId_BiTangent = 0x3,
	  VertexAttributeId_Color0 = 0x4,
	  VertexAttributeId_Color1 = 0x5,
	  VertexAttributeId_Color2 = 0x6,
	  VertexAttributeId_TexCoord0 = 0x7,
	  VertexAttributeId_TexCoord1 = 0x8,
	  VertexAttributeId_TexCoord2 = 0x9,
	  VertexAttributeId_TexCoord3 = 0xA,
	  VertexAttributeId_TexCoord4 = 0xB,
	  VertexAttributeId_TexCoord5 = 0xC,
	  VertexAttributeId_TexCoord6 = 0xD,
	  VertexAttributeId_TexCoord7 = 0xE,
	  VertexAttributeId_BoneIndex = 0xF,
	  VertexAttributeId_BoneWeight = 0x10,
	  VertexAttributeId_Count = 0x11,
	  VertexAttributeId_Invalid = 0xFF,
	};

	/* 64 */
	enum ProjectionType
	{
	  ProjectionType_Perspective = 0x0,
	  ProjectionType_Orthographic = 0x1,
	  ProjectionType_Count = 0x2,
	};

	/* 65 */
	enum VertexAttributeFormat
	{
	  VertexAttributeFormat_x32_float = 0x0,
	  VertexAttributeFormat_x32y32_float = 0x1,
	  VertexAttributeFormat_x32y32z32_float = 0x2,
	  VertexAttributeFormat_x32y32z32w32_float = 0x3,
	  VertexAttributeFormat_x16y16z16w16_float = 0x4,
	  VertexAttributeFormat_x16y16z16w16_sint = 0x5,
	  VertexAttributeFormat_x16y16z16w16_uint = 0x6,
	  VertexAttributeFormat_x16y16z16w16_snorm = 0x7,
	  VertexAttributeFormat_x16y16z16w16_unorm = 0x8,
	  VertexAttributeFormat_x8y8z8w8_unorm = 0x9,
	  VertexAttributeFormat_x8y8z8w8_uint = 0xA,
	  VertexAttributeFormat_x8y8z8w8_snorm = 0xB,
	  VertexAttributeFormat_x8y8z8w8_sint = 0xC,
	  VertexAttributeFormat_x16y16_float = 0xD,
	  VertexAttributeFormat_x16y16_sint = 0xE,
	  VertexAttributeFormat_x16y16_snorm = 0xF,
	  VertexAttributeFormat_x16y16_uint = 0x10,
	  VertexAttributeFormat_x16y16_unorm = 0x11,
	  VertexAttributeFormat_x10y10z10_snorm = 0x12,
	  VertexAttributeFormat_x10y10z10w2_snorm = 0x13,
	  VertexAttributeFormat_x11y11z10_snorm = 0x14,
	  VertexAttributeFormat_z8y8x8w8_unorm = 0x15,
	  VertexAttributeFormat_D3dColor = 0x16,
	  VertexAttributeFormat_x16y16z16_snorm = 0x17,
	  VertexAttributeFormat_x8y8z8_snorm = 0x18,
	  VertexAttributeFormat_Count = 0x19,
	  VertexAttributeFormat_Default_Position3d = 0x2,
	  VertexAttributeFormat_Default_Normal = 0x2,
	  VertexAttributeFormat_Default_TangentFlip = 0x3,
	  VertexAttributeFormat_Default_TexCoord2d = 0xD,
	  VertexAttributeFormat_Default_Color = 0x9,
	  VertexAttributeFormat_Invalid = 0xFF,
	};

	/* 66 */
	enum StringParameterType
	{
	  StringParameterType_Invalid = 0x0,
	  StringParameterType_IntegerUnsigned = 0x1,
	  StringParameterType_IntegerSigned = 0x2,
	  StringParameterType_Float = 0x3,
	  StringParameterType_String = 0x4,
	};

	/* 67 */
	enum PixelFormat
	{
	  PixelFormat_None = 0x0,
	  PixelFormat_Bc1 = 0x1,
	  PixelFormat_Bc1_Gamma = 0x2,
	  PixelFormat_Bc2 = 0x3,
	  PixelFormat_Bc2_Gamma = 0x4,
	  PixelFormat_Bc3 = 0x5,
	  PixelFormat_Bc3_Gamma = 0x6,
	  PixelFormat_Bc4 = 0x7,
	  PixelFormat_Bc4_Gamma = 0x8,
	  PixelFormat_Bc5 = 0x9,
	  PixelFormat_Bc5_Gamma = 0xA,
	  PixelFormat_Bc6H_SF16 = 0xB,
	  PixelFormat_Bc6H_UF16 = 0xC,
	  PixelFormat_Bc7 = 0xD,
	  PixelFormat_Bc7_Gamma = 0xE,
	  PixelFormat_Index4 = 0xF,
	  PixelFormat_A4 = 0x10,
	  PixelFormat_L4 = 0x11,
	  PixelFormat_A8 = 0x12,
	  PixelFormat_L8 = 0x13,
	  PixelFormat_Index8 = 0x14,
	  PixelFormat_L4A4 = 0x15,
	  PixelFormat_G8R8 = 0x16,
	  PixelFormat_R8G8 = 0x17,
	  PixelFormat_R5G6B5 = 0x18,
	  PixelFormat_R5G5B5A1 = 0x19,
	  PixelFormat_R4G4B4A4 = 0x1A,
	  PixelFormat_R5G5B5A3 = 0x1B,
	  PixelFormat_Index14x2 = 0x1C,
	  PixelFormat_R8G8B8 = 0x1D,
	  PixelFormat_R8G8B8_Gamma = 0x1E,
	  PixelFormat_R32F = 0x1F,
	  PixelFormat_Y16X16 = 0x20,
	  PixelFormat_A8R8G8B8 = 0x21,
	  PixelFormat_A8R8G8B8_Gamma = 0x22,
	  PixelFormat_X8R8G8B8 = 0x23,
	  PixelFormat_X8R8G8B8_Gamma = 0x24,
	  PixelFormat_A8B8G8R8 = 0x25,
	  PixelFormat_A8B8G8R8_Gamma = 0x26,
	  PixelFormat_R8G8B8A8 = 0x27,
	  PixelFormat_R8G8B8A8_Gamma = 0x28,
	  PixelFormat_A2R10G10B10F = 0x29,
	  PixelFormat_A16B16G16R16F = 0x2A,
	  PixelFormat_A32B32G32R32F = 0x2B,
	  PixelFormat_Depth8 = 0x2C,
	  PixelFormat_Depth16 = 0x2D,
	  PixelFormat_Depth24Stencil8 = 0x2E,
	  PixelFormat_ETC1_RGB8 = 0x2F,
	  PixelFormat_ETC1_RGB8A4 = 0x30,
	  PixelFormat_Pvrtc2 = 0x31,
	  PixelFormat_Pvrtc4 = 0x32,
	  PixelFormat_Pvrtc2A = 0x33,
	  PixelFormat_Pvrtc4A = 0x34,
	  PixelFormat_Ctx1 = 0x35,
	  PixelFormat_DxN = 0x36,
	  PixelFormat_Depth32F = 0x37,
	  PixelFormat_Depth24FStencil8 = 0x38,
	  PixelFormat_R11G11B10F = 0x39,
	  PixelFormat_Depth32FStencil8 = 0x3A,
	  PixelFormat_Depth16Stencil8 = 0x3B,
	  PixelFormat_Count = 0x3C,
	  PixelFormat_Invalid = 0x3C,
	  PixelFormat_Native_RGBA32 = 0x27,
	  PixelFormat_Native_RGBA32_Gamma = 0x28,
	  PixelFormat_Default_Depth = 0x2E,
	  PixelFormat_Dxt1 = 0x1,
	  PixelFormat_Dxt1_Gamma = 0x2,
	  PixelFormat_Dxt23 = 0x3,
	  PixelFormat_Dxt23_Gamma = 0x4,
	  PixelFormat_Dxt45 = 0x5,
	  PixelFormat_Dxt45_Gamma = 0x6,
	};

	//*** Needs fix ***//
	/* 68 */
	enum TGAWriter::Format
	{
	  Format_BGR = 0x0,
	  Format_BGRA = 0x1,
	  Format_Count = 0x2,
	};

	//*** Needs fix ***//
	/* 69 */
	enum Plane::HalfSpace
	{
	  HalfSpace_OnPlane = 0x0,
	  HalfSpace_Positive = 0x1,
	  HalfSpace_Negative = 0x2,
	};

	//*** Needs fix ***//
	/* 70 */
	enum Frustum::PlaneSide
	{
	  PlaneSide_Left = 0x0,
	  PlaneSide_Right = 0x1,
	  PlaneSide_Top = 0x2,
	  PlaneSide_Bottom = 0x3,
	  PlaneSide_Near = 0x4,
	  PlaneSide_Far = 0x5,
	  PlaneSide_Count = 0x6,
	};

	//*** Needs fix ***//
	/* 71 */
	enum Frustum::PlaneMask
	{
	  PlaneMask_Left = 0x1,
	  PlaneMask_Right = 0x2,
	  PlaneMask_Top = 0x4,
	  PlaneMask_Bottom = 0x8,
	  PlaneMask_Near = 0x10,
	  PlaneMask_Far = 0x20,
	  PlaneMask_All = 0x3F,
	  PlaneMask_AllSides = 0xF,
	};

	//*** Needs fix ***//
	/* 72 */
	enum Frustum::CornerPoint
	{
	  CornerPoint_LeftNearTop = 0x0,
	  CornerPoint_RightNearTop = 0x1,
	  CornerPoint_RightNearBottom = 0x2,
	  CornerPoint_LeftNearBottom = 0x3,
	  CornerPoint_LeftFarTop = 0x4,
	  CornerPoint_RightFarTop = 0x5,
	  CornerPoint_RightFarBottom = 0x6,
	  CornerPoint_LeftFarBottom = 0x7,
	  CornerPoint_Count = 0x8,
	};

	/* 74 */
	enum HardwareThread
	{
	  HardwareThread_Cpu0 = 0x0,
	  HardwareThread_Cpu1 = 0x1,
	  HardwareThread_Cpu2 = 0x2,
	  HardwareThread_Cpu3 = 0x3,
	  HardwareThread_Cpu4 = 0x4,
	  HardwareThread_Cpu5 = 0x5,
	  HardwareThread_Cpu6 = 0x6,
	  HardwareThread_Cpu7 = 0x7,
	  HardwareThread_Cpu8 = 0x8,
	  HardwareThread_Cpu9 = 0x9,
	  HardwareThread_Cpu10 = 0xA,
	  HardwareThread_Cpu11 = 0xB,
	  HardwareThread_Cpu12 = 0xC,
	  HardwareThread_Cpu13 = 0xD,
	  HardwareThread_Cpu14 = 0xE,
	  HardwareThread_Cpu15 = 0xF,
	  HardwareThread_Count = 0x10,
	};

	/* 77 */
	enum ResourceConfigurationEndianness
	{
	  ResourceConfigurationEndianness_Little = 0x0,
	  ResourceConfigurationEndianness_Big = 0x1,
	  ResourceConfigurationEndianness_Count = 0x2,
	};

	/* 78 */
	enum ResourceConfigurationPointerSize
	{
	  ResourceConfigurationPointerSize_32 = 0x0,
	  ResourceConfigurationPointerSize_64 = 0x1,
	  ResourceConfigurationPointerSize_Count = 0x2,
	};

	/* 79 */
	enum ResourceConfigurationMathTypeAlignment
	{
	  ResourceConfigurationMathTypeAlignment_4Byte = 0x0,
	  ResourceConfigurationMathTypeAlignment_16Byte = 0x1,
	  ResourceConfigurationMathTypeAlignment_Count = 0x2,
	};

	/* 80 */
	enum ResourceConfigurationPadBaseType
	{
	  ResourceConfigurationPadBaseType_true = 0x0,
	  ResourceConfigurationPadBaseType_false = 0x1,
	  ResourceConfigurationPadBaseType_Count = 0x2,
	};

	/* 82 */
	enum MemoryAllocatorCreationFlag
	{
	  MemoryAllocatorCreationFlag_TrackMemory = 0x0,
	  MemoryAllocatorCreationFlag_MarkMemory = 0x1,
	  MemoryAllocatorCreationFlag_RegisterGlobal = 0x2,
	  MemoryAllocatorCreationFlag_CheckIntegrity = 0x3,
	  MemoryAllocatorCreationFlag_DisableFallbackUsage = 0x4,
	  MemoryAllocatorCreationFlag_DontWarnOnAlignment = 0x5,
	  MemoryAllocatorCreationFlag_FailingExpected = 0x6,
	};

	enum LoadFailReason
	{
	  LoadFailReason_None = 0x0,
	  LoadFailReason_Unknown = 0x1,
	  LoadFailReason_FileNotFound = 0x2,
	  LoadFailReason_FileCorrupt = 0x3,
	  LoadFailReason_Memory = 0x4,
	  LoadFailReason_Factory = 0x5,
	  LoadFailReason_ResourceInitialize = 0x6,
	  LoadFailReason_InvalidContext = 0x7,
	  LoadFailReason_Abort = 0x8,
	};

	/* 88 */
	enum ResourceContextIndex
	{
	  ResourceContextIndex_Root = 0xFF,
	};

	/* 89 */
	enum PlatformType
	{
	  PlatformType_Invalid = 0xFF,
	  PlatformType_Ngc = 0x1,
	  PlatformType_Nds = 0x2,
	  PlatformType_Wii = 0x3,
	  PlatformType_Ctr = 0x4,
	  PlatformType_WiiU = 0x5,
	  PlatformType_Ps2 = 0x6,
	  PlatformType_Ps3 = 0x7,
	  PlatformType_Psp = 0x8,
	  PlatformType_XB360 = 0x9,
	  PlatformType_Win32 = 0xA,
	  PlatformType_Linux = 0xB,
	  PlatformType_Osx = 0xC,
	  PlatformType_IOS = 0xD,
	  PlatformType_Ps4 = 0xE,
	  PlatformType_Android = 0xF,
	  PlatformType_XBone = 0x10,
	  PlatformType_PsV = 0x11,
	  PlatformType_Switch = 0x12,
	};

	/* 90 */
	enum ResourceConfigurationApiId
	{
	  ResourceConfigurationApiId_Generic = 0x0,
	  ResourceConfigurationApiId_Gcm = 0x1,
	  ResourceConfigurationApiId_Edge = 0x2,
	  ResourceConfigurationApiId_Direct3D11 = 0x3,
	  ResourceConfigurationApiId_Direct3D9 = 0x4,
	  ResourceConfigurationApiId_XGraphics = 0x5,
	  ResourceConfigurationApiId_Gnm = 0x6,
	  ResourceConfigurationApiId_GX2 = 0x7,
	  ResourceConfigurationApiId_XAudio2 = 0x8,
	  ResourceConfigurationApiId_MultiStream = 0x9,
	  ResourceConfigurationApiId_Bink = 0xA,
	  ResourceConfigurationApiId_AX = 0xB,
	  ResourceConfigurationApiId_OpenGL_ES = 0xC,
	  ResourceConfigurationApiId_PhysX_PC = 0xD,
	  ResourceConfigurationApiId_PhysX_PlayStation3 = 0xE,
	  ResourceConfigurationApiId_PhysX_Xenon = 0xF,
	  ResourceConfigurationApiId_AJM = 0x10,
	  ResourceConfigurationApiId_PICA = 0x11,
	  ResourceConfigurationApiId_OpenGL = 0x12,
	  ResourceConfigurationApiId_OpenAL = 0x13,
	  ResourceConfigurationApiId_XBone = 0x14,
	  ResourceConfigurationApiId_Gxm = 0x15,
	  ResourceConfigurationApiId_Nvn = 0x16,
	  ResourceConfigurationApiId_Atk = 0x17,
	  ResourceConfigurationApiId_Count = 0x18,
	};

	/* 92 */
	enum SectionType
	{
	  SectionType_Resources = 0x0,
	  SectionType_Data = 0x1,
	  SectionType_RelocationData = 0x2,
	  SectionType_ResourceReferences = 0x3,
	  SectionType_StringTable = 0x4,
	  SectionType_DebugData = 0x5,
	  SectionType_Count = 0x6,
	};

	/* 93 */
	enum ReferenceType
	{
	  ReferenceType_Internal = 0x0,
	  ReferenceType_External = 0x1,
	};

	/* 96 */
	enum ResourceObjectAllocatorType
	{
	  ResourceObjectAllocatorType_Generic_ResourceObjects = 0x0,
	  ResourceObjectAllocatorType_Generic_CPUAccessible = 0x1,
	  ResourceObjectAllocatorType_PS3_RSX = 0x2,
	  ResourceObjectAllocatorType_XB360_Physical = 0x2,
	  ResourceObjectAllocatorType_Wii_Memory1 = 0x2,
	  ResourceObjectAllocatorType_Wii_Memory2 = 0x3,
	  ResourceObjectAllocatorType_CTR_Device = 0x2,
	  ResourceObjectAllocatorType_WiiU_Memory1 = 0x2,
	  ResourceObjectAllocatorType_PS4_Garlic = 0x2,
	  ResourceObjectAllocatorType_PSV_GPUMapped = 0x2,
	  ResourceObjectAllocatorType_XBone_APU = 0x3,
	  ResourceObjectAllocatorType_Switch_Audiobuffers = 0x3,
	  ResourceObjectAllocatorType_Count = 0x4,
	  ResourceObjectAllocatorType_StreamData = 0x5D,
	};

	/* 99 */
	enum FilePath::CompletePathState
	{
	  CompletePathState_Invalid = 0x0,
	  CompletePathState_CompletePath = 0x1,
	  CompletePathState_DirectoryWithPrefix = 0x2,
	  CompletePathState_FileNameWithExtension = 0x3,
	  CompletePathState_LastDirectoryPart = 0x4,
	  CompletePathState_Count = 0x5,
	};

	/* 100 */
	enum AllocationEntryUsage
	{
	  AllocationEntryUsage_Generic = 0x0,
	  AllocationEntryUsage_WeakReferences = 0x1,
	};

	/* 102 */
	enum ResourceRequest::State
	{
	  State_Idle = 0x0,
	  State_Loading = 0x1,
	  State_Complete = 0x2,
	};

	/* 103 */
	enum ResourceRequest::LoadFlags
	{
	  LoadFlags_Optional = 0x1,
	  LoadFlags_Reload = 0x2,
	  LoadFlags_HighPriorityHack = 0x4,
	};

	/* 106 */
	enum ProtocolMessageFieldType
	{
	  ProtocolMessageFieldType_Bool = 0x0,
	  ProtocolMessageFieldType_Float32 = 0x1,
	  ProtocolMessageFieldType_Float64 = 0x2,
	  ProtocolMessageFieldType_SInt8 = 0x3,
	  ProtocolMessageFieldType_UInt8 = 0x4,
	  ProtocolMessageFieldType_SInt16 = 0x5,
	  ProtocolMessageFieldType_UInt16 = 0x6,
	  ProtocolMessageFieldType_SInt32 = 0x7,
	  ProtocolMessageFieldType_UInt32 = 0x8,
	  ProtocolMessageFieldType_SInt64 = 0x9,
	  ProtocolMessageFieldType_UInt64 = 0xA,
	  ProtocolMessageFieldType_String = 0xB,
	  ProtocolMessageFieldType_Message = 0xC,
	  ProtocolMessageFieldType_Enum = 0xD,
	  ProtocolMessageFieldType_QuantizedSInt = 0xE,
	  ProtocolMessageFieldType_QuantizedUInt = 0xF,
	  ProtocolMessageFieldType_VarUInt32 = 0x10,
	  ProtocolMessageFieldType_VarSInt32 = 0x11,
	  ProtocolMessageFieldType_Count = 0x12,
	};

	/* 107 */
	enum ProtocolMessageFieldCppType
	{
	  ProtocolMessageFieldCppType_Bool = 0x0,
	  ProtocolMessageFieldCppType_Float32 = 0x1,
	  ProtocolMessageFieldCppType_Float64 = 0x2,
	  ProtocolMessageFieldCppType_SInt8 = 0x3,
	  ProtocolMessageFieldCppType_UInt8 = 0x4,
	  ProtocolMessageFieldCppType_SInt16 = 0x5,
	  ProtocolMessageFieldCppType_UInt16 = 0x6,
	  ProtocolMessageFieldCppType_SInt32 = 0x7,
	  ProtocolMessageFieldCppType_UInt32 = 0x8,
	  ProtocolMessageFieldCppType_SInt64 = 0x9,
	  ProtocolMessageFieldCppType_UInt64 = 0xA,
	  ProtocolMessageFieldCppType_Message = 0xB,
	  ProtocolMessageFieldCppType_Enum = 0xC,
	  ProtocolMessageFieldCppType_String = 0xD,
	  ProtocolMessageFieldCppType_Count = 0xE,
	};

	/* 121 */
	enum StringReadResult
	{
	  StringReadResult_Ok = 0x0,
	  StringReadResult_Overflow = 0x1,
	  StringReadResult_NoNumber = 0x2,
	};

	/* 122 */
	enum NetworkErrorId
	{
	  NetworkErrorId_None = 0x0,
	  NetworkErrorId_WouldBlock = 0x2733,
	  NetworkErrorId_Again = 0x2733,
	  NetworkErrorId_ConnectionReset = 0x2746,
	  NetworkErrorId_InProgress = 0x2734,
	  NetworkErrorId_AlreadyConnected = 0x2735,
	  NetworkErrorId_IsConnected = 0x2748,
	  NetworkErrorId_NotConnected = 0x2749,
	  NetworkErrorId_PipeClosed = 0x2749,
	};
	
	/* 127 */
	enum NetworkSocketType
	{
	  NetworkSocketType_TCP = 0x0,
	  NetworkSocketType_UDP = 0x1,
	};

	//*** Needs fix ***//
	/* 139 */
	enum RandomNumberGenerator::MersenneTwisterFlags
	{
	  W = 0x20,
	  N = 0x270,
	  M = 0x18D,
	  R = 0x1F,
	  A = 0x9908B0DF,
	  U = 0xB,
	  S = 0x7,
	  B = 0x9D2C5680,
	  T = 0xF,
	  C = 0xEFC60000,
	  L = 0x12,
	  LLMASK = 0x7FFFFFFF,
	  UMASK = 0x80000000,
	};

	/* 205 */
	enum SteamStatType
	{
	  SteamStatType_Unknown = 0xFFFFFFFF,
	  SteamStatType_Int = 0x0,
	  SteamStatType_Float = 0x1,
	  SteamStatType_Count = 0x2,
	};

	//*** Needs fix ***//
	/* 226 */
	enum SaveData::OperationStatus
	{
	  OperationStatus_Nop = 0x0,
	  OperationStatus_Busy = 0x1,
	  OperationStatus_Finished = 0x2,
	};

	//*** Needs fix ***//
	/* 227 */
	enum SaveData::OperationResult
	{
	  OperationResult_Ok = 0x0,
	  OperationResult_Missing = 0x1,
	  OperationResult_Corrupted = 0x2,
	  OperationResult_Error = 0x3,
	  OperationResult_NotFinished = 0x4,
	  OperationResult_InsufficientSpace = 0x5,
	  OperationResult_MaxInstallmentsReached = 0x6,
	  OperationResult_UserCanceled = 0x7,
	  OperationResult_MSUnknownPSP = 0x8,
	};

	//*** Needs fix ***//
	/* 228 */
	enum SaveData::CurrentOperation
	{
	  CurrentOperation_Idle = 0x0,
	  CurrentOperation_CheckingSaveDataSet = 0x1,
	  CurrentOperation_CreatingSaveDataSet = 0x2,
	  CurrentOperation_ErasingSaveDataSet = 0x3,
	  CurrentOperation_CreatingSaveData = 0x4,
	  CurrentOperation_ErasingSaveData = 0x5,
	  CurrentOperation_ReadingSaveData = 0x6,
	  CurrentOperation_WritingSaveData = 0x7,
	  CurrentOperation_ErasingFromListPSx = 0x8,
	  CurrentOperation_RecheckingSaveDataSetPSP = 0x9,
	  CurrentOperation_CreatingProfile = 0xA,
	  CurrentOperation_UpdatingProfile = 0xB,
	  CurrentOperation_ErasingProfile = 0xC,
	};

	//*** Needs fix ***//
	/* 229 */
	enum SaveData::SaveDataSystemType
	{
	  SaveDataSystemType_Invalid = 0x0,
	  SaveDataSystemType_Win32Dev = 0x1,
	  SaveDataSystemType_Win32Native = 0x2,
	  SaveDataSystemType_Steam = 0x3,
	  SaveDataSystemType_Ps3 = 0x4,
	  SaveDataSystemType_Xb360 = 0x5,
	  SaveDataSystemType_Ps4 = 0x6,
	  SaveDataSystemType_OSXNative = 0x7,
	  SaveDataSystemType_XBone = 0x8,
	  SaveDataSystemType_PsV = 0x9,
	  SaveDataSystemType_Switch = 0xA,
	  SaveDataSystemType_Count = 0xB,
	};

	//*** Needs fix ***//
	/* 230 */
	enum SaveFlowState
	{
	  SaveFlowState_Invalid = 0xFFFFFFFF,
	  SaveFlowState_Idle = 0x0,
	  SaveFlowState_StartUp_CheckSaveDataSet = 0x1,
	  SaveFlowState_StartUp_SelectionCanceled = 0x2,
	  SaveFlowState_StartUp_Corrupt = 0x3,
	  SaveFlowState_StartUp_ConfirmErase = 0x4,
	  SaveFlowState_StartUp_Erase = 0x5,
	  SaveFlowState_StartUp_EraseFailed = 0x6,
	  SaveFlowState_StartUp_InformUserNewDevice = 0x7,
	  SaveFlowState_StartUp_CreateNewSet = 0x8,
	  SaveFlowState_StartUp_CreateNewSaveGame = 0x9,
	  SaveFlowState_StartUp_CreationFailed = 0xA,
	  SaveFlowState_StartUp_InsufficientSpace = 0xB,
	  SaveFlowState_StartUp_EraseFromList = 0xC,
	  SaveFlowState_Startup_Read = 0xD,
	  SaveFlowState_Startup_UserBindingError = 0xE,
	  SaveFlowState_Startup_UserBindingErrorConfirmErase = 0xF,
	  SaveFlowState_Startup_ReadError = 0x10,
	  SaveFlowState_Startup_ReadErrorConfirmErase = 0x11,
	  SaveFlowState_Startup_ReadErrorErase = 0x12,
	  SaveFlowState_Startup_ConfirmDisable = 0x13,
	  SaveFlowState_Startup_End_Usable = 0x14,
	  SaveFlowState_Startup_End_Disable = 0x15,
	  SaveFlowState_Write_Writing = 0x16,
	  SaveFlowState_Write_WriteError = 0x17,
	  SaveFlowState_Write_Overwrite = 0x18,
	  SaveFlowState_Write_Disable = 0x19,
	  SaveFlowState_Write_Done = 0x1A,
	  SaveFlowState_Count = 0x1B,
	};

	//*** Needs fix ***//
	/* 232 */
	enum SaveDataHandler::SaveGameClientState
	{
	  SaveGameClientState_Free = 0x0,
	  SaveGameClientState_Startup = 0x1,
	  SaveGameClientState_Ready = 0x2,
	  SaveGameClientState_Count = 0x3,
	};

	//*** Needs fix ***//
	/* 235 */
	enum SaveData::SaveDataProviderWin32Steam::WriteMode
	{
	  WriteMode_FillSpace = 0x0,
	  WriteMode_SkipSpace = 0x1,
	};

	/* 238 */
	enum RenderTargetPartFlagMask
	{
	  RenderTargetPartFlagMask_None = 0x0,
	  RenderTargetPartFlagMask_Target0 = 0x1,
	  RenderTargetPartFlagMask_Target1 = 0x2,
	  RenderTargetPartFlagMask_Target2 = 0x4,
	  RenderTargetPartFlagMask_Target3 = 0x8,
	  RenderTargetPartFlagMask_Depth = 0x10,
	  RenderTargetPartFlagMask_Stencil = 0x20,
	  RenderTargetPartFlagMask_Color = 0xF,
	  RenderTargetPartFlagMask_DepthStencil = 0x30,
	  RenderTargetPartFlagMask_All = 0x3F,
	};

	/* 241 */
	enum IndexFormat
	{
	  IndexFormat_Invalid = 0x0,
	  IndexFormat_Uint16 = 0x1,
	  IndexFormat_Uint32 = 0x2,
	  IndexFormat_Count = 0x3,
	};

	/* 242 */
	enum PrimitiveType
	{
	  PrimitiveType_Invalid = 0xFFFFFFFF,
	  PrimitiveType_TriangleList = 0x0,
	  PrimitiveType_TriangleStrip = 0x1,
	  PrimitiveType_LineList = 0x2,
	  PrimitiveType_LineStrip = 0x3,
	  PrimitiveType_QuadList = 0x4,
	  PrimitiveType_Count = 0x5,
	};

	/* 249 */
	enum TextureFlag
	{
	  TextureFlag_Bind_ShaderInput = 0x0,
	  TextureFlag_Bind_RenderTarget = 0x1,
	  TextureFlag_Bind_DepthStencil = 0x2,
	  TextureFlag_Bind_ShadowMap = 0x3,
	  TextureFlag_Bind_VertexTexture = 0x4,
	  TextureFlag_Bind_ResolveRenderTarget = 0x5,
	  TextureFlag_AlphaIsPremultiplied = 0x6,
	  TextureFlag_Platform_Start = 0x7,
	};

	/* 251 */
	enum TextureFlagMask
	{
	  TextureFlagMask_Bind_ShaderInput = 0x1,
	  TextureFlagMask_Bind_RenderTarget = 0x2,
	  TextureFlagMask_Bind_DepthStencil = 0x4,
	  TextureFlagMask_Bind_ShadowMap = 0x8,
	  TextureFlagMask_Bind_VertexTexture = 0x10,
	  TextureFlagMask_Bind_ResolveRenderTarget = 0x20,
	  TextureFlagMask_AlphaIsPremultiplied = 0x40,
	};

	/* 252 */
	enum TextureFlagPS3
	{
	  TextureFlagPS3_BindZCull = 0x7,
	  TextureFlagPS3_BindTile = 0x8,
	  TextureFlagPS3_Swizzled = 0x9,
	};

	/* 253 */
	enum TextureFlagXB360
	{
	  TextureFlagXB360_Tiled = 0x7,
	  TextureFlagXB360_Expand = 0x8,
	  TextureFlagXB360_CPU_CACHED_MEMORY = 0x9,
	};

	/* 255 */
	enum TextureFlagWiiU
	{
	  TextureFlagWiiU_Tiling = 0x7,
	  TextureFlagWiiU_EnableHiZ = 0xB,
	};

	/* 256 */
	enum TextureFlagPs4
	{
	  TextureFlagPs4_Tilemode = 0x7,
	  TextureFlagPs4_Bind_Displayout = 0xC,
	  TextureFlagPs4_EnableHTile = 0xD,
	};

	/* 257 */
	enum TextureFlagXBone
	{
	  TextureFlagXBone_Tilemode = 0x7,
	  TextureFlagXBone_UseESRAM = 0xC,
	};

	/* 258 */
	enum TextureFlagSwitch
	{
	  TextureFlagSwitch_BindDisplay = 0x7,
	  TextureFlagSwitch_Compressible = 0x8,
	  TextureFlagSwitch_LinearTiling = 0x9,
	};

	/* 260 */
	enum TextureFlagD3D11
	{
	  TextureFlagD3D11_AlphaIsPremultiplied = 0x7,
	  TextureFlagD3D11_AliasableFormat = 0x8,
	};

	/* 277 */
	enum TilingMode
	{
	  TilingMode_None = 0x0,
	  TilingMode_TwoVertical = 0x1,
	  TilingMode_FourVertical = 0x2,
	  TilingMode_TwoHorizontal = 0x3,
	  TilingMode_FourHorizontal = 0x4,
	};

	/* 281 */
	enum BlendOperation
	{
	  BlendOperation_Invalid = 0xFFFFFFFF,
	  BlendOperation_None = 0x0,
	  BlendOperation_Add = 0x1,
	  BlendOperation_Subtract = 0x2,
	  BlendOperation_RevSubtract = 0x3,
	  BlendOperation_Min = 0x4,
	  BlendOperation_Max = 0x5,
	  BlendOperation_Count = 0x6,
	};

	/* 283 */
	enum BlendFactor
	{
	  BlendFactor_Invalid = 0xFFFFFFFF,
	  BlendFactor_Zero = 0x0,
	  BlendFactor_One = 0x1,
	  BlendFactor_SrcColor = 0x2,
	  BlendFactor_InvSrcColor = 0x3,
	  BlendFactor_SrcAlpha = 0x4,
	  BlendFactor_InvSrcAlpha = 0x5,
	  BlendFactor_DestAlpha = 0x6,
	  BlendFactor_InvDestAlpha = 0x7,
	  BlendFactor_DestColor = 0x8,
	  BlendFactor_InvDestColor = 0x9,
	  BlendFactor_SrcAlphaSat = 0xA,
	  BlendFactor_BlendFactor = 0xB,
	  BlendFactor_InvBlendFactor = 0xC,
	  BlendFactor_Count = 0xD,
	};

	/* 286 */
	enum FillMode
	{
	  FillMode_Invalid = 0xFFFFFFFF,
	  FillMode_Wireframe = 0x0,
	  FillMode_Solid = 0x1,
	  FillMode_Count = 0x2,
	};

	/* 288 */
	enum CullMode
	{
	  CullMode_Invalid = 0xFFFFFFFF,
	  CullMode_None = 0x0,
	  CullMode_Front = 0x1,
	  CullMode_Back = 0x2,
	  CullMode_Count = 0x3,
	};

	/* 289 */
	enum WindingOrder
	{
	  WindingOrder_Invalid = 0xFFFFFFFF,
	  WindingOrder_Ccw = 0x0,
	  WindingOrder_Cw = 0x1,
	  WindingOrder_Count = 0x2,
	};

	/* 290 */
	enum SamplerFilterMode
	{
	  SamplerFilterMode_Invalid = 0xFFFFFFFF,
	  SamplerFilterMode_None = 0x0,
	  SamplerFilterMode_Nearest = 0x1,
	  SamplerFilterMode_Linear = 0x2,
	  SamplerFilterMode_Anisotropic = 0x3,
	  SamplerFilterMode_Count = 0x4,
	};

	/* 291 */
	enum SamplerAddressMode
	{
	  SamplerAddressMode_Invalid = 0xFFFFFFFF,
	  SamplerAddressMode_Wrap = 0x0,
	  SamplerAddressMode_Mirror = 0x1,
	  SamplerAddressMode_Clamp = 0x2,
	  SamplerAddressMode_MirrorOnce = 0x3,
	  SamplerAddressMode_Border = 0x4,
	  SamplerAddressMode_Count = 0x5,
	};

	/* 292 */
	enum ComparisonFunction
	{
	  ComparisonFunction_Invalid = 0xFFFFFFFF,
	  ComparisonFunction_Never = 0x0,
	  ComparisonFunction_Less = 0x1,
	  ComparisonFunction_Equal = 0x2,
	  ComparisonFunction_LessEqual = 0x3,
	  ComparisonFunction_Greater = 0x4,
	  ComparisonFunction_NotEqual = 0x5,
	  ComparisonFunction_GreaterEqual = 0x6,
	  ComparisonFunction_Always = 0x7,
	  ComparisonFunction_Count = 0x8,
	};

	/* 296 */
	enum StencilOperation
	{
	  StencilOperation_Keep = 0x0,
	  StencilOperation_Zero = 0x1,
	  StencilOperation_Replace = 0x2,
	  StencilOperation_Increment = 0x3,
	  StencilOperation_Decrement = 0x4,
	  StencilOperation_IncrementWrap = 0x5,
	  StencilOperation_DecrementWrap = 0x6,
	  StencilOperation_Invert = 0x7,
	  StencilOperation_Count = 0x8,
	};

	/* 300 */
	enum BlendMode
	{
	  BlendMode_Invalid = 0xFFFFFFFF,
	  BlendMode_Solid = 0x0,
	  BlendMode_Over = 0x1,
	  BlendMode_Add = 0x2,
	  BlendMode_Count = 0x3,
	};

	/* 301 */
	enum ShaderMask
	{
	  ShaderMask_Vertex = 0x1,
	  ShaderMask_Fragment = 0x2,
	  ShaderMask_VertexAndFragment = 0x3,
	};

	/* 302 */
	enum ColorWriteMask
	{
	  ColorWriteMask_Red = 0x1,
	  ColorWriteMask_Green = 0x2,
	  ColorWriteMask_Blue = 0x4,
	  ColorWriteMask_Alpha = 0x8,
	  ColorWriteMask_RGB = 0x7,
	  ColorWriteMask_All = 0xF,
	};

	//*** Needs Fix ***//
	/* 303 */
	enum FallbackRenderEffect::DisplayMode
	{
	  DisplayMode_Modulate = 0x0,
	  DisplayMode_ShowVertexColor = 0x1,
	  DisplayMode_Count = 0x2,
	};

	/* 310 */
	enum GraphicsStockVertexFormat
	{
	  GraphicsStockVertexFormat_Pos2f = 0x0,
	  GraphicsStockVertexFormat_Pos2f_Tex2f = 0x1,
	  GraphicsStockVertexFormat_Immediate = 0x2,
	  GraphicsStockVertexFormat_Count = 0x3,
	};

	/* 311 */
	enum RenderEffectId
	{
	  RenderEffectId_Invalid = 0x0,
	  RenderEffectId_Fallback = 0x1,
	  RenderEffectId_ParticleLight = 0x2,
	  RenderEffectId_ParticleLineLight = 0x3,
	  RenderEffectId_Callback = 0x4,
	  RenderEffectId_FirstUserId = 0x8,
	};

	/* 313 */
	enum GraphicsGeometryMode
	{
	  GraphicsGeometryMode_Static = 0x0,
	  GraphicsGeometryMode_Skinned = 0x1,
	  GraphicsGeometryMode_Instanced = 0x2,
	  GraphicsGeometryMode_Immediate = 0x3,
	  GraphicsGeometryMode_Count = 0x4,
	};

	/* 325 */
	enum TextureAccessMode
	{
	  TextureAccessMode_None = 0x0,
	  TextureAccessMode_Read = 0x1,
	  TextureAccessMode_Write = 0x2,
	  TextureAccessMode_ReadWrite = 0x3,
	  TextureAccessMode_Count = 0x4,
	};

	/* 326 */
	enum MultiSampleType
	{
	  MultiSampleType_None = 0x0,
	  MultiSampleType_MSAA_2x = 0x1,
	  MultiSampleType_MSAA_4x = 0x2,
	  MultiSampleType_Count = 0x3,
	};

	/* 327 */
	enum GraphicsGeometryModeMask
	{
	  GraphicsGeometryModeMask_Static = 0x1,
	  GraphicsGeometryModeMask_Skinned = 0x2,
	  GraphicsGeometryModeMask_Instanced = 0x4,
	  GraphicsGeometryModeMask_Immediate = 0x8,
	  GraphicsGeometryModeMask_Default = 0x7,
	};

	/* 328 */
	enum RasterizerFlagMask
	{
	  RasterizerFlagMask_CullAgainstFrustum = 0x1,
	  RasterizerFlagMask_EnableScissorTest = 0x2,
	  RasterizerFlagMask_Default = 0x1,
	};

	/* 329 */
	enum TextureFlagMaskXBone
	{
	  TextureFlagMaskXBone_Tilemode = 0xF80,
	  TextureFlagMaskXBone_UseESRAM = 0x1000,
	};

	/* 331 */
	enum TextureType
	{
	  TextureType_1d = 0x0,
	  TextureType_2d = 0x1,
	  TextureType_3d = 0x2,
	  TextureType_Cube = 0x3,
	  TextureType_Count = 0x4,
	};

	/* 333 */
	enum TextureAddressMode
	{
	  TextureAddressMode_Wrap = 0x0,
	  TextureAddressMode_Mirror = 0x1,
	  TextureAddressMode_Clamp = 0x2,
	  TextureAddressMode_MirrorOnce = 0x3,
	  TextureAddressMode_Count = 0x4,
	};

	/* 335 */
	enum TextureFlagMaskPs4
	{
	  TextureFlagMaskPs4_Tilemode = 0xF80,
	  TextureFlagMaskPs4_Bind_Displayout = 0x1000,
	  TextureFlagMaskPs4_EnableHTile = 0x2000,
	};

	/* 337 */
	enum RenderGeometryAccessMode
	{
	  RenderGeometryAccessMode_None = 0x0,
	  RenderGeometryAccessMode_Read = 0x1,
	  RenderGeometryAccessMode_Write = 0x2,
	  RenderGeometryAccessMode_ReadWrite = 0x3,
	  RenderGeometryAccessMode_Count = 0x4,
	};

	/* 338 */
	enum GraphicsMapType
	{
	  GraphicsMapType_Read = 0x0,
	  GraphicsMapType_Write = 0x1,
	  GraphicsMapType_ReadWrite = 0x2,
	  GraphicsMapType_WriteDiscard = 0x3,
	  GraphicsMapType_WriteNoOverwrite = 0x4,
	  GraphicsMapType_Count = 0x5,
	};

	//*** Needs Fix ***//
	/* 341 */
	enum animation::KeySize
	{
	  KeySize_Orientation = 0x8,
	  KeySize_ConstOrientation = 0x4,
	  KeySize_Position = 0x6,
	  KeySize_ConstPosition = 0x3,
	  KeySize_Scale = 0x6,
	  KeySize_ConstScale = 0x3,
	};

	//*** Needs Fix ***//
	/* 342 */
	enum animation::LveDeltaIndices
	{
	  LveDeltaIndices_StartIndex = 0x0,
	  LveDeltaIndices_EndIndex = 0x1,
	  LveDeltaIndices_IndexCount = 0x2,
	};

	/* 343 */
	enum AnimationCommandType
	{
	  AnimationCommandType_JointBegin = 0x0,
	  AnimationCommandType_JointSample = 0x1,
	  AnimationCommandType_JointSampleAndAdd = 0x2,
	  AnimationCommandType_JointSampleAndLerp = 0x3,
	  AnimationCommandType_JointAdd = 0x4,
	  AnimationCommandType_JointAddWithMultipleWeights = 0x5,
	  AnimationCommandType_JointLerp = 0x6,
	  AnimationCommandType_JointLerpWithMultipleWeights = 0x7,
	  AnimationCommandType_JointExportMatrix = 0x8,
	  AnimationCommandType_JointExportSkinningMatrices = 0x9,
	  AnimationCommandType_JointExportJoint = 0xA,
	  AnimationCommandType_JointEnd = 0xB,
	  AnimationCommandType_LveBegin = 0xC,
	  AnimationCommandType_LveSample = 0xD,
	  AnimationCommandType_LveLerp = 0xE,
	  AnimationCommandType_LveExportState = 0xF,
	  AnimationCommandType_LveExportDelta = 0x10,
	  AnimationCommandType_LveEnd = 0x11,
	};

	/* 344 */
	enum LveAnimationFlags
	{
	  LveAnimationFlags_Clamp = 0x0,
	  LveAnimationFlags_Looped = 0x1,
	};

	/* 345 */
	enum JointAnimationFlags
	{
	  JointAnimationFlags_Clamp = 0x0,
	  JointAnimationFlags_Looped = 0x1,
	};

	/* 351 */
	enum UserAccountAsyncOperationState
	{
	  UserAccountAsyncOperationState_Invalid = 0x0,
	  UserAccountAsyncOperationState_Busy = 0x1,
	  UserAccountAsyncOperationState_Error = 0x2,
	  UserAccountAsyncOperationState_Success = 0x3,
	};

	/* 352 */
	enum UserAccountAsyncOperationType
	{
	  UserAccountAsyncOperationType_Invalid = 0x0,
	  UserAccountAsyncOperationType_ShowSelectUserUi = 0x1,
	};

	//*** Needs Fix ***//
	/* 412 */
	enum network::SmtpState
	{
	  SmtpState_Disconnected = 0x0,
	  SmtpState_Connected = 0x1,
	  SmtpState_Error = 0x2,
	};

	//*** Needs Fix ***//
	/* 414 */
	enum network::Condition
	{
	  Condition_Good = 0x0,
	  Condition_Bad = 0x1,
	};

	/* 416 */
	enum SmptError
	{
	  SmptError_Socket = 0x258,
	  SmptError_Address = 0x259,
	  SmptError_Protocol = 0x25A,
	  SmptError_Message = 0x25B,
	  SmptError_ErrorState = 0x25C,
	};

	//*** Needs Fix ***//
	/* 418 */
	enum network::PacketProtocol::AcknowledgeMethod
	{
	  AcknowledgeMethod_None = 0x0,
	  AcknowledgeMethod_Ack = 0x1,
	};

	/* 425 */
	enum ErrorSimulationPresetId
	{
	  ErrorSimulationPresetId_NoErrorSimulation = 0x0,
	  ErrorSimulationPresetId_10PercentPacketLoss = 0x1,
	  ErrorSimulationPresetId_80PercentPacketLoss = 0x2,
	  ErrorSimulationPresetId_6PercentPacketLoss_150msLag = 0x3,
	  ErrorSimulationPresetId_150msLagOnly = 0x4,
	  ErrorSimulationPresetId_250msLagOnly = 0x5,
	  ErrorSimulationPresetId_500msLagOnly = 0x6,
	  ErrorSimulationPresetId_DuplicationOnly = 0x7,
	  ErrorSimulationPresetId_MinimumWorkingConnection = 0x8,
	  ErrorSimulationPresetId_TypicalConnection = 0x9,
	  ErrorSimulationPresetId_Xb360_TCR = 0xA,
	  ErrorSimulationPresetId_Count = 0xB,
	};

	/* 426 */
	enum AsyncNetworkOperationType
	{
	  AsyncNetworkOperationType_Accept = 0x0,
	  AsyncNetworkOperationType_Connect = 0x1,
	  AsyncNetworkOperationType_Read = 0x2,
	  AsyncNetworkOperationType_Write = 0x3,
	  AsyncNetworkOperationType_User = 0x4,
	  AsyncNetworkOperationType_Count = 0x5,
	};

	/* 427 */
	enum AsyncNetworkIoError
	{
	  AsyncNetworkIoError_Ok = 0x0,
	  AsyncNetworkIoError_Closed = 0x1,
	  AsyncNetworkIoError_Error = 0x2,
	  AsyncNetworkIoError_Count = 0x3,
	};

	/* 430 */
	enum AxisFunction
	{
	  AxisFunction_None = 0x0,
	  AxisFunction_Flip = 0x1,
	};

	/* 432 */
	enum InputSystemControllerAutoCatchType
	{
	  InputSystemControllerAutoCatchType_AnyButton = 0x0,
	  InputSystemControllerAutoCatchType_Anything = 0x1,
	  InputSystemControllerAutoCatchType_StartButtonOnly = 0x2,
	  InputSystemControllerAutoCatchType_Disabled = 0x3,
	  InputSystemControllerAutoCatchType_AnythingIncludingControllerConnected = 0x4,
	  InputSystemControllerAutoCatchType_ControllerConnected = 0x5,
	};

	/* 433 */
	enum SteamControllerActionType
	{
	  SteamControllerActionType_Set = 0x0,
	  SteamControllerActionType_Button = 0x1,
	  SteamControllerActionType_Axis = 0x2,
	};

	/* 434 */
	enum SteamControllerAxisMode
	{
	  SteamControllerAxisMode_XAndY = 0x0,
	  SteamControllerAxisMode_XOnly = 0x1,
	  SteamControllerAxisMode_YOnly = 0x2,
	};

	/* 436 */
	enum SteamControllerActionOrigin
	{
	  SteamControllerActionOrigin_None = 0x0,
	  SteamControllerActionOrigin_A = 0x1,
	  SteamControllerActionOrigin_B = 0x2,
	  SteamControllerActionOrigin_X = 0x3,
	  SteamControllerActionOrigin_Y = 0x4,
	  SteamControllerActionOrigin_LeftBumper = 0x5,
	  SteamControllerActionOrigin_RightBumper = 0x6,
	  SteamControllerActionOrigin_LeftGrip = 0x7,
	  SteamControllerActionOrigin_RightGrip = 0x8,
	  SteamControllerActionOrigin_Start = 0x9,
	  SteamControllerActionOrigin_Back = 0xA,
	  SteamControllerActionOrigin_LeftPad_Touch = 0xB,
	  SteamControllerActionOrigin_LeftPad_Swipe = 0xC,
	  SteamControllerActionOrigin_LeftPad_Click = 0xD,
	  SteamControllerActionOrigin_LeftPad_DPadNorth = 0xE,
	  SteamControllerActionOrigin_LeftPad_DPadSouth = 0xF,
	  SteamControllerActionOrigin_LeftPad_DPadWest = 0x10,
	  SteamControllerActionOrigin_LeftPad_DPadEast = 0x11,
	  SteamControllerActionOrigin_RightPad_Touch = 0x12,
	  SteamControllerActionOrigin_RightPad_Swipe = 0x13,
	  SteamControllerActionOrigin_RightPad_Click = 0x14,
	  SteamControllerActionOrigin_RightPad_DPadNorth = 0x15,
	  SteamControllerActionOrigin_RightPad_DPadSouth = 0x16,
	  SteamControllerActionOrigin_RightPad_DPadWest = 0x17,
	  SteamControllerActionOrigin_RightPad_DPadEast = 0x18,
	  SteamControllerActionOrigin_LeftTrigger_Pull = 0x19,
	  SteamControllerActionOrigin_LeftTrigger_Click = 0x1A,
	  SteamControllerActionOrigin_RightTrigger_Pull = 0x1B,
	  SteamControllerActionOrigin_RightTrigger_Click = 0x1C,
	  SteamControllerActionOrigin_LeftStick_Move = 0x1D,
	  SteamControllerActionOrigin_LeftStick_Click = 0x1E,
	  SteamControllerActionOrigin_LeftStick_DPadNorth = 0x1F,
	  SteamControllerActionOrigin_LeftStick_DPadSouth = 0x20,
	  SteamControllerActionOrigin_LeftStick_DPadWest = 0x21,
	  SteamControllerActionOrigin_LeftStick_DPadEast = 0x22,
	  SteamControllerActionOrigin_Gyro_Move = 0x23,
	  SteamControllerActionOrigin_Gyro_Pitch = 0x24,
	  SteamControllerActionOrigin_Gyro_Yaw = 0x25,
	  SteamControllerActionOrigin_Gyro_Roll = 0x26,
	  SteamControllerActionOrigin_PS4_X = 0x27,
	  SteamControllerActionOrigin_PS4_Circle = 0x28,
	  SteamControllerActionOrigin_PS4_Triangle = 0x29,
	  SteamControllerActionOrigin_PS4_Square = 0x2A,
	  SteamControllerActionOrigin_PS4_LeftBumper = 0x2B,
	  SteamControllerActionOrigin_PS4_RightBumper = 0x2C,
	  SteamControllerActionOrigin_PS4_Options = 0x2D,
	  SteamControllerActionOrigin_PS4_Share = 0x2E,
	  SteamControllerActionOrigin_PS4_LeftPad_Touch = 0x2F,
	  SteamControllerActionOrigin_PS4_LeftPad_Swipe = 0x30,
	  SteamControllerActionOrigin_PS4_LeftPad_Click = 0x31,
	  SteamControllerActionOrigin_PS4_LeftPad_DPadNorth = 0x32,
	  SteamControllerActionOrigin_PS4_LeftPad_DPadSouth = 0x33,
	  SteamControllerActionOrigin_PS4_LeftPad_DPadWest = 0x34,
	  SteamControllerActionOrigin_PS4_LeftPad_DPadEast = 0x35,
	  SteamControllerActionOrigin_PS4_RightPad_Touch = 0x36,
	  SteamControllerActionOrigin_PS4_RightPad_Swipe = 0x37,
	  SteamControllerActionOrigin_PS4_RightPad_Click = 0x38,
	  SteamControllerActionOrigin_PS4_RightPad_DPadNorth = 0x39,
	  SteamControllerActionOrigin_PS4_RightPad_DPadSouth = 0x3A,
	  SteamControllerActionOrigin_PS4_RightPad_DPadWest = 0x3B,
	  SteamControllerActionOrigin_PS4_RightPad_DPadEast = 0x3C,
	  SteamControllerActionOrigin_PS4_CenterPad_Touch = 0x3D,
	  SteamControllerActionOrigin_PS4_CenterPad_Swipe = 0x3E,
	  SteamControllerActionOrigin_PS4_CenterPad_Click = 0x3F,
	  SteamControllerActionOrigin_PS4_CenterPad_DPadNorth = 0x40,
	  SteamControllerActionOrigin_PS4_CenterPad_DPadSouth = 0x41,
	  SteamControllerActionOrigin_PS4_CenterPad_DPadWest = 0x42,
	  SteamControllerActionOrigin_PS4_CenterPad_DPadEast = 0x43,
	  SteamControllerActionOrigin_PS4_LeftTrigger_Pull = 0x44,
	  SteamControllerActionOrigin_PS4_LeftTrigger_Click = 0x45,
	  SteamControllerActionOrigin_PS4_RightTrigger_Pull = 0x46,
	  SteamControllerActionOrigin_PS4_RightTrigger_Click = 0x47,
	  SteamControllerActionOrigin_PS4_LeftStick_Move = 0x48,
	  SteamControllerActionOrigin_PS4_LeftStick_Click = 0x49,
	  SteamControllerActionOrigin_PS4_LeftStick_DPadNorth = 0x4A,
	  SteamControllerActionOrigin_PS4_LeftStick_DPadSouth = 0x4B,
	  SteamControllerActionOrigin_PS4_LeftStick_DPadWest = 0x4C,
	  SteamControllerActionOrigin_PS4_LeftStick_DPadEast = 0x4D,
	  SteamControllerActionOrigin_PS4_RightStick_Move = 0x4E,
	  SteamControllerActionOrigin_PS4_RightStick_Click = 0x4F,
	  SteamControllerActionOrigin_PS4_RightStick_DPadNorth = 0x50,
	  SteamControllerActionOrigin_PS4_RightStick_DPadSouth = 0x51,
	  SteamControllerActionOrigin_PS4_RightStick_DPadWest = 0x52,
	  SteamControllerActionOrigin_PS4_RightStick_DPadEast = 0x53,
	  SteamControllerActionOrigin_PS4_DPad_North = 0x54,
	  SteamControllerActionOrigin_PS4_DPad_South = 0x55,
	  SteamControllerActionOrigin_PS4_DPad_West = 0x56,
	  SteamControllerActionOrigin_PS4_DPad_East = 0x57,
	  SteamControllerActionOrigin_PS4_Gyro_Move = 0x58,
	  SteamControllerActionOrigin_PS4_Gyro_Pitch = 0x59,
	  SteamControllerActionOrigin_PS4_Gyro_Yaw = 0x5A,
	  SteamControllerActionOrigin_PS4_Gyro_Roll = 0x5B,
	  SteamControllerActionOrigin_XBoxOne_A = 0x5C,
	  SteamControllerActionOrigin_XBoxOne_B = 0x5D,
	  SteamControllerActionOrigin_XBoxOne_X = 0x5E,
	  SteamControllerActionOrigin_XBoxOne_Y = 0x5F,
	  SteamControllerActionOrigin_XBoxOne_LeftBumper = 0x60,
	  SteamControllerActionOrigin_XBoxOne_RightBumper = 0x61,
	  SteamControllerActionOrigin_XBoxOne_Menu = 0x62,
	  SteamControllerActionOrigin_XBoxOne_View = 0x63,
	  SteamControllerActionOrigin_XBoxOne_LeftTrigger_Pull = 0x64,
	  SteamControllerActionOrigin_XBoxOne_LeftTrigger_Click = 0x65,
	  SteamControllerActionOrigin_XBoxOne_RightTrigger_Pull = 0x66,
	  SteamControllerActionOrigin_XBoxOne_RightTrigger_Click = 0x67,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_Move = 0x68,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_Click = 0x69,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_DPadNorth = 0x6A,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_DPadSouth = 0x6B,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_DPadWest = 0x6C,
	  SteamControllerActionOrigin_XBoxOne_LeftStick_DPadEast = 0x6D,
	  SteamControllerActionOrigin_XBoxOne_RightStick_Move = 0x6E,
	  SteamControllerActionOrigin_XBoxOne_RightStick_Click = 0x6F,
	  SteamControllerActionOrigin_XBoxOne_RightStick_DPadNorth = 0x70,
	  SteamControllerActionOrigin_XBoxOne_RightStick_DPadSouth = 0x71,
	  SteamControllerActionOrigin_XBoxOne_RightStick_DPadWest = 0x72,
	  SteamControllerActionOrigin_XBoxOne_RightStick_DPadEast = 0x73,
	  SteamControllerActionOrigin_XBoxOne_DPad_North = 0x74,
	  SteamControllerActionOrigin_XBoxOne_DPad_South = 0x75,
	  SteamControllerActionOrigin_XBoxOne_DPad_West = 0x76,
	  SteamControllerActionOrigin_XBoxOne_DPad_East = 0x77,
	  SteamControllerActionOrigin_XBox360_A = 0x78,
	  SteamControllerActionOrigin_XBox360_B = 0x79,
	  SteamControllerActionOrigin_XBox360_X = 0x7A,
	  SteamControllerActionOrigin_XBox360_Y = 0x7B,
	  SteamControllerActionOrigin_XBox360_LeftBumper = 0x7C,
	  SteamControllerActionOrigin_XBox360_RightBumper = 0x7D,
	  SteamControllerActionOrigin_XBox360_Start = 0x7E,
	  SteamControllerActionOrigin_XBox360_Back = 0x7F,
	  SteamControllerActionOrigin_XBox360_LeftTrigger_Pull = 0x80,
	  SteamControllerActionOrigin_XBox360_LeftTrigger_Click = 0x81,
	  SteamControllerActionOrigin_XBox360_RightTrigger_Pull = 0x82,
	  SteamControllerActionOrigin_XBox360_RightTrigger_Click = 0x83,
	  SteamControllerActionOrigin_XBox360_LeftStick_Move = 0x84,
	  SteamControllerActionOrigin_XBox360_LeftStick_Click = 0x85,
	  SteamControllerActionOrigin_XBox360_LeftStick_DPadNorth = 0x86,
	  SteamControllerActionOrigin_XBox360_LeftStick_DPadSouth = 0x87,
	  SteamControllerActionOrigin_XBox360_LeftStick_DPadWest = 0x88,
	  SteamControllerActionOrigin_XBox360_LeftStick_DPadEast = 0x89,
	  SteamControllerActionOrigin_XBox360_RightStick_Move = 0x8A,
	  SteamControllerActionOrigin_XBox360_RightStick_Click = 0x8B,
	  SteamControllerActionOrigin_XBox360_RightStick_DPadNorth = 0x8C,
	  SteamControllerActionOrigin_XBox360_RightStick_DPadSouth = 0x8D,
	  SteamControllerActionOrigin_XBox360_RightStick_DPadWest = 0x8E,
	  SteamControllerActionOrigin_XBox360_RightStick_DPadEast = 0x8F,
	  SteamControllerActionOrigin_XBox360_DPad_North = 0x90,
	  SteamControllerActionOrigin_XBox360_DPad_South = 0x91,
	  SteamControllerActionOrigin_XBox360_DPad_West = 0x92,
	  SteamControllerActionOrigin_XBox360_DPad_East = 0x93,
	  SteamControllerActionOrigin_SteamV2_A = 0x94,
	  SteamControllerActionOrigin_SteamV2_B = 0x95,
	  SteamControllerActionOrigin_SteamV2_X = 0x96,
	  SteamControllerActionOrigin_SteamV2_Y = 0x97,
	  SteamControllerActionOrigin_SteamV2_LeftBumper = 0x98,
	  SteamControllerActionOrigin_SteamV2_RightBumper = 0x99,
	  SteamControllerActionOrigin_SteamV2_LeftGrip = 0x9A,
	  SteamControllerActionOrigin_SteamV2_RightGrip = 0x9B,
	  SteamControllerActionOrigin_SteamV2_LeftGrip_Upper = 0x9C,
	  SteamControllerActionOrigin_SteamV2_RightGrip_Upper = 0x9D,
	  SteamControllerActionOrigin_SteamV2_LeftBumper_Pressure = 0x9E,
	  SteamControllerActionOrigin_SteamV2_RightBumper_Pressure = 0x9F,
	  SteamControllerActionOrigin_SteamV2_LeftGrip_Pressure = 0xA0,
	  SteamControllerActionOrigin_SteamV2_RightGrip_Pressure = 0xA1,
	  SteamControllerActionOrigin_SteamV2_LeftGrip_Upper_Pressure = 0xA2,
	  SteamControllerActionOrigin_SteamV2_RightGrip_Upper_Pressure = 0xA3,
	  SteamControllerActionOrigin_SteamV2_Start = 0xA4,
	  SteamControllerActionOrigin_SteamV2_Back = 0xA5,
	  SteamControllerActionOrigin_SteamV2_LeftPad_Touch = 0xA6,
	  SteamControllerActionOrigin_SteamV2_LeftPad_Swipe = 0xA7,
	  SteamControllerActionOrigin_SteamV2_LeftPad_Click = 0xA8,
	  SteamControllerActionOrigin_SteamV2_LeftPad_Pressure = 0xA9,
	  SteamControllerActionOrigin_SteamV2_LeftPad_DPadNorth = 0xAA,
	  SteamControllerActionOrigin_SteamV2_LeftPad_DPadSouth = 0xAB,
	  SteamControllerActionOrigin_SteamV2_LeftPad_DPadWest = 0xAC,
	  SteamControllerActionOrigin_SteamV2_LeftPad_DPadEast = 0xAD,
	  SteamControllerActionOrigin_SteamV2_RightPad_Touch = 0xAE,
	  SteamControllerActionOrigin_SteamV2_RightPad_Swipe = 0xAF,
	  SteamControllerActionOrigin_SteamV2_RightPad_Click = 0xB0,
	  SteamControllerActionOrigin_SteamV2_RightPad_Pressure = 0xB1,
	  SteamControllerActionOrigin_SteamV2_RightPad_DPadNorth = 0xB2,
	  SteamControllerActionOrigin_SteamV2_RightPad_DPadSouth = 0xB3,
	  SteamControllerActionOrigin_SteamV2_RightPad_DPadWest = 0xB4,
	  SteamControllerActionOrigin_SteamV2_RightPad_DPadEast = 0xB5,
	  SteamControllerActionOrigin_SteamV2_LeftTrigger_Pull = 0xB6,
	  SteamControllerActionOrigin_SteamV2_LeftTrigger_Click = 0xB7,
	  SteamControllerActionOrigin_SteamV2_RightTrigger_Pull = 0xB8,
	  SteamControllerActionOrigin_SteamV2_RightTrigger_Click = 0xB9,
	  SteamControllerActionOrigin_SteamV2_LeftStick_Move = 0xBA,
	  SteamControllerActionOrigin_SteamV2_LeftStick_Click = 0xBB,
	  SteamControllerActionOrigin_SteamV2_LeftStick_DPadNorth = 0xBC,
	  SteamControllerActionOrigin_SteamV2_LeftStick_DPadSouth = 0xBD,
	  SteamControllerActionOrigin_SteamV2_LeftStick_DPadWest = 0xBE,
	  SteamControllerActionOrigin_SteamV2_LeftStick_DPadEast = 0xBF,
	  SteamControllerActionOrigin_SteamV2_Gyro_Move = 0xC0,
	  SteamControllerActionOrigin_SteamV2_Gyro_Pitch = 0xC1,
	  SteamControllerActionOrigin_SteamV2_Gyro_Yaw = 0xC2,
	  SteamControllerActionOrigin_SteamV2_Gyro_Roll = 0xC3,
	  SteamControllerActionOrigin_Count = 0xC4,
	  SteamControllerActionOrigin_SwitchProCon_A = 0xC4,
	  SteamControllerActionOrigin_SwitchProCon_B = 0xC5,
	  SteamControllerActionOrigin_SwitchProCon_X = 0xC6,
	  SteamControllerActionOrigin_SwitchProCon_Y = 0xC7,
	  SteamControllerActionOrigin_SwitchProCon_L = 0xC8,
	  SteamControllerActionOrigin_SwitchProCon_R = 0xC9,
	  SteamControllerActionOrigin_SwitchProCon_Plus = 0xCA,
	  SteamControllerActionOrigin_SwitchProCon_Minus = 0xCB,
	  SteamControllerActionOrigin_SwitchProCon_Capture = 0xCC,
	  SteamControllerActionOrigin_SwitchProCon_ZL_Pull = 0xCD,
	  SteamControllerActionOrigin_SwitchProCon_ZL_Click = 0xCE,
	  SteamControllerActionOrigin_SwitchProCon_ZR_Pull = 0xCF,
	  SteamControllerActionOrigin_SwitchProCon_ZR_Click = 0xD0,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_Move = 0xD1,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_Click = 0xD2,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_DPadNorth = 0xD3,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_DPadSouth = 0xD4,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_DPadWest = 0xD5,
	  SteamControllerActionOrigin_SwitchProCon_LeftStick_DPadRight = 0xD6,
	  SteamControllerActionOrigin_SwitchProCon_RightStick_Move = 0xD7,
	  SteamControllerActionOrigin_SwitchProCon_RichtStick_Click = 0xD8,
	  SteamControllerActionOrigin_SwitchProCon_RightStick_DPadNorth = 0xD9,
	  SteamControllerActionOrigin_SwitchProCon_RightStick_DPadSouth = 0xDA,
	  SteamControllerActionOrigin_SwitchProCon_RightStick_DPadWest = 0xDB,
	  SteamControllerActionOrigin_SwitchProCon_RightStick_DPadEast = 0xDC,
	  SteamControllerActionOrigin_SwitchProCon_DPad_North = 0xDD,
	  SteamControllerActionOrigin_SwitchProCon_DPad_South = 0xDE,
	  SteamControllerActionOrigin_SwitchProCon_DPad_West = 0xDF,
	  SteamControllerActionOrigin_SwitchProCon_DPad_East = 0xE0,
	};

	/* 437 */
	enum ControllerType
	{
	  ControllerType_Unkown = 0x0,
	  ControllerType_Keyboard = 0x1,
	  ControllerType_Mouse = 0x2,
	  ControllerType_PS3 = 0x3,
	  ControllerType_DualShock4 = 0x4,
	  ControllerType_Xbox360 = 0x5,
	  ControllerType_3ds = 0x6,
	  ControllerType_WiiUGamePad = 0x7,
	  ControllerType_WiiMote = 0x8,
	  ControllerType_OSX = 0x9,
	  ControllerType_XBone = 0xA,
	  ControllerType_PSVita = 0xB,
	  ControllerType_Steam = 0xC,
	  ControllerType_JoyConPair = 0xD,
	  ControllerType_JoyConSingle = 0xE,
	  ControllerType_SwitchProController = 0xF,
	  ControllerType_Count = 0x10,
	};

	/* 439 */
	enum ControllerClass
	{
	  ControllerClass_None = 0x0,
	  ControllerClass_Keyboard = 0x1,
	  ControllerClass_Mouse = 0x2,
	  ControllerClass_Controller = 0x3,
	  ControllerClass_Touch = 0x4,
	  ControllerClass_Count = 0x5,
	};

	/* 442 */
	enum FlickDirection
	{
	  FlickDirection_Left = 0x0,
	  FlickDirection_Right = 0x1,
	  FlickDirection_Up = 0x2,
	  FlickDirection_Down = 0x3,
	};

	/* 444 */
	enum WindowsControllerApi
	{
	  WindowsControllerApi_XInput = 0x0,
	  WindowsControllerApi_DInput = 0x1,
	  WindowsControllerApi_SteamController = 0x2,
	  WindowsControllerApi_Count = 0x3,
	};

	/* 445 */
	enum InputEventType
	{
	  InputEventType_GameButtonDown = 0x0,
	  InputEventType_GameButtonUp = 0x1,
	  InputEventType_GameAxis = 0x2,
	  InputEventType_GameAxis2d = 0x3,
	  InputEventType_ControllerConnected = 0x4,
	  InputEventType_ControllerDisconnected = 0x5,
	  InputEventType_ControllerTypeChanged = 0x6,
	  InputEventType_RawButtonDown = 0x7,
	  InputEventType_RawButtonUp = 0x8,
	  InputEventType_RawAxis = 0x9,
	  InputEventType_Key = 0xA,
	  InputEventType_MouseMove = 0xB,
	  InputEventType_MouseRelativeMovement = 0xC,
	  InputEventType_MouseWheel = 0xD,
	  InputEventType_FocusLost = 0xE,
	  InputEventType_FocusRestored = 0xF,
	  InputEventType_TouchBegin = 0x10,
	  InputEventType_TouchEnd = 0x11,
	  InputEventType_TouchCancel = 0x12,
	  InputEventType_TouchMove = 0x13,
	  InputEventType_VirtualKeyboardOpened = 0x14,
	  InputEventType_VirtualKeyboardText = 0x15,
	  InputEventType_VirtualKeyboardClosed = 0x16,
	  InputEventType_Flick = 0x17,
	  InputEventType_Drag = 0x18,
	  InputEventType_DragBegin = 0x19,
	  InputEventType_DragEnd = 0x1A,
	  InputEventType_GyroAcceleration = 0x1B,
	  InputEventType_GyroAngularVelocity = 0x1C,
	  InputEventType_GyroOrientation = 0x1D,
	  InputEventType_Count = 0x1E,
	};

	/* 448 */
	enum InputType
	{
	  InputType_Binary = 0x0,
	  InputType_1dAnalogValue = 0x1,
	  InputType_2dAnalogValue = 0x2,
	};

	/* 449 */
	enum ControllerInput
	{
	  ControllerInput_Axis = 0x0,
	  ControllerInput_Button = 0x1,
	  ControllerInput_ButtonToAxis = 0x2,
	  ControllerInput_MouseToAxis = 0x3,
	};

	/* 451 */
	enum FixedControllerId
	{
	  FixedControllerId_Keyboard = 0x0,
	  FixedControllerId_Mouse = 0x1,
	  FixedControllerId_Xbox360_0 = 0x2,
	  FixedControllerId_Xbox360_1 = 0x3,
	  FixedControllerId_Xbox360_2 = 0x4,
	  FixedControllerId_Xbox360_3 = 0x5,
	  FixedControllerId_DinputStart = 0x6,
	  FixedControllerId_DinputEnd = 0xD,
	  FixedControllerId_SteamControllerStart = 0xE,
	};

	/* 452 */
	enum StandardButtonId
	{
	  StandardButtonId_Unknown = 0x0,
	  StandardButtonId_Left = 0x1,
	  StandardButtonId_Right = 0x2,
	  StandardButtonId_Up = 0x3,
	  StandardButtonId_Down = 0x4,
	  StandardButtonId_Confirm = 0x5,
	  StandardButtonId_Exit = 0x6,
	  StandardButtonId_StartPause = 0x7,
	  StandardButtonId_Select = 0x8,
	};

	//*** Needs Fix ***//
	/* 457 */
	enum ControllerSteam::Max
	{
	  MaxNumActionSets = 0xA,
	  MaxNumActions = 0x80,
	  MaxNumAnalogActions = 0x30,
	};

	/* 460 */
	enum ControllerNds::ButtonId
	{
	  ButtonId_A = 0x1,
	  ButtonId_B = 0x2,
	  ButtonId_Select = 0x4,
	  ButtonId_Start = 0x8,
	  ButtonId_Right = 0x10,
	  ButtonId_Left = 0x20,
	  ButtonId_Up = 0x40,
	  ButtonId_Down = 0x80,
	  ButtonId_R = 0x100,
	  ButtonId_L = 0x200,
	  ButtonId_X = 0x400,
	  ButtonId_Y = 0x800,
	  ButtonId_Debug = 0x2000,
	  ButtonId_Force32Bit = 0x7FFFFFFF,
	};

	/* 462 */
	enum ImmediateBlendMode
	{
	  ImmediateBlendMode_Invalid = 0xFFFFFFFF,
	  ImmediateBlendMode_None = 0x0,
	  ImmediateBlendMode_Blend_Alpha = 0x1,
	  ImmediateBlendMode_Add_Alpha = 0x2,
	  ImmediateBlendMode_Sub_Alpha = 0x3,
	  ImmediateBlendMode_Add = 0x4,
	  ImmediateBlendMode_Sub = 0x5,
	  ImmediateBlendMode_Count = 0x6,
	};

	/* 463 */
	enum ImmediateAlphaMode
	{
	  ImmediateAlphaMode_Invalid = 0xFFFFFFFF,
	  ImmediateAlphaMode_PremultipliedAlpha = 0x0,
	  ImmediateAlphaMode_NonPremultipliedAlpha = 0x1,
	  ImmediateAlphaMode_Count = 0x2,
	  ImmediateAlphaMode_PlatformDefault = 0x1,
	};

	/* 464 */
	enum ImmediateDepthTestMode
	{
	  ImmediateDepthTestMode_Never = 0x0,
	  ImmediateDepthTestMode_Less = 0x1,
	  ImmediateDepthTestMode_Equal = 0x2,
	  ImmediateDepthTestMode_LessEqual = 0x3,
	  ImmediateDepthTestMode_Greater = 0x4,
	  ImmediateDepthTestMode_NotEqual = 0x5,
	  ImmediateDepthTestMode_GreaterEqual = 0x6,
	  ImmediateDepthTestMode_Always = 0x7,
	  ImmediateDepthTestMode_Count = 0x8,
	};

	/* 465 */
	enum ImmediateDepthWriteMode
	{
	  ImmediateDepthWriteMode_Enabled = 0x0,
	  ImmediateDepthWriteMode_Disabled = 0x1,
	  ImmediateDepthWriteMode_Count = 0x2,
	};

	/* 466 */
	enum ImmediateCullMode
	{
	  ImmediateCullMode_None = 0x0,
	  ImmediateCullMode_Back = 0x1,
	  ImmediateCullMode_Front = 0x2,
	  ImmediateCullMode_Count = 0x3,
	};

	/* 467 */
	enum ImmediateFillMode
	{
	  ImmediateFillMode_Solid = 0x0,
	  ImmediateFillMode_Wireframe = 0x1,
	  ImmediateFillMode_Count = 0x2,
	};

	/* 468 */
	enum ImmediateTextureFilterMode
	{
	  ImmediateTextureFilterMode_Nearest = 0x0,
	  ImmediateTextureFilterMode_BiLinear = 0x1,
	  ImmediateTextureFilterMode_TriLinear = 0x2,
	  ImmediateTextureFilterMode_Count = 0x3,
	};

	/* 469 */
	enum ImmediateTextureAddressMode
	{
	  ImmediateTextureAddressMode_Wrap = 0x0,
	  ImmediateTextureAddressMode_Mirror = 0x1,
	  ImmediateTextureAddressMode_Clamp = 0x2,
	  ImmediateTextureAddressMode_Count = 0x3,
	};

	/* 470 */
	enum GraphicsStockVertexShaderId
	{
	  GraphicsStockVertexShaderId_Immediate = 0x0,
	  GraphicsStockVertexShaderId_Copy = 0x1,
	  GraphicsStockVertexShaderId_Count = 0x2,
	};

	// /* 471 */
	// enum $473ED3F5E5CA33C6A1A78277275E18E6
	// {
	//   MaxEdramBlockCount = 0x40,
	//   MaxSlotsPerAllocation = 0x5,
	// };

	/* 472 */
	enum GraphicsStockFragmentShaderId
	{
	  GraphicsStockFragmentShaderId_Immediate = 0x0,
	  GraphicsStockFragmentShaderId_Immediate_VolumeSlice = 0x1,
	  GraphicsStockFragmentShaderId_Copy = 0x2,
	  GraphicsStockFragmentShaderId_Count = 0x3,
	};

	/* 473 */
	enum GraphicsStockShaderPipelineId
	{
	  GraphicsStockShaderPipelineId_Immediate = 0x0,
	  GraphicsStockShaderPipelineId_Immediate_VolumeSlice = 0x1,
	  GraphicsStockShaderPipelineId_Copy = 0x2,
	  GraphicsStockShaderPipelineId_Count = 0x3,
	};

	/* 474 */
	enum GraphicsStockTextureId
	{
	  GraphicsStockTextureId_White = 0x0,
	  GraphicsStockTextureId_Count = 0x1,
	};

	/* 477 */
	enum ScreenCaptureState
	{
	  ScreenCaptureState_Recording = 0x0,
	  ScreenCaptureState_StartWriting = 0x1,
	  ScreenCaptureState_Writing = 0x2,
	  ScreenCaptureState_StartRecording = 0x3,
	};

	/* 484 */
	enum GraphicsStateObjectType
	{
	  GraphicsStateObjectType_BlendState = 0x0,
	  GraphicsStateObjectType_RasterizerState = 0x1,
	  GraphicsStateObjectType_SamplerState = 0x2,
	  GraphicsStateObjectType_DepthStencilState = 0x3,
	  GraphicsStateObjectType_VertexFormat = 0x4,
	  GraphicsStateObjectType_VertexInputBinding = 0x5,
	  GraphicsStateObjectType_Count = 0x6,
	};

	// /* 485 */
	// enum $BA7F8EDEE36FB4209BD0DB5D8EF86D8E
	// {
	//   Handle_Invalid = 0xFFFFFFFF,
	// };

	/* 486 */
	enum TextureFlagMaskD3D11
	{
	  TextureFlagWinMaskD3D11_AlphaIsPremultiplied = 0x80,
	  TextureFlagWinMaskD3D11_AliasableFormat = 0x100,
	};

	/* 487 */
	enum GraphicsMapFlagMask
	{
	  GraphicsMapFlagMask_NonBlocking = 0x1,
	};

	// /* 488 */
	// enum $FA8851A9C07D47D490413CF52DB1E47D
	// {
	//   BucketSize = 0x4,
	//   MinBucketCount = 0x8,
	// };

	//*** Needs Fix ***//
	/* 489 */
	enum EdramManager::BlockState
	{
	  BlockState_Invalid = 0x0,
	  BlockState_Free = 0x1,
	  BlockState_Reusable = 0x2,
	  BlockState_Unresolved = 0x3,
	  BlockState_Used = 0x4,
	};

	// /* 490 */
	// enum $EF7C0E4A8CCB173AAC63430876B3E86B
	// {
	//   WCODE_HRESULT_FIRST = 0x80040200,
	//   WCODE_HRESULT_LAST = 0x8004FFFF,
	// };

	// /* 491 */
	// enum DXGI_MODE_ROTATION
	// {
	// };

	/* 492 */
	enum LineSegmentIntersectionType
	{
	  LineSegmentIntersectionType_NoIntersection = 0x0,
	  LineSegmentIntersectionType_Intersect = 0x1,
	  LineSegmentIntersectionType_Collinear = 0x2,
	};

	/* 493 */
	// enum $494E8E5437B7F5B9813AA15E80A3F7BB
	// {
	//   SoundProviderId_WaveWin32 = 0x0,
	// };

	/* 494 */
	enum SoundFlag
	{
	  SoundFlag_Loop = 0x1,
	  SoundFlag_StartPaused = 0x2,
	  SoundFlag_SynchronousStream = 0x4,
	  SoundFlag_StartSilent = 0x8,
	};

	// /* 495 */
	// enum $2305C325CECB5E0FDA668EE5E38A8FA2
	// {
	//   SoundProviderId_Invalid = 0xFF,
	// };

	//*** Needs Fix ***//
	/* 496 */
	enum SoundSystem::Positioning
	{
	  Positioning_listener = 0x0,
	  Positioning_world = 0x1,
	};

	//*** Needs Fix ***//
	/* 497 */
	enum SoundSystem::ChannelIDs
	{
	  ChannelIDs_FrontLeft = 0x0,
	  ChannelIDs_FrontRight = 0x1,
	  ChannelIDs_RearLeft = 0x2,
	  ChannelIDs_RearRight = 0x3,
	  ChannelIDs_BackLeft = 0x4,
	  ChannelIDs_BackRight = 0x5,
	};

	// /* 498 */
	// enum $14CD41B32F0C62A52EB3A7E11BCA0DF1
	// {
	//   SoundHandle_SoundIndexMask = 0x3FFF,
	//   SoundHandle_SoundIndexShift = 0x0,
	//   SoundHandle_RunCountMask = 0xFFFF0000,
	//   SoundHandle_RunCountShift = 0x10,
	//   SoundHandle_IndexedSoundFlag = 0x4000,
	//   SoundHandle_FlagsMask = 0xC000,
	// };

	// /* 499 */
	// enum $9566E5C8146C7C7494FFB8D421330E37
	// {
	//   SoundFileHeaderFlag_Loopable = 0x1,
	//   SoundFileHeaderFlag_BufferInterleaved = 0x2,
	// };

	//*** Needs Fix ***//
	/* 500 */
	enum SoundSystem::BaseSound::Flag
	{
	  Flag_Looped = 0x8000,
	  Flag_KeyOn = 0x4000,
	  Flag_Mask = 0xC000,
	  Flag_RunCountMask = 0x3FFF,
	};

	//*** Needs Fix ***//
	/* 501 */
	enum SoundSystem::ParameterAutomation::Command
	{
	  Command_Nop = 0x0,
	  Command_FadeVolume = 0x1,
	  Command_PitchBend = 0x2,
	  Command_FadeoutAndStop = 0x3,
	};

	// /* 502 */
	// enum $38DCDA02E7542A0B511F6A5B107BA8A3
	// {
	//   RunFlag_FadeOutAndStop = 0x1,
	//   RunFlag_KeyOnRequested = 0x4,
	//   RunFlag_Paused = 0x8,
	// };

	// /* 503 */
	// enum $A8EC429846103EA5CA6FA5310BF725EE
	// {
	//   StopTimer_Default = 0x4,
	// };

	//*** Needs Fix ***//
	/* 504 */
	enum SoundSystem::SoundDefinitionFlags
	{
	  SoundDefinitionFlags_isBgm = 0x1,
	};

	/* 525 */
	enum RegionId
	{
	  RegionId_Unknown = 0x0,
	  RegionId_Europe = 0x1,
	  RegionId_NorthAmerica = 0x2,
	  RegionId_Count = 0x3,
	};

	/* 526 */
	enum LanguageFamily
	{
	  LanguageFamily_En = 0x0,
	  LanguageFamily_De = 0x1,
	  LanguageFamily_Fr = 0x2,
	  LanguageFamily_It = 0x3,
	  LanguageFamily_Es = 0x4,
	  LanguageFamily_Pl = 0x5,
	  LanguageFamily_Ru = 0x6,
	  LanguageFamily_Ja = 0x7,
	  LanguageFamily_Pt = 0x8,
	  LanguageFamily_Ko = 0x9,
	  LanguageFamily_Cs = 0xA,
	  LanguageFamily_Es_LA = 0xB,
	  LanguageFamily_Zh_Simplified = 0xC,
	  LanguageFamily_Zh_Traditional = 0xD,
	  LanguageFamily_Arabic = 0xE,
	  LanguageFamily_Count = 0xF,
	};

	/* 527 */
	enum LanguageId
	{
	  LanguageId_En_En = 0x0,
	  LanguageId_En_Us = 0x1,
	  LanguageId_De_De = 0x2,
	  LanguageId_Fr_Fr = 0x3,
	  LanguageId_It_It = 0x4,
	  LanguageId_Es_Es = 0x5,
	  LanguageId_Pl_Pl = 0x6,
	  LanguageId_Ru_Ru = 0x7,
	  LanguageId_Ja_Jp = 0x8,
	  LanguageId_Pt_Br = 0x9,
	  LanguageId_Pt_Pt = 0xA,
	  LanguageId_Ko_Kr = 0xB,
	  LanguageId_Cs_Cz = 0xC,
	  LanguageId_Es_Ar = 0xD,
	  LanguageId_Es_Bo = 0xE,
	  LanguageId_Es_Cl = 0xF,
	  LanguageId_Es_Co = 0x10,
	  LanguageId_Es_Cr = 0x11,
	  LanguageId_Es_Do = 0x12,
	  LanguageId_Es_Ec = 0x13,
	  LanguageId_Es_Gt = 0x14,
	  LanguageId_Es_Hn = 0x15,
	  LanguageId_Es_Mx = 0x16,
	  LanguageId_Es_Ni = 0x17,
	  LanguageId_Es_Pa = 0x18,
	  LanguageId_Es_Pe = 0x19,
	  LanguageId_Es_Pr = 0x1A,
	  LanguageId_Es_Py = 0x1B,
	  LanguageId_Es_Sv = 0x1C,
	  LanguageId_Es_Uy = 0x1D,
	  LanguageId_Es_Ve = 0x1E,
	  LanguageId_Zh_Cn = 0x1F,
	  LanguageId_Zh_Tw = 0x20,
	  LanguageId_Ar_Eg = 0x21,
	  LanguageId_Ar_Dz = 0x22,
	  LanguageId_Ar_Bh = 0x23,
	  LanguageId_Ar_Iq = 0x24,
	  LanguageId_Ar_Jo = 0x25,
	  LanguageId_Ar_Kw = 0x26,
	  LanguageId_Ar_Lb = 0x27,
	  LanguageId_Ar_Ly = 0x28,
	  LanguageId_Ar_Ma = 0x29,
	  LanguageId_Ar_Om = 0x2A,
	  LanguageId_Ar_Qa = 0x2B,
	  LanguageId_Ar_Sa = 0x2C,
	  LanguageId_Ar_Sy = 0x2D,
	  LanguageId_Ar_Tn = 0x2E,
	  LanguageId_Ar_Ae = 0x2F,
	  LanguageId_Ar_Ye = 0x30,
	  LanguageId_Count = 0x31,
	};

	/* 528 */
	enum SteamError
	{
	  SteamError_Ok = 0x0,
	  SteamError_FailedInitialization = 0x1,
	  SteamError_NotSubscribedToApp = 0x2,
	};

	/* 530 */
	enum ApplicationProcessState
	{
	  ApplicationProcessState_Foreground = 0x0,
	  ApplicationProcessState_ForegroundWithSystemMessageOpen = 0x1,
	  ApplicationProcessState_Background = 0x2,
	};

	/* 535 */
	enum FatalErrorTypeId
	{
	  FatalErrorTypeId_ContentError = 0x0,
	  FatalErrorTypeId_Count = 0x1,
	};

	// /* 536 */
	// enum $626CF69AFF07CF528DE2DBBA8767C00F
	// {
	//   DeltaCompression_MaxRunLength = 0xFF,
	// };

	/* 537 */
	enum DirectoryWatchChangeFlags
	{
	  DirectoryWatchChangeFlags_None = 0x0,
	  DirectoryWatchChangeFlags_Modified = 0x1,
	  DirectoryWatchChangeFlags_Added = 0x2,
	  DirectoryWatchChangeFlags_Removed = 0x4,
	  DirectoryWatchChangeFlags_Renamed = 0x8,
	  DirectoryWatchChangeFlags_All = 0xF,
	};

	// /* 538 */
	// enum $BBF2C74F60E60FB79F879E7BCBBCFD41
	// {
	//   PakfileChunkSize = 0x1000,
	//   MaxCompressedChunkSize = 0x2000,
	// };

	// /* 539 */
	// enum $06963531A56E7E69CF32240D014103CE
	// {
	//   MaxMemoryBlockCount = 0x80,
	// };

	/* 540 */
	enum IniVariableTokenType
	{
	  IniVariableTokenType_Invalid = 0xFFFFFFFF,
	  IniVariableTokenType_Identifier = 0x0,
	  IniVariableTokenType_StringLiteral = 0x1,
	  IniVariableTokenType_IntegerLiteral = 0x2,
	  IniVariableTokenType_FloatLiteral = 0x3,
	  IniVariableTokenType_LeftBrace = 0x4,
	  IniVariableTokenType_RightBrace = 0x5,
	  IniVariableTokenType_Semicolon = 0x6,
	  IniVariableTokenType_Assignment = 0x7,
	  IniVariableTokenType_Append = 0x8,
	  IniVariableTokenType_Namespace = 0x9,
	  IniVariableTokenType_Include = 0xA,
	  IniVariableTokenType_Count = 0xB,
	};

	/* 543 */
	enum StateTreeStateId
	{
	  StateTreeStateId_Invalid = 0xFFFFFFFF,
	  StateTreeStateId_Root = 0x0,
	};

	/* 544 */
	enum RequestedTimeZone
	{
	  RequestedTimeZone_UTC = 0x0,
	  RequestedTimeZone_Local = 0x1,
	};

	/* 545 */
	enum CharacterEncodingId
	{
	  CharacterEncodingId_ASCII = 0x0,
	  CharacterEncodingId_UTF8 = 0x1,
	  CharacterEncodingId_UTF16 = 0x2,
	  CharacterEncodingId_USC2 = 0x3,
	};

	// /* 546 */
	// enum $0D36974819FA191F220C8BB90D9C4961
	// {
	//   InvalidFileDeviceFileHandle = 0xFFFF,
	//   MaxFileDeviceStreamCount = 0xFFFE,
	// };

	// /* 547 */
	// enum $736A1EB088D751ED95FA93B5E34E1414
	// {
	//   DecompressionBufferSize = 0x800,
	// };

	// /* 548 */
	// enum $8D35E3C460FEF4601CBFA2D1B10A610B
	// {
	//   InvalidChunkIndex = 0xFFFFFFFF,
	// };

	// /* 549 */
	// typedef $8508ECD3827895F22B49FF1E1A13E1B8 $164D3D12C2CC6CD2CD2DBEE6C6A9D032;

	// /* 550 */
	// enum $ADF832B0788153EFE7EF304C1903B01F
	// {
	//   MaxVariableNameLength = 0x100,
	//   MaxVariableValueLength = 0x100,
	// };

	// /* 551 */
	// enum $A78FF6C32FC6D822E9EEF182F59D57BE
	// {
	//   MaxPutBackCharCount = 0x8,
	// };

	/* 552 */
	enum ResourceConfigurationSkuId
	{
	  ResourceConfigurationSkuId_Count = 0x10,
	};

	/* 553 */
	enum TerminationStep
	{
	  TerminationStep_AbortLoading = 0x0,
	  TerminationStep_TerminateMovieAndSound = 0x1,
	  TerminationStep_TerminateLibraries = 0x2,
	  TerminationStep_CompleteWrite = 0x3,
	  TerminationStep_PS3_EndRSX = 0x4,
	};

	//*** Needs Fix ***//
	/* 558 */
	enum XmlWriter::ElementType
	{
	  ElementType_StartEnd = 0x0,
	  ElementType_Empty = 0x1,
	};

	// /* 559 */
	// enum $0F7889596B6D0DF1AF5A82E8B67C9B47
	// {
	//   BaseTypeBitCount = 0x8,
	// };

	//*** Needs Fix ***//
	/* 560 */
	enum FormatOutputOptions::Mode
	{
	  Mode_Decimal = 0x0,
	  Mode_Short = 0x1,
	};

	/* 561 */
	enum DebugCommandResult
	{
	};

	// /* 562 */
	// enum $259B422CD699DDC0FD13E1315A789A95
	// {
	//   MaxLexemLength = 0x100,
	// };

	/* 563 */
	enum DebugConnectionState
	{
	  DebugConnectionState_Disconnected = 0x0,
	  DebugConnectionState_Connected = 0x1,
	};

	/* 564 */
	enum KnownWindowsFolderId
	{
	  KnownWindowsFolderId_Videos = 0x0,
	  KnownWindowsFolderId_Pictures = 0x1,
	  KnownWindowsFolderId_RoamingAppData = 0x2,
	  KnownWindowsFolderId_MyDocuments = 0x3,
	  KnownWindowsFolderId_Count = 0x4,
	};

    
	//STRUCTS START HERE


	/* 2328 */
	struct IniVariableBase
	{
	  IniVariableBaseVtbl *vfptr;
	  const char *m_pName;
	  const char *m_pDescription;
	  const char *m_pOwner;
	  bool m_hasChanged;
	  IniVariableBase *m_pNext;
	  IniVariableBase *m_pPrev;
	};

	/* 2331 */
	struct IniVariableBaseVtbl
	{
	  void* (__thiscall* __vecDelDtor)(IniVariableBase* this, unsigned int);
	  bool (__thiscall* setValueFromString)(IniVariableBase* this, const char*);
	  void (__thiscall* toString)(IniVariableBase* this, char* , unsigned int);
	  void (__thiscall* setCurrentValueAsDefaultValue)(IniVariableBase* this);
	  void (__thiscall* reset)(IniVariableBase* this);
	  void (__thiscall* destroy)(IniVariableBase* this);
	  void (__thiscall* getDefinitionString)(IniVariableBase* this, char*, unsigned int);
	  EnumVariableBase* (__thiscall* castToEnumVariable)(IniVariableBase* this);
	};

	/* 2329 */
	const struct EnumDescriptionEntry
	{
	  int value;
	  const char *pName;
	};

	/* 2330 */
	struct __unaligned __declspec(align(4)) EnumVariableBase : IniVariableBase
	{
	  int m_value;
	  int m_defaultValue;
	  EnumDescriptionEntry *m_pEntries;
	  unsigned int m_entryCount;
	};

	/* 2332 */
	struct __declspec(align(4)) IntVariable : IniVariableBase
	{
	  int m_value;
	  int m_defaultValue;
	  int m_minValue;
	  int m_maxValue;
	  bool m_clampValue;
	};

	/* 2333 */
	struct String
	{
	  const char *pStart;
	  const char *pEnd;
	};

	/* 2334 */
	struct float3
	{
	  float x;
	  float y;
	  float z;
	};

	/* 2335 */
	struct float4
	{
	  float x;
	  float y;
	  float z;
	  float w;
	};

	/* 2336 */
	struct __declspec(align(4)) BoolVariable : IniVariableBase
	{
	  bool m_value;
	  bool m_defaultValue;
	};

	/* 2337 */
	struct __declspec(align(4)) FloatVariable : IniVariableBase
	{
	  float m_value;
	  float m_defaultValue;
	  float m_minValue;
	  float m_maxValue;
	  bool m_clampValue;
	};

	/* 2338 */
	struct float1
	{
	  float x;
	};

	/* 2339 */
	struct StringVariable : IniVariableBase
	{
	  bool m_deleteValue;
	  bool m_deleteDefaultValue;
	  const char* m_pValue;
	  const char* m_pDefaultValue;
	};

	/* 2340 */
	struct float2
	{
	  float x;
	  float y;
	};

	/* 2341 */
/*	union __m64
	{
	  unsigned long long m64_u64;
	  float m64_f32[2];
	  char m64_i8[8];
	  short m64_i16[4];
	  int m64_i32[2];
	  long long m64_i64;
	  char m64_u8[8];
	  unsigned short m64_u16[4];
	  unsigned int m64_u32[2];
	};*/

	/* 2342 */
	struct MemoryBlockDefinition
	{
	  unsigned int size;
	  unsigned int alignment;
	  unsigned short type;
	  unsigned short flags;
	  unsigned int initialProtectionMask;
	  const char* pDescription;
	};

	/* 2343 */
	struct MemoryLayoutDefinition
	{
	  MemoryBlockDefinition* pBlockDefinitions;
	  unsigned int blockCount;
	};

	/* 2374 */
	struct MemoryBlock
	{
	  char* pStart;
	  unsigned int size;
	};

	/* 2391 */
	struct SequenceResourceHandleType
	{
	};

	/* 2392 */
	struct FileDeviceInterface
	{
	  FileDeviceInterfaceVtbl* vfptr;
	};

	/* 2400 */
	struct FileDeviceInterfaceVtbl
	{
	  void* (__thiscall* __vecDelDtor)(FileDeviceInterface* this, unsigned int);
	  _BYTE gap4[4];
	  IoError (__thiscall* closeFile)(FileDeviceInterface* this, unsigned __int16);
	  IoError (__thiscall* freeMountData)(FileDeviceInterface* this, MemoryAllocator* , FileDeviceMountData* );
	  IoResult<unsigned int> (__thiscall* read)(FileDeviceInterface* this, unsigned __int16, void* , unsigned int);
	  IoResult<unsigned int> (__thiscall* write)(FileDeviceInterface* this, unsigned __int16, const void*, unsigned int);
	  IoError (__thiscall* flushWriteBuffer)(FileDeviceInterface* this, unsigned __int16);
	  IoResult<unsigned __int64>* (__thiscall* getSize)(FileDeviceInterface* this, IoResult<unsigned __int64>* result, unsigned __int16);
	  IoError (__thiscall* setPosition)(FileDeviceInterface* this, unsigned __int16, unsigned __int64);
	  IoResult<unsigned __int64>* (__thiscall* getPosition)(FileDeviceInterface* this, IoResult<unsigned __int64>* result, unsigned __int16);
	  IoError (__thiscall* setFilePermissionByName)(FileDeviceInterface* this, FileDeviceMountData*, const char*, bool);
	  IoError (__thiscall* getFileStatusByName)(FileDeviceInterface* this, FileStatus*, FileDeviceMountData*, const char*, unsigned int);
	  bool (__thiscall* getNativeFilePath)(FileDeviceInterface* this, char*, unsigned int, FileDeviceMountData*, const char*);
	};

	/* 2393 */
	struct IoResult<unsigned short>
	{
	  unsigned __int16 result;
	  IoError error;
	};

	/* 2394 */
	const struct FileDeviceMountData
	{

	};

	/* 2395 */
	struct MemoryAllocator
	{
	  MemoryAllocatorVtbl* vfptr;
	};

	/* 2396 */
	struct MemoryAllocatorVtbl
	{
	  void* (__thiscall* __vecDelDtor)(MemoryAllocator* this, unsigned int);
	  void* (__thiscall* allocate)(MemoryAllocator* this, unsigned int, unsigned int, unsigned int, const char*);
	  void (__thiscall* free)(MemoryAllocator* this, void*);
	  const char* (__thiscall* getName)(MemoryAllocator* this);
	};

	/* 2397 */
	struct IoResult<unsigned int>
	{
	  unsigned int result;
	  IoError error;
	};

	/* 2398 */
	struct __declspec(align(8)) IoResult<unsigned long long>
	{
	  unsigned long long result;
	  IoError error;
	};

	/* 2399 */
	struct __declspec(align(4)) FileStatus
	{
	  int lastModificationTime;
	  unsigned long long size;
	  char nativeFileName[260];
	  bool isWriteable;
	  bool isDirectory;
	};

	/* 2401 */
	struct SequenceEventData
	{
	  unsigned short time;
	  unsigned short type;
	  const void* pData;
	};

	/* 2402 */
	struct StaticArray<SequenceEventData>
	{
	  SequenceEventData* m_pData;
	  unsigned int m_size;
	};

	/* 2403 */
	const struct __declspec(align(2)) SequenceData
	{
	  StaticArray<SequenceEventData> events;
	  unsigned short length;
	  bool mustComplete;
	};

	/* 2404 */
	struct SequencePlaybackState
	{
	  unsigned int flags;
	  unsigned int quantizedTime;
	  float time;
	  float sequenceLength;
	  SequenceData* pSequence;
	  unsigned int currentSequenceEventIndex;
	  unsigned int lastQueriedSequenceEventIndex;
	};

	/* 2405 */
	struct __declspec(align(4)) PlatformCppTypeConfiguration
	{
	  unsigned int intSize;
	  unsigned int pointerSize;
	  unsigned int mathTypeAlignment;
	  bool padBaseTypes;
	};

	/* 2406 */
	struct Mutex
	{
	  char m_name[32];
	  unsigned int m_criticalSectionData[6];
	};

	/* 2407 */
	struct MutexLock
	{
	  Mutex* m_pMutex;
	};

	/* 2408 */
	struct AutoMemoryBlock : MemoryBlock
	{
	  MemoryAllocator* m_pAllocator;
	};

	/* 2409 */
	struct ResourceFactory
	{
	  ResourceFactoryVtbl* vfptr;
	  ResourceFactory* m_pNextRegisteredFactory;
	};

	/* 2410 */
	struct Resource
	{
	  unsigned short m_flags;
	  char m_tag;
	  char m_unused;
	  unsigned int m_key;
	};

	/* 2411 */
	struct ResourceFactoryVtbl
	{
	  void* (__thiscall* __vecDelDtor)(ResourceFactory* this, unsigned int);
	  _BYTE gap4[4];
	  Resource* (__thiscall* createResource)(ResourceFactory* this, MemoryAllocator*, unsigned int);
	  void (__thiscall* destroyResource)(ResourceFactory* this, MemoryAllocator*, Resource*);
	  bool (__thiscall* unlockAllResources)(ResourceFactory* this, unsigned int);
	  bool (__thiscall* initializeResource)(ResourceFactory* this, Resource*, unsigned int, const void*, unsigned int);
	  void (__thiscall* postInitializeResource)(ResourceFactory* this, Resource*);
	  void (__thiscall* shutdownResource)(ResourceFactory* this, Resource*);
	  bool (__thiscall* createEmergencyResource)(ResourceFactory* this, Resource*, const char*);
	};

	/* 2412 */
	struct SequenceFactory : ResourceFactory
	{

	};

	/* 2413 */
	struct __declspec(align(4)) FileSystemCreationParameters
	{
	  	unsigned int maxDeviceCount;
	  	unsigned int maxMountPoints;
	  	unsigned int maxNativeStreamCount;
	  	unsigned int maxMemoryStreamCount;
	  	unsigned int maxMemoryFileCount;
	  	unsigned int maxPakStreamCount;
	  	unsigned int maxAliasStreamCount;
	  	unsigned int maxPakFileSize;
	  	unsigned int nativeThreadBufferSize;
	  	bool enableDefaultMount;
	  	bool useReadThreads;
	};

	/* 2414 */
	struct SequenceInitializationData
	{
	  	SequenceData* pSequenceData;
	};

	/* 2415 */
	struct BasePoolAllocator
	{
	  	MemoryBlock m_memoryBlock;
	  	unsigned int m_capacity;
	  	unsigned int m_size;
	  	unsigned int m_elementSize;
	  	unsigned int m_firstFreeIndex;
	};

	/* 2416 */
	struct PoolAllocator<FileSystemDeviceEntry>
	{
		BasePoolAllocator m_pool;
	};

	/* 2417 */
	struct PoolAllocator<FileSystemMountPoint>
	{
	  	BasePoolAllocator m_pool;
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2418 */
	struct PoolAllocator<NativeFileDevice::FileStreamData>
	{
	 	 BasePoolAllocator m_pool;
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2419 */
	struct FileStreamAllocator<NativeFileDevice::FileStreamData>
	{
	  	PoolAllocator<NativeFileDevice::FileStreamData> m_streamAllocator;
	  	Mutex m_streamMutex;
	};

	/* 2420 */
	struct Thread
	{
	  	void* m_threadHandle;
	  	unsigned int m_threadId;
	 	 volatile void* m_pArgument;
	 	 char m_identifier[64];
	 	 bool m_quitRequested;
		  int (__cdecl* m_pFunction)(Thread*);
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2421 */
	struct __declspec(align(8)) NativeFileDevice::ReadBuffer
	{
	 	 MemoryBlock data;
	 	 unsigned long long filePosition;
	 	 unsigned int size;
	 	 unsigned int readOffset;
	 	 IoError result;
	};

	/* 2422 */
	struct Event
	{
		  void* m_eventHandle;
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2423 */
	struct NativeFileDevice::ReadThreadContext
	{
		  Thread thread;
		  NativeFileDevice::ReadBuffer buffers[2]; //
		  Event bufferEmpty;
		  Event bufferFilled;
		  unsigned int bufferReadIndex;
		  unsigned int bufferWriteIndex;
		  bool hasBuffer;
		  void* fileHandle;
		  unsigned long long filePosition;
		  unsigned long long fileSize;
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2424 */
	struct Array<NativeFileDevice::ReadThreadContext>
	{
	 	 NativeFileDevice::ReadThreadContext* m_pData;
	 	 unsigned int m_size;
	};

	//*** Needs Fix -- NativeFileDevice::***//
	/* 2425 */
	struct __declspec(align(4)) NativeFileDevice : FileDeviceInterface
	{
	  	FileStreamAllocator<NativeFileDevice::FileStreamData> m_streams;
	  	Array<NativeFileDevice::ReadThreadContext> m_readThreadContexts;
	 	Mutex m_mutex;
	  	bool m_useReadThread;
	};

	/* 2426 */
	struct PoolAllocator<MemoryFileDevice::StreamEntry>
	{
	  	BasePoolAllocator m_pool;
	};

	//*** Needs Fix ***//
	/* 2427 */
	struct FileStreamAllocator<MemoryFileDevice::StreamEntry>
	{
	 	 PoolAllocator<MemoryFileDevice::StreamEntry> m_streamAllocator;
	 	 Mutex m_streamMutex;
	};

	/* 2428 */
	struct MemoryFileDeviceMountData : FileDeviceMountData
	{
	  	MemoryAllocator* pAllocator;
	  	unsigned int fileHandle;
	};

	/* 2429 */
	struct __declspec(align(4)) MemoryFileDevice::FileEntry
	{
		MemoryFileDeviceMountData *pMountData;
		MemoryBlock memoryBlock;
		unsigned int fileSize;
		unsigned int openCount;
		unsigned int fileNameCrc;
		bool isWritten;
		bool isWriteable;
	};

	/* 2430 */
	struct Array<MemoryFileDevice::FileEntry>
	{
	 	MemoryFileDevice::FileEntry *m_pData;
	  	unsigned int m_size;
	};

	/* 2431 */
	struct SizedArray<unsigned int>
	{
		unsigned int* m_pData;
	 	unsigned int m_size;
	 	unsigned int m_capacity;
	};

	/* 2432 */
	struct IndexArray
	{
	  	SizedArray<unsigned int> m_indices;
	};

	/* 2433 */
	struct MemoryFileDevice : FileDeviceInterface
	{
		FileStreamAllocator<MemoryFileDevice::StreamEntry> m_streams;
		Array<MemoryFileDevice::FileEntry> m_files;
		IndexArray m_fileIndices;
	};

	/* 2434 */
	struct PoolAllocator<PakFileDevice::PakFileStream>
	{
	  	BasePoolAllocator m_pool;
	};

	//*** Needs Fix ***//
	/* 2435 */
	struct FileStreamAllocator<PakFileDevice::PakFileStream>
	{
		PoolAllocator<PakFileDevice::PakFileStream> m_streamAllocator;
		Mutex m_streamMutex;
	};

	/* 2436 */
	struct TlsfAllocator
	{
	  	MemoryBlock m_memoryBlock;
	  	void* m_pPool;
	};

	/* 2437 */
	struct BaseMemoryAllocator<TlsfAllocator> : MemoryAllocator
	{
		Mutex m_mutex;
		char m_name[128];
		TlsfAllocator m_allocator;
		MemoryBlock m_memoryBlock;
		unsigned int m_allocatedSize;
		unsigned int m_maxAllocatedSize;
		unsigned int m_allocationCount;
		unsigned int m_flags;
	};

	/* 2438 */
	struct TlsfMemoryAllocator : BaseMemoryAllocator<TlsfAllocator>
	{

	};

	/* 2439 */
	struct PakFileDevice : FileDeviceInterface
	{
		FileStreamAllocator<PakFileDevice::PakFileStream> m_streams;
		TlsfMemoryAllocator m_chunkAllocator;
	};

	/* 2440 */
	struct PoolAllocator<AliasPathFileDevice::StreamEntry>
	{
		BasePoolAllocator m_pool;
	};

	//*** Needs Fix ***//
	/* 2441*/
	struct FileStreamAllocator<AliasPathFileDevice::StreamEntry>
	{
	  PoolAllocator<AliasPathFileDevice::StreamEntry> m_streamAllocator;
	  Mutex m_streamMutex;
	};

	//*** Needs Fix ***//
	/* 2442*/
	struct  AliasPathFileDevice : FileDeviceInterface
	{
	  FileStreamAllocator<AliasPathFileDevice::StreamEntry> m_streams;
	};

	/* 2444 */
	struct TreeNode<FileSystemMountPoint>
	{
	  FileSystemMountPoint* pNextSibling;
	  FileSystemMountPoint* pPrevSibling;
	  FileSystemMountPoint* pParent;
	  FileSystemMountPoint* pFirstChild;
	};

	/* 2443 */
	struct  FileSystemMountPoint : TreeNode<FileSystemMountPoint>
	{
	  char path[128];
	  FileSystemDeviceEntry* pFirstDevice;
	};

	/* 2446 */
	struct ListEntry<FileSystemDeviceEntry>
	{
	  FileSystemDeviceEntry* pNext;
	  FileSystemDeviceEntry* pPrev;
	};

	/* 2445 */
	struct  __declspec(align(4)) FileSystemDeviceEntry : ListEntry<FileSystemDeviceEntry>
	{
	  FileDeviceMountData* pMountData;
	  FileDeviceInterface* pDevice;
	  bool isInternalDevice;
	};

	/* 2447 */
	struct __declspec(align(4)) FileSystem
	{
	  PoolAllocator<FileSystemDeviceEntry> devices;
	  PoolAllocator<FileSystemMountPoint> mountPoints;
	  NativeFileDevice nativeFileDevice;
	  MemoryFileDevice memoryFileDevice;
	  PakFileDevice pakFileDevice;
	  AliasPathFileDevice aliasPathFileDevice;
	  FileSystemMountPoint* pRootPoint;
	  unsigned int nativeMountHandle;
	  Mutex mutex;
	  unsigned int openFileStack;
	  MemoryAllocator* pAllocator;
	  volatile unsigned int useIo;
	  bool ignoreFirstChild;
	};

	//*** Needs Fix ***//
	/* 2448 */
	struct __declspec(align(2)) File
	{
	  FileSystem* m_pFileSystem;
	  unsigned int m_fileHandle;
	  unsigned __int64 m_fileSize;
	  unsigned __int64 m_filePosition;
	  File::State m_state;
	  bool m_needEndianSwapping;
	  bool m_ownsFileHandle;
	  bool m_fileSizeDirty;
	};

	/* 2449 */
	struct MemoryAllocatorInfo
	{
	  const void* pBaseAddress;
	  unsigned int totalSize;
	  unsigned int allocatedSize;
	  unsigned int maxAllocatedSize;
	  unsigned int allocationCount;
	};

	/* 2450 */
	struct  SequenceResource : Resource
	{
	  SequenceData* m_pData;
	};

	/* 2451 */
	struct Slice<ResourceFactory*>
	{
	  ResourceFactory** m_pStart;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	//*** Needs Fix ***//
	/* 2452 */
	struct InternalListBase::Listable
	{
	  InternalListBase::Listable* m_pNext;
	  InternalListBase::Listable* m_pPrev;
	};

	//*** Needs Fix ***//
	/* 2453 */
	struct InternalListBase::IteratorBase
	{
	  InternalListBase::Listable* m_pCurrent;
	};

	//*** Needs Fix ***//
	/* 2454 */
	struct InternalListBase
	{
	  InternalListBase::Listable* m_pFirst;
	  InternalListBase::Listable* m_pLast;
	  unsigned int m_numObjects;
	  InternalListBase::IteratorBase m_begin;
	  InternalListBase::IteratorBase m_end;
	  InternalListBase::IteratorBase m_local;
	};

	/* 2455 */
	struct SequenceEvent
	{
	  unsigned short time;
	  unsigned short type;
	  const void* pData;
	};

	/* 2456 */
	struct $_TypeDescriptor$_extraBytes_20
	{
	  const void* pVFTable;
	  void* spare;
	  char name[20];
	};

	/* 2458 */
	struct VertexAttributeSemanticInfo
	{
	  const char* pName;
	};

	/* 2459 */
	struct VertexAttributeFormatInfo
	{
	  const char* pName;
	  unsigned int sizeInBytes;
	  unsigned int componentCount;
	};

	/* 2460 */
	struct __declspec(align(4)) PixelFormatInfo
	{
	  const char* pName;
	  unsigned int bitsPerPixel;
	  unsigned int bitsPer4x4Block;
	  bool isInGammaSpace;
	};

	/* 2461 */
	struct __unaligned __declspec(align(1)) $_TypeDescriptor$_extraBytes_27
	{
	  const void* pVFTable;
	  void* spare;
	  char name[27];
	};

	/* 2462 */
	struct  Vector3 : float3
	{
	};

	/* 2463 */
	struct  Vector2 : float2
	{
	};

	/* 2464 */
	struct Matrix33
	{
	  Vector3 x;
	  Vector3 y;
	  Vector3 z;
	};

	/* 2465 */
	struct Matrix43
	{
	  Matrix33 rot;
	  Vector3 pos;
	};

	/* 2466 */
	struct TGAWriter::BGRAPixel
	{
	  char b;
	  char g;
	  char r;
	  char a;
	};

	/* 2467 */
	struct TGAWriter::BGRPixel
	{
	  char b;
	  char g;
	  char r;
	};

	/* 2468 */
	struct WriteStream
	{
	  char* m_pStart;
	  unsigned int m_capacity;
	  unsigned int m_size;
	  IoError m_error;
	  void (__cdecl* m_pFlushFunction)(WriteStream*);
	  const char* m_pName;
	};

	/* 2469 */
	struct __declspec(align(4)) BinaryWriter
	{
	  WriteStream* m_pBuffer;
	  bool m_needEndianSwapping;
	};

	/* 2470 */
	struct TGAWriter
	{
	  BinaryWriter m_writer;
	  unsigned int m_width;
	  unsigned int m_height;
	  TGAWriter::Format m_format;
	  unsigned int m_lineCount;
	};

	/* 2471 */
	struct PerspectiveProjection
	{
	  float aspectRatio;
	  float nearClip;
	  float farClip;
	  float fovY;
	};

	/* 2472 */
	struct OrthographicProjection
	{
	  float x0;
	  float x1;
	  float y0;
	  float y1;
	  float z0;
	  float z1;
	};

	/* 2473 */
	union $BF4FE4277C2DBB62089E59F5A39002B2
	{
	  PerspectiveProjection perspective;
	  OrthographicProjection orthographic;
	};

	/* 2474 */
	struct __declspec(align(4)) Projection
	{
	  $BF4FE4277C2DBB62089E59F5A39002B2 data;
	  ProjectionType type;
	  bool rightHanded;
	};

	/* 2475 */
	union $A02EE800BA1647DBCF69C3CB15F683F7
	{
	  float floatValue;
	  unsigned int integerValue;
	  const char *pStringValue;
	};

	/* 2476 */
	struct StringParameter
	{
	  StringParameterType type;
	  $A02EE800BA1647DBCF69C3CB15F683F7 ___u1;
	};

	/* 2477 */
	struct Viewport
	{
	  unsigned int x;
	  unsigned int y;
	  unsigned int width;
	  unsigned int height;
	  float minDepth;
	  float maxDepth;
	};

	/* 2478 */
	struct half4
	{
	  unsigned short x;
	  unsigned short y;
	  unsigned short z;
	  unsigned short w;
	};

	/* 2479 */
	struct half2
	{
	  unsigned short x;
	  unsigned short y;
	};

	/* 2480 */
	struct  Vector4 : float4
	{

	};

	/* 2481 */
	struct Plane
	{
	  Vector4 data;
	};

	/* 2482 */
	struct GraphicsMatrix43
	{
	  float row0[4];
	  float row1[4];
	  float row2[4];
	};

	/* 2483 */
	struct Frustum
	{
	  Plane m_planes[6];
	};

	/* 2484 */
	struct AxisAlignedBox
	{
	  Vector3 m_min;
	  Vector3 m_max;
	};

	/* 2485 */
	struct VertexAttributeDescription
	{
	  char id;
	  char format;
	  char inputStreamIndex;
	  char instanceStepRate;
	};

	/* 2486 */
	struct  ColorVariable : IniVariableBase
	{
	  Vector4 m_value;
	  Vector4 m_defaultValue;
	};

	/* 2487 */
	struct  Quaternion : float4
	{

	};

	/* 2488 */
	struct ModelPose
	{
	  __m128* pData;
	  unsigned int alignedJointCount;
	};

	/* 2489 */
	struct Matrix44
	{
	  Vector4 x;
	  Vector4 y;
	  Vector4 z;
	  Vector4 w;
	};

	/* 2490 */
	struct __declspec(align(4)) Camera
	{
	  Matrix43 m_worldMatrix;
	  Projection m_projection;
	  Matrix43 m_viewMatrix;
	  Frustum m_frustum;
	  bool m_viewDirty;
	  bool m_frustumDirty;
	};

	/* 2491 */
	struct GraphicsMatrix44
	{
	  float row0[4];
	  float row1[4];
	  float row2[4];
	  float row3[4];
	};

	/* 2492 */
	struct StringParameterBuilder
	{
	  StringParameter m_parameters[16];
	  unsigned int m_parameterCount;
	};

	/* 2493 */
	struct BlobResourceFactory : ResourceFactory
	{
	};

	/* 2494 */
	struct __declspec(align(8)) ResourceConfigurationCompatibility
	{
	  unsigned long long supportedApiMask;
	  unsigned short supportedSkuMask;
	  unsigned short supportedHardwareConfiguration;
	};

	/* 2495 */
	struct __declspec(align(4)) ExternalReference
	{
	  Resource* pResource;
	  unsigned int type;
	  unsigned int key;
	  const char* pOptionalResourceName;
	  bool isResolved;
	  bool isOwner;
	};

	/* 2496 */
	struct ExternalReferences
	{
	  ExternalReference* pReferences;
	  unsigned int referenceCount;
	};

	/* 2497 */
	struct AutoArray<MemoryAllocator*>
	{
	  MemoryAllocator* m_pAllocator;
	  MemoryAllocator** m_pData;
	  unsigned int m_size;
	};

	/* 2498 */
	struct ResourceAllocationContext
	{
	  AutoArray<MemoryAllocator*> allocators;
	};

	/* 2499 */
	struct FactoryEntry
	{
	  ResourceFactory* pFactory;
	  unsigned int resourceType;
	};

	/* 2500 */
	struct  InternalList<ResourceRequest> : InternalListBase
	{

	};

	/* 2501 */
	struct  InternalList<ResourceRequest>::Iterator : InternalListBase::IteratorBase
	{

	};

	//*** Needs Fix ***//
	/* 2502 */
	struct  __declspec(align(2)) ResourceRequest : InternalListBase::Listable
	{
	  ResourceRequest::State m_state;
	  unsigned int m_resourceContextIndex;
	  char m_resourceName[128];
	  unsigned int m_resourceType;
	  Resource* m_pResource;
	  char m_resourceTag;
	  bool m_abortLoading;
	  char m_loadFlags;
	};

	/* 2503 */
	struct  DebugCommandHandler
	{

	};

	/* 2504 */
	struct TextWriter
	{
	  WriteStream* m_pStream;
	};

	/* 2505 */
	struct ResourceEntry
	{
	  Resource* pResource;
	  unsigned int resourceType;
	};

	/* 2506 */
	struct ResourceObjectFileHeader
	{
	  unsigned int headerKey;
	  char formatRevision;
	  char chunkCount;
	  char totalSectionCount;
	  char pad;
	};

	/* 2507 */
	struct WeakResourceReferenceHolder
	{
	  unsigned int referenceIndex;
	};

	/* 2508 */
	struct  __declspec(align(4)) FileWriteStream : WriteStream
	{
	  char m_buffer[2048];
	  FileSystem* m_pFileSystem;
	  unsigned int m_fileHandle;
	  bool m_isInternalHandle;
	};

	/* 2509 */
	struct AllocationEntry
	{
	  void* pMemory;
	  __int16 allocatorIndex;
	  char allocationUsage;
	  char _pad0;
	};

	/* 2510 */
	struct StaticArray<AllocationEntry>
	{
	  AllocationEntry* m_pData;
	  unsigned int m_size;
	};

	/* 2511 */
	struct KrofFileEntry
	{
	  ExternalReferences externalReferences;
	  StaticArray<AllocationEntry> allocationEntries;
	  ResourceEntry* pResources;
	  unsigned int resourceEntryCount;
	  unsigned int resourceContextIndex;
	};

	/* 2512 */
	struct SizedArray<KrofFileEntry>
	{
	  KrofFileEntry* m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2513 */
	struct SizedArray<FactoryEntry>
	{
	  FactoryEntry* m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2514 */
	const struct __declspec(align(4)) ResourceContextDescriptor
	{
	  ResourceAllocationContext* pAllocationContext;
	  char parentIndex;
	  char resourceTag;
	};

	/* 2515 */
	struct ReadStream
	{
	  const char* m_pStart;
	  unsigned int m_size;
	  unsigned int m_position;
	  IoError m_error;
	  void (__cdecl* m_pRefillFunction)(ReadStream*);
	  const char* m_pName;
	};

	/* 2516 */
	struct  InitializationDataReadStream : ReadStream
	{
	  char* m_pBuffer;
	  unsigned int m_bufferSize;
	  FileSystem* m_pFileSystem;
	  unsigned int m_fileHandle;
	  unsigned long long m_fileStartOffset;
	  unsigned int m_bytesRead;
	  unsigned int m_dataSize;
	};

	/* 2517 */
	struct __declspec(align(8)) KrofManager
	{
	  SizedArray<KrofFileEntry> m_krofFiles;
	  MemoryAllocator* m_pAllocator;
	  MemoryAllocator* m_pScratchAllocator;
	  SizedArray<FactoryEntry> m_factories;
	  ResourceFactory* m_pFallbackFactory;
	  FileSystem* m_pFileSystem;
	  char m_basePath[260];
	  volatile bool* m_pAbortLoading;
	  ResourceContextDescriptor* m_pResourceContexts;
	  unsigned int m_numResourceContexts;
	  ResourceConfigurationCompatibility m_supportedResourceConfiguration;
	  char m_readStreamBuffer[2048];
	  InitializationDataReadStream m_readStreams[1];
	  unsigned int m_readStreamCount;
	};

	/* 2518 */
	struct SynchronousResourceReader
	{
	  KrofManager* m_pKrofManager;
	};

	/* 2519 */
	struct LoadFailReport
	{
	  LoadFailReason reason;
	  char string[64];
	};

	/* 2520 */
	union $C958D7F9BB233D815E081A6A01C84606
	{
	  unsigned short fileNameStringOffset;
	  unsigned short resourceId;
	};

	/* 2521 */
	struct ResourceReference
	{
	  char sectionIndex;
	  char referenceType;
	  $C958D7F9BB233D815E081A6A01C84606 ___u2;
	  unsigned int resourceType;
	  unsigned int offsetToResourcePointer;
	};

	/* 2522 */
	struct ResourceHeader
	{
	  unsigned int resourceKey;
	  unsigned int offsetInResourceDataSection;
	  unsigned int resourceType;
	  unsigned int contentFormatKey;
	  unsigned short resourceIntializationDataSize;
	  unsigned short resourceId;
	};

	/* 2523 */
	struct  BlobResource : Resource
	{
	  const char* m_pData;
	  unsigned int m_size;
	};

	/* 2524 */
	struct ResourceSectionHeader
	{
	  unsigned short resourcesCount;
	  unsigned short relocationEntryCount;
	};

	/* 2525 */
	struct Array<ResourceContextDescriptor>
	{
	  ResourceContextDescriptor* m_pData;
	  unsigned int m_size;
	};

	/* 2526 */
	struct MemoryBlockInfo
	{
	  MemoryBlock block;
	  unsigned int flags;
	};

	/* 2527 */
	struct Slice<MemoryBlockInfo>
	{
	  MemoryBlockInfo* m_pStart;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2528 */
	struct NetworkWriter
	{
	  WriteStream* m_pStream;
	};

	/* 2529 */
	struct SizedArray<AllocationEntry>
	{
	  AllocationEntry* m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	//*** Needs Fix ***//
	/* 2530 */
	struct FilePath
	{
	  char m_completePath[260];
	  FilePath::CompletePathState m_completePathState;
	  char m_prefix[64];
	  char m_directory[256];
	  char m_fileName[256];
	  char m_extension[256];
	};

	/* 2531 */
	struct __declspec(align(4)) StringBuilder
	{
	  char* m_pOriginalDestination;
	  unsigned int m_originalCapacity;
	  char* m_pCurrentDestination;
	  unsigned int m_remainingCapacity;
	  bool m_overflow;
	};

	/* 2532 */
	struct ResourceReferenceSectionHeader
	{
	  unsigned int referencesCount;
	};

	/* 2533 */
	struct RelocationEntry
	{
	  char sectionIndex;
	  char referredSectionIndex;
	  unsigned __int16 pad;
	  unsigned int positionOffset;
	  unsigned int referredOffset;
	};

	/* 2534 */
	struct SectionHeader
	{
	  char sectionType;
	  char pad;
	  char alignment;
	  char allocatorType;
	  unsigned int fileOffset;
	  unsigned int sectionDataSize;
	  unsigned int fileDataSize;
	};

	/* 2535 */
	struct  FallbackResourceFactory : ResourceFactory
	{

	};

	/* 2536 */
	struct  __declspec(align(2)) ResourceManager : DebugCommandHandler
	{
	  KrofManager* m_pKrofManager;
	  ResourceAllocationContext* m_pDefaultResourceAllocationContext;
	  Array<ResourceContextDescriptor> m_resourceContexts;
	  AutoMemoryBlock m_krofMemory;
	  AutoMemoryBlock m_krofScratchMemory;
	  TlsfMemoryAllocator m_krofAllocator;
	  TlsfMemoryAllocator m_krofScratchAllocator;
	  Thread m_loadingThread;
	  Event m_requestEvent;
	  Mutex m_requestMutex;
	  Mutex m_krofMutex;
	  FallbackResourceFactory m_fallbackFactory;
	  InternalList<ResourceRequest> m_resourceRequests;
	  const char* m_pCurrentRequestName;
	  unsigned int m_checkReleasedResourceCounter;
	  bool m_runAsynchronous;
	  volatile bool m_isUpdating;
	  bool m_resolveReferences;
	};

	/* 2537 */
	struct ResourceManagerInitParams
	{
	  ResourceConfigurationCompatibility supportedResourceConfigurations;
	  unsigned int krofAllocatorSize;
	  unsigned int krofScratchAllocatorSize;
	  unsigned int numberOfResourceTypes;
	  unsigned int numberOfFiles;
	  unsigned int numberOfAdditionalAllocations;
	  unsigned int resourceContextCount;
	  FileSystem* pFileSystem;
	  const char* pBasePath;
	  bool runAsynchronous;
	  bool resolveReferences;
	  bool useDebugCommands;
	  bool useFallbackFactory;
	  ResourceAllocationContext *pDefaultAllocationContext;
	};

	/* 2538 */
	struct  FallbackResource : Resource
	{
	  const void* m_pData;
	  unsigned int m_format;
	};

	/* 2539 */
	struct KrofManager::ChunkInfo
	{
	  unsigned int startSectionIndex;
	  unsigned int endSectionIndex;
	};

	/* 2540 */
	struct  SectionHeaderRuntimeData : SectionHeader
	{
	  unsigned int sectionOffset;
	  unsigned int chunkIndex;
	};

	/* 2541 */
	struct KrofManager::KrofLoadContext
	{
	  ResourceContextDescriptor* pResourceContext;
	  unsigned int resourceContextIndex;
	  char fileName[256];
	  ResourceObjectFileHeader fileHeader;
	  KrofManager::ChunkInfo chunks[20];
	  SectionHeaderRuntimeData sections[64];
	  void *pSectionData[64];
	  unsigned int sectionCount;
	  unsigned int currentSectionIndex;
	  ResourceReferenceSectionHeader *resReferencesSections[20];
	  unsigned int resReferencesSectionChunkIndex[20];
	  ResourceReferenceSectionHeader *weakResReferencesSections[20];
	  unsigned int weakResReferenceSectionIndicies[20];
	  unsigned int resReferenceSectionCount;
	  unsigned int weakResReferenceSectionCount;
	  ExternalReferences externalReferences;
	  KrofFileEntry* pKrofFileEntry;
	  Resource* pResourceToUse;
	  LoadFailReport* pLoadFailReport;
	  unsigned __int64 startPosition;
	  bool convertDataEndianness[64];
	};

	/* 2542 */
	struct  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk> : InternalListBase
	{

	};

	/* 2543 */
	struct  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk>::Iterator : InternalListBase::IteratorBase
	{

	};

	/* 2544 */
	struct  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk>::ConstIterator : InternalListBase::IteratorBase
	{

	};

	/* 2545 */
	struct  ChunkedSizedArray<AllocationEntry>::Chunk : InternalListBase::Listable
	{
	  SizedArray<AllocationEntry> entries;
	};

	//*** Needs Fix ***//
	/* 2546 */
	struct ChunkedSizedArray<AllocationEntry>::ConstIterator
	{
	  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk>::ConstIterator m_chunk;
	  unsigned int m_index;
	};

	//*** Needs Fix ***//
	/* 2547 */
	struct ChunkedSizedArray<AllocationEntry>::Iterator
	{
	  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk>::Iterator m_chunk;
	  unsigned int m_index;
	};

	/* 2548 */
	struct ChunkedSizedArray<AllocationEntry>
	{
	  MemoryAllocator* m_pAllocator;
	  InternalList<ChunkedSizedArray<AllocationEntry>::Chunk> m_chunks;
	  unsigned int m_chunkSize;
	  unsigned int m_alignment;
	  ChunkedSizedArray<AllocationEntry>::Iterator m_start;
	  ChunkedSizedArray<AllocationEntry>::Iterator m_end;
	};

	/* 2549 */
	struct ChunkHeader
	{
	  unsigned short configuration;
	  char sectionCount;
	  char pad;
	};

	/* 2550 */
	struct NetworkReader
	{
	  ReadStream* m_pStream;
	};

	/* 2551 */
	struct StreamInitializationData
	{
	  ReadStream* pStream;
	  unsigned int totalSize;
	};

	//*** Needs Fix ***//
	/* 2552 */
	struct BlobResourceFactory::initializeResource::__l2::BlobInitializationData
	{
	  const char* pData;
	  unsigned int size;
	};

	/* 2553 */
	struct ProtocolMessageEnumMemberDescription
	{
	  const char* pName;
	  long long value;
	};

	/* 2554 */
	struct ProtocolMessageTypeDescription
	{
	  const char* pName;
	  unsigned int cppTypeSize;
	};

	/* 2555 */
	struct BitReadBuffer
	{
	  const char* pData;
	  unsigned int bitCount;
	  unsigned int bitPosition;
	};

	/* 2556 */
	const struct ProtocolMessageFieldDescription
	{
	  const char* pName;
	  ProtocolMessageFieldType wireType;
	  ProtocolMessageFieldCppType cppType;
	  unsigned int dataOffsetInBytes;
	  unsigned int sizeOffsetInBytes;
	  unsigned int minRepeatCount;
	  unsigned int maxRepeatCount;
	  unsigned int quantizationBitCount;
	  ProtocolMessageTypeDescription* pTypeDescription;
	};

	/* 2557 */
	struct  ProtocolMessageDescription : ProtocolMessageTypeDescription
	{
	  ProtocolMessageFieldDescription* pFieldDescriptions;
	  unsigned int fieldDescriptionCount;
	};

	/* 2558 */
	struct __declspec(align(4)) BitReader
	{
	  BitReadBuffer* m_pBitReadBuffer;
	  BitReadBuffer m_localBuffer;
	  unsigned int m_initialBitPosition;
	  bool m_hasCapacityExeeded;
	};

	/* 2559 */
	struct BitWriteBuffer
	{
	  char* pData;
	  unsigned int bitCount;
	  unsigned int bitPosition;
	};

	/* 2560 */
	struct __declspec(align(4)) BitWriter
	{
	  BitWriteBuffer* m_pBitWriteBuffer;
	  BitWriteBuffer m_localBuffer;
	  unsigned int m_initialBitPosition;
	  bool m_hasCapacityExeeded;
	};

	/* 2561 */
	struct  ProtocolMessageEnumDescription : ProtocolMessageTypeDescription
	{
	  ProtocolMessageEnumMemberDescription* pMember;
	  unsigned int memberCount;
	  unsigned int minBitCount;
	};

	/* 2562 */
	struct ProtocolDescription
	{
	  ProtocolMessageDescription* pProtocolMessageDescriptions;
	  unsigned int messageDescriptionCount;
	  ProtocolMessageEnumDescription* pEnumDescriptions;
	  unsigned int enumDescriptionCount;
	};

	/* 2568 */
	struct RandomNumberGenerator
	{
	  int m_index;
	  unsigned int m_mt[624];
	};

	/* 2663 */
	struct CCallback<ISteamLobbyDataListener, LobbyDataUpdate_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyDataListener* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyDataListener* this, LobbyDataUpdate_t*);
	};

	/* 2660 */
	struct ISteamLobbyDataListener
	{
	  ISteamLobbyDataListenerVtbl* vfptr;
	  CCallback<ISteamLobbyDataListener, LobbyDataUpdate_t, 0> m_onLobbyDataUpdate;
	};

	/* 2662 */
	struct ISteamLobbyDataListenerVtbl
	{
	  void* (__thiscall* __vecDelDtor)(ISteamLobbyDataListener* this, unsigned int);
	  void (__thiscall* onLobbyDataUpdate)(ISteamLobbyDataListener* this, LobbyDataUpdate_t*);
	};

	/* 2669 */
	struct CCallback<ISteamStatsCallback, UserStatsReceived_t, 0> : CCallbackImpl<24>
	{
	  ISteamStatsCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamStatsCallback* this, UserStatsReceived_t*);
	};

	/* 2671 */
	struct CCallback<ISteamStatsCallback, UserStatsStored_t, 0> : CCallbackImpl<16>
	{
	  ISteamStatsCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamStatsCallback* this, UserStatsStored_t*);
	};

	/* 2665 */
	struct ISteamStatsCallback
	{
	  ISteamStatsCallbackVtbl* vfptr;
	  CCallback<ISteamStatsCallback, UserStatsReceived_t, 0> m_onUserStatsReceived;
	  CCallback<ISteamStatsCallback, UserStatsStored_t, 0> m_onUserStatsStored;
	};

	/* 2668 */
	struct ISteamStatsCallbackVtbl
	{
	  void* (__thiscall* __vecDelDtor)(ISteamStatsCallback* this, unsigned int);
	  void (__thiscall* onUserStatsReceived)(ISteamStatsCallback* this, UserStatsReceived_t*);
	  void (__thiscall* onUserStatsStored)(ISteamStatsCallback* this, UserStatsStored_t*);
	};

	/* 2736 */
	struct CCallback<ISteamLobbyCallback, LobbyInvite_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyInvite_t* );
	};

	/* 2737 */
	struct CCallback<ISteamLobbyCallback, LobbyEnter_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback*  this, LobbyEnter_t*);
	};

	/* 2738 */
	struct CCallback<ISteamLobbyCallback, LobbyDataUpdate_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyDataUpdate_t*);
	};

	/* 2740 */
	struct CCallback<ISteamLobbyCallback, LobbyChatUpdate_t, 0> : CCallbackImpl<32>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyChatUpdate_t*);
	};

	/* 2741 */
	struct CCallback<ISteamLobbyCallback, LobbyChatMsg_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyChatMsg_t*);
	};

	/* 2742 */
	struct CCallback<ISteamLobbyCallback, LobbyGameCreated_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyGameCreated_t*);
	};

	/* 2743 */
	struct CCallback<ISteamLobbyCallback, LobbyKicked_t, 0> : CCallbackImpl<24>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyKicked_t*);
	};

	/* 2744 */
	struct CCallback<ISteamLobbyCallback, LobbyCreated_t, 0> : CCallbackImpl<16>
	{
	  ISteamLobbyCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamLobbyCallback* this, LobbyCreated_t*);
	};

	/* 2728 */
	struct ISteamLobbyCallback
	{
	  ISteamLobbyCallbackVtbl* vfptr;
	  CCallback<ISteamLobbyCallback, LobbyInvite_t, 0> m_onLobbyInvite;
	  CCallback<ISteamLobbyCallback, LobbyEnter_t, 0> m_onLobbyEnter;
	  CCallback<ISteamLobbyCallback, LobbyDataUpdate_t, 0> m_onLobbyDataUpdate;
	  CCallback<ISteamLobbyCallback, LobbyChatUpdate_t, 0> m_onLobbyChatUpdate;
	  CCallback<ISteamLobbyCallback, LobbyChatMsg_t, 0> m_onLobbyChatMsg;
	  CCallback<ISteamLobbyCallback, LobbyGameCreated_t, 0> m_onLobbyGameCreated;
	  CCallback<ISteamLobbyCallback, LobbyKicked_t, 0> m_onLobbyKicked;
	  CCallback<ISteamLobbyCallback, LobbyCreated_t, 0> m_onLobbyCreated;
	};

	/* 2735 */
	struct ISteamLobbyCallbackVtbl
	{
	  void* (__thiscall* __vecDelDtor)(ISteamLobbyCallback* this, unsigned int);
	  _BYTE gap4[4];
	  void (__thiscall* onLobbyEnter)(ISteamLobbyCallback* this, LobbyEnter_t*);
	  void (__thiscall* onLobbyDataUpdate)(ISteamLobbyCallback* this, LobbyDataUpdate_t*);
	  void (__thiscall* onLobbyChatUpdate)(ISteamLobbyCallback* this, LobbyChatUpdate_t*);
	  void (__thiscall* onLobbyChatMsg)(ISteamLobbyCallback* this, LobbyChatMsg_t*);
	  void (__thiscall* onLobbyGameCreated)(ISteamLobbyCallback* this, LobbyGameCreated_t*);
	  void (__thiscall* onLobbyKicked)(ISteamLobbyCallback* this, LobbyKicked_t*);
	  void (__thiscall* onLobbyCreated)(ISteamLobbyCallback* this, LobbyCreated_t*);
	};

	/* 2811 */
	struct CCallback<ISteamNetworkingCallback, P2PSessionRequest_t, 0> : CCallbackImpl<8>
	{
	  ISteamNetworkingCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamNetworkingCallback* this, P2PSessionRequest_t*);
	};

	/* 2812 */
	struct CCallback<ISteamNetworkingCallback, P2PSessionConnectFail_t, 0> : CCallbackImpl<9>
	{
	  ISteamNetworkingCallback* m_pObj;
	  void (__thiscall* m_Func)(ISteamNetworkingCallback* this, P2PSessionConnectFail_t*);
	};

	/* 2807 */
	struct ISteamNetworkingCallback
	{
	  ISteamNetworkingCallbackVtbl* vfptr;
	  CCallback<ISteamNetworkingCallback, P2PSessionRequest_t, 0> m_onP2PSessionRequest;
	  CCallback<ISteamNetworkingCallback, P2PSessionConnectFail_t, 0> m_onP2PSessionConnectFail;
	};

	/* 2808 */
	struct P2PSessionRequest_t
	{
	  CSteamID m_steamIDRemote;
	};

	/* 2809 */
	struct __unaligned __declspec(align(1)) P2PSessionConnectFail_t
	{
	  CSteamID m_steamIDRemote;
	  char m_eP2PSessionError;
	};

	/* 2810 */
	struct ISteamNetworkingCallbackVtbl
	{
	  void* (__thiscall* __vecDelDtor)(ISteamNetworkingCallback* this, unsigned int);
	  void (__thiscall* onP2PSessionRequest)(ISteamNetworkingCallback* this, P2PSessionRequest_t*);
	  void (__thiscall* onP2PSessionConnectFail)(ISteamNetworkingCallback* this, P2PSessionConnectFail_t*);
	};

	/* 2884 */
	struct UserAccountId
	{
	  char providerData[8];
	  bool isValid;
	};

	//*** Needs Fix ***//
	/* 2900 */
	struct SoundSystem::SoundProvider
	{
	  SoundSystem::SoundProviderVtbl *vfptr;
	};

	/* 2901 */
	const struct  SoundDefinitionResourceHandleType
	{
	};

	/* 2902 */
	const struct SoundFileData
	{
	  char providerId;
	  char xmaBuffer[52];
	  const void *pData;
	  unsigned int dataLength;
	  unsigned int durationInms;
	};

	//*** Needs Fix ***//
	/* 2903 */
	struct SoundSystem::ParameterAutomation
	{
	  SoundSystem::ParameterAutomation *pNext;
	  SoundSystem::ParameterAutomation::Command command;
	  bool init;
	  float targetValue;
	  float velocity;
	};

	//*** Needs Fix ***//
	/* 2904 */
	struct SoundSystem::BaseSound
	{
	  float3 position;
	  unsigned __int16 runCountAndFlags;
	  char pauseGroup;
	  char voiceIndex;
	  float volume;
	  float pitch;
	  SoundDefinitionResourceHandleType *definition;
	  SoundFileData *pSoundFileData;
	  unsigned int startTimeInms;
	  SoundSystem::ParameterAutomation *pAutomation;
	  float initialVolume;
	  float initialPitch;
	};

	//*** Needs Fix ***//
	/* 2905 */
	struct SoundSystem::VoiceSound
	{
	  char m_providerType;
	  char m_runFlags;
	  void *m_pProviderData;
	  SoundSystem::BaseSound *m_pBaseSound;
	};

	/* 2908 */
	struct Array<SoundSystem::BaseSound>
	{
	  SoundSystem::BaseSound *m_pData;
	  unsigned int m_size;
	};

	/* 2909 */
	struct Array<SoundSystem::VoiceSound>
	{
	  SoundSystem::VoiceSound *m_pData;
	  unsigned int m_size;
	};

	/* 2910 */
	struct Array<SoundSystem::ParameterAutomation>
	{
	  SoundSystem::ParameterAutomation *m_pData;
	  unsigned int m_size;
	};

	//*** Needs Fix ***//
	/* 2911 */
	struct SoundSystem::VolumeDefinition
	{
	  float currentValue;
	  float targetValue;
	  float speed;
	};

	//*** Needs Fix ***//
	/* 2912 */
	struct SoundSystem::BusDefinition
	{
	  int targetBusses[4];
	};

	//*** Needs Fix ***//
	/* 2913 */
	struct SoundSystem::BusImplementation
	{
	  SoundSystem::VolumeDefinition gain;
	  SoundSystem::VolumeDefinition drySendVolumes[4];
	  SoundSystem::VolumeDefinition wetSendVolumes[4];
	  SoundSystem::BusDefinition definition;
	  SoundSystem::VolumeDefinition duckingGain;
	  unsigned int effectIndices[4];
	};

	//*** Needs Fix ***//
	/* 2914 */
	struct SoundSystem::EffectStorage
	{
	  float gain;
	  unsigned int effectId;
	  char opaqueParameterData[128];
	  void *pPlatformData;
	};

	/* 2921 */
	struct Array<SoundSystem::TemporarySoundDefinition>
	{
	  SoundSystem::TemporarySoundDefinition *m_pData;
	  unsigned int m_size;
	};

	/* 2923 */
	struct Array<SoundSystem::SoundTriggerMemory>
	{
	  SoundSystem::SoundTriggerMemory *m_pData;
	  unsigned int m_size;
	};

	//*** Needs Fix ***//
	/* 2924 */
	struct __declspec(align(4)) SoundSystem::Systembase
	{
	  SoundSystem::SoundProvider *soundProviders[8];
	  Matrix43 listenerMatrix;
	  Matrix43 inverseListenerMatrix;
	  int nextPauseGroup;
	  unsigned int allocatedPauseGroups[1];
	  RandomNumberGenerator randomNumberGenerator;
	  Array<SoundSystem::BaseSound> sounds;
	  Array<SoundSystem::VoiceSound> voiceSounds;
	  unsigned int currentTimeInms;
	  Array<SoundSystem::ParameterAutomation> automations;
	  unsigned int busCount;
	  SoundSystem::BusImplementation busses[30];
	  SoundSystem::EffectStorage effects[16];
	  Array<SoundSystem::TemporarySoundDefinition> tempSoundDefinitions;
	  Array<SoundSystem::SoundTriggerMemory> repetitionMemory;
	  bool soundOutputDisabled;
	};

	/* 2927 */
	struct Array<SoundSystem::SoundVoiceXAudio2>
	{
	  SoundSystem::SoundVoiceXAudio2 *m_pData;
	  unsigned int m_size;
	};

	//*** Needs Fix ***//
	/* 2928 */
	struct SoundSystem::SoundVoiceManagerXAudio2
	{
	  Array<SoundSystem::SoundVoiceXAudio2> m_voices;
	  IXAudio2 *m_pXAudioDevice;
	};

	//*** Needs Fix ***//
	/* 2929 */
	struct  SoundSystem::SoundProviderWaveXAudio2 : SoundSystem::SoundProvider
	{
	  SoundSystem::SoundVoiceManagerXAudio2 *m_pVoiceManager;
	  unsigned int m_providerId;
	};

	//*** Needs Fix ***//
	/* 2931 */
	struct  SoundSystem::SoundSystemEngineCallback : IXAudio2EngineCallback
	{
	  SoundSystem::SystemXaudio2 *m_pSystem;
	};

	//*** Needs Fix ***//
	/* 2930 */
	struct __declspec(align(4)) SoundSystem::SystemXaudio2
	{
	  IXAudio2 *pAudioDevice;
	  IXAudio2MasteringVoice *pMasteringVoice;
	  SoundSystem::SoundVoiceManagerXAudio2 voiceManager;
	  SoundSystem::SoundProviderWaveXAudio2 waveProvider;
	  SoundSystem::SoundSystemEngineCallback callbackWrapper;
	  unsigned int channelCount;
	  unsigned int masterVoiceSampleRate;
	  unsigned int reverbOutputChannels;
	  IXAudio2SubmixVoice *pBusVoices[30];
	  IXAudio2SubmixVoice *pBusFXVoices[30];
	  wchar_t currentDeviceID[256];
	  float timeUntilDeviceSelection;
	  unsigned int externalXaudio2Voices;
	  bool deviceUpdatePending;
	  bool isInDeviceChangeCallback;
	};

	//*** Needs Fix ***//
	/* 2932 */
	struct  SoundSystem::SoundProviderNull : SoundSystem::SoundProvider
	{
	};

	/* 2934 */
	struct SingleLinkedInternalList<SoundDeviceChangedCallback,SoundDeviceChangedCallback *,4>::Iterator
	{
	  SoundDeviceChangedCallback *m_pCurrent;
	};

	/* 2935 */
	struct SingleLinkedInternalList<SoundDeviceChangedCallback,SoundDeviceChangedCallback *,4>
	{
	  SoundDeviceChangedCallback *m_pFirst;
	  SingleLinkedInternalList<SoundDeviceChangedCallback,SoundDeviceChangedCallback *,4>::Iterator m_begin;
	  SingleLinkedInternalList<SoundDeviceChangedCallback,SoundDeviceChangedCallback *,4>::Iterator m_end;
	};

	//*** Needs Fix ***//
	/* 2906 */
	struct  SoundSystem::System : SoundSystem::Systembase
	{
	  SoundSystem::SystemXaudio2 xaudio2State;
	  SoundSystem::SoundProviderNull nullProvider;
	  SingleLinkedInternalList<SoundDeviceChangedCallback,SoundDeviceChangedCallback *,4> deviceChangedCallbacks;
	};

	//*** Needs Fix ***//
	/* 2907 */
	struct SoundSystem::SoundProviderVtbl
	{
	  void *(__thiscall *__vecDelDtor)(SoundSystem::SoundProvider *this, unsigned int);
	  bool (__thiscall *startSound)(SoundSystem::SoundProvider *this, SoundSystem::VoiceSound *, float, unsigned int, SoundSystem::System *);
	  void (__thiscall *stopSound)(SoundSystem::SoundProvider *this, SoundSystem::VoiceSound *, SoundSystem::System *);
	  void (__thiscall *pauseSound)(SoundSystem::SoundProvider *this, SoundSystem::VoiceSound *);
	  void (__thiscall *resumeSound)(SoundSystem::SoundProvider *this, SoundSystem::VoiceSound *);
	  int (__thiscall *getNumAllocatedElements)(SoundSystem::SoundProvider *this);
	};

	/* 2915 */
	const struct  SoundFileHandleType
	{
	};

	//*** Needs Fix ***//
	/* 2916 */
	struct SoundSystem::SoundFileEntry
	{
	  float chance;
	  SoundFileHandleType *soundFile;
	};

	/* 2917 */
	struct StaticArray<SoundSystem::SoundFileEntry>
	{
	  SoundSystem::SoundFileEntry *m_pData;
	  unsigned int m_size;
	};

	//*** Needs Fix ***//
	/* 2918 */
	const struct SoundSystem::SoundDefinition
	{
	  char output_bus;
	  char positioning;
	  char priority;
	  char flags;
	  float pitch;
	  float pitchVariant;
	  float volume;
	  float volumeVariant;
	  float centerFraction;
	  float minDistance;
	  float maxDistance;
	  float positionVariation;
	  float panAngle;
	  float panDistance;
	  float panAngleVariation;
	  char countGroup;
	  char maxCount;
	  char minimumDelay;
	  char avoidRepeatingLastX;
	  StaticArray<SoundSystem::SoundFileEntry> soundFiles;
	};

	/* 2919 */
	struct  SoundDefinitionResource : Resource
	{
	  SoundSystem::SoundDefinition *m_pData;
	};

	//*** Needs Fix ***//
	/* 2920 */
	struct  SoundSystem::TemporarySoundDefinition : SoundDefinitionResource
	{
	  bool m_inUse;
	  SoundSystem::SoundDefinition m_data;
	  SoundSystem::SoundFileEntry m_soundFiles[1];
	};

	//*** Needs Fix ***//
	/* 2922 */
	struct SoundSystem::SoundTriggerMemory
	{
	  SoundSystem::SoundDefinition *pSoundDefinition;
	  unsigned int lastTriggerTimeInms;
	  char lastTriggeredIndex[8];
	};

	//*** Needs Fix ***//
	/* 2925 */
	struct SoundSystem::Voice
	{
	  IXAudio2SourceVoice *pSourceVoice;
	  bool running;
	  bool paused;
	  unsigned int stopTimer;
	};

	//*** Needs Fix ***//
	/* 2926 */
	struct __declspec(align(4)) SoundSystem::SoundVoiceXAudio2
	{
	  SoundSystem::Voice m_voice;
	  unsigned int m_currentPositionInMs;
	  SoundFileData *m_pSoundFile;
	  unsigned int m_flags;
	  bool m_looped;
	  char m_busIndex;
	};

	/* 2933 */
	struct SoundDeviceChangedCallback
	{
	  SoundDeviceChangedCallbackVtbl *vfptr;
	  SoundDeviceChangedCallback *m_pNext;
	};

	/* 2936 */
	struct SoundDeviceChangedCallbackVtbl
	{
	  void (__thiscall *handleAboutToDestroyMasteringVoice)(SoundDeviceChangedCallback *this, SoundSystem::System *);
	  void (__thiscall *handleMasteringVoiceCreated)(SoundDeviceChangedCallback *this, SoundSystem::System *);
	};

	/* 2950 */
	struct keen::SizedArray<kaiko::GameLinkRemoteStationSteam>
	{
	  kaiko::GameLinkRemoteStationSteam *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2951 */
	struct keen::Array<unsigned int>
	{
	  unsigned int *m_pData;
	  unsigned int m_size;
	};

	/* 2953 */
	struct keen::SizedArray<kaiko::GameLinkSearchResult>
	{
	  kaiko::GameLinkSearchResult *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2962 */
	struct keen::SizedArray<kaiko::GameLinkSteamVoiceChatData>
	{
	  kaiko::GameLinkSteamVoiceChatData *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 2969 */
	struct keen::ISteamLeaderboardsCallback
	{
	  keen::ISteamLeaderboardsCallbackVtbl *vfptr;
	  CCallback<keen::ISteamLeaderboardsCallback,LeaderboardFindResult_t,0> m_onLeaderboardFindResult;
	  CCallback<keen::ISteamLeaderboardsCallback,LeaderboardScoresDownloaded_t,0> m_onLeaderboardScoresDownloaded;
	  CCallback<keen::ISteamLeaderboardsCallback,LeaderboardScoreUploaded_t,0> m_onLeaderboardScoreUploaded;
	};

	// /* 2974 */
	// struct __cppobj CCallback<keen::ISteamLeaderboardsCallback,LeaderboardFindResult_t,0> : CCallbackImpl<16>
	// {
	//   keen::ISteamLeaderboardsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamLeaderboardsCallback *this, LeaderboardFindResult_t *);
	// };

	// /* 2975 */
	// struct __cppobj CCallback<keen::ISteamLeaderboardsCallback,LeaderboardScoresDownloaded_t,0> : CCallbackImpl<24>
	// {
	//   keen::ISteamLeaderboardsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamLeaderboardsCallback *this, LeaderboardScoresDownloaded_t *);
	// };

	// /* 2976 */
	// struct __cppobj CCallback<keen::ISteamLeaderboardsCallback,LeaderboardScoreUploaded_t,0> : CCallbackImpl<32>
	// {
	//   keen::ISteamLeaderboardsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamLeaderboardsCallback *this, LeaderboardScoreUploaded_t *);
	// };

	/* 2973 */
	struct keen::ISteamLeaderboardsCallbackVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::ISteamLeaderboardsCallback *this, unsigned int);
	  void (__thiscall *onLeaderboardFindResult)(keen::ISteamLeaderboardsCallback *this, LeaderboardFindResult_t *);
	  void (__thiscall *onLeaderboardScoresDownloaded)(keen::ISteamLeaderboardsCallback *this, LeaderboardScoresDownloaded_t *);
	  void (__thiscall *onLeaderboardScoreUploaded)(keen::ISteamLeaderboardsCallback *this, LeaderboardScoreUploaded_t *);
	};

	// /* 2983 */
	// struct __cppobj CCallback<keen::ISteamFriendsCallback,PersonaStateChange_t,0> : CCallbackImpl<16>
	// {
	//   keen::ISteamFriendsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamFriendsCallback *this, PersonaStateChange_t *);
	// };

	//  2984 
	// struct __cppobj CCallback<keen::ISteamFriendsCallback,GameLobbyJoinRequested_t,0> : CCallbackImpl<16>
	// {
	//   keen::ISteamFriendsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamFriendsCallback *this, GameLobbyJoinRequested_t *);
	// };

	/* 2981 */
	struct keen::ISteamFriendsCallback
	{
	  keen::ISteamFriendsCallbackVtbl *vfptr;
	  CCallback<keen::ISteamFriendsCallback,PersonaStateChange_t,0> m_onPersonaStateChange;
	  CCallback<keen::ISteamFriendsCallback,GameLobbyJoinRequested_t,0> m_onGameLobbyJoinRequested;
	};

	/* 2982 */
	struct keen::ISteamFriendsCallbackVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::ISteamFriendsCallback *this, unsigned int);
	  void (__thiscall *onPersonaStateChange)(keen::ISteamFriendsCallback *this, PersonaStateChange_t *);
	  void (__thiscall *onGameLobbyJoinRequested)(keen::ISteamFriendsCallback *this, GameLobbyJoinRequested_t *);
	};

	/* 2995 */
	struct keen::Array<unit4::RankingSendData>
	{
	  unit4::RankingSendData *m_pData;
	  unsigned int m_size;
	};

	/* 2996 */
	struct keen::Queue<unit4::RankingSendData>
	{
	  unsigned int m_size;
	  unsigned int m_bottom;
	  unsigned int m_top;
	  keen::Array<unit4::RankingSendData> m_data;
	};

	/* 2998 */
	struct keen::SizedArray<unit4::RankingListEntry>
	{
	  unit4::RankingListEntry *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 3000 */
	struct keen::Array<unit4::RankingBoardCacheEntry>
	{
	  unit4::RankingBoardCacheEntry *m_pData;
	  unsigned int m_size;
	};

	// /* 3006 */
	// struct __cppobj CCallbackImpl<152> : CCallbackBase
	// {
	// };

	// /* 3007 */
	// struct __cppobj CCallback<keen::ISteamAchievementsCallback,UserAchievementStored_t,0> : CCallbackImpl<152>
	// {
	//   keen::ISteamAchievementsCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamAchievementsCallback *this, UserAchievementStored_t *);
	// };

	/* 3004 */
	struct keen::ISteamAchievementsCallback
	{
	  keen::ISteamAchievementsCallbackVtbl *vfptr;
	  CCallback<keen::ISteamAchievementsCallback,UserAchievementStored_t,0> m_onUserAchievementStored;
	};

	/* 3005 */
	struct keen::ISteamAchievementsCallbackVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::ISteamAchievementsCallback *this, unsigned int);
	  void (__thiscall *onUserAchievementStored)(keen::ISteamAchievementsCallback *this, UserAchievementStored_t *);
	};

	/* 3008 */
	struct __cppobj __declspec(align(8)) keen::SteamAchievements : keen::ISteamAchievementsCallback, keen::ISteamStatsCallback
	{
	  ISteamUserStats *m_pSteamUserStats;
	  unsigned __int64 m_gameSteamID64;
	  const unsigned int *m_pAchievementIdMap;
	  const unsigned int *m_pAchievementUnlockCountMap;
	  unsigned int m_achievementCount;
	  unsigned int m_platinumAchievementId;
	  bool m_platinumAchievementUnlocked;
	};

	/* 3009 */
	struct __cppobj keen::SteamStats : keen::ISteamStatsCallback
	{
	  ISteamUserStats *m_pSteamUserStats;
	  unsigned __int64 m_gameSteamID64;
	  unit4::StatUpdateData *m_pStatUpdateMap;
	  unsigned int m_statUpdateCount;
	  bool m_requestingUserStats;
	  bool m_statsAvailable;
	  bool m_storingStats;
	  bool m_hasUnstoredStats;
	  float m_secondsSinceLastUpdate;
	  bool m_hasCached;
	  long double m_cachedAdds[64];
	  keen::SteamStatType m_statTypes[64];
	};

	/* 3020 */
	struct keen::Array<kaiko::gamelink::GameLinkLan::UserDefinedPacket>
	{
	  kaiko::gamelink::GameLinkLan::UserDefinedPacket *m_pData;
	  unsigned int m_size;
	};

	/* 3021 */
	struct keen::Queue<kaiko::gamelink::GameLinkLan::UserDefinedPacket>
	{
	  unsigned int m_size;
	  unsigned int m_bottom;
	  unsigned int m_top;
	  keen::Array<kaiko::gamelink::GameLinkLan::UserDefinedPacket> m_data;
	};

	// /* 3022 */
	// struct __cppobj kaiko::gamelink::GameLinkRemoteStationLan : kaiko::GameLinkRemoteStation
	// {
	//   unsigned int lastReceivedLobbyStateId;
	//   unsigned int timeLastKeepAliveReceived;
	//   unsigned int timeAdded;
	// };

	/* 3023 */
	struct keen::SizedArray<kaiko::gamelink::GameLinkRemoteStationLan>
	{
	  kaiko::gamelink::GameLinkRemoteStationLan *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 3032 */
	struct keen::SteamworksSystem
	{
	  unsigned int m_appId;
	};

	/* 3035 */
	struct keen::UserAccountSystemCreationParameters
	{
	  keen::SteamworksSystem *pSteamworksSystem;
	  char userNameWin32[256];
	};

	/* 3036 */
	struct __cppobj keen::SoundFile : keen::Resource
	{
	  keen::SoundFileData m_data;
	};

	/* 3037 */
	struct keen::SoundSystem::SoundFileHeader
	{
	  char platform;
	  char version;
	  char numChannels;
	  char flags;
	  unsigned int typeKey;
	  unsigned int sampleRate;
	  unsigned int bufferSize;
	  unsigned int numSamples;
	  char extendedData[12];
	};

	/* 3038 */
	struct keen::UserAccountName
	{
	  char providerData[257];
	};

	/* 3039 */
	struct keen::UserAccount
	{
	  char guestIndex;
	  bool isLoggedIn;
	  keen::UserAccountId id;
	  keen::UserAccountName name;
	};

	/* 3040 */
	struct keen::SPSCQueue::Node
	{
	  keen::SPSCQueue::Node *pNext;
	};

	/* 3041 */
	struct keen::SPSCQueue
	{
	  keen::Mutex m_mutex;
	  keen::SPSCQueue::Node *m_pHead;
	  keen::SPSCQueue::Node *m_pTail;
	};

	/* 3042 */
	struct keen::SystemTimer
	{
	  unsigned int m_startTime;
	};

	/* 3043 */
	struct keen::SoundSystem::SoundDefinitionParameter3d
	{
	  float minDistance;
	  float maxDistance;
	  float positionVariation;
	};

	/* 3044 */
	struct keen::SoundSystem::SoundDefinitionParameter2d
	{
	  float centerFraction;
	  float panAngle;
	  float panDistance;
	  float panAngleVariation;
	};

	// /* 3047 */
	// struct __cppobj CCallback<keen::ISteamMatchmakingCallback,LobbyMatchList_t,0> : CCallbackImpl<4>
	// {
	//   keen::ISteamMatchmakingCallback *m_pObj;
	//   void (__thiscall *m_Func)(keen::ISteamMatchmakingCallback *this, LobbyMatchList_t *);
	// };

	/* 3045 */
	struct keen::ISteamMatchmakingCallback
	{
	  keen::ISteamMatchmakingCallbackVtbl *vfptr;
	  CCallback<keen::ISteamMatchmakingCallback,LobbyMatchList_t,0> m_onLobbyMatchList;
	};

	/* 3046 */
	struct keen::ISteamMatchmakingCallbackVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::ISteamMatchmakingCallback *this, unsigned int);
	  void (__thiscall *onLobbyMatchList)(keen::ISteamMatchmakingCallback *this, LobbyMatchList_t *);
	};

	/* 3054 */
	struct keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam::Segment
	{
	  unsigned int size;
	  unsigned int offset;
	};

	/* 3055 */
	struct keen::Array<keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam::Segment>
	{
	  keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam::Segment *m_pData;
	  unsigned int m_size;
	};

	/* 3056 */
	struct keen::SaveData::SaveDataProviderWin32Interface
	{
	  keen::SaveData::SaveDataProviderWin32InterfaceVtbl *vfptr;
	};

	/* 3057 */
	const struct keen::SaveData::SaveDataFormat
	{
	  unsigned int minimumInstallments;
	  unsigned int maximumInstallments;
	  unsigned int numSegments;
	  const unsigned int *pSegmentSizes;
	};

	/* 3058 */
	struct __cppobj keen::SaveData::SaveDataSystemCreationProviderParameters
	{
	};

	/* 3059 */
	const struct keen::SaveData::SaveDataSystemCreationParameters
	{
	  keen::SaveData::SaveDataSystemType saveDataSystemType;
	  unsigned int maxProfileCount;
	  keen::SaveData::SaveDataFormat *pSaveDataFormats;
	  unsigned int saveDataFormatCount;
	  bool suppressSystemDialogs;
	  keen::SaveData::SaveDataFormat *pGlobalSaveDataFormats;
	  unsigned int globalsaveDataFormatCount;
	  keen::SaveData::SaveDataSystemCreationProviderParameters *pProviderParameters;
	};

	/* 3060 */
	struct keen::SaveData::Profile
	{
	  bool isUsed;
	  char name[64];
	};

	/* 3061 */
	struct keen::SizedArray<keen::SaveData::Profile>
	{
	  keen::SaveData::Profile *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 3062 */
	struct keen::SaveData::SaveData
	{
	  unsigned int formatIndex;
	  unsigned int id;
	};

	/* 3063 */
	struct keen::SizedArray<keen::SaveData::SaveData>
	{
	  keen::SaveData::SaveData *m_pData;
	  unsigned int m_size;
	  unsigned int m_capacity;
	};

	/* 3064 */
	const struct keen::SaveData::StorageOperation
	{
	  unsigned int segmentIndex;
	  void *pBuffer;
	  keen::SaveData::StorageOperation *pNext;
	};

	/* 3065 */
	struct keen::SaveData::SaveDataProviderWin32InterfaceVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  _BYTE gap4[8];
	  bool (__thiscall *enumerateProfiles)(keen::SaveData::SaveDataProviderWin32Interface *this, keen::SizedArray<keen::SaveData::Profile> *);
	  bool (__thiscall *enumerateSaveData)(keen::SaveData::SaveDataProviderWin32Interface *this, keen::SizedArray<keen::SaveData::SaveData> *, unsigned int, unsigned int);
	  bool (__thiscall *connectProfileWithUser)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::UserAccountId);
	  bool (__thiscall *disconnectProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  bool (__thiscall *isProfileConnected)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  void (__thiscall *updateCreateProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::Profile *);
	  void (__thiscall *updateUpdateProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::Profile *);
	  void (__thiscall *updateEraseProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  void (__thiscall *updateConnectProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::Profile *);
	  void (__thiscall *updateDisconnectProfile)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::Profile *);
	  void (__thiscall *updateCheckSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  void (__thiscall *updateCreateSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  void (__thiscall *updateEraseSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	  void (__thiscall *updateCreateSaveData)(keen::SaveData::SaveDataProviderWin32Interface *this, keen::SaveData::SaveData *, unsigned int, keen::SaveData::StorageOperation *);
	  void (__thiscall *updateWriteSaveData)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::SaveData *, keen::SaveData::StorageOperation *);
	  void (__thiscall *updateReadSaveData)(keen::SaveData::SaveDataProviderWin32Interface *this, keen::SaveData::StorageOperation *, unsigned int, keen::SaveData::SaveData *);
	  void (__thiscall *updateEraseSaveData)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int, keen::SaveData::SaveData *);
	  bool (__thiscall *hasFinishedOperation)(keen::SaveData::SaveDataProviderWin32Interface *this);
	  keen::SaveData::OperationResult (__thiscall *getOperationResult)(keen::SaveData::SaveDataProviderWin32Interface *this);
	  unsigned int (__thiscall *getSegmentCount)(keen::SaveData::SaveDataProviderWin32Interface *this, unsigned int);
	};

	/* 3066 */
	struct __declspec(align(4)) keen::SaveDataSystem
	{
	  keen::MemoryAllocator *pAllocator;
	  keen::SaveData::SaveDataSystemType saveDataSystemWin32Type;
	  keen::SaveData::SaveDataProviderWin32Interface *pProvider;
	  keen::SaveData::CurrentOperation currentOperation;
	  keen::SaveData::OperationStatus currentOperationStatus;
	  unsigned int operationProfileIndex;
	  keen::SaveData::Profile *pOperationProfile;
	  keen::SaveData::SaveData *pOperationSaveDataInput;
	  keen::SaveData::SaveData *pOperationSaveDataOutput;
	  keen::SaveData::StorageOperation *pOperationStorageData;
	  bool suppressSystemDialogs;
	};

	/* 3067 */
	struct keen::SaveDataInteractionData
	{
	  kaiko::GameSessionInteractionId id;
	  kaiko::GameSessionResponseId responseOptions[2];
	  unsigned int responseOptionCount;
	};

	/* 3068 */
	struct keen::Array<unsigned char>
	{
	  char *m_pData;
	  unsigned int m_size;
	};

	/* 3069 */
	struct keen::SaveDataHandler::SaveGameData
	{
	  keen::Array<unsigned char> data;
	  unsigned int id;
	};

	/* 3070 */
	struct __declspec(align(2)) keen::SaveDataHandler::SaveGameClientData
	{
	  keen::SizedArray<keen::SaveData::SaveData> currentSaveDatas;
	  keen::SaveDataHandler::SaveGameData saveData;
	  keen::UserAccountId userAccountId;
	  unsigned int lastSavedDataId;
	  keen::SaveDataHandler::SaveGameClientState state;
	  bool isSaveEnabled;
	  bool isShutdownRequested;
	  bool isNewlyCreatedSaveGame;
	};

	/* 3071 */
	struct keen::Array<keen::SaveDataHandler::SaveGameClientData>
	{
	  keen::SaveDataHandler::SaveGameClientData *m_pData;
	  unsigned int m_size;
	};

	/* 3072 */
	struct keen::SaveDataHandler
	{
	  keen::SaveFlowState m_state;
	  unsigned int m_activeClientIndex;
	  keen::SaveDataInteractionData m_currentUserInteraction;
	  keen::SaveDataSystem *m_pSaveDataSystem;
	  keen::SaveDataHandler::SaveGameData m_saveDataForIO;
	  keen::Array<keen::SaveDataHandler::SaveGameClientData> m_clientData;
	  keen::Array<unsigned char> m_defaultSaveGameData;
	  bool (__cdecl *m_pCheckSaveGameDataCallback)(const void *, unsigned int);
	  keen::SaveData::StorageOperation m_saveDataOp;
	  bool m_isDefaultSaveGameDataSet;
	  keen::SizedArray<keen::SaveData::Profile> m_profileList;
	};

	/* 3073 */
	struct keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam
	{
	  keen::Array<keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam::Segment> segments;
	  unsigned int totalSize;
	  unsigned int minimumInstallments;
	  unsigned int maximumInstallments;
	};

	/* 3074 */
	struct keen::Array<keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam>
	{
	  keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam *m_pData;
	  unsigned int m_size;
	};

	/* 3075 */
	struct keen::StringTokenizer
	{
	  char *m_pNextToken;
	};

	/* 3076 */
	struct __cppobj keen::SaveData::SaveDataProviderWin32Steam : keen::SaveData::SaveDataProviderWin32Interface
	{
	  bool isCurrentOperationFinished;
	  keen::SaveData::OperationResult operationResult;
	  wchar_t saveDataFolderName[128];
	  keen::MemoryAllocator *pMemoryAllocator;
	  ISteamRemoteStorage *pSteamStorage;
	  unsigned int connectedUserProfileIndex;
	  keen::UserAccountId connectedUserAccountId;
	  keen::Array<keen::SaveData::SaveDataProviderWin32Steam::SaveDataFormatSteam> saveDataFormats;
	  keen::Event helperThreadEvent;
	  keen::Thread helperThread;
	  bool asyncReadStarted;
	  bool asyncReadFinished;
	  char readFileName[256];
	  char *pReadBuffer;
	  int asyncRequestedSize;
	  int asyncReadBytes;
	};

	/* 3077 */
	struct __cppobj keen::SaveData::SaveDataSystemCreationProviderParametersWin32 : keen::SaveData::SaveDataSystemCreationProviderParameters
	{
	  keen::SteamworksSystem *pSteamworksSystem;
	  const char *pApplicationName;
	};

	/* 3078 */
	struct keen::DebugFontConfiguration
	{
	  int characterWidth;
	  int characterHeight;
	  int baseLineOffset;
	};

	/* 3079 */
	struct keen::DebugRendererConfiguration
	{
	  keen::DebugFontConfiguration fontConfig;
	  unsigned int max2dCommandCount;
	  unsigned int max2dVertexCount;
	  unsigned int max3dCommandCount;
	  unsigned int max3dVertexCount;
	  unsigned int maxTextCharacterCount;
	};
};
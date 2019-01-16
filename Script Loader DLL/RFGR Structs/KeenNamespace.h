#pragma once
#include "BasicTypes.h"
#include "KaikoNamespace.h"
#include "Unit4Namespace.h"
#include <Windows.h>

namespace keen
{
	/* 224 */
	enum $CD5D4A53338CE19DE2CC9E1908B0A091
	{
		MaxSaveDataSetCount = 0x1,
		MaxSaveDataCount = 0x1,
	};

	/* 225 */
	enum $A95F17188CF907CE4977894292478A00
	{
		SaveDataProfileIndex_Invalid = 0xFFFF,
	};

	/* 2884 */
	struct UserAccountId
	{
		char providerData[8];
		bool isValid;
	};

	namespace SaveData
	{
		/* 226 */
		enum OperationStatus
		{
			OperationStatus_Nop = 0x0,
			OperationStatus_Busy = 0x1,
			OperationStatus_Finished = 0x2,
		};

		/* 227 */
		enum OperationResult
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

		/* 228 */
		enum CurrentOperation
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

		/* 229 */
		enum SaveDataSystemType
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

		/* 3064 */
		const struct StorageOperation
		{
			unsigned int segmentIndex;
			void* pBuffer;
			StorageOperation *pNext;
		};

		/* 3060 */
		struct Profile
		{
			bool isUsed;
			char name[64];
		};

		/* 3062 */
		struct SaveData
		{
			unsigned int formatIndex;
			unsigned int id;
		};

		/* 3063 */
		struct SizedArraySaveData
		{
			keen::SaveData::SaveData *m_pData;
			unsigned int m_size;
			unsigned int m_capacity;
		};

		/* 3065 */
		struct SaveDataProviderWin32InterfaceVtbl
		{
			void *(__thiscall *__vecDelDtor)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			char gap4[8];
			bool(__thiscall *enumerateProfiles)(keen::SaveData::SaveDataProviderWin32Interface* This, keen::SizedArrayProfile*);
			bool(__thiscall *enumerateSaveData)(keen::SaveData::SaveDataProviderWin32Interface* This, keen::SaveData::SizedArraySaveData*, unsigned int, unsigned int);
			bool(__thiscall *connectProfileWithUser)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::UserAccountId);
			bool(__thiscall *disconnectProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			bool(__thiscall *isProfileConnected)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			void(__thiscall *updateCreateProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::SaveData::Profile *);
			void(__thiscall *updateUpdateProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::SaveData::Profile *);
			void(__thiscall *updateEraseProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			void(__thiscall *updateConnectProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::SaveData::Profile *);
			void(__thiscall *updateDisconnectProfile)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::SaveData::Profile *);
			void(__thiscall *updateCheckSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			void(__thiscall *updateCreateSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			void(__thiscall *updateEraseSaveDataSet)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
			void(__thiscall *updateCreateSaveData)(keen::SaveData::SaveDataProviderWin32Interface* This, keen::SaveData::SaveData *, unsigned int, keen::SaveData::StorageOperation *);
			void(__thiscall *updateWriteSaveData)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int, keen::SaveData::SaveData *, keen::SaveData::StorageOperation *);
			void(__thiscall *updateReadSaveData)(keen::SaveData::SaveDataProviderWin32Interface* This, keen::SaveData::StorageOperation *, unsigned int, keen::SaveData::SaveData *);
			void(__thiscall *updateEraseSaveData)(keen::SaveData::SaveDataProviderWin32Interface * This, unsigned int, keen::SaveData::SaveData *);
			bool(__thiscall *hasFinishedOperation)(keen::SaveData::SaveDataProviderWin32Interface* This);
			keen::SaveData::OperationResult(__thiscall *getOperationResult)(keen::SaveData::SaveDataProviderWin32Interface* This);
			unsigned int(__thiscall *getSegmentCount)(keen::SaveData::SaveDataProviderWin32Interface* This, unsigned int);
		};

		/* 3056 */
		struct SaveDataProviderWin32Interface
		{
			keen::SaveData::SaveDataProviderWin32InterfaceVtbl *vfptr;
		};
	};

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

	/* 3068 */
	struct ArrayUnsignedChar
	{
		char *m_pData;
		unsigned int m_size;
	};

	/* 232 */
	enum SaveGameClientState
	{
		SaveGameClientState_Free = 0x0,
		SaveGameClientState_Startup = 0x1,
		SaveGameClientState_Ready = 0x2,
		SaveGameClientState_Count = 0x3,
	};

	/* 3069 */
	struct SaveGameData
	{
		ArrayUnsignedChar data;
		unsigned int id;
	};
	
	namespace SaveDataHandler
	{
		/* 3069 */
		struct SaveGameData
		{
			ArrayUnsignedChar data;
			unsigned int id;
		};

		/* 232 */
		enum SaveGameClientState
		{
			SaveGameClientState_Free = 0x0,
			SaveGameClientState_Startup = 0x1,
			SaveGameClientState_Ready = 0x2,
			SaveGameClientState_Count = 0x3,
		};
	}

	/* 3063 */
	struct SizedArraySaveData
	{
		keen::SaveData::SaveData *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3070 */
	struct __declspec(align(2)) SaveGameClientData
	{
		SizedArraySaveData currentSaveDatas;
		keen::SaveDataHandler::SaveGameData saveData;
		keen::UserAccountId userAccountId;
		unsigned int lastSavedDataId;
		keen::SaveDataHandler::SaveGameClientState state;
		bool isSaveEnabled;
		bool isShutdownRequested;
		bool isNewlyCreatedSaveGame;
	};

	/* 3071 */
	struct ArraySaveGameClientData
	{
		SaveGameClientData *m_pData;
		unsigned int m_size;
	};

	/* 3061 */
	struct SizedArrayProfile
	{
		keen::SaveData::Profile* m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3072 */
	struct SaveDataHandler
	{
		SaveFlowState m_state;
		unsigned int m_activeClientIndex;
		SaveDataInteractionData m_currentUserInteraction;
		SaveDataSystem* m_pSaveDataSystem;
		SaveGameData m_saveDataForIO;
		ArraySaveGameClientData m_clientData;
		ArrayUnsignedChar m_defaultSaveGameData;
		bool(__cdecl *m_pCheckSaveGameDataCallback)(const void *, unsigned int);
		SaveData::StorageOperation m_saveDataOp;
		bool m_isDefaultSaveGameDataSet;
		SizedArrayProfile m_profileList;
	};

	/* 3067 */
	struct SaveDataInteractionData
	{
		kaiko::GameSessionInteractionId id;
		kaiko::GameSessionResponseId responseOptions[2];
		unsigned int responseOptionCount;
	};

	/* 2395 */
	struct MemoryAllocator
	{
		MemoryAllocatorVtbl* vfptr;
	};

	/* 2396 */
	struct MemoryAllocatorVtbl
	{
		void* (__thiscall* __vecDelDtor)(MemoryAllocator* This, unsigned int);
		void* (__thiscall* allocate)(MemoryAllocator* This, unsigned int, unsigned int, unsigned int, const char*);
		void(__thiscall* free)(MemoryAllocator* This, void*);
		const char* (__thiscall* getName)(MemoryAllocator* This);
	};


	/* 3066 */
	struct __declspec(align(4)) SaveDataSystem
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

	/* 3537 */
	struct ConnectedEventData
	{
		keen::ControllerType controllerType;
		unsigned int features;
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

	/* 3538 */
	struct ButtonEventData
	{
		unsigned int buttonIndex;
		keen::StandardButtonId standardButton;
	};

	/* 3539 */
	struct AxisEventData
	{
		unsigned int axisIndex;
		float value;
		float previousValue;
	};

	/* 3540 */
	struct KeyEventData
	{
		unsigned int keyCode;
	};

	/* 2340 */
	struct float2
	{
		float x;
		float y;
	};

	/* 3541 */
	struct MouseEventData
	{
		keen::float2 position;
	};

	/* 3542 */
	struct MouseWheelEventData
	{
		int wheelDelta;
	};

	/* 3543 */
	struct TouchEventData
	{
		unsigned int touchId;
		keen::float2 position;
	};

	/* 442 */
	enum FlickDirection
	{
		FlickDirection_Left = 0x0,
		FlickDirection_Right = 0x1,
		FlickDirection_Up = 0x2,
		FlickDirection_Down = 0x3,
	};

	/* 3544 */
	struct FlickEventData
	{
		keen::FlickDirection direction;
		float speed;
		keen::float2 startPosition;
	};

	/* 3545 */
	struct DragEventData
	{
		keen::float2 startPosition;
		keen::float2 deltaPosition;
	};

	/* 3546 */
	struct Axis2dEventData
	{
		unsigned int axisIndex;
		float x;
		float y;
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

	/* 3547 */
	union GyroEventData
	{
		keen::float3 acceleration;
		keen::float3 angularVelocity;
		keen::float4 orientation;
	};

	/* 3548 */
	union InputEventData
	{
		keen::ConnectedEventData connected;
		keen::ButtonEventData button;
		keen::AxisEventData axis;
		keen::KeyEventData key;
		keen::MouseEventData mouse;
		keen::MouseWheelEventData wheel;
		keen::TouchEventData touch;
		keen::FlickEventData flick;
		keen::DragEventData drag;
		keen::Axis2dEventData axis2d;
		keen::GyroEventData gyro;
	};

	/* 3549 */
	struct InputEvent
	{
		char controllerId;
		char controllerClass;
		char localPlayerId;
		char type;
		keen::InputEventData data;
	};

	/* 3365 */
	struct GraphicsCommandWriter
	{
		keen::GraphicsCommandBuffer *m_pBuffer;
		keen::GraphicsSystem *m_pGraphicsSystem;
		keen::RenderTarget *m_pRenderTarget;
		keen::VertexInputBinding *m_pVertexInputBinding;
		keen::BlendState *m_pBlendState;
		keen::RasterizerState *m_pRasterizerState;
		keen::DepthStencilState *m_pDepthStencilState;
		keen::SamplerState *m_fragmentShaderSamplerStates[16];
		keen::TextureData *m_fragmentShaderTextures[16];
		keen::ShaderPipeline *m_pShaderPipeline;
		keen::TextureData *m_vertexShaderTextures[16];
		keen::SamplerState *m_vertexShaderSamplerStates[16];
		keen::VertexFormat *m_screenQuadVertexFormats[3];
		keen::RenderTarget *m_renderPassStack[4];
		keen::StaticConstantBuffer *m_currentStaticVertexConstantBuffers[8];
		keen::StaticConstantBuffer *m_currentStaticFragmentConstantBuffers[8];
		unsigned int m_renderPassStackIndex;
		unsigned int m_stencilRefValue;
		unsigned int m_mappedConstantBufferSlotIndex;
	};

	/* 4588 */
	struct GameFrameworkSystemNative
	{
		HWND* hwnd;
		bool quit;
		bool showBreakHandlerMessage;
		bool quitWithEscape;
		bool resizeableWindow;
		int triggerAltEnter;
	};

	/* 4595 */
	struct __declspec(align(4)) GameFrameworkSystem : GameFrameworkSystemNative
	{
	  keen::MemorySystem *pMemorySystem;
	  keen::TlsfMemoryAllocator defaultAllocator;
	  keen::MemoryAllocator *pDefaultAllocator;
	  keen::FileSystem *pFileSystem;
	  keen::TaskSystem *pTaskSystem;
	  keen::GraphicsSystem *pGraphicsSystem;
	  keen::RenderEffectSystem *pRenderEffectSystem;
	  keen::GraphicsCommandWriter commandWriter;
	  unsigned int shaderMountHandle;
	  bool useSound;
	  unsigned int lastUpdateTime;
	  keen::SoundSystem::System *pSoundSystem;
	  keen::UserAccountSystem *pUserAccountSystem;
	  keen::SaveDataSystem *pSaveDataSystem;
	  unit4::SystemServices *pSystemServices;
	  bool useSteam;
	  keen::SteamworksSystem *pSteamworksSystem;
	  unsigned int debugMountHandle;
	  char userName[64];
	  keen::InputSystem *pInputSystem;
	  bool hideMouseCursorInFullscreen;
	  bool wasInFullscreen;
	  keen::ApplicationProcessState currentProcessState;
	  bool isShutdownRequested;
	  bool renderingSuspended;
	};

	/* 4591 */
	const struct GameApplicationParameters
	{
		int argc;
		char **argv;
	};

	/* 4589 */
	struct __declspec(align(4)) GameApplication
	{
		GameApplicationVtbl *vfptr;
	  	bool m_isShutdownRequested;
	};

	/* 4596 */
	struct GameApplicationVtbl
	{
	  void* (__thiscall* __vecDelDtor)(GameApplication* This, unsigned int);
	  char gap4[4];//_BYTE gap4[4];
	  void (__thiscall* initialize)(GameApplication* This, GameFrameworkSystem*, GameApplicationParameters*);
	  bool (__thiscall* isReadyToShutdown)(GameApplication* This, GameFrameworkSystem*);
	  void (__thiscall* shutdownRequested)(GameApplication* This, GameFrameworkSystem*);
	  void (__thiscall* shutdown)(GameApplication* This, GameFrameworkSystem*);
	  void (__thiscall* updateTime)(GameApplication* This, float);
	  void (__thiscall* render)(GameApplication* This, GraphicsCommandWriter*);
	  bool (__thiscall* processInputEvent)(GameApplication* This, InputEvent*);
	};

	/* 2420 */
	struct Thread
	{
		void* m_threadHandle;
		unsigned int m_threadId;
		volatile void* m_pArgument;
		char m_identifier[64];
		bool m_quitRequested;
		int(__cdecl* m_pFunction)(Thread*);
	};

	namespace rfg
	{
		/* 11805 */
		struct Application : GameApplication
		{
		  	unsigned int m_rfgGameInitializationStep;
		  	keen::Thread m_rfgGameInitializeThread;
		  	bool m_rfgGameInitializeThreadDone;
		  	unit4::LocalGameSession m_localGameSession;
		  	keen::UserAccountSystem *m_pUserAccountSystem;
		  	keen::InputSystem *m_pInputSystem;
		  	unit4::SystemServices *m_pSystemServices;
		  	unsigned int m_userAccountOperationHandle;
		  	char m_nativeGamebuildPath[1024];
		  	keen::GameFrameworkSystem *m_pGameframework;
		  	keen::SoundSystem::System *m_pSoundSystem;
		  	int m_gameSessionMsgboxHandle;
		  	unit4::SessionInteractionData m_gameSessionLastInteraction;
		  	unsigned int m_gameSessionMsgboxSelection;
		  	keen::Thread m_simulationThread;
		  	keen::Event m_simulationSignal;
		  	keen::Event m_renderSignal;
		  	volatile bool m_simulationDone;
		  	bool m_hasDoneSimulationFrame;
		  	keen::Mutex m_renderMutex;
		  	keen::ControllerClass m_lastControllerClass;
		};
	}
}
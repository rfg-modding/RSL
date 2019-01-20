#pragma once
#include "BasicTypes.h"
#include "KaikoNamespace.h"
#include "Unit4Namespace.h"
#include "KeenSoundSystem.hpp"
#include "KeenGameFrameworkSystem.hpp"
#include "KeenGraphicsSystem.hpp"
#include "KeenMemorySystem.hpp"
#include "KeenTaskSystem.h"
#include "KeenFileSystem.h"
#include "KeenTlsfAllocator.h"
#include "KeenRenderEffectSystem.h"
#include <Windows.h>

namespace keen
{
	/* 430 */
	enum AxisFunction
	{
		AxisFunction_None = 0x0,
		AxisFunction_Flip = 0x1,
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

	/* 167 */
	enum EResult
	{
		k_EResultOK = 0x1,
		k_EResultFail = 0x2,
		k_EResultNoConnection = 0x3,
		k_EResultInvalidPassword = 0x5,
		k_EResultLoggedInElsewhere = 0x6,
		k_EResultInvalidProtocolVer = 0x7,
		k_EResultInvalidParam = 0x8,
		k_EResultFileNotFound = 0x9,
		k_EResultBusy = 0xA,
		k_EResultInvalidState = 0xB,
		k_EResultInvalidName = 0xC,
		k_EResultInvalidEmail = 0xD,
		k_EResultDuplicateName = 0xE,
		k_EResultAccessDenied = 0xF,
		k_EResultTimeout = 0x10,
		k_EResultBanned = 0x11,
		k_EResultAccountNotFound = 0x12,
		k_EResultInvalidSteamID = 0x13,
		k_EResultServiceUnavailable = 0x14,
		k_EResultNotLoggedOn = 0x15,
		k_EResultPending = 0x16,
		k_EResultEncryptionFailure = 0x17,
		k_EResultInsufficientPrivilege = 0x18,
		k_EResultLimitExceeded = 0x19,
		k_EResultRevoked = 0x1A,
		k_EResultExpired = 0x1B,
		k_EResultAlreadyRedeemed = 0x1C,
		k_EResultDuplicateRequest = 0x1D,
		k_EResultAlreadyOwned = 0x1E,
		k_EResultIPNotFound = 0x1F,
		k_EResultPersistFailed = 0x20,
		k_EResultLockingFailed = 0x21,
		k_EResultLogonSessionReplaced = 0x22,
		k_EResultConnectFailed = 0x23,
		k_EResultHandshakeFailed = 0x24,
		k_EResultIOFailure = 0x25,
		k_EResultRemoteDisconnect = 0x26,
		k_EResultShoppingCartNotFound = 0x27,
		k_EResultBlocked = 0x28,
		k_EResultIgnored = 0x29,
		k_EResultNoMatch = 0x2A,
		k_EResultAccountDisabled = 0x2B,
		k_EResultServiceReadOnly = 0x2C,
		k_EResultAccountNotFeatured = 0x2D,
		k_EResultAdministratorOK = 0x2E,
		k_EResultContentVersion = 0x2F,
		k_EResultTryAnotherCM = 0x30,
		k_EResultPasswordRequiredToKickSession = 0x31,
		k_EResultAlreadyLoggedInElsewhere = 0x32,
		k_EResultSuspended = 0x33,
		k_EResultCancelled = 0x34,
		k_EResultDataCorruption = 0x35,
		k_EResultDiskFull = 0x36,
		k_EResultRemoteCallFailed = 0x37,
		k_EResultPasswordUnset = 0x38,
		k_EResultExternalAccountUnlinked = 0x39,
		k_EResultPSNTicketInvalid = 0x3A,
		k_EResultExternalAccountAlreadyLinked = 0x3B,
		k_EResultRemoteFileConflict = 0x3C,
		k_EResultIllegalPassword = 0x3D,
		k_EResultSameAsPreviousValue = 0x3E,
		k_EResultAccountLogonDenied = 0x3F,
		k_EResultCannotUseOldPassword = 0x40,
		k_EResultInvalidLoginAuthCode = 0x41,
		k_EResultAccountLogonDeniedNoMail = 0x42,
		k_EResultHardwareNotCapableOfIPT = 0x43,
		k_EResultIPTInitError = 0x44,
		k_EResultParentalControlRestricted = 0x45,
		k_EResultFacebookQueryError = 0x46,
		k_EResultExpiredLoginAuthCode = 0x47,
		k_EResultIPLoginRestrictionFailed = 0x48,
		k_EResultAccountLockedDown = 0x49,
		k_EResultAccountLogonDeniedVerifiedEmailRequired = 0x4A,
		k_EResultNoMatchingURL = 0x4B,
		k_EResultBadResponse = 0x4C,
		k_EResultRequirePasswordReEntry = 0x4D,
		k_EResultValueOutOfRange = 0x4E,
		k_EResultUnexpectedError = 0x4F,
		k_EResultDisabled = 0x50,
		k_EResultInvalidCEGSubmission = 0x51,
		k_EResultRestrictedDevice = 0x52,
		k_EResultRegionLocked = 0x53,
		k_EResultRateLimitExceeded = 0x54,
		k_EResultAccountLoginDeniedNeedTwoFactor = 0x55,
		k_EResultItemDeleted = 0x56,
		k_EResultAccountLoginDeniedThrottle = 0x57,
		k_EResultTwoFactorCodeMismatch = 0x58,
		k_EResultTwoFactorActivationCodeMismatch = 0x59,
		k_EResultAccountAssociatedToMultiplePartners = 0x5A,
		k_EResultNotModified = 0x5B,
		k_EResultNoMobileDevice = 0x5C,
		k_EResultTimeNotSynced = 0x5D,
		k_EResultSmsCodeFailed = 0x5E,
		k_EResultAccountLimitExceeded = 0x5F,
		k_EResultAccountActivityLimitExceeded = 0x60,
		k_EResultPhoneActivityLimitExceeded = 0x61,
		k_EResultRefundToWallet = 0x62,
		k_EResultEmailSendFailure = 0x63,
		k_EResultNotSettled = 0x64,
		k_EResultNeedCaptcha = 0x65,
		k_EResultGSLTDenied = 0x66,
		k_EResultGSOwnerDenied = 0x67,
		k_EResultInvalidItemType = 0x68,
		k_EResultIPBanned = 0x69,
		k_EResultGSLTExpired = 0x6A,
		k_EResultInsufficientFunds = 0x6B,
		k_EResultTooManyPending = 0x6C,
		k_EResultNoSiteLicensesFound = 0x6D,
		k_EResultWGNetworkSendExceeded = 0x6E,
		k_EResultAccountNotFriends = 0x6F,
		k_EResultLimitedUserAccount = 0x70,
	};

	/* 205 */
	enum SteamStatType
	{
		SteamStatType_Unknown = 0xFFFFFFFF,
		SteamStatType_Int = 0x0,
		SteamStatType_Float = 0x1,
		SteamStatType_Count = 0x2,
	};

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

	/* 1 */
	struct _GUID
	{
		unsigned __int32 Data1;
		unsigned __int16 Data2;
		unsigned __int16 Data3;
		unsigned __int8 Data4[8];
	};

	/* 2 */
	typedef struct _GUID GUID;

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
	
	/* 2415 */
	struct BasePoolAllocator
	{
		keen::MemoryBlock m_memoryBlock;
		unsigned int m_capacity;
		unsigned int m_size;
		unsigned int m_elementSize;
		unsigned int m_firstFreeIndex;
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

	/* 3530 */
	struct UserAccountAsyncOperationShowSelectUiResult
	{
		keen::UserAccountId userId;
	};

	/* 3531 */
	struct UserAccountAsyncOperationResultData
	{
		keen::UserAccountAsyncOperationShowSelectUiResult showSelectUi;
	};

	/* 3532 */
	struct __declspec(align(4)) UserAccountAsyncOperationResult
	{
		UserAccountAsyncOperationType type;
		UserAccountAsyncOperationResultData resultData;
		bool success;
	};

	/* 3533 */
	struct UserAccountAsyncOperation
	{
		UserAccountAsyncOperationType type;
		UserAccountAsyncOperationState state;
		UserAccountAsyncOperationResult result;
	};

	/* 3032 */
	struct SteamworksSystem
	{
		unsigned int m_appId;
	};

	/* 3035 */
	struct UserAccountSystemCreationParameters
	{
		SteamworksSystem* pSteamworksSystem;
		char userNameWin32[256];
	};

	/* 3534 */
	struct UserAccountSystemBase
	{
		UserAccountSystemCreationParameters creationParameters;
		UserAccountAsyncOperation runningOperations[1];
	};

	/* 2564 */
	struct CSteamID_SteamID_t_SteamIDComponent_t
	{
		unsigned __int32 m_unAccountID : 32;
		unsigned __int32 m_unAccountInstance : 20;
		unsigned __int32 m_EAccountType : 4;
		__int32 m_EUniverse : 8;
	};

	/* 2565 */
	union CSteamID_SteamID_t
	{
		CSteamID_SteamID_t_SteamIDComponent_t m_comp;
		unsigned __int64 m_unAll64Bits;
	};

	/* 2566 */
	struct CSteamID
	{
		CSteamID_SteamID_t m_steamid;
	};

	/* 3535 */
	struct /*__unaligned*/ __declspec(align(2)) UserAccountSteam
	{
	  CSteamID steamId;
	  char userName[257];
	  bool isConnected;
	};

	/* 3536 */
	struct UserAccountSystem : UserAccountSystemBase
	{
		UserAccountSteam accounts[16];
		unsigned int accountCount;
	};

	/* 3537 */
	struct ConnectedEventData
	{
		keen::ControllerType controllerType;
		unsigned int features;
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

	/* 3550 */
	struct Array_InputEvent
	{
		keen::InputEvent *m_pData;
		unsigned int m_size;
	};

	/* 3564 */
	struct SizedArray_InputEvent
	{
		keen::InputEvent* m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3551 */
	struct Queue_InputEvent
	{
		unsigned int m_size;
		unsigned int m_bottom;
		unsigned int m_top;
		struct Array_InputEvent m_data;
	};

	/* 3567 */
	struct GestureHelper_MoveData
	{
		keen::float2 distance;
		float time;
	};

	/* 3568 */
	struct StaticArray_GestureHelper_MoveData
	{
		keen::GestureHelper_MoveData* m_pData;
		unsigned int m_size;
	};

	/* 3569 */
	struct RingBuffer_GestureHelper_MoveData
	{
		keen::StaticArray_GestureHelper_MoveData m_data;
		unsigned int m_start;
		unsigned int m_end;
		unsigned int m_capacity;
	};

	/* 3570 */
	struct GestureHelper
	{
		keen::RingBuffer_GestureHelper_MoveData m_moveHistory;
		bool m_isTouchInProgress;
		keen::float2 m_startDragPosition;
		keen::float2 m_lastPosition;
		keen::float2 m_accumulatedFrameDeltaPosition;
		float m_currentDeltaTime;
		unsigned int m_controllerId;
		unsigned int m_touchId;
	};

	/* 3564 */
	struct SizedArray_InputEvent
	{
		keen::InputEvent *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3565 */
	struct __declspec(align(4)) ControllerInfo
	{
		keen::ControllerClass controllerClass;
		keen::ControllerType type;
		unsigned int features;
		unsigned int buttonCount;
		unsigned int axisCount;
		char localPlayerId;
	};

	/* 3566 */
	struct MappedAxisButtonState
	{
		bool isPressed;
	};

	struct IUnknownVtbl;
	/* 2572 */
	struct IUnknown
	{
		IUnknownVtbl *lpVtbl;
	};

	/* 22012 */
	//typedef int HRESULT;

	/* 2573 */
	struct IUnknownVtbl
	{
		HRESULT(__stdcall *QueryInterface)(IUnknown *, _GUID *const, void **);
		unsigned int(__stdcall *AddRef)(IUnknown *);
		unsigned int(__stdcall *Release)(IUnknown *);
	};

	/* 3554 */
	struct IDirectInput8A : IUnknown
	{

	};

	/* 3555 */
	struct IDirectInputDevice8A : IUnknown
	{

	};

	/* 3556 */
	struct $775283C53B829FC8B9747CA0366937F7
	{
		unsigned int guid0;
		unsigned __int16 guid1;
		unsigned __int16 guid2;
		char guid3[8];
	};

	/* 3557 */
	const struct DInputControllerConfig
	{
		$775283C53B829FC8B9747CA0366937F7 guid;
		keen::ControllerType type;
		int axisIndex[8];
		keen::AxisFunction axisFunction[8];
		unsigned __int64 buttonIds[32];
		unsigned __int64 povButtonIds[4][4];
	};

	/* 3558 */
	struct ControllerDInputWin32
	{
		IDirectInputDevice8A *m_pDevice;
		keen::DInputControllerConfig *m_pConfig;
	};

	namespace input
	{
		/* 3559 */
		struct ButtonBitfield
		{
			unsigned __int64 low;
			unsigned __int64 high;
		};

		/* 3560 */
		struct __declspec(align(8)) GenericPadInput
		{
			keen::input::ButtonBitfield buttons;
			float axis[48];
			keen::float3 acceleration;
			keen::float3 angularVelocity;
			keen::float4 orientation;
			bool isConnected;
		};
	}

	/* 3561 */
	struct __declspec(align(8)) ControllerSteam
	{
		unsigned __int64 m_steamControllerHandle;
		unsigned int m_setIndex;
		float m_leftMotorIntensity;
		float m_rightMotorIntensity;
		keen::float4 m_orientationOrigin;
		keen::float4 m_lastOrientation;
	};

	/* 3562 */
	struct SizedArray_DInputControllerConfig
	{
		DInputControllerConfig *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3552 */
	struct _XINPUT_VIBRATION
	{
		unsigned __int16 wLeftMotorSpeed;
		unsigned __int16 wRightMotorSpeed;
	};

	/* 3553 */
	struct ControllerXb360
	{
		bool m_isConnected;
		bool m_retryVibration;
		_XINPUT_VIBRATION m_vibrationState;
		keen::ControllerType m_controllerType;
	};

	/* 3563 */
	struct __declspec(align(8)) PlatformControllerState
	{
		keen::ControllerXb360 controllers[4];
		bool mouseVisible;
		bool clipMouseCursorWhileInvisible;
		bool mousePositionRelative;
		bool deviceChangeReceived;
		keen::float2 lastMousePosition;
		IDirectInput8A *pDirect8;
		keen::ControllerDInputWin32 directInputControllers[8];
		unsigned int directInputControllerCount;
		keen::input::GenericPadInput lastState[16];
		unsigned int mouseWheelButtonFlags;
		keen::ControllerSteam steamController[4];
		unsigned int steamControllerCount;
		keen::SizedArray_DInputControllerConfig directInputControllerConfigs;
		bool apiHidden[3];
	};

	/* 3571 */
	struct InputSystem
	{
		keen::Queue_InputEvent eventQueue;
		keen::PlatformControllerState controllerState;
		keen::SizedArray_InputEvent storedEvents;
		keen::ControllerInfo controllerInfos[16];
		keen::InputSystemControllerAutoCatchType autoCatchType;
		void* LocalPlayerIdStructureType;//keen::LocalPlayerIdStructureType* autoCatchPlayerId;
		keen::MappedAxisButtonState mappedAxisButtonStates[7][16];
		keen::GestureHelper gestureHelper;
	};

	/* 2780 */
	/*struct ISteamUserStatsVtbl
	{
		bool(__thiscall *RequestCurrentStats)(ISteamUserStats *this);
		_BYTE gap4[20];
		bool(__thiscall *GetAchievement)(ISteamUserStats *this, const char *, bool *);
		bool(__thiscall *SetAchievement)(ISteamUserStats *this, const char *);
		bool(__thiscall *ClearAchievement)(ISteamUserStats *this, const char *);
		bool(__thiscall *GetAchievementAndUnlockTime)(ISteamUserStats *this, const char *, bool *, unsigned int *);
		bool(__thiscall *StoreStats)(ISteamUserStats *this);
		int(__thiscall *GetAchievementIcon)(ISteamUserStats *this, const char *);
		const char *(__thiscall *GetAchievementDisplayAttribute)(ISteamUserStats *this, const char *, const char *);
		bool(__thiscall *IndicateAchievementProgress)(ISteamUserStats *this, const char *, unsigned int, unsigned int);
		unsigned int(__thiscall *GetNumAchievements)(ISteamUserStats *this);
		const char *(__thiscall *GetAchievementName)(ISteamUserStats *this, unsigned int);
		unsigned __int64(__thiscall *RequestUserStats)(ISteamUserStats *this, CSteamID);
		bool(__thiscall *GetUserStat)(ISteamUserStats *this, CSteamID, const char *, float *);
		bool(__thiscall *GetUserStat)(ISteamUserStats *this, CSteamID, const char *, int *);
		bool(__thiscall *GetUserAchievement)(ISteamUserStats *this, CSteamID, const char *, bool *);
		bool(__thiscall *GetUserAchievementAndUnlockTime)(ISteamUserStats *this, CSteamID, const char *, bool *, unsigned int *);
		bool(__thiscall *ResetAllStats)(ISteamUserStats *this, bool);
		unsigned __int64(__thiscall *FindOrCreateLeaderboard)(ISteamUserStats *this, const char *, ELeaderboardSortMethod, ELeaderboardDisplayType);
		unsigned __int64(__thiscall *FindLeaderboard)(ISteamUserStats *this, const char *);
		const char *(__thiscall *GetLeaderboardName)(ISteamUserStats *this, unsigned __int64);
		int(__thiscall *GetLeaderboardEntryCount)(ISteamUserStats *this, unsigned __int64);
		ELeaderboardSortMethod(__thiscall *GetLeaderboardSortMethod)(ISteamUserStats *this, unsigned __int64);
		ELeaderboardDisplayType(__thiscall *GetLeaderboardDisplayType)(ISteamUserStats *this, unsigned __int64);
		unsigned __int64(__thiscall *DownloadLeaderboardEntries)(ISteamUserStats *this, unsigned __int64, ELeaderboardDataRequest, int, int);
		unsigned __int64(__thiscall *DownloadLeaderboardEntriesForUsers)(ISteamUserStats *this, unsigned __int64, CSteamID *, int);
		bool(__thiscall *GetDownloadedLeaderboardEntry)(ISteamUserStats *this, unsigned __int64, int, LeaderboardEntry_t *, int *, int);
		unsigned __int64(__thiscall *UploadLeaderboardScore)(ISteamUserStats *this, unsigned __int64, ELeaderboardUploadScoreMethod, int, const int *, int);
		unsigned __int64(__thiscall *AttachLeaderboardUGC)(ISteamUserStats *this, unsigned __int64, unsigned __int64);
		unsigned __int64(__thiscall *GetNumberOfCurrentPlayers)(ISteamUserStats *this);
		unsigned __int64(__thiscall *RequestGlobalAchievementPercentages)(ISteamUserStats *this);
		int(__thiscall *GetMostAchievedAchievementInfo)(ISteamUserStats *this, char *, unsigned int, float *, bool *);
		int(__thiscall *GetNextMostAchievedAchievementInfo)(ISteamUserStats *this, int, char *, unsigned int, float *, bool *);
		bool(__thiscall *GetAchievementAchievedPercent)(ISteamUserStats *this, const char *, float *);
		unsigned __int64(__thiscall *RequestGlobalStats)(ISteamUserStats *this, int);
		bool(__thiscall *GetGlobalStat)(ISteamUserStats *this, const char *, long double *);
		bool(__thiscall *GetGlobalStat)(ISteamUserStats *this, const char *, __int64 *);
		int(__thiscall *GetGlobalStatHistory)(ISteamUserStats *this, const char *, long double *, unsigned int);
		int(__thiscall *GetGlobalStatHistory)(ISteamUserStats *this, const char *, __int64 *, unsigned int);
	};*/

	/* 2778 */
	struct ISteamUserStats
	{
		void* vfptr;//ISteamUserStatsVtbl *vfptr;
	};

	/* 2657 */
	struct CCallbackBase
	{
		CCallbackBaseVtbl *vfptr;
		char m_nCallbackFlags;
		int m_iCallback;
	};

	/* 2658 */
	struct CCallbackBaseVtbl
	{
		void(__thiscall *Run)(CCallbackBase *This, void *, bool, unsigned __int64);
		void(__thiscall *Run)(CCallbackBase *This, void *);
		int(__thiscall *GetCallbackSizeBytes)(CCallbackBase *This);
	};

	struct CCallbackImpl_16 : CCallbackBase
	{

	};

	/* 2659 */
	struct CCallbackImpl_24 : CCallbackBase
	{

	};

	/* 2988 */
	struct __declspec(align(8)) UserAchievementStored_t
	{
		unsigned __int64 m_nGameID;
		bool m_bGroupAchievement;
		char m_rgchAchievementName[128];
		unsigned int m_nCurProgress;
		unsigned int m_nMaxProgress;
	};

	/* 2666 */
	struct __declspec(align(8)) UserStatsReceived_t
	{
		unsigned __int64 m_nGameID;
		EResult m_eResult;
		__unaligned __declspec(align(1)) CSteamID m_steamIDUser;
	};

	/* 2667 */
	struct __declspec(align(8)) UserStatsStored_t
	{
		unsigned __int64 m_nGameID;
		EResult m_eResult;
	};

	/* 2669 */
	struct CCallback_ISteamStatsCallback_UserStatsReceived_t_0 : CCallbackImpl_24
	{
		keen::ISteamStatsCallback *m_pObj;
		void(__thiscall *m_Func)(keen::ISteamStatsCallback *This, UserStatsReceived_t *);
	};

	/* 2671 */
	struct CCallback_ISteamStatsCallback_UserStatsStored_t_0 : CCallbackImpl_16
	{
		keen::ISteamStatsCallback *m_pObj;
		void(__thiscall *m_Func)(keen::ISteamStatsCallback *This, UserStatsStored_t *);
	};

	/* 2665 */
	struct ISteamStatsCallback
	{
		void* vfptr;//keen::ISteamStatsCallbackVtbl *vfptr;
		CCallback_ISteamStatsCallback_UserStatsReceived_t_0 m_onUserStatsReceived;
		CCallback_ISteamStatsCallback_UserStatsStored_t_0 m_onUserStatsStored;
	};

	/* 2669 */
	struct CCallback_ISteamStatsCallback_UserStatsReceived_t_0 : CCallbackImpl_24
	{
		keen::ISteamStatsCallback *m_pObj;
		void(__thiscall *m_Func)(keen::ISteamStatsCallback *This, UserStatsReceived_t *);
	};

	/* 3006 */
	struct CCallbackImpl_152 : CCallbackBase
	{
	};

	/* 3007 */
	struct CCallback_ISteamAchievementsCallback_UserAchievementStored_t_0 : CCallbackImpl_152
	{
	  keen::ISteamAchievementsCallback *m_pObj;
	  void (__thiscall *m_Func)(keen::ISteamAchievementsCallback *This, UserAchievementStored_t *);
	};

	/* 3004 */
	struct ISteamAchievementsCallback
	{
	  keen::ISteamAchievementsCallbackVtbl *vfptr;
	  CCallback_ISteamAchievementsCallback_UserAchievementStored_t_0 m_onUserAchievementStored;
	};

	/* 3005 */
	struct ISteamAchievementsCallbackVtbl
	{
	  void *(__thiscall *__vecDelDtor)(keen::ISteamAchievementsCallback *This, unsigned int);
	  void (__thiscall *onUserAchievementStored)(keen::ISteamAchievementsCallback *This, UserAchievementStored_t *);
	};

	/* 3008 */
	struct __declspec(align(8)) SteamAchievements : ISteamAchievementsCallback, ISteamStatsCallback
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
	struct SteamStats : ISteamStatsCallback
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

	/* 3010 */
	struct INetworkListManager : IDispatch
	{

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

	/* 2422 */
	struct Event
	{
		void *m_eventHandle;
	};

	/* 2406 */
	struct Mutex
	{
		char m_name[32];
		unsigned int m_criticalSectionData[6];
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
		  	keen::UserAccountSystem* m_pUserAccountSystem;
		  	keen::InputSystem* m_pInputSystem;
		  	unit4::SystemServices* m_pSystemServices;
		  	unsigned int m_userAccountOperationHandle;
		  	char m_nativeGamebuildPath[1024];
		  	keen::GameFrameworkSystem* m_pGameframework;
		  	keen::SoundSystem::System* m_pSoundSystem;
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
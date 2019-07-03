#pragma once


namespace keen
{
	/* 2 */
	typedef struct _GUID GUID;

	/* 2884 */
	struct UserAccountId
	{
		char providerData[8];
		bool isValid;
	};

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

}
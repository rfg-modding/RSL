#pragma once
#include "KeenNamespace.h"
#include "Unit4Namespace.h"

namespace kaiko
{
	/* 123 */
	enum GameSessionInteractionId
	{
		GameSessionInteractionId_SelectionCanceled = 0x1001,
		GameSessionInteractionId_SaveGameCorrupt = 0x1002,
		GameSessionInteractionId_EraseFailed = 0x1003,
		GameSessionInteractionId_NotEnoughSpace_RetryDisable = 0x1004,
		GameSessionInteractionId_NotEnoughSpace_EraseDisable = 0x1005,
		GameSessionInteractionId_CreateFailed = 0x1006,
		GameSessionInteractionId_ReadError = 0x1007,
		GameSessionInteractionId_ReadError_Erase = 0x1008,
		GameSessionInteractionId_UserBindingError = 0x1009,
		GameSessionInteractionId_WriteError = 0x100A,
		GameSessionInteractionId_Overwrite = 0x100B,
		GameSessionInteractionId_ConfirmDisable = 0x100C,
		GameSessionInteractionId_ConfirmErase = 0x100D,
		GameSessionInteractionId_InformDeviceChanged = 0x100E,
		GameSessionInteractionId_WaitingForProcess = 0x100F,
		GameSessionInteractionId_NotOnline = 0x2000,
		GameSessionInteractionId_ConnectionFailed = 0x2001,
		GameSessionInteractionId_RankingSendFailed_NotOnline = 0x2002,
		GameSessionInteractionId_RankingSendFailed_ConnectionFailed = 0x2003,
		GameSessionInteractionId_RankingSendFailed_ForbiddenByParentalControl = 0x2004,
		GameSessionInteractionId_GotDisconnected = 0x2005,
		GameSessionInteractionId_ForbiddenByParentalControl = 0x2004,
		GameSessionInteractionId_xxx = 0x2005,
		GameSessionInteractionId_FailedRetryOrDisable = 0x2006,
		GameSessionInteractionId_ShowProfileRestricted = 0x2007,
		GameSessionInteractionId_ShowProfileError = 0x2008,
		GameSessionInteractionId_GenericControllerDisconnected = 0x3001,
		GameSessionInteractionId_WiiUProControllerDisconnected = 0x3002,
		GameSessionInteractionId_DisplayingSignInUi = 0x4001,
		GameSessionInteractionId_SignInSkipped = 0x4002,
		GameSessionInteractionId_SignedOut = 0x4003,
		GameSessionInteractionId_SwitchedAccount = 0x4004,
		GameSessionInteractionId_CreatePartyCancelled = 0x5000,
		GameSessionInteractionId_KickedFromLobby = 0x5001,
		GameSessionInteractionId_JoinLobbyFailed_Unknown = 0x5002,
		GameSessionInteractionId_JoinLobbyFailed_Timeout = 0x5003,
		GameSessionInteractionId_JoinLobbyFailed_Locked = 0x5004,
		GameSessionInteractionId_JoinLobbyFailed_NotAllowedToJoin = 0x5005,
		GameSessionInteractionId_JoinLobbyFailed_WrongPassword = 0x5006,
		GameSessionInteractionId_JoinLobbyFailed_Full = 0x5007,
		GameSessionInteractionId_JoinLobbyFailed_NotFound = 0x5008,
		GameSessionInteractionId_CreateLobbyFailed_Unknown = 0x5009,
		GameSessionInteractionId_CreateLobbyFailed_Timeout = 0x500A,
		GameSessionInteractionId_General_Timeout = 0x500B,
		GameSessionInteractionId_HostMigrationFailed = 0x500C,
		GameSessionInteractionId_SessionLost = 0x500D,
		GameSessionInteractionId_ServerNotAvailable = 0x500E,
		GameSessionInteractionId_NotSignedIn = 0x500F,
		GameSessionInteractionId_NoNetworkAccess = 0x5010,
		GameSessionInteractionId_NoInternetAccess = 0x5011,
		GameSessionInteractionId_Unknown = 0x5012,
		GameSessionInteractionId_ServiceUnavailable = 0x5013,
		GameSessionInteractionId_UserBlocked = 0x5015,
		GameSessionInteractionId_NoMultiplayerUnknown = 0x5016,
		GameSessionInteractionId_NoMultiplayerSubscriptionRequired = 0x5017,
		GameSessionInteractionId_NoMultiplayerBanned = 0x5018,
		GameSessionInteractionId_NoMultiplayerAgeRestricted = 0x5019,
		GameSessionInteractionId_NoVoiceChatUnknown = 0x501A,
		GameSessionInteractionId_NoVoiceChatSubscriptionRequired = 0x501B,
		GameSessionInteractionId_NoVoiceChatBanned = 0x501C,
		GameSessionInteractionId_NoVoiceChatAgeRestricted = 0x501D,
		GameSessionInteractionId_NetworkConnectionLost = 0x501E,
		GameSessionInteractionId_InternetConnectionLost = 0x501F,
		GameSessionInteractionId_AskToEnableParty = 0x5020,
		GameSessionInteractionId_NoMultiplayerNotSignedIn = 0x5021,
		GameSessionInteractionId_NoMultiplayerSystemupdateRequired = 0x5022,
		GameSessionInteractionId_NoMultiplayerGameUpdateRequired = 0x5023,
		GameSessionInteractionId_WaitForPermissionCheck = 0x5024,
		GameSessionInteractionId_NoMultiplayerRestricted = 0x5025,
		GameSessionInteractionId_SignedOutMultiplayer = 0x5026,
		GameSessionInteractionId_ErrorViewerRequired = 0x6000,
		GameSessionInteractionId_None = 0x0,
		GameSessionInteractionId_Invalid = 0xFFFFFFFF,
	};

	/* 133 */
	enum GameSessionResponseId
	{
		GameSessionResponseId_Ok = 0x1,
		GameSessionResponseId_Cancel = 0x2,
		GameSessionResponseId_Exit = 0x3,
		GameSessionResponseId_RetryFunction = 0x1003,
		GameSessionResponseId_Disable = 0x1004,
		GameSessionResponseId_Erase = 0x1005,
		GameSessionResponseId_DeviceSelection = 0x1006,
		GameSessionResponseId_Overwrite = 0x1007,
		GameSessionResponseId_ContinueWithoutConnection = 0x2001,
		GameSessionResponseId_RetryConnecting = 0x2002,
		GameSessionResponseId_RetrySignIn = 0x4001,
		GameSessionResponseId_SkipSignIn = 0x4002,
		GameSessionResponseId_RepeatSignIn = 0x4003,
		GameSessionResponseId_None = 0xFFFFFFFF,
	};

	enum kaiko::GameSessionInteractionParameterType
	{
		GameSessionInteractionParameterType_PlatformErrorCode = 0x0,
		GameSessionInteractionParameterType_UserNameString = 0x1,
	};

	namespace GameSessionInteractionParameter
	{
		/* 3572 */
		union GameSessionInteractionParameterValue
		{
			int sint32Value;
			char stringValue[64];
		};
	}

	/* 3573 */
	struct GameSessionInteractionParameter
	{
		kaiko::GameSessionInteractionParameterType type;
		kaiko::GameSessionInteractionParameter::GameSessionInteractionParameterValue value;
	};

	/* 3574 */
	struct GameSessionInteractionParameterList
	{
		kaiko::GameSessionInteractionParameter parameters[4];
		unsigned int parameterCount;
	};
}
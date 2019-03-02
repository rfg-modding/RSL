#pragma once
//#include "KeenNamespace.h"
//#include "KaikoNamespace.h"

/*#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long*/

#include "KeenNamespace2.h"

namespace unit4
{
	//namespace SystemServices
	//{
		enum SendRankingStep
		{
			SendRankingStep_Invalid = 0x0,
			SendRankingStep_FindLeaderboard = 0x1,
			SendRankingStep_UploadScore = 0x2,
		};

		enum ReceiveRankingStep
		{
			ReceiveRankingStep_Invalid = 0x0,
			ReceiveRankingStep_FindLeaderboard = 0x1,
			ReceiveRankingStep_DownloadLeaderboard = 0x2,
		};
	//}

	enum RankingListQueryType
	{
		RankingListQueryType_AllWithOffset = 0x0,
		RankingListQueryType_AllCenteredOnUser = 0x1,
		RankingListQueryType_FriendsWithOffset = 0x2,
		RankingListQueryType_FriendsCenteredOnUser = 0x3,
	};

	enum LocalPlayerType
	{
		LocalPlayerType_WithAccount = 0x0,
		LocalPlayerType_Guest = 0x1,
	};

	enum LocalUserState //LocalGameSession::LocalUserState
	{
		LocalUserState_Unused = 0x0,
		LocalUserState_NoAccount = 0x1,
		LocalUserState_NoSavedata = 0x2,
		LocalUserState_Savedata = 0x3,
		LocalUserState_SkippedSignIn = 0x4,
		LocalUserState_SignedOut = 0x5,
		LocalUserState_SwitchedAccount = 0x6,
		LocalUserState_Exited = 0x7,
	};

	enum InteractionStarter //unit4::LocalGameSession::InteractionStarter
	{
		InteractionStarter_Invalid = 0x0,
		InteractionStarter_SaveData = 0x1,
		InteractionStarter_SystemServices = 0x2,
		InteractionStarter_Input = 0x3,
		InteractionStarter_UserAccountSystem = 0x4,
	};

	struct SaveDataDescriptionInterfaceVtbl;
	/* 4543 */
	struct SaveDataDescriptionInterface
	{
		SaveDataDescriptionInterfaceVtbl *vfptr;
	};

	/* 4544 */
	struct SaveDataDescriptionInterfaceVtbl
	{
		void *(__thiscall *__vecDelDtor)(unit4::SaveDataDescriptionInterface* This, unsigned int);
		unsigned int(__thiscall *getSaveDataSize)(unit4::SaveDataDescriptionInterface* This);
		bool(__thiscall *isSaveDataValid)(unit4::SaveDataDescriptionInterface* This, const void*);
		void(__thiscall *initializeSaveDataToDefault)(unit4::SaveDataDescriptionInterface* This, void*);
	};

	struct SessionInteractionData
	{
		unsigned int id;
		unsigned int responseOptions[2];
		unsigned int responseOptionCount;
		keen::UserAccountId user;
		kaiko::GameSessionInteractionParameterList params;
	};

	/* 2326 */
	struct StatUpdateData
	{
		unsigned int statId;
		char statName[64];
	};

	/* 2889 */
	struct RemoteUserId
	{
		char providerData[8];
		char guestIndex;
		bool isValid;
	};

	/* 2890 */
	struct NamedRemoteUserId
	{
		unit4::RemoteUserId id;
		char displayName[64];
	};

	struct RankingSendData
	{
		unsigned __int16 tableId;
		unit4::RemoteUserId user;
		unsigned int score;
		unsigned int scoreDetails[16];
		unsigned int numScoreDetails;
	};

	struct Array__unit4_RankingSendData
	{
		RankingSendData* m_pData;
		unsigned int m_size;
	};

	struct Queue__unit4_RankingSendData
	{
		unsigned int m_size;
		unsigned int m_bottom;
		unsigned int m_top;
		Array__unit4_RankingSendData m_data;
	};

	struct RankingListEntry
	{
		unit4::NamedRemoteUserId userInfo;
		unsigned int rank;
		unsigned int score;
		unsigned int scoreDetails[16];
		unsigned int numScoreDetails;
	};

	/* 2998 */
	struct SizedArray__unit4_RankingListEntry
	{
		unit4::RankingListEntry *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 2999 */
	struct RankingBoardCacheEntry
	{
		unsigned __int16 tableId;
		unit4::RemoteUserId user;
		unit4::RankingListQueryType type;
		SizedArray__unit4_RankingListEntry entries;
		unsigned int totalEntriesOnBoard;
		unsigned int downloadTimeInMs;
	};

	/* 3000 */
	struct Array__unit4_RankingBoardCacheEntry
	{
		unit4::RankingBoardCacheEntry *m_pData;
		unsigned int m_size;
	};

	/* 3001 */
	struct RankingReceiveData
	{
		Array__unit4_RankingBoardCacheEntry cachedBoards;
		bool servingFromCache;
		bool downloadInProgress;
		unsigned __int16 tableId;
		unit4::RemoteUserId user;
		int type;//unit4::RankingListQueryType type;
		unsigned int offset;
		unsigned int entriesToQuery;
		unsigned int cacheToUseForResult;
	};

	/* 3002 */
	struct __declspec(align(4)) SystemServicesInteractionData
	{
		unsigned int id;
		unsigned int responseOptions[2];
		unsigned int responseOptionCount;
		keen::UserAccountId user;
	};

	/* 126 */
	enum RankingError
	{
		RankingError_None = 0x0,
		RankingError_NotOnline = 0x2000,
		RankingError_ConnectionFailed = 0x2001,
		RankingError_ForbiddenByParentalControl = 0x2004,
		RankingError_xxx = 0x2005,
		RankingError_FailedRetryOrDisable = 0x2006,
	};

	struct SystemServicesBase
	{
		unsigned int currentTimeInMs;
		bool rankingSendInProgress;
		unit4::RankingSendData currentRankingSendData;
		Queue__unit4_RankingSendData rankingSendDataQueue; //keen::Queue<unit4::RankingSendData> rankingSendDataQueue;
		unit4::RankingReceiveData rankingReceiveData;
		unit4::RankingError currentRankingError;
		unit4::SystemServicesInteractionData rankingSendInteraction;
		unit4::SystemServicesInteractionData onlineInteraction;
	};

	struct __declspec(align(8)) SystemServices : SystemServicesBase
	{
		keen::SteamAchievements steamAchievements;
		keen::SteamStats steamStats;
		const char *pPresenceStrings[64];
		unsigned int presenceStringCount;
		SendRankingStep sendRankingStep;
		unsigned __int64 sendRankingCall;
		ReceiveRankingStep receiveRankingStep;
		unsigned __int64 receiveRankingCall;
		INetworkListManager* pNetworkListManager;
	};

	struct __declspec(align(4)) LocalUserData //LocalGameSession::LocalUserData
	{
		bool skippedSignIn;
		bool hasExpectedUserId;
		keen::UserAccount expectedUser;
		LocalUserState state;
		LocalUserState stateBeforeProfileChange;
		unit4::LocalPlayerType playerType;
		unsigned int saveProfileIndex;
		bool controllerDisconnected;
	};

	struct Array__unit4_LocalGameSession_LocalUserData
	{
		LocalUserData *m_pData;
		unsigned int m_size;
	};

	struct LocalGameSession
	{
		unit4::SaveDataDescriptionInterface *m_pSaveDataInterface;
		keen::SaveDataHandler* m_pSaveDataHandler;
		keen::UserAccountSystem* m_pUserAccountSystem;
		unit4::SystemServices* m_pSystemServices;
		keen::InputSystem *m_pInputSystem;
		bool m_showingSignInUi;
		Array__unit4_LocalGameSession_LocalUserData m_userData;
		unsigned int m_userAccountOperationHandle;
		keen::ControllerInfo m_lastUsedControllerInfo;
		InteractionStarter m_lastInteractionStartedBy;
	};
}

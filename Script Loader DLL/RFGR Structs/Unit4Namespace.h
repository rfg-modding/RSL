#pragma once
#include "KeenNamespace.h"
#include "KaikoNamespace.h"

/*#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long*/

namespace unit4
{
	/* 4543 */
	struct SaveDataDescriptionInterface
	{
		SaveDataDescriptionInterfaceVtbl *vfptr;
	};

	/* 4544 */
	struct SaveDataDescriptionInterfaceVtbl
	{
		void *(__thiscall *__vecDelDtor)(unit4::SaveDataDescriptionInterface* This, unsigned int);
		unsigned int(__thiscall *getSaveDataSize)(unit4::SaveDataDescriptionInterface* This;
		bool(__thiscall *isSaveDataValid)(unit4::SaveDataDescriptionInterface* This, const void*);
		void(__thiscall *initializeSaveDataToDefault)(unit4::SaveDataDescriptionInterface* This, void*);
	};

	/* 4552 */
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

	/* 3011 */
	struct __declspec(align(8)) SystemServices : SystemServicesBase
	{
		keen::SteamAchievements steamAchievements;
		keen::SteamStats steamStats;
		const char *pPresenceStrings[64];
		unsigned int presenceStringCount;
		unit4::SystemServices::SendRankingStep sendRankingStep;
		unsigned __int64 sendRankingCall;
		unit4::SystemServices::ReceiveRankingStep receiveRankingStep;
		unsigned __int64 receiveRankingCall;
		INetworkListManager *pNetworkListManager;
	};

	struct LocalGameSession
	{
		unit4::SaveDataDescriptionInterface *m_pSaveDataInterface;
		keen::SaveDataHandler *m_pSaveDataHandler;
		keen::UserAccountSystem *m_pUserAccountSystem;
		unit4::SystemServices *m_pSystemServices;
		keen::InputSystem *m_pInputSystem;
		bool m_showingSignInUi;
		keen::Array<unit4::LocalGameSession::LocalUserData> m_userData;
		unsigned int m_userAccountOperationHandle;
		keen::ControllerInfo m_lastUsedControllerInfo;
		unit4::LocalGameSession::InteractionStarter m_lastInteractionStartedBy;
	};
}

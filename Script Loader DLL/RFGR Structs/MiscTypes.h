#pragma once

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
	  void (__thiscall *Run)(CCallbackBase *this, void *, bool, unsigned __int64);
	  void (__thiscall *Run)(CCallbackBase *this, void *);
	  int (__thiscall *GetCallbackSizeBytes)(CCallbackBase *this);
	};

	/* 2659 */
	struct CCallbackImpl<24> : CCallbackBase
	{

	};

	/* 2661 */
	struct __declspec(align(8)) LobbyDataUpdate_t
	{
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned __int64 m_ulSteamIDMember;
	  char m_bSuccess;
	};

	/* 2664 */
	struct XAUDIO2_VOICE_DETAILS
	{
	  unsigned int CreationFlags;
	  unsigned int InputChannels;
	  unsigned int InputSampleRate;
	};

	/* 2670 */
	struct __cppobj CCallbackImpl<16> : CCallbackBase
	{

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

	/* 2739 */
	struct CCallbackImpl<32> : CCallbackBase
	{
		
	};

		/* 2729 */
	struct LobbyInvite_t
	{
	  unsigned __int64 m_ulSteamIDUser;
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned __int64 m_ulGameID;
	};

	/* 2730 */
	struct __declspec(align(8)) LobbyEnter_t
	{
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned int m_rgfChatPermissions;
	  bool m_bLocked;
	  unsigned int m_EChatRoomEnterResponse;
	};

	/* 2731 */
	struct __declspec(align(8)) LobbyChatUpdate_t
	{
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned __int64 m_ulSteamIDUserChanged;
	  unsigned __int64 m_ulSteamIDMakingChange;
	  unsigned int m_rgfChatMemberStateChange;
	};

	/* 2732 */
	struct LobbyChatMsg_t
	{
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned __int64 m_ulSteamIDUser;
	  char m_eChatEntryType;
	  unsigned int m_iChatID;
	};

	/* 2733 */
	struct __declspec(align(8)) LobbyKicked_t
	{
	  unsigned __int64 m_ulSteamIDLobby;
	  unsigned __int64 m_ulSteamIDAdmin;
	  char m_bKickedDueToDisconnect;
	};

	/* 2734 */
	struct LobbyCreated_t
	{
	  EResult m_eResult;
	  unsigned __int64 m_ulSteamIDLobby;
	};
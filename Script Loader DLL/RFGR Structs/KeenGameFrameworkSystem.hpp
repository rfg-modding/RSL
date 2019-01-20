#pragma once
#include "KeenNamespace.h"

namespace keen
{
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
		void(__thiscall* initialize)(GameApplication* This, GameFrameworkSystem*, GameApplicationParameters*);
		bool(__thiscall* isReadyToShutdown)(GameApplication* This, GameFrameworkSystem*);
		void(__thiscall* shutdownRequested)(GameApplication* This, GameFrameworkSystem*);
		void(__thiscall* shutdown)(GameApplication* This, GameFrameworkSystem*);
		void(__thiscall* updateTime)(GameApplication* This, float);
		void(__thiscall* render)(GameApplication* This, GraphicsCommandWriter*);
		bool(__thiscall* processInputEvent)(GameApplication* This, InputEvent*);
	};
};
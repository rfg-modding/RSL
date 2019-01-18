#pragma once
#include "KeenNamespace.h"

namespace keen
{
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
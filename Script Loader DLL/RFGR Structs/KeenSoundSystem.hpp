#pragma once
#include "KeenNamespace.h"

namespace keen
{
	namespace SoundSystem
	{
		/* 501 */
		enum Command
		{
			Command_Nop = 0x0,
			Command_FadeVolume = 0x1,
			Command_PitchBend = 0x2,
			Command_FadeoutAndStop = 0x3,
		};

		struct SoundProviderVtbl;
		/* 2900 */
		struct SoundProvider
		{
			SoundProviderVtbl *vfptr;
		};

		/* 2903 */
		struct ParameterAutomation
		{
			ParameterAutomation *pNext;
			keen::SoundSystem::Command command;
			bool init;
			float targetValue;
			float velocity;
		};

		/* 2904 */
		struct BaseSound
		{
			keen::float3 position;
			unsigned __int16 runCountAndFlags;
			char pauseGroup;
			char voiceIndex;
			float volume;
			float pitch;
			keen::SoundDefinitionResourceHandleType* definition;
			keen::SoundFileData* pSoundFileData;
			unsigned int startTimeInms;
			keen::SoundSystem::ParameterAutomation* pAutomation;
			float initialVolume;
			float initialPitch;
		};

		/* 2905 */
		struct VoiceSound
		{
			char m_providerType;
			char m_runFlags;
			void *m_pProviderData;
			keen::SoundSystem::BaseSound *m_pBaseSound;
		};

		/* 2911 */
		struct VolumeDefinition
		{
			float currentValue;
			float targetValue;
			float speed;
		};

		/* 2912 */
		struct BusDefinition
		{
			int targetBusses[4];
		};

		/* 2913 */
		struct BusImplementation
		{
			keen::SoundSystem::VolumeDefinition gain;
			keen::SoundSystem::VolumeDefinition drySendVolumes[4];
			keen::SoundSystem::VolumeDefinition wetSendVolumes[4];
			keen::SoundSystem::BusDefinition definition;
			keen::SoundSystem::VolumeDefinition duckingGain;
			unsigned int effectIndices[4];
		};

		/* 2914 */
		struct EffectStorage
		{
			float gain;
			unsigned int effectId;
			char opaqueParameterData[128];
			void *pPlatformData;
		};

		/* 2924 */
		struct __declspec(align(4)) Systembase
		{
			keen::SoundSystem::SoundProvider *soundProviders[8];
			keen::Matrix43 listenerMatrix;
			keen::Matrix43 inverseListenerMatrix;
			int nextPauseGroup;
			unsigned int allocatedPauseGroups[1];
			keen::RandomNumberGenerator randomNumberGenerator;
			keen::Array<keen::SoundSystem::BaseSound> sounds;
			keen::Array<keen::SoundSystem::VoiceSound> voiceSounds;
			unsigned int currentTimeInms;
			keen::Array<keen::SoundSystem::ParameterAutomation> automations;
			unsigned int busCount;
			keen::SoundSystem::BusImplementation busses[30];
			keen::SoundSystem::EffectStorage effects[16];
			keen::Array<keen::SoundSystem::TemporarySoundDefinition> tempSoundDefinitions;
			keen::Array<keen::SoundSystem::SoundTriggerMemory> repetitionMemory;
			bool soundOutputDisabled;
		};

		/* 2928 */
		struct SoundVoiceManagerXAudio2
		{
			keen::Array<keen::SoundSystem::SoundVoiceXAudio2> m_voices;
			IXAudio2 *m_pXAudioDevice;
		};

		/* 2929 */
		struct SoundProviderWaveXAudio2 : keen::SoundSystem::SoundProvider
		{
			keen::SoundSystem::SoundVoiceManagerXAudio2 *m_pVoiceManager;
			unsigned int m_providerId;
		};

		/* 2931 */
		struct SoundSystemEngineCallback : IXAudio2EngineCallback
		{
			keen::SoundSystem::SystemXaudio2 *m_pSystem;
		};

		/* 2930 */
		struct __declspec(align(4)) SystemXaudio2
		{
			IXAudio2 *pAudioDevice;
			IXAudio2MasteringVoice *pMasteringVoice;
			keen::SoundSystem::SoundVoiceManagerXAudio2 voiceManager;
			keen::SoundSystem::SoundProviderWaveXAudio2 waveProvider;
			keen::SoundSystem::SoundSystemEngineCallback callbackWrapper;
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

		/* 2932 */
		struct SoundProviderNull : SoundProvider
		{

		};

		/* 2906 */
		struct System : Systembase
		{
			keen::SoundSystem::SystemXaudio2 xaudio2State;
			keen::SoundSystem::SoundProviderNull nullProvider;
			keen::SingleLinkedInternalList<keen::SoundDeviceChangedCallback, keen::SoundDeviceChangedCallback *, 4> deviceChangedCallbacks;
		};

		/* 2907 */
		struct SoundProviderVtbl
		{
			void *(__thiscall *__vecDelDtor)(keen::SoundSystem::SoundProvider *this, unsigned int);
			bool(__thiscall *startSound)(keen::SoundSystem::SoundProvider *this, keen::SoundSystem::VoiceSound *, float, unsigned int, keen::SoundSystem::System *);
			void(__thiscall *stopSound)(keen::SoundSystem::SoundProvider *this, keen::SoundSystem::VoiceSound *, keen::SoundSystem::System *);
			void(__thiscall *pauseSound)(keen::SoundSystem::SoundProvider *this, keen::SoundSystem::VoiceSound *);
			void(__thiscall *resumeSound)(keen::SoundSystem::SoundProvider *this, keen::SoundSystem::VoiceSound *);
			int(__thiscall *getNumAllocatedElements)(keen::SoundSystem::SoundProvider *this);
		};

		/* 2916 */
		struct SoundFileEntry
		{
			float chance;
			keen::SoundFileHandleType *soundFile;
		};

		/* 2918 */
		const struct SoundDefinition
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
			keen::StaticArray<keen::SoundSystem::SoundFileEntry> soundFiles;
		};

		/* 2920 */
		struct TemporarySoundDefinition : keen::SoundDefinitionResource
		{
			bool m_inUse;
			keen::SoundSystem::SoundDefinition m_data;
			keen::SoundSystem::SoundFileEntry m_soundFiles[1];
		};

		/* 2922 */
		struct SoundTriggerMemory
		{
			keen::SoundSystem::SoundDefinition *pSoundDefinition;
			unsigned int lastTriggerTimeInms;
			char lastTriggeredIndex[8];
		};

		/* 2925 */
		struct Voice
		{
			IXAudio2SourceVoice *pSourceVoice;
			bool running;
			bool paused;
			unsigned int stopTimer;
		};

		/* 2926 */
		struct __declspec(align(4)) SoundVoiceXAudio2
		{
			keen::SoundSystem::Voice m_voice;
			unsigned int m_currentPositionInMs;
			keen::SoundFileData *m_pSoundFile;
			unsigned int m_flags;
			bool m_looped;
			char m_busIndex;
		};
	}

	/* 2901 */
	const struct SoundDefinitionResourceHandleType
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

	/* 2908 */
	struct Array_BaseSound
	{
		keen::SoundSystem::BaseSound *m_pData;
		unsigned int m_size;
	};

	/* 2909 */
	struct Array_VoiceSound
	{
		keen::SoundSystem::VoiceSound *m_pData;
		unsigned int m_size;
	};

	/* 2910 */
	struct Array_ParameterAutomation
	{
		keen::SoundSystem::ParameterAutomation *m_pData;
		unsigned int m_size;
	};

	/* 2921 */
	struct Array_TemporarySoundDefinition
	{
		keen::SoundSystem::TemporarySoundDefinition *m_pData;
		unsigned int m_size;
	};

	/* 2923 */
	struct Array_SoundTriggerMemory
	{
		keen::SoundSystem::SoundTriggerMemory *m_pData;
		unsigned int m_size;
	};

	/* 2927 */
	struct Array_SoundVoiceXAudio2
	{
		keen::SoundSystem::SoundVoiceXAudio2 *m_pData;
		unsigned int m_size;
	};

	struct SoundDeviceChangedCallbackVtbl;
	/* 2933 */
	struct SoundDeviceChangedCallback
	{
		keen::SoundDeviceChangedCallbackVtbl *vfptr;
		keen::SoundDeviceChangedCallback *m_pNext;
	};

	/* 2936 */
	struct keen::SoundDeviceChangedCallbackVtbl
	{
		void(__thiscall *handleAboutToDestroyMasteringVoice)(keen::SoundDeviceChangedCallback *This, keen::SoundSystem::System *);
		void(__thiscall *handleMasteringVoiceCreated)(keen::SoundDeviceChangedCallback *This, keen::SoundSystem::System *);
	};


	/* 2934 */
	struct SingleLinkedInternalList_SoundDeviceChangedCallback_SoundDeviceChangedCallback_4_Iterator
	{
		keen::SoundDeviceChangedCallback *m_pCurrent;
	};

	/* 2935 */
	struct SingleLinkedInternalList_SoundDeviceChangedCallback_SoundDeviceChangedCallback_4
	{
		keen::SoundDeviceChangedCallback *m_pFirst;
		SingleLinkedInternalList_SoundDeviceChangedCallback_SoundDeviceChangedCallback_4_Iterator m_begin;
		SingleLinkedInternalList_SoundDeviceChangedCallback_SoundDeviceChangedCallback_4_Iterator m_end;
	};

	/* 2915 */
	const struct SoundFileHandleType
	{

	};

	/* 2917 */
	struct StaticArray_SoundFileEntry
	{
		keen::SoundSystem::SoundFileEntry *m_pData;
		unsigned int m_size;
	};

	/* 2410 */
	struct Resource
	{
		unsigned __int16 m_flags;
		char m_tag;
		char m_unused;
		unsigned int m_key;
	};

	/* 2919 */
	struct SoundDefinitionResource : keen::Resource
	{
		keen::SoundSystem::SoundDefinition *m_pData;
	};

	/* 2933 */
	struct SoundDeviceChangedCallback
	{
		keen::SoundDeviceChangedCallbackVtbl *vfptr;
		keen::SoundDeviceChangedCallback *m_pNext;
	};

	/* 2936 */
	struct SoundDeviceChangedCallbackVtbl
	{
		void(__thiscall *handleAboutToDestroyMasteringVoice)(keen::SoundDeviceChangedCallback *This, keen::SoundSystem::System *);
		void(__thiscall *handleMasteringVoiceCreated)(keen::SoundDeviceChangedCallback *This, keen::SoundSystem::System *);
	};

	/* SOUND SYSTEM END*/
};
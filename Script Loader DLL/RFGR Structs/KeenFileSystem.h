#pragma once
//#include "KeenNamespace.h"

namespace keen
{
	/* 55 */
	enum IoError
	{
		IoError_Ok = 0x0,
		IoError_Generic = 0x1,
		IoError_CompressionError = 0x2,
		IoError_DecompressionError = 0x3,
		IoError_ReadError = 0x4,
		IoError_WriteError = 0x5,
		IoError_NotImplemented = 0x6,
		IoError_EofReached = 0x7,
		IoError_InvalidState = 0x8,
		IoError_FileNotFound = 0x9,
		IoError_InvalidPosition = 0xA,
		IoError_NoPermission = 0xB,
		IoError_NoConnection = 0xC,
		IoError_TimeOut = 0xD,
		IoError_InvalidArgument = 0xE,
		IoError_OutOfMemory = 0xF,
		IoError_AlreadyExists = 0x10,
		IoError_NotSupported = 0x11,
		IoError_Count = 0x12,
	};

	/* 2408 */
	struct AutoMemoryBlock : keen::MemoryBlock
	{
		keen::MemoryAllocator *m_pAllocator;
	};

	/* 2409 */
	struct ResourceFactory
	{
		keen::ResourceFactoryVtbl *vfptr;
		keen::ResourceFactory *m_pNextRegisteredFactory;
	};

	/* 2410 */
	struct Resource
	{
		unsigned __int16 m_flags;
		char m_tag;
		char m_unused;
		unsigned int m_key;
	};

	/* 2411 */
	struct ResourceFactoryVtbl
	{
		void *(__thiscall *__vecDelDtor)(keen::ResourceFactory* This, unsigned int);
		char gap4[4];
		keen::Resource *(__thiscall *createResource)(keen::ResourceFactory* This, keen::MemoryAllocator *, unsigned int);
		void(__thiscall *destroyResource)(keen::ResourceFactory* This, keen::MemoryAllocator *, keen::Resource *);
		bool(__thiscall *unlockAllResources)(keen::ResourceFactory* This, unsigned int);
		bool(__thiscall *initializeResource)(keen::ResourceFactory* This, keen::Resource *, unsigned int, const void *, unsigned int);
		void(__thiscall *postInitializeResource)(keen::ResourceFactory* This, keen::Resource *);
		void(__thiscall *shutdownResource)(keen::ResourceFactory* This, keen::Resource *);
		bool(__thiscall *createEmergencyResource)(keen::ResourceFactory* This, keen::Resource *, const char *);
	};

	/* 2412 */
	struct  SequenceFactory : keen::ResourceFactory
	{

	};

	/* 2413 */
	struct __declspec(align(4)) FileSystemCreationParameters
	{
		unsigned int maxDeviceCount;
		unsigned int maxMountPoints;
		unsigned int maxNativeStreamCount;
		unsigned int maxMemoryStreamCount;
		unsigned int maxMemoryFileCount;
		unsigned int maxPakStreamCount;
		unsigned int maxAliasStreamCount;
		unsigned int maxPakFileSize;
		unsigned int nativeThreadBufferSize;
		bool enableDefaultMount;
		bool useReadThreads;
	};

	/* 2401 */
	struct SequenceEventData
	{
		unsigned short time;
		unsigned short type;
		const void* pData;
	};

	/* 2402 */
	struct StaticArray_SequenceEventData
	{
		SequenceEventData* m_pData;
		unsigned int m_size;
	};

	/* 2403 */
	const struct __declspec(align(2)) SequenceData
	{
		StaticArray_SequenceEventData events;
		unsigned short length;
		bool mustComplete;
	};

	/* 2414 */
	struct SequenceInitializationData
	{
		keen::SequenceData *pSequenceData;
	};

	/* 2416 */
	struct PoolAllocator_FileSystemDeviceEntry
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2417 */
	struct PoolAllocator_FileSystemMountPoint
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2418 */
	struct PoolAllocator_NativeFileDevice_FileStreamData
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2419 */
	struct FileStreamAllocator_NativeFileDevice_FileStreamData
	{
		keen::PoolAllocator_NativeFileDevice_FileStreamData m_streamAllocator;
		keen::Mutex m_streamMutex;
	};

	/* 2422 */
	struct Event
	{
		void *m_eventHandle;
	};

	/* 2392 */
	struct FileDeviceInterface
	{
		void* vfptr; //FileDeviceInterfaceVtbl* vfptr;
	};

	/* 2400 */
	/*struct FileDeviceInterfaceVtbl
	{
		void* (__thiscall* __vecDelDtor)(FileDeviceInterface* This, unsigned int);
		_BYTE gap4[4];
		IoError(__thiscall* closeFile)(FileDeviceInterface* This, unsigned __int16);
		IoError(__thiscall* freeMountData)(FileDeviceInterface* This, MemoryAllocator*, FileDeviceMountData*);
		IoResult<unsigned int>(__thiscall* read)(FileDeviceInterface* This, unsigned __int16, void*, unsigned int);
		IoResult<unsigned int>(__thiscall* write)(FileDeviceInterface* This, unsigned __int16, const void*, unsigned int);
		IoError(__thiscall* flushWriteBuffer)(FileDeviceInterface* This, unsigned __int16);
		IoResult<unsigned __int64>* (__thiscall* getSize)(FileDeviceInterface* This, IoResult<unsigned __int64>* result, unsigned __int16);
		IoError(__thiscall* setPosition)(FileDeviceInterface* This, unsigned __int16, unsigned __int64);
		IoResult<unsigned __int64>* (__thiscall* getPosition)(FileDeviceInterface* This, IoResult<unsigned __int64>* result, unsigned __int16);
		IoError(__thiscall* setFilePermissionByName)(FileDeviceInterface* This, FileDeviceMountData*, const char*, bool);
		IoError(__thiscall* getFileStatusByName)(FileDeviceInterface* This, FileStatus*, FileDeviceMountData*, const char*, unsigned int);
		bool(__thiscall* getNativeFilePath)(FileDeviceInterface* This, char*, unsigned int, FileDeviceMountData*, const char*);
	};*/

	/* 2393 */
	struct IoResult_unsigned_short
	{
		unsigned __int16 result;
		IoError error;
	};

	/* 2424 */
	struct Array_NativeFileDevice_ReadThreadContext
	{
		keen::NativeFileDevice::ReadThreadContext *m_pData;
		unsigned int m_size;
	};

	/* 2425 */
	struct  __declspec(align(4)) NativeFileDevice : keen::FileDeviceInterface
	{
		/* 2421 */
		struct __declspec(align(8)) ReadBuffer
		{
			keen::MemoryBlock data;
			unsigned __int64 filePosition;
			unsigned int size;
			unsigned int readOffset;
			keen::IoError result;
		};

		/* 2423 */
		struct ReadThreadContext
		{
			keen::Thread thread;
			keen::NativeFileDevice::ReadBuffer buffers[2];
			keen::Event bufferEmpty;
			keen::Event bufferFilled;
			unsigned int bufferReadIndex;
			unsigned int bufferWriteIndex;
			bool hasBuffer;
			void *fileHandle;
			unsigned __int64 filePosition;
			unsigned __int64 fileSize;
		};

		keen::FileStreamAllocator_NativeFileDevice_FileStreamData m_streams;
		keen::Array_NativeFileDevice_ReadThreadContext m_readThreadContexts;
		keen::Mutex m_mutex;
		bool m_useReadThread;
	};

	/* 2426 */
	struct PoolAllocator_MemoryFileDevice_StreamEntry
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2427 */
	struct FileStreamAllocator_MemoryFileDevice_StreamEntry
	{
		keen::PoolAllocator_MemoryFileDevice_StreamEntry m_streamAllocator;
		keen::Mutex m_streamMutex;
	};

	/* 2394 */
	const struct FileDeviceMountData
	{

	};

	/* 2428 */
	struct  MemoryFileDeviceMountData : keen::FileDeviceMountData
	{
		keen::MemoryAllocator *pAllocator;
		unsigned int fileHandle;
	};

	/* 2430 */
	struct Array_MemoryFileDevice_FileEntry
	{
		keen::MemoryFileDevice::FileEntry *m_pData;
		unsigned int m_size;
	};

	/* 2431 */
	struct SizedArray_unsigned_int
	{
		unsigned int *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 2432 */
	struct IndexArray
	{
		keen::SizedArray_unsigned_int m_indices;
	};

	/* 2433 */
	struct  MemoryFileDevice : keen::FileDeviceInterface
	{
		/* 2429 */
		struct __declspec(align(4)) FileEntry
		{
			keen::MemoryFileDeviceMountData *pMountData;
			keen::MemoryBlock memoryBlock;
			unsigned int fileSize;
			unsigned int openCount;
			unsigned int fileNameCrc;
			bool isWritten;
			bool isWriteable;
		};

		keen::FileStreamAllocator_MemoryFileDevice_StreamEntry m_streams;
		keen::Array_MemoryFileDevice_FileEntry m_files;
		keen::IndexArray m_fileIndices;
	};

	/* 2434 */
	struct PoolAllocator_PakFileDevice_PakFileStream
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2435 */
	struct FileStreamAllocator_PakFileDevice_PakFileStream
	{
		keen::PoolAllocator_PakFileDevice_PakFileStream m_streamAllocator;
		keen::Mutex m_streamMutex;
	};

	/* 2436 */
	struct TlsfAllocator
	{
		keen::MemoryBlock m_memoryBlock;
		void *m_pPool;
	};

	/* 2437 */
	struct  BaseMemoryAllocator_TlsfAllocator : keen::MemoryAllocator
	{
		keen::Mutex m_mutex;
		char m_name[128];
		keen::TlsfAllocator m_allocator;
		keen::MemoryBlock m_memoryBlock;
		unsigned int m_allocatedSize;
		unsigned int m_maxAllocatedSize;
		unsigned int m_allocationCount;
		unsigned int m_flags;
	};

	/* 2438 */
	struct  TlsfMemoryAllocator : keen::BaseMemoryAllocator_TlsfAllocator
	{
	};

	/* 2439 */
	struct  PakFileDevice : keen::FileDeviceInterface
	{
		keen::FileStreamAllocator_PakFileDevice_PakFileStream m_streams;
		keen::TlsfMemoryAllocator m_chunkAllocator;
	};

	/* 2440 */
	struct PoolAllocator_AliasPathFileDevice_StreamEntry
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2441 */
	struct FileStreamAllocator_AliasPathFileDevice_StreamEntry
	{
		keen::PoolAllocator_AliasPathFileDevice_StreamEntry m_streamAllocator;
		keen::Mutex m_streamMutex;
	};

	/* 2442 */
	struct  AliasPathFileDevice : keen::FileDeviceInterface
	{
		keen::FileStreamAllocator_AliasPathFileDevice_StreamEntry m_streams;
	};

	/* 2444 */
	struct TreeNode_FileSystemMountPoint
	{
		keen::FileSystemMountPoint *pNextSibling;
		keen::FileSystemMountPoint *pPrevSibling;
		keen::FileSystemMountPoint *pParent;
		keen::FileSystemMountPoint *pFirstChild;
	};

	/* 2443 */
	struct  FileSystemMountPoint : keen::TreeNode_FileSystemMountPoint
	{
		char path[128];
		keen::FileSystemDeviceEntry *pFirstDevice;
	};

	/* 2446 */
	struct ListEntry_FileSystemDeviceEntry
	{
		keen::FileSystemDeviceEntry *pNext;
		keen::FileSystemDeviceEntry *pPrev;
	};

	/* 2445 */
	struct  __declspec(align(4)) FileSystemDeviceEntry : keen::ListEntry_FileSystemDeviceEntry
	{
		keen::FileDeviceMountData *pMountData;
		keen::FileDeviceInterface *pDevice;
		bool isInternalDevice;
	};

	/* 2447 */
	struct __declspec(align(4)) FileSystem
	{
		keen::PoolAllocator_FileSystemDeviceEntry devices;
		keen::PoolAllocator_FileSystemMountPoint mountPoints;
		keen::NativeFileDevice nativeFileDevice;
		keen::MemoryFileDevice memoryFileDevice;
		keen::PakFileDevice pakFileDevice;
		keen::AliasPathFileDevice aliasPathFileDevice;
		keen::FileSystemMountPoint *pRootPoint;
		unsigned int nativeMountHandle;
		keen::Mutex mutex;
		unsigned int openFileStack;
		keen::MemoryAllocator *pAllocator;
		volatile unsigned int useIo;
		bool ignoreFirstChild;
	};
};
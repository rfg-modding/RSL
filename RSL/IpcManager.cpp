#include "IpcManager.h"
#include <aclapi.h>

IpcManager::IpcManager()
{

}

IpcManager::~IpcManager()
{

}

void IpcManager::StartIpcThread()
{
    static uint PipesThreadCount = 0;
    if (PipesThreadCount > 0)
    {
        Logger::LogWarning("Attempted to start more than one IPC thread!\n");
        return;
    }
    PipesThreadCount++;

    IpcThread = std::thread(&IpcManager::Run, this);
}

void IpcManager::Run()
{
    Logger::Log("\n");
    Logger::Log("IPC thread started.\n");

    Logger::Log("Creating RSLMainPipe\n");
    auto SecurityAttributes = CreateEveryoneSecurityAttribute();
    HANDLE RslMainPipe = CreateNamedPipeA(TEXT("\\\\.\\pipe\\RSLMainPipe"), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        0,
        0,
        0,
        &SecurityAttributes);

    if (RslMainPipe == nullptr || RslMainPipe == INVALID_HANDLE_VALUE)
    {
        Logger::LogError("Failed to create RSLMainPipe. Last win32 error: {0}\n", Globals::GetLastWin32ErrorAsString());
        return;
    }

    Logger::Log("Waiting for a client to connect to RSLMainPipe.\n");
    bool ConnectResult = ConnectNamedPipe(RslMainPipe, nullptr);
    if(!ConnectResult)
    {
        Logger::LogError("RSLMainPipe failed to make a connection with a client. Last win32 error: {0}\n", Globals::GetLastWin32ErrorAsString());
        CloseHandle(RslMainPipe);
        return;
    }

    float InputBuffer[3]; //Enough to hold 3 floats / 1 vec3f
    DWORD NumBytesRead;
    while(true)
    {
        bool ReadResult = ReadFile(RslMainPipe,
            InputBuffer,
            12,
            &NumBytesRead,
            nullptr);

        if(ReadResult)
        {
            vector pos { InputBuffer[0], InputBuffer[1], InputBuffer[2] };

            Logger::Log("Read data from pipe!\n");
            Logger::Log("Num bytes read: {0}\n", NumBytesRead);
            Logger::Log("Data:: x: {0}, y: {1}, z: {2} ... Attempting to teleport the player to that location.\n",
                InputBuffer[0], InputBuffer[1], InputBuffer[2]);

            if(Globals::PlayerPtr)
            {
                //Todo: Make a function to check for valid/reasonable positions
                //Todo: Make some kind of event system/class to avoid needing to do this and having tons of globals laying around
                Globals::PlayerTeleportPos = pos;
                Globals::PlayerNeedsTeleport = true;
                //HumanTeleportUnsafe(Globals::PlayerPtr, pos, Globals::PlayerPtr->Orientation);
                Logger::Log("Teleported player to {0}", pos.GetDataString(false, true));
            }
            else
            {
                Logger::LogError("Cannot teleport the player as the player ptr is null. Ensure that you have a save loaded.\n");
            }
        }
    }
    //Todo: Add exit condition for loop. Though the thread dying when the game closes might be enough for this.
    CloseHandle(RslMainPipe);
    Logger::Log("IPC thread exited.\n");
}

//This function is a slightly modified of this SO answer: https://stackoverflow.com/a/48175136
SECURITY_ATTRIBUTES IpcManager::CreateEveryoneSecurityAttribute()
{
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
    PSID everyone_sid = NULL;
    AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID,
        0, 0, 0, 0, 0, 0, 0, &everyone_sid);

    EXPLICIT_ACCESS ea;
    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
    ea.grfAccessPermissions = SPECIFIC_RIGHTS_ALL | STANDARD_RIGHTS_ALL;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance = NO_INHERITANCE;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea.Trustee.ptstrName = static_cast<LPSTR>(everyone_sid);

    PACL acl = NULL;
    SetEntriesInAcl(1, &ea, NULL, &acl);

    auto sd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR,
        SECURITY_DESCRIPTOR_MIN_LENGTH);
    InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(sd, TRUE, acl, FALSE);

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = sd;
    sa.bInheritHandle = false;
    return sa;
}

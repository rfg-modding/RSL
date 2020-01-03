#include "Patching.h"
#include "IpcManager.h"
#include "ISnippetManager.h"
#include "SnippetManager.h"

namespace Patching
{
    void LockGameMain()
    {
        auto SnippetManager = IocContainer->resolve<ISnippetManager>();
        //.text:019D0E80 rfg.exe:$810E80 #810280 <WinMain>
        DWORD RFGWinMainAddress = Globals::FindPattern("rfg.exe", "\x8B\x4C\x24\x3C\x53\x33\xDB\xBA", "xxxxxxxx");
        std::vector<int> NewOpcodes{ NOP, JMP_REL8, 0xFD, NOP };

        SnippetManager->ReplaceSnippet("RFG WinMain", RFGWinMainAddress, NewOpcodes);
    }

    void UnlockGameMain()
    {
        auto SnippetManager = IocContainer->resolve<ISnippetManager>();
        SnippetManager->RestoreSnippet("RFG WinMain", true);
    }
}

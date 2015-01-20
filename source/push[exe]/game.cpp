#include <sl.h>
#include <wchar.h>

#include "game.h"
#include "push.h"
#include "ini.h"


#define GAME_INSTALL_PATH L"InstallPath"


PushGame::PushGame( WCHAR* Game )
{
    // Allocate some memory for the game name
    GameWin32Name = (WCHAR*) RtlAllocateHeap(
        PushHeapHandle,
        0,
        (SlStringGetLength(Game) + 1) * sizeof(WCHAR)
        );

    // Save new batchfile name
    wcscpy(GameWin32Name, Game);

}


WCHAR*
PushGame::GetName()
{
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);
    
    return IniReadSubKey(L"Game Settings", gameId, L"Name");
}


VOID
PushGame::SetName( WCHAR* Name )
{
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);

    IniWriteSubKey(L"Game Settings", gameId, L"Name", Name);
}


WCHAR*
PushGame::GetInstallPath()
{
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);

    return IniReadSubKey(L"Game Settings", gameId, GAME_INSTALL_PATH);
}


VOID
PushGame::SetInstallPath( WCHAR* Path )
{
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);

    IniWriteSubKey(L"Game Settings", gameId, GAME_INSTALL_PATH, Path);
}


DWORD
PushGame::GetFlags()
{
    DWORD flags = 0;
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);

    // Need ramdisk?
    if (IniReadSubKeyBoolean(L"Game Settings", gameId, L"UseRamDisk", FALSE))
        flags |= GAME_RAMDISK;

    //check for forced vsync
    if (IniReadSubKeyBoolean(L"Game Settings", gameId, L"ForceVsync", FALSE))
        flags |= GAME_VSYNC;

    //check for key repeat
    if (IniReadSubKeyBoolean(L"Game Settings", gameId, L"DisableRepeatKeys", FALSE))
        flags |= GAME_REPEAT_KEYS;

    // Check if user wants to emulate arrow keys with WASD keys
    if (IniReadSubKeyBoolean(L"Game Settings", gameId, L"SwapWASD", FALSE))
        flags |= GAME_WASD;

    return flags;
}


VOID
PushGame::SetFlags( DWORD Flags )
{
    WCHAR* gameId;

    gameId = IniReadString(L"Games", GameWin32Name, NULL);

    if (Flags & GAME_RAMDISK)
        IniWriteSubKey(L"Game Settings", gameId, L"UseRamDisk", L"True");
}
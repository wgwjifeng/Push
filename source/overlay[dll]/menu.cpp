#include <windows.h>
#include <OvRender.h>
#include <sloverlay.h>


SlOverlayMenu* MnuMenu;

MenuVars MnuOsd[20];
MenuVars MnuCache[10];

WCHAR* GroupOpt[] = {L"", L""};
WCHAR* ItemOpt[] = {L"Off", L"On"};

BOOLEAN MnuInitialized;


//Add menu items to menu

VOID
AddItems()
{
	MnuMenu->AddGroup(L"OSD", GroupOpt, &MnuOsd[0].Var);

	if (MnuOsd[0].Var)
	{
		MnuMenu->AddItem(L"GPU Core utilization",    ItemOpt, &MnuOsd[1].Var);
		MnuMenu->AddItem(L"GPU Core temperature",    ItemOpt, &MnuOsd[2].Var);
		MnuMenu->AddItem(L"GPU Engine Clock",        ItemOpt, &MnuOsd[3].Var);
		MnuMenu->AddItem(L"GPU Memory Clock",        ItemOpt, &MnuOsd[4].Var);
		MnuMenu->AddItem(L"GPU VRAM usage",          ItemOpt, &MnuOsd[5].Var);
		MnuMenu->AddItem(L"CPU utilization",         ItemOpt, &MnuOsd[6].Var);
		MnuMenu->AddItem(L"CPU temperature",         ItemOpt, &MnuOsd[7].Var);
		MnuMenu->AddItem(L"RAM usage",               ItemOpt, &MnuOsd[8].Var);
		MnuMenu->AddItem(L"Max core usage",          ItemOpt, &MnuOsd[9].Var);
		MnuMenu->AddItem(L"Max thread usage",        ItemOpt, &MnuOsd[10].Var);
		MnuMenu->AddItem(L"Disk read-write rate",    ItemOpt, &MnuOsd[11].Var);
		MnuMenu->AddItem(L"Disk response time",      ItemOpt, &MnuOsd[12].Var);
		MnuMenu->AddItem(L"Frame Buffer count",      ItemOpt, &MnuOsd[13].Var);
		MnuMenu->AddItem(L"Show Time",               ItemOpt, &MnuOsd[14].Var);
	}

	MnuMenu->AddGroup(L"CACHE", GroupOpt, &MnuCache[0].Var);

	if (MnuCache[0].Var)
	{
		MnuMenu->AddItem(L"NULL", ItemOpt, &MnuCache[1].Var);
		MnuMenu->AddItem(L"NULL", ItemOpt, &MnuCache[2].Var);
		MnuMenu->AddItem(L"NULL", ItemOpt, &MnuCache[3].Var);
		MnuMenu->AddItem(L"NULL", ItemOpt, &MnuCache[4].Var);
	}
}


VOID
MnuRender( OvOverlay* Overlay )
{
    if (!MnuInitialized)
    {
        MnuMenu = new SlOverlayMenu(300);
        MnuInitialized = TRUE;
    }

    if( MnuMenu->mSet.MaxItems == 0 )
		AddItems();

	//Call drawing and navigation functions
	MnuMenu->Render(100, 200, Overlay);
	MnuMenu->Navigate();
}

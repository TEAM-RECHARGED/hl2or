"GameMenu"
{
	"1"
	{
		"label" "#GameUI_GameMenu_ResumeGame"
		"command" "ResumeGame"
		"OnlyInGame" "1"
	}
	"2"
	{
		"label" "#GameUI_GameMenu_MAINMENU2"
		"command" "disconnect"
		"OnlyInGame" "1"
	}
	"3"
	{
		"label" "#GameUI_GameMenu_NewGame"
		"command" "OpenNewGameDialog"
		"notmulti" "1"
	}
	"4"
	{
		"label" "#GameUI_GameMenu_LoadGame"
		"command" "OpenLoadGameDialog"
		"notmulti" "1"
	}
	"5"
	{
		"label" "#GameUI_GameMenu_SaveGame"
		"command" "OpenSaveGameDialog"
		"notmulti" "1"
		"OnlyInGame" "1"
	}
	"6"
	{
		"label" "#GameUI_GameMenu_Options"
		"command" "OpenOptionsDialog"
	}	
	"7"
	{
		"label" "Advanced Options"
		"command" "engine ToggleAdvOptions"	
	}
	"8"
	{
		"label" "------------------------"
	}
	"9"	[$WIN32]
	{
		//"label" "#GameUI_GameMenu_BonusMaps"
		//"command" "OpenBonusMapsDialog"
		"label"	"FAST SETTINGS - OVERCHARGED"
		"command" "engine exec fastpreset/OverCharged_cfgpreset1"
		"notmulti" "1"
	}
	"10"
	{
		//"label"	"#GameUI_GameMenu_FEED"
		//"command" "engine exec Feedback"
		"label"	"FAST SETTINGS - REALISM"
		"command" "engine exec fastpreset/OverCharged_cfgpreset7"
	}
       "11"
	{
		"label"	"FAST SETTINGS - HL2 DEFAULT"
		"command" "engine exec fastpreset/OverCharged_cfgpreset8"
	}
	"12"
	{
		"label" "------------------------"
	}
	"13"
	{
		"label" "#GameUI_Controller"
		"command" "OpenControllerDialog"
		"ConsoleOnly" "1"
	}
	"14"
	{
		"label" "#GameUI_GameMenu_Quit"
		"command" "Quit"
	}
}
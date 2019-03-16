#pragma once
#include "BaseGui.h"

class TeleportGui : public BaseGui
{
public:
	TeleportGui(bool* _OpenState, std::string _Title);
	~TeleportGui();

	void Draw();

	bool LoadTeleportLocations();
	bool SaveTeleportLocations();
	/*Sets a new teleport location in the provided json object.*/
	bool SetTeleportLocation(std::string Name, float x, float y, float z, std::string Description);
	/*Changes an existing teleport location in the provided json object.*/
	bool ChangeTeleportLocation(std::string CurrentName, std::string NewName, float NewX, float NewY, float NewZ, std::string NewDescription);
	bool HumanTeleportSafe(float x, float y, float z, int TimeToHover = 5000);
	void HumanTeleportSafe(vector NewPosition, int TimeToHover = 5000);

	nlohmann::json TeleportLocations;

	bool TeleportEditPopupOpen = false;
	std::string NewTeleportName;
	vector NewTeleportPosition;
	std::string NewTeleportDescription;

	float PlayerPositionTargetArray[3] = { 0 };

	ImGuiWindowFlags WindowFlags = 0;
	ImGuiWindowFlags ModalFlags = 0;
};


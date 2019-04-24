#pragma once
#include "BaseGui.h"

class TeleportGui : public BaseGui
{
public:
	TeleportGui(bool* OpenState_, std::string Title_);
	~TeleportGui() = default;

	void Draw() override;

	bool LoadTeleportLocations();
	bool SaveTeleportLocations();
	/*Sets a new teleport location in the provided json object.*/
	bool SetTeleportLocation(std::string Name, float x, float y, float z, std::string Description);
	/*Changes an existing teleport location in the provided json object.*/
	bool ChangeTeleportLocation(std::string CurrentName, std::string NewName, float NewX, float NewY, float NewZ, std::string NewDescription);

	nlohmann::json TeleportLocations;

	bool TeleportEditPopupOpen = false;
	std::string NewTeleportName;
	vector NewTeleportPosition;
	std::string NewTeleportDescription;

	float PlayerPositionTargetArray[3] = { 0 };

	ImGuiWindowFlags WindowFlags = 0;
	ImGuiWindowFlags ModalFlags = 0;
};


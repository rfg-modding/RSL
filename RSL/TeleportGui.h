#pragma once
#include "BaseGui.h"

class TeleportGui : public BaseGui
{
public:
	TeleportGui(std::string Title_);
	~TeleportGui() = default;

	void Draw() override;
    void DrawMenuHeader();
    void DrawLocationList();
    void DrawSavePopup();

	bool LoadTeleportLocations();
	bool SaveTeleportLocations();
	/*Sets a new teleport location in the provided json object.*/
	bool SetTeleportLocation(std::string Name, float x, float y, float z, std::string Description);
	/*Changes an existing teleport location in the provided json object.*/
	bool ChangeTeleportLocation(std::string CurrentName, std::string NewName, float NewX, float NewY, float NewZ, std::string NewDescription);

private:
	nlohmann::json TeleportLocations;
	bool TeleportEditPopupOpen = false;
	std::string NewTeleportName{};
	vector NewTeleportPosition{ 0.0f };
	std::string NewTeleportDescription{};
	vector PlayerPositionTarget = { 0.0f };
	ImGuiWindowFlags ModalFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
};
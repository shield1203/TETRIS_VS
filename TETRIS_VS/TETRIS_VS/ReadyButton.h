#pragma once
class ResourceManager;
class InputSystem;
class PacketManager;

class ReadyButton
{
private:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;
	PacketManager* m_packetManager = nullptr;
public:
	void Update();

	void BackLobby();
	void PlayerReady();

	ReadyButton();
	~ReadyButton();
};


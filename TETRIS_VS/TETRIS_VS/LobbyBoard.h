#pragma once
class InputSystem;
class PacketManager;

class LobbyBoard
{
private:
	InputSystem* m_inputSystem = nullptr;
	PacketManager* m_packetManager = nullptr;
public:
	void Update();

	LobbyBoard();
	~LobbyBoard();
};


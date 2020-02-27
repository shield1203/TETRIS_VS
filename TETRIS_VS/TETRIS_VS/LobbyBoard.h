#pragma once
class InputSystem;
class PacketManager;

class LobbyBoard
{
private:
	InputSystem* m_inputSystem = nullptr;
	PacketManager* m_packetManager = nullptr;
public:
	bool m_on = false;
public:
	void Update();

	LobbyBoard();
	~LobbyBoard();
};


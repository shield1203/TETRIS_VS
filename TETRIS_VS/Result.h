#pragma once
class InputSystem;
class PacketManager;

class Result
{
private:
	PacketManager* m_packetManager = nullptr;
	InputSystem* m_inputSystem = nullptr;
public:
	bool m_win = false;
	bool m_lose = false;

	void Update();
	void BackRoom();

	Result();
	~Result();
};


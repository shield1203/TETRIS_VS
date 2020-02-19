#pragma once
class PacketManager;

class SocketManager
{
private:
	static SocketManager* Inst;
	SocketManager();
public:
	PacketManager* m_packetManager = nullptr;

	WSADATA wsadata;

	SOCKET m_sock;
	SOCKADDR_IN m_servaddr = { 0 };
public:
	static SocketManager* getInstance();

	void Recv(GAME_STEP);
	void Send(GAME_STEP);

	void CleanSocket();

	~SocketManager();
};


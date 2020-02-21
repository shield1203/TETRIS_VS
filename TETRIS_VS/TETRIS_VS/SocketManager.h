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

	int m_connect = 0;
public:
	static SocketManager* getInstance();

	SOCKET SetTCPClient();

	void Communication(GAME_STEP);
	void Recv(GAME_STEP);
	void Send(GAME_STEP);

	void CheckPacket(GAME_STEP);
	void CheckLobbyPacket();
	void CheckRoomPacket();

	void CleanSocket();

	~SocketManager();
};
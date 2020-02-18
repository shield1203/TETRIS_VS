#pragma once
class SocketManager
{
private:
	static SocketManager* Inst;
	SocketManager();
public:
	WSADATA wsadata;

	SOCKET m_sock;
	SOCKADDR_IN m_servaddr = { 0 };
public:
	static SocketManager* getInstance();

	void Recv();
	void Send();

	void CleanSocket();

	~SocketManager();
};


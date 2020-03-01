#pragma once
class ResourceManager;
class SocketManager;
class PacketManager;

class Map;
class Block;
class Result;

enum VERSUS_ENUM { VERSUS_XPOS = 39 };

class VersusPalySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
	SocketManager* m_socketManager = nullptr;
	PacketManager* m_packetManager = nullptr;

	Map* m_map = nullptr;
	Block* m_block = nullptr;
	Result* m_result = nullptr;
public:
	virtual void Init();
	virtual void Update();
	void CheckPacket();
	virtual void Render();
	virtual void Release();

	VersusPalySystem();
	~VersusPalySystem();
};


#pragma once
class PacketManager;

enum LOBBY_Selector : unsigned int { ROOM_LIST_Y = 4 };

class LobbySelector : public SelectorFrame
{
private:
	PacketManager* m_packetManager = nullptr;
	int m_selectedRoom = 0;
public:
	virtual void Init();
	virtual void Update();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void Select();

	void ListEmpty();
	void BackMenu();
	void ReqeatEnterRoom();
	void ReqestCreateRoom();

	LobbySelector();
	~LobbySelector();
};


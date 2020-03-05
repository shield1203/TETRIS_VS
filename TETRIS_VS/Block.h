#pragma once
class ResourceManager;
class InputSystem;

enum BlockEnum : unsigned int { BLOCK_START_X = 10, BLOCK_START_Y = 0, NEXT_BLOCK_X = 27, NEXT_BLOCK_Y = 3, 
	BLOCK_SHAPE = 7, BLOCK_TYPE = 4, INIT_SPEED = 400, UP_SPEED = 2 };

class Block
{
private:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;

	bool bBlock = false;
	unsigned int m_blockSpeed = 0;
	unsigned int m_nextBlockShape = 0;
	unsigned __int64 m_time = 0;
public:
	void Update();

	void CreateBlock();

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void TurnBlock();

	void MoveStraightDwon();

	void ApplyToMap();

	Block();
	~Block();
private:
	const int m_Block[BLOCK_SHAPE][BLOCK_TYPE][4][2] = { // n_Block[BlockShape][BlockType][OneBlock][X Y]
		// ■■■	0번
		// ■	
		{
			{{0, 1}, {2, 1}, {4, 1}, {0, 2}},
			{{0, 0}, {2, 0}, {2, 1}, {2, 2}},
			{{4, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {2, 1}, {2, 2}, {4, 2}}
		},
		// ■■■	1번
		//     ■	
		{
			{{0, 1}, {2, 1}, {4, 1}, {4, 2}},
			{{2, 0}, {2, 1}, {0, 2}, {2, 2}},
			{{0, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {4, 0}, {2, 1}, {2, 2}}
		},
		//   ■■	2번
		// ■■
		{
			{{2, 1}, {4, 1}, {0, 2}, {2, 2}},
			{{0, 0}, {0, 1}, {2, 1}, {2, 2}},
			{{2, 0}, {4, 0}, {0, 1}, {2, 1}},
			{{2, 0}, {2, 1}, {4, 1}, {4, 2}}
		},
		// ■■		3번
		//   ■■
		{
			{{0, 1}, {2, 1}, {2, 2}, {4, 2}},
			{{2, 0}, {0, 1}, {2, 1}, {0, 2}},
			{{0, 0}, {2, 0}, {2, 1}, {4, 1}},
			{{4, 0}, {2, 1}, {4, 1}, {2, 2}}
		},
		//   ■		4번
		// ■■■ 
		{
			{{2, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {2, 1}, {4, 1}, {2, 2}},
			{{0, 1}, {2, 1}, {4, 1}, {2, 2}},
			{{2, 0}, {0, 1}, {2, 1}, {2, 2}}
		},
		//  ■■		5번
		//  ■■ 
		{
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}}
		},
		//  ■■■■ 		6번
		{
			{{0, 1}, {2, 1}, {4, 1}, {6, 1}},
			{{4, 0}, {4, 1}, {4, 2}, {4, 3}},
			{{0, 2}, {2, 2}, {4, 2}, {6, 2}},
			{{2, 0}, {2, 1}, {2, 2}, {2, 3}}
		}
	};
	
};


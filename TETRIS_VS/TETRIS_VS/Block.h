#pragma once
class ResourceManager;
class InputSystem;

enum BlockEnum { BLOCK_START_X = 10, BLOCK_START_Y = 0, BLOCK_SHAPE = 7, BLOCK_TYPE = 4, INIT_SPEED, UP_SPEED };

class Block
{
private:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;

	bool bBlock = false;
public:
	void Update();

	void CreateBlock();

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	void DropBlock();

	bool CollisionCheck();

	void SetBlock();

	Block();
	~Block();
private:
	const int m_Block[7][4][4][2] = { // n_Block[BlockShape][BlockType][OneBlock][X Y]
		// ■ ■ ■	0번
		// ■	
		{
			{{0, 1}, {2, 1}, {4, 1}, {0, 2}},
			{{0, 0}, {2, 0}, {2, 1}, {2, 2}},
			{{4, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {2, 1}, {2, 2}, {4, 2}}
		},
		// ■ ■ ■	1번
		//     ■	
		{
			{{0, 1}, {2, 1}, {4, 1}, {4, 2}},
			{{2, 0}, {2, 1}, {0, 2}, {2, 2}},
			{{0, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {4, 0}, {2, 1}, {2, 2}}
		},
		//   ■ ■	2번
		// ■ ■
		{
			{{2, 1}, {4, 1}, {0, 2}, {2, 2}},
			{{0, 0}, {0, 1}, {2, 1}, {2, 2}},
			{{2, 0}, {4, 0}, {0, 1}, {2, 1}},
			{{2, 0}, {2, 1}, {4, 1}, {4, 2}}
		},
		// ■ ■		3번
		//   ■ ■
		{
			{{0, 1}, {2, 1}, {2, 2}, {4, 2}},
			{{2, 0}, {0, 1}, {2, 1}, {0, 2}},
			{{0, 0}, {2, 0}, {2, 1}, {4, 1}},
			{{4, 0}, {2, 1}, {4, 1}, {2, 2}}
		},
		//   ■		4번
		// ■ ■ ■ 
		{
			{{2, 0}, {0, 1}, {2, 1}, {4, 1}},
			{{2, 0}, {2, 1}, {4, 1}, {2, 2}},
			{{0, 1}, {2, 1}, {4, 1}, {2, 2}},
			{{2, 0}, {0, 1}, {2, 1}, {2, 2}}
		},
		//  ■ ■		5번
		//  ■ ■ 
		{
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}},
			{{0, 0}, {2, 0}, {0, 1}, {2, 1}}
		},
		//  ■ ■ ■ ■ 		6번
		{
			{{0, 1}, {2, 1}, {4, 1}, {6, 1}},
			{{4, 0}, {4, 1}, {4, 2}, {4, 3}},
			{{0, 2}, {2, 2}, {4, 2}, {6, 2}},
			{{2, 0}, {2, 1}, {2, 2}, {2, 3}}
		}
	};
	
};


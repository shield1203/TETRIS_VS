#pragma once

enum MENU_Selector : unsigned int { SINGLE_PLAY = 11, VERSUS_PLAY = 14, EXIT = 17, SELECTOR_Y = 3 };

class MenuSelector : public SelectorFrame
{
public:
	virtual void Init();
	virtual void Update();

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void Select();

	MenuSelector();
	~MenuSelector();
};


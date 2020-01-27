#pragma once

class SystemFrame
{
protected:
	unsigned int m_consolWidth = 0;
	unsigned int m_consolHigh = 0;
public:
	virtual void Init() {};
	virtual void LoadData() {};
	virtual void Update() {};
	virtual void Render() {};

	SystemFrame();
	~SystemFrame();
};


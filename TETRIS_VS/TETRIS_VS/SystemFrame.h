#pragma once

class SystemFrame
{
protected:
	COORD m_consoleSize;
	string m_sizeCommend;
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};

	void GetConsoleSize(COORD&);

	SystemFrame();
	~SystemFrame();
};
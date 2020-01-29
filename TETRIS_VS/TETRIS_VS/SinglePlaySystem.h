#pragma once
class SystemFrame;
class ResourceManager;

class SinglePlaySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	SinglePlaySystem();
	~SinglePlaySystem();
};


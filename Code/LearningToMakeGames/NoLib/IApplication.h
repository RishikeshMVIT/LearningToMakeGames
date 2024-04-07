#pragma once
class IApplication
{
public:
	IApplication();
	~IApplication();

	bool Start() = 0;
	void Run() = 0;
	bool Shutdown() = 0;

	void OnStartup() = 0;
	void OnShutdown() = 0;

private:
	bool isRunning = false;

};


#pragma once
#include "ProDisplayManager.h"
#include "gameApp.h"

class mainApp
{
public:
	mainApp();
	~mainApp();

	void run();
	void render();
	void start();
	void stop();

private:
	ProDisplayManager* m_displayManager;
	gameApp m_game;
	bool m_isRunning = false;
};


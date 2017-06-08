#pragma once
#include "graphics\Window.h"
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
	graphics::Window* m_window;
	gameApp m_game;
	bool m_isRunning = false;
};


#include "mainApp.h"

#include "ProTime.h"
#include "input\InputHandler.h"

#include <iostream>

using namespace graphics;
using namespace input;

mainApp::mainApp()
{
	m_window = new Window("3D Game Engine - Prometheus", 800, 600);
}

mainApp::~mainApp()
{
}

void mainApp::run()
{
	int frames = 0;
	long long frameCount = 0;

	double const  frameTime = 1.0 / 5000.0f;

	auto lastTime = ProTime::GetTime();
	double unprocessedTime = 0;


	while (m_isRunning)
	{
		bool doRender = false;

		auto newTime = ProTime::GetTime();
		auto passedTime = newTime - lastTime;
		lastTime = newTime;

		unprocessedTime += passedTime.count() / SECOND;
		frameCount += passedTime.count();

		while (unprocessedTime > frameTime)
		{
			doRender = true;

			unprocessedTime -= frameTime;

			ProTime::setDelta(frameTime);

			InputHandler::Update();
			m_game.input();
			m_game.update();

			if (InputHandler::isKeyDown(256))
				stop();

			if (frameCount >= SECOND) {
				std::cout << "FPS: " << frames << " \n";
				frames = 0;
				frameCount = 0;
			}
		}

		if (doRender) {
			render();
			frames++;
		}
	}
}

void mainApp::render()
{
	m_window->clear();
	m_game.render();
	m_window->render();
}

void mainApp::start()
{
	if (m_isRunning)
		return;

	m_isRunning = true;
	InputHandler::Init(m_window->getWindow());

	m_game.start();
	run();
}

void mainApp::stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
	m_window->close();
}
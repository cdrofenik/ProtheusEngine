#include "mainApp.h"

#include "ProTime.h"
#include "ProInputHandler.h"
#include "ProRenderUtil.h"

#include <iostream>

mainApp::mainApp()
{
	m_displayManager = new ProDisplayManager(800, 600, "3D Game Engine - Prometheus");
	ProRenderUtil::initGraphics();
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

			m_game.input();
			ProInputHandler::Update();

			m_game.update();

			if (m_displayManager->isClosed() || ProInputHandler::isKeyDown(256))
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
	ProRenderUtil::clearScreen();
	m_game.render();
	m_displayManager->Render();
}

void mainApp::start()
{
	if (m_isRunning)
		return;

	m_isRunning = true;
	ProInputHandler::Init(m_displayManager->GetWindow());

	m_game.start();
	run();
}

void mainApp::stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
	m_displayManager->Close();
}
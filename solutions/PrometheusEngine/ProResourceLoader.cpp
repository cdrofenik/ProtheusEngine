#include "ProResourceLoader.h"

#include <iostream>
#include <fstream>

std::string ProResourceLoader::GetStringFromFile(std::string filePath)
{
	std::string fileString;
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open()) {
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", filePath.c_str());
		getchar();
		return 0;
	}

	return fileString;
}

std::string ProResourceLoader::GetStringFromFile(const char* filePath)
{
	std::string fileString;
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open()) {
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", filePath);
		getchar();
		return 0;
	}

	return fileString;
}

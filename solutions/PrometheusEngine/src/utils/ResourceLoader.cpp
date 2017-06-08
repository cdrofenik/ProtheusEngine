#include "ResourceLoader.h"

#include "core\math\Vector2.hpp"

#include <vector>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <string>
#include <cstring>

using namespace math;

std::string ResourceLoader::GetStringFromFile(const char* filePath)
{
	FILE * file = fopen(filePath, "rt");
	if (file == NULL) {
		printf("[ProResourceLoader] Impossible to open the file ! Are you in the right path?\n");
		getchar();
	}
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* data = new char[length + 1];
	memset(data, 0, length + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);
	fclose(file);

	std::string fileString(data);
	delete data;
	return fileString;
}

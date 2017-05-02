#include "ProMesh.h"

#include <string>

class ProResourceLoader
{
public:
	static std::string GetStringFromFile(std::string filePath);
	static std::string GetStringFromFile(const char* filePath);

	static bool GetMeshFromFile(std::string filePath, ProMesh& outMesh);
};
#include <string>

class ProResourceLoader
{
public:
	static std::string GetStringFromFile(const std::string&filePath);
	static std::string GetStringFromFile(const char* filePath);
};
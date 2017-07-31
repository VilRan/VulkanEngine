#include "FileHelper.h"

#include <fstream>

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}

std::vector<char> FileHelper::ReadText(const std::string & filePath)
{
	std::ifstream file(filePath, std::ios::ate);
	return Read(file);
}

std::vector<char> FileHelper::ReadBinary(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);
	return Read(file);
}

std::vector<char> FileHelper::Read(std::ifstream& file)
{
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

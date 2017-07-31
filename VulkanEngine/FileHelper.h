#pragma once

#include <vector>

class FileHelper
{
public:
	FileHelper();
	virtual ~FileHelper();

	static std::vector<char> ReadText(const std::string& filePath);
	static std::vector<char> ReadBinary(const std::string& filePath);

private:
	static std::vector<char> Read(std::ifstream& file);
};


#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

class FileManager {
	public:
		int HowMuchContent(fs::path dirPath);
		int HowMannyFiles(fs::path dirPath);
		bool FileUseExtension(fs::path filePath, std::string fileExtension);
		fs::path FindFile(fs::path dirPath, std::string fileName);
		fs::recursive_directory_iterator GetIterator(fs::path dirPath);
};

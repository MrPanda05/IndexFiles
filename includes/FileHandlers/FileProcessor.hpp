#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
#include "FileManager.hpp"
namespace fs = std::filesystem;

class FileProcessor {
	private:
		fs::path _stopWordsFilePath;
		fs::path _saveFile;
		std::ifstream _stopWordFile;
		std::unordered_set<std::string> _stopSet;
		FileManager& _fileManager;
		int SearchForStopWordText();
		bool WordIsStopWord(std::string word);
		void SetWordSet();
	public:
		FileProcessor(FileManager& fileManager);
		~FileProcessor();
		int ProcessFile(fs::path path);
};
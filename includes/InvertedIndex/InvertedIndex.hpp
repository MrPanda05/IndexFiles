#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
class InvertedIndex {
	private:
		std::unordered_map<std::string, std::unordered_set<std::string>> _wordMap;
		std::unordered_map<int, std::string> _docNamesToInt;
		int _fileCount = 0;
	public:
		InvertedIndex();
		~InvertedIndex();
		void AddWord(std::string word, std::string fileName);
		void PrintMap();
		void PrintFileSet();
		std::unordered_map<std::string, std::unordered_set<std::string>>& GetMap() { return _wordMap; };
		std::unordered_map<int, std::string>& GetFileNames() { return _docNamesToInt; };
		void SetFileNames(std::unordered_map<int, std::string> fileName) { _docNamesToInt = fileName; };
		void SetWordMap(std::unordered_map<std::string, std::unordered_set<std::string>> map) { _wordMap = map; };
};




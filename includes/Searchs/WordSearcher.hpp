#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
class WordSearcher {
	private:
		std::unordered_map<std::string, std::unordered_set<std::string>>& _wordMap;
		std::vector<std::string>& _words;
		std::unordered_map<std::string, int> _fileMap;
	public:
		WordSearcher(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::vector<std::string>& words);
		std::unordered_map<std::string, int> GetFileMap() { return _fileMap; };
		int Find();
};
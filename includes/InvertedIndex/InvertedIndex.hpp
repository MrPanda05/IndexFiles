#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
class InvertedIndex {
	private:
		//std::unordered_map<std::string, std::vector<std::string>> _wordMap;
		std::unordered_map<std::string, std::unordered_set<std::string>> _wordMap;
	public:
		InvertedIndex();
		~InvertedIndex();
		void AddWord(std::string word, std::string fileName);
		void PrintMap();
		std::unordered_map<std::string, std::unordered_set<std::string>> GetMap() { return _wordMap; };
};


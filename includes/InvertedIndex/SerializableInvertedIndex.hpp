#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
struct SerializableInvertedIndex {
	public:
		std::unordered_map<std::string, std::unordered_set<int>> wordMap;
		std::unordered_map<int, std::string> docNamesToInt;
};
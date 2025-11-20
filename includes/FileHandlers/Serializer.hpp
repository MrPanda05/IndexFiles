#pragma once
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

class Serializer {
	private:
		std::unordered_set<std::string> _docNames;
	public:
		void AddDocNames(std::string name);
		void Serialize(std::unordered_map<std::string, std::unordered_set<std::string>> wordMap);
};
#include "Serializer.hpp"

void Serializer::AddDocNames(std::string name)
{
	_docNames.insert(name);
}

void Serializer::Serialize(std::unordered_map<std::string, std::unordered_set<std::string>> wordMap)
{
	std::ofstream  saveFile("index.bat", std::ios::binary);
}

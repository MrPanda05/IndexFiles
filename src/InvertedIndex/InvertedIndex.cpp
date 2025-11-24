#include "InvertedIndex.hpp"

InvertedIndex::InvertedIndex()
{
}

InvertedIndex::~InvertedIndex()
{
}

void InvertedIndex::AddWord(std::string word, std::string fileName)
{
	_wordMap[word].insert(fileName);
	bool alreadyInserted = false;
	for (const auto& pair : _docNamesToInt) {
		if (pair.second == fileName) {
			alreadyInserted = true;
			break;
		}
	}

	if (!alreadyInserted) {
		_docNamesToInt[_fileCount] = fileName;
		_fileCount++;
	}

}

void InvertedIndex::PrintMap()
{
	for (auto it = _wordMap.begin(); it != _wordMap.end(); it++)
	{
		std::cout << it->first << ": ";
		for (const auto& fileName : it->second)
		{
			std::cout << fileName << " ";
		}
		std::cout << std::endl;
	}
}

void InvertedIndex::PrintFileSet()
{
	for (auto itr = _docNamesToInt.begin(); itr != _docNamesToInt.end(); ++itr) {
		std::cout << itr->first << " " << itr->second << std::endl;
	}
}

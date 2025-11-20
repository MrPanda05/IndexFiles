#include "InvertedIndex.hpp"

InvertedIndex::InvertedIndex()
{
}

InvertedIndex::~InvertedIndex()
{
}

void InvertedIndex::AddWord(std::string word, std::string fileName)
{
	/*if (_wordMap.count(word) == 1) {
		bool foundIt = false;
		for (int i = 0; i < _wordMap[word].size(); i++) {
			if (_wordMap[word][i] == fileName) {
				foundIt = true;
			}
		}
		if (!foundIt) {
			_wordMap[word].push_back(fileName);
		}
	}
	else {
		_wordMap[word].push_back(fileName);
	}*/
	_wordMap[word].insert(fileName);

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

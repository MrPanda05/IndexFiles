#include "WordSearcher.hpp"

WordSearcher::WordSearcher(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::vector<std::string>& words): _wordMap(wordMap), _words(words)
{
}

/// <summary>
/// Como que para dada uma lista de palavras, para achar os arquivos onde toda lista aparece, prescisa satisfazer as seguintes coisas
/// 1-todas as palavras devem aparecer na lista
/// 2-A quantidade de vezes que um arquivo pareceu, deve ser igual ao tamanho da lista de palavras
/// </summary>
/// <returns></returns>
int WordSearcher::Find()
{
	for (int i = 0; i < _words.size(); i++) {
		if (_wordMap.find(_words[i]) == _wordMap.end()) return -1;
		for (std::string file : _wordMap.at(_words[i])) {
			_fileMap[file] += 1;
		}
	}
	for (auto it = _fileMap.begin(); it != _fileMap.end(); it++) {
		if (it->second == _words.size()) {
			std::cout << "A(s) palavra(s) foram achada(s)" << std::endl;
			return 1;
		}
	}

	return -1;
}

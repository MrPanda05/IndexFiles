#include <iostream>
#include <string>
#include <filesystem>
#include "FileManager.hpp"
#include "FileProcessor.hpp"
#include "InvertedIndex.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"
#include "WordSearcher.hpp"
namespace fs = std::filesystem;

enum State {
	indexing,
	searching,
	none,
	debug
};
/// <summary>
/// Inicializa o estado do programa
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="state"></param>
/// <returns></returns>
bool Initialize(int argc, char* argv[], State& state) {
	if (argc < 2) {
		std::cout << "Por favor, incluir qual modo execucao" << std::endl;
		std::cout << "Modo Indexacao: indice construir <caminho_do_diretorio>" << std::endl;
		std::cout << "Modo Busca: indice busca <termos_de_busca>" << std::endl;
		return false;
	}
	std::string firstArg = argv[1];
	if (firstArg == "debug") {
		std::cout << "Voce escolheu modo de debug" << std::endl;
		state = State::debug;
		return true;
	}
	if (firstArg != "indice") {
		std::cout << "Por favor, insira os argumentos corretamente";
		std::cout << "Modo Indexacao: indice construir <caminho_do_diretorio>" << std::endl;
		std::cout << "Modo Busca: indice busca <termos_de_busca>" << std::endl;
		return false;
	}
	if (argc < 3) {
		std::cout << "Escolha um modo valido" << std::endl;
		return false;
	}
	std::string secondArg = argv[2];
	if (secondArg != "construir" && secondArg != "busca") {
		std::cout << "Escolha um modo valido" << std::endl;
		return false;
	}
	//Todo add search here later
	if (secondArg == "construir") {
		std::cout << "Voce escolheu modo de indexacao" << std::endl;
		state = State::indexing;
		return true;
	}
	if (secondArg == "busca") {
		std::cout << "Voce escolheu modo de busca" << std::endl;
		state = State::searching;
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	State currentState = State::none;
	if (!Initialize(argc, argv, currentState)) return -1;
	FileManager* fileMan = new FileManager();
	

	if (currentState == State::indexing) {
		if (argc < 4) {
			std::cout << "Por favor, inserir caminho valido" << std::endl;
			return -1;
		}
		fs::path pathToFolder(argv[3]);
		if (!fs::exists(pathToFolder)) {
			std::cout << "Por favor, inserir caminho valido" << std::endl;
			return -1;
		}
		//std::cout << pathToFolder << std::endl
		//	<< "has " << fileMan->HowMannyFiles(pathToFolder) << " files";

		FileProcessor* filePross = new FileProcessor(*fileMan);
		filePross->ProcessFile(pathToFolder);
		delete filePross;
		return 1;
	}
	if (currentState == State::searching) {
		if (argc < 4) {
			std::cout << "Por favor, inserir pelo menos uma palavra" << std::endl;
			return -1;
		}
		if (fileMan->FindFileFullName(".", "index.bat") == "") {
			std::cout << "arquivo.bat nao existe, execute em bodo de indexacao primeiro." << std::endl;
			return -1;
		}
		InvertedIndex* invIndex = new InvertedIndex();
		Deserializer* deserializer = new Deserializer();
		if (deserializer->Deserialize(*invIndex) != 1) return 1;
		std::vector<std::string> args(argv + 3, argv + argc);
		WordSearcher* wordSeacher = new WordSearcher(invIndex->GetMap(), args);
		if (wordSeacher->Find() == 1) {
			auto files = wordSeacher->GetFileMap();
			for (auto it = files.begin(); it != files.end(); it++) {
				if (it->second == args.size()) {
					std::cout << it->first << std::endl;
				}
			}
		}
		else {
			std::cout << "A(s) palavra(s) nao foram achada(s)" << std::endl;
		}
		delete invIndex;
		delete deserializer;
		delete wordSeacher;
		return 1;
	}
	if (currentState == State::debug) {
		FileProcessor* filePross = new FileProcessor(*fileMan);
		InvertedIndex* invIndex = new InvertedIndex();
		Serializer* serializer = new Serializer();
		Deserializer* deserializer = new Deserializer();
		std::cout << "Serializing" << std::endl;
		serializer->TestSerialize();
		std::cout << "Deserializing" << std::endl;
		deserializer->TestDeserialize();
		delete filePross;
		delete invIndex;
		delete serializer;
		delete deserializer;
		return 1;
	}
}
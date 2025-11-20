#include <iostream>
#include <string>
#include <filesystem>
#include "FileManager.hpp"
#include "FileProcessor.hpp"
#include "InvertedIndex.hpp"
namespace fs = std::filesystem;

enum State {
	indexing,
	searching,
	none
};

bool Initialize(int argc, char* argv[], State& state) {
	if (argc <= 1) {
		std::cout << "Por favor, incluir qual modo execucao" << std::endl;
		std::cout << "Modo Indexacao: indice construir <caminho_do_diretorio>" << std::endl;
		std::cout << "Modo Busca: indice busca <termos_de_busca>" << std::endl;
		return false;
	}
	std::string firstArg = argv[1];
	if (firstArg != "indice") {
		std::cout << "Por favor, insira os argumentos corretamente";
		std::cout << "Modo Indexacao: indice construir <caminho_do_diretorio>" << std::endl;
		std::cout << "Modo Busca: indice busca <termos_de_busca>" << std::endl;
		return false;
	}
	std::string secondArg = argv[2];
	if (secondArg != "construir" && secondArg != "buscar") {
		std::cout << "Escolha um modo valido" << std::endl;
		return false;
	}
	//Todo add search here later
	if (secondArg == "construir") {
		std::cout << "Voce escolheu modo de indexacao" << std::endl;
		state = State::indexing;
		return true;
	}
	if (secondArg == "buscar") {
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
	}
}
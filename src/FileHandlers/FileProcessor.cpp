#include "FileProcessor.hpp"
#include "InvertedIndex.hpp"
#include "Serializer.hpp"

int FileProcessor::SearchForStopWordText()
{
	_stopWordsFilePath = _fileManager.FindFile(".", "stopwords");
	if (_stopWordsFilePath != "") {
		std::cout << "Stop word file achado, vscode" << std::endl;
		_stopWordFile.open(_stopWordsFilePath);
		return 1;
	}
	_stopWordsFilePath = _fileManager.FindFile("../../../", "stopwords");
	if (_stopWordsFilePath != "") {
		std::cout << "Stop word file achado, visual studio" << std::endl;
		_stopWordFile.open(_stopWordsFilePath);
		return 1;
	}
	return 0;
}

bool FileProcessor::WordIsStopWord(std::string word)
{
	return _stopSet.count(word) > 0;
}

void FileProcessor::SetWordSet()
{
	_stopWordFile.clear();
	_stopWordFile.seekg(0);
	std::string temp;
	while (std::getline(_stopWordFile, temp)) {
		if (temp.back() == '\n') {
			temp.pop_back();
		}
		if (temp.back() == ' ') {
			temp.pop_back();
		}
		if (temp.back() == '\t') {
			temp.pop_back();
		}
		if (temp.back() == '\r') {
			temp.pop_back();
		}
		_stopSet.insert(temp);
	}
}

FileProcessor::FileProcessor(FileManager& fileManager) : _fileManager(fileManager)
{
	if (SearchForStopWordText() == 1) {
		SetWordSet();
	}
	else {
		std::cout << "Um erro ocorreu ao tentar achar o arquivo stopword.txt" << std::endl;
	}
}

FileProcessor::~FileProcessor()
{
	_stopWordFile.close();
}

int FileProcessor::ProcessFile(fs::path path)
{
	if (!_stopWordFile.is_open()) {
		std::cout << "Arquivo stop word nao existe/ ou nao foi encontrado" << std::endl;
		return 0;
	}
	std::string text;
	InvertedIndex* invIndex = new InvertedIndex();
	Serializer* serializer = new Serializer();
	for (auto const& dir_entry : _fileManager.GetIterator(path)) {
		if (!_fileManager.FileUseExtension(dir_entry.path(), ".txt")) continue;
		std::cout << "Current Book: " << dir_entry.path().stem().string() << std::endl;
		std::fstream currentFile(dir_entry.path(), std::ios::in | std::ios::out);
		std::string fileBuffer((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
		std::string newFileBuffer;
		newFileBuffer.reserve(fileBuffer.size());
		std::string temp;
		for (int i = 0; i < fileBuffer.size(); i++) {
			char currentChar = fileBuffer[i];
			if (currentChar == ' ' || currentChar == '\n') {
				if (!temp.empty()) {
					if (WordIsStopWord(temp)) {
						//std::cout << "Valid word: " << temp << std::endl;
						temp.clear();
					}
					else {
						newFileBuffer.append(temp);
						invIndex->AddWord(temp, dir_entry.path().stem().string() + dir_entry.path().extension().string());
						serializer->AddDocNames(dir_entry.path().stem().string() + dir_entry.path().extension().string());
						temp.clear();
					}
				}
				continue;
			}
			if (std::isupper(static_cast<unsigned char>(currentChar))) {
				currentChar = std::tolower(static_cast<unsigned char>(currentChar));
			}
			if (std::ispunct(static_cast<unsigned char>(currentChar))) continue;
			temp.push_back(currentChar);
		}
		if (!fs::exists("bin/ProcessFiles")) {
			fs::create_directories("bin/ProcessFiles");
		}
		fs::path outputPath = fs::path("bin/ProcessFiles") / (dir_entry.path().stem().string() + ".txt");
		std::ofstream outPutFile(outputPath);
		outPutFile << newFileBuffer;
		outPutFile.close();
		currentFile.close();
		//invIndex->PrintMap();
	}
	serializer->Serialize(invIndex->GetMap());
	delete invIndex;
	delete serializer;
	std::cout << "File processes sucessfully" << std::endl;
	return 1;
}

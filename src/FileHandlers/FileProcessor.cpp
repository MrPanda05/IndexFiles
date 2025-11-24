#include "FileProcessor.hpp"
#include "InvertedIndex.hpp"
#include "Serializer.hpp"

/// <summary>
/// Procura o stopfile.txt
/// </summary>
/// <returns></returns>
int FileProcessor::SearchForStopWordText()
{
	_stopWordsFilePath = _fileManager.FindFile(".", "stopwords");
	if (_stopWordsFilePath != "") {
		std::cout << "Stop word file achado" << std::endl;
		_stopWordFile.open(_stopWordsFilePath);
		return 1;
	}
	std::cout << "Stop word file nao achado" << std::endl;
	return 0;
}
/// <summary>
/// Check se uma palavra é stopword
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
bool FileProcessor::WordIsStopWord(std::string word)
{
	return _stopSet.count(word) > 0;
}

/// <summary>
/// Procura o index.bat
/// </summary>
/// <returns></returns>
bool FileProcessor::HasSaveFile()
{
	fs::path saveFilePath = "";
	saveFilePath = _fileManager.FindFileFullName(".", "index.bat");
	std::cout << saveFilePath << std::endl;
	if (saveFilePath != "") {
		std::cout << "Save file file achado" << std::endl;
		//_stopWordFile.open(saveFilePath);
		return true;
	}
	std::cout << "Save file file nao achado" << std::endl;
	return false;
}

/// <summary>
/// Carrega o stopword file na memoria
/// </summary>
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
/// <summary>
/// retorna caracteres sem acentos
/// </summary>
/// <param name="byte1"></param>
/// <param name="byte2"></param>
/// <returns></returns>
char FileProcessor::MapUtf8ToAscii(unsigned char byte1, unsigned char byte2)
{
	if (byte1 == 0xC3) {
		if ((byte2 >= 0xA0 && byte2 <= 0xA5) || (byte2 >= 0x80 && byte2 <= 0x85)) return 'a';
		if ((byte2 >= 0xA8 && byte2 <= 0xAB) || (byte2 >= 0x88 && byte2 <= 0x8B)) return 'e';
		if ((byte2 >= 0xAC && byte2 <= 0xAF) || (byte2 >= 0x8C && byte2 <= 0x8F)) return 'i';
		if ((byte2 >= 0xB2 && byte2 <= 0xB6) || (byte2 >= 0x92 && byte2 <= 0x96)) return 'o';
		if ((byte2 >= 0xB9 && byte2 <= 0xBC) || (byte2 >= 0x99 && byte2 <= 0x9C)) return 'u';
		if (byte2 == 0xA7 || byte2 == 0x87) return 'c';
		if (byte2 == 0xB1 || byte2 == 0x91) return 'n';
	}
	return 0;
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
	if (HasSaveFile()) {

	}
	std::string text;
	InvertedIndex* invIndex = new InvertedIndex();
	//Para cada arquivo achado no caminho utilizado
	for (auto const& dir_entry : _fileManager.GetIterator(path)) {
		if (!_fileManager.FileUseExtension(dir_entry.path(), ".txt")) continue;
		//abre o arquivo
		//crie um buffer
		std::cout << "Current Book: " << dir_entry.path().stem().string() << std::endl;
		std::fstream currentFile(dir_entry.path(), std::ios::in | std::ios::out);
		std::string fileBuffer((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
		std::string newFileBuffer;
		newFileBuffer.reserve(fileBuffer.size());
		std::string temp;
		//Para cada caracter do arquivo e os remove
		for (int i = 0; i < fileBuffer.size(); i++) {
			//Detecta characteres que sao maiores que um byte
			unsigned char uChar = static_cast<unsigned char>(fileBuffer[i]);
			if (uChar >= 0xC0) {
				if (uChar == 0xE2 && i + 2 < fileBuffer.size()) {
					unsigned char b2 = static_cast<unsigned char>(fileBuffer[i + 1]);
					unsigned char b3 = static_cast<unsigned char>(fileBuffer[i + 2]);

					if (b2 == 0x80) {
						if (b3 == 0x9C || b3 == 0x9D || b3 == 0x98 || b3 == 0x99 ||
							b3 == 0x93 || b3 == 0x94) {

							// É pontuação especial! Pula os 2 bytes extras
							i += 2;
							continue;
						}
					}
				}
				if (i + 1 < fileBuffer.size()) {
					unsigned char nextChar = static_cast<unsigned char>(fileBuffer[i + 1]);
					char asciiEquivalent = MapUtf8ToAscii(uChar, nextChar);
					if (asciiEquivalent != 0) {
						temp.push_back(asciiEquivalent);
						i++; // Skip 1 byte
						continue;
					}
				}
			}
			//Detecta characteres normais 1 byte
			//Remove stopwords, espacos, especiais
			char currentChar = fileBuffer[i];
			if (currentChar == ' ' || currentChar == '\n') {
				if (!temp.empty()) {
					if (WordIsStopWord(temp)) {
						//std::cout << "Valid word: " << temp << std::endl;
						temp.clear();
					}
					else {
						newFileBuffer.append(temp);
						invIndex->AddWord(temp, dir_entry.path().string());
						temp.clear();
					}
				}
				continue;
			}
			if (std::isupper(static_cast<unsigned char>(currentChar))) {
				currentChar = std::tolower(static_cast<unsigned char>(currentChar));
			}
			if (std::ispunct(static_cast<unsigned char>(currentChar))) continue;

			//adiciona as palavras validas para o buffer
			temp.push_back(currentChar);
		}
		//cria diretorio de output
		if (!fs::exists("bin/ProcessFiles")) {
			fs::create_directories("bin/ProcessFiles");
		}
		//escreve of buffer para o arquivo
		fs::path outputPath = fs::path("bin/ProcessFiles") / (dir_entry.path().stem().string() + ".txt");
		std::ofstream outPutFile(outputPath);
		outPutFile << newFileBuffer;
		outPutFile.close();
		currentFile.close();
	}
	//Serializa os arquivos
	Serializer* serializer = new Serializer();
	serializer->Serialize(invIndex->GetMap(), invIndex->GetFileNames());
	delete invIndex;
	delete serializer;
	std::cout << "File processes sucessfully" << std::endl;
	return 1;
}

#include "Serializer.hpp"
#include "Deserializer.hpp"
/// <summary>
/// converte um std::unordered_map<std::string, std::unordered_set<std::string>> para um std::unordered_map<std::string, std::unordered_set<int>>
/// </summary>
/// <param name="wordMap"></param>
/// <param name="fileNamesInt"></param>
void Serializer::ConvertMap(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt)
{
	//Para cada palavra ["Word"]
	for (auto it = wordMap.begin(); it != wordMap.end(); it++)
	{
		//std::cout << it->first << std::endl;
		//para cada set de arquivos ["arquivo.txt"]
		for (const auto& fileName : it->second)
		{
			int test = 0;
			//std::cout << fileName << std::endl;
			for (auto nums = fileNamesInt.begin(); nums != fileNamesInt.end(); nums++) {
				if (nums->second == fileName) {
					//std::cout << nums->second << " has id: " << nums->first << std::endl;
					_convertedMap[it->first].insert(nums->first);
					break;
				}
			}
		}
	}
}
/// <summary>
/// save file versao de texto, usado para visulização
/// </summary>
/// <param name="fileNamesInt"></param>
void Serializer::TextSerialization(std::unordered_map<int, std::string>& fileNamesInt)
{
	std::string fileBuffer;
	std::ofstream testFile("testSere.txt", std::ios::binary);
	const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
	testFile.write(reinterpret_cast<const char*>(bom), sizeof(bom));

	testFile.write(fileBuffer.c_str(), fileBuffer.size());

	for (auto it = fileNamesInt.begin(); it != fileNamesInt.end(); it++) {
		fileBuffer += std::to_string(it->first) + " " + it->second + "\n";
	}
	for (auto it = _convertedMap.begin(); it != _convertedMap.end(); it++)
	{
		std::string miniBuffer;
		for (int fileID : it->second)
		{
			miniBuffer += std::to_string(fileID) + " ";
		}
		fileBuffer += it->first + " " + miniBuffer + '\n';
	}

	testFile << fileBuffer;
	testFile.close();
}
/// <summary>
/// wordMap eh o verdadeiro indice invertido, nao se pode serelizar ele direto, pois salvaria muitos dados repitodos(nomes dos arquivos), entao, como temos o fileNamesInt, que mapeia 
/// um numero para o arquivo, faremos o seguinte, para cada chave(palavra), subistituia o nome de arquivo, pelo seu numero
/// ou seja, dado a seguinte palavra ["arroz"] = {"arquivo1.txt, "arquivo2.txt}
/// e dado um fileNamesInt 0 = "arquivo1.txt", 1 = "arquivo2.txt"
/// Convertemos para ["arroz"] = {0, 1}
/// esse nomo dado eh que sera serelizado
/// fileNamesInt tambem eh serelizado para fazer o processo inverto
/// </summary>
/// <param name="wordMap"></param>
/// <param name="fileNamesInt"></param>
void Serializer::Serialize(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt)
{
	ConvertMap(wordMap, fileNamesInt);
	std::string fileBuffer;
	std::ofstream saveFile("index.bat", std::ios::binary);
	SaveData(saveFile, fileNamesInt);
	SaveData(saveFile, _convertedMap);
	saveFile.close();
	//TextSerialization(fileNamesInt);
}

void Serializer::TestSerialize()
{

	std::ofstream saveFile("indexTest.bat", std::ios::binary);
	//int TestData = 10;
	//std::string TestData = "bolo do roblox";
	//std::unordered_set<std::string> TestData = { "alho", "nariz", "lasanha" };
	std::unordered_map<int, std::string> TestData1 =
	{
		{0, "livro"},
		{1, "limao"},
		{2, "arroz"}
	};
	SaveData(saveFile, TestData1);
	std::unordered_map<std::string, std::unordered_set<int>> TestData2 =
	{
		{"cat", {0, 2, 4}},
		{"bi", {1, 2, 4}},
		{"camarao", {0, 2}},
	};
	std::cout << "Original data: TestData1" << std::endl;
	for (auto it = TestData1.begin(); it != TestData1.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
	std::cout << "Original data: TestData2" << std::endl;
	for (auto it = TestData2.begin(); it != TestData2.end(); it++)
	{
		std::cout << it->first << " ";
		for (const auto& num : it->second) {
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
	SaveData(saveFile, TestData2);
	saveFile.close();
}

#include "Deserializer.hpp"

void Deserializer::DeconvertMap(std::unordered_map<std::string, std::unordered_set<int>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt)
{
	for (auto it = wordMap.begin(); it != wordMap.end(); it++)
	{
		std::string word = it->first;
		for (const auto& id : it->second)
		{
			if (fileNamesInt.find(id) != fileNamesInt.end()) {
				std::string fileName = fileNamesInt[id];

				_deconvertedMap[word].insert(fileName);

			}
		}
	}
}

void Deserializer::TextDeserialization(std::unordered_map<int, std::string>& fileNamesInt)
{
	std::string fileBuffer;
	std::ofstream testFile("testDese.txt", std::ios::binary);
	const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
	testFile.write(reinterpret_cast<const char*>(bom), sizeof(bom));

	testFile.write(fileBuffer.c_str(), fileBuffer.size());

	for (auto it = fileNamesInt.begin(); it != fileNamesInt.end(); it++) {
		fileBuffer += std::to_string(it->first) + " " + it->second + "\n";
	}
	for (auto it = _deconvertedMap.begin(); it != _deconvertedMap.end(); it++)
	{
		std::string miniBuffer;
		for (std::string fileID : it->second)
		{
			miniBuffer += fileID + " ";
		}
		fileBuffer += it->first + " " + miniBuffer + '\n';
	}

	testFile << fileBuffer;
	testFile.close();
}
/// <summary>
/// Deserializa os dados, processo inverso do Serializer
/// </summary>
/// <param name="invIndex"></param>
/// <returns></returns>
int Deserializer::Deserialize(InvertedIndex& invIndex)
{
	std::ifstream saveFile("index.bat", std::ios::binary);
	if (!saveFile.is_open()) {
		std::cout << "Erro ao abrir o arquivo" << std::endl;
		return -1;
	}
	invIndex.SetFileNames(LoadData<std::unordered_map<int, std::string>>(saveFile));
	std::unordered_map<std::string, std::unordered_set<int>> serilizedDataMap = LoadData<std::unordered_map<std::string, std::unordered_set<int>>>(saveFile);
	saveFile.close();
	DeconvertMap(serilizedDataMap, invIndex.GetFileNames());
	invIndex.SetWordMap(_deconvertedMap);
	//TextDeserialization(invIndex.GetFileNames());
	return 1;
}

void Deserializer::TestDeserialize()
{
	
	std::ifstream savefile("indexTest.bat", std::ios::binary);
	//int TestData = LoadData<int>(savefile);
	//std::string TestData = LoadData<std::string>(savefile);
	//std::unordered_set<std::string> TestData = LoadData<std::unordered_set<std::string>>(savefile);
	std::unordered_map<int, std::string> TestData1 = LoadData<std::unordered_map<int, std::string>>(savefile);
	std::unordered_map<std::string, std::unordered_set<int>> TestData2 = LoadData<std::unordered_map<std::string, std::unordered_set<int>>>(savefile);
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
	savefile.close();
}

#pragma once
#include "InvertedIndex.hpp"
#include "SerializableInvertedIndex.hpp"
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

class Deserializer {
	private:
		std::unordered_map<int, std::string> _docNamesToInt;
		int _fileCounter = 0;
		void DeconvertMap(std::unordered_map<std::string, std::unordered_set<int>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt);
		std::unordered_map<std::string, std::unordered_set<std::string>> _deconvertedMap;
		template <typename T> T LoadData(std::ifstream& file);
		void TextDeserialization(std::unordered_map<int, std::string>& fileNamesInt);
	public:
		void Deserialize(InvertedIndex& invIndex);
		void TestDeserialize();
};

template<typename T>
inline T Deserializer::LoadData(std::ifstream& file)
{
	T data;
	file.read(reinterpret_cast<char*>(&data), sizeof(data));
	//std::cout << "deserializing simple data, value: " << data << std::endl;
	return data;
}

template<>
inline std::string Deserializer::LoadData<std::string>(std::ifstream& file)
{
	std::string buffer;
	size_t len = 0;
	file.read(reinterpret_cast<char*>(&len), sizeof(len));//Le o tamanho da string
	buffer.resize(len); //resize no tamanho do buffer
	file.read(&buffer[0], len);// le o arr de caracteres
	//std::cout << "Deserializing complex string data, value: " << buffer << std::endl;
	return buffer;
}
template<>
inline std::unordered_set<std::string> Deserializer::LoadData<std::unordered_set<std::string>>(std::ifstream& file)
{
	std::unordered_set<std::string> data;
	size_t count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		std::string temp = LoadData<std::string>(file);
		data.insert(temp);
	}
	/*std::cout << "Deserializing complex string set, value: ";
	for (auto x : data)
		std::cout << x << " ";
	std::cout << std::endl;*/
	return data;
}
template<>
inline std::unordered_set<int> Deserializer::LoadData<std::unordered_set<int>>(std::ifstream& file)
{
	std::unordered_set<int> data;
	size_t count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		int temp = LoadData<int>(file);
		data.insert(temp);
	}
	/*std::cout << "Deserializing complex string set, value: ";
	for (auto x : data)
		std::cout << x << " ";
	std::cout << std::endl;*/
	return data;
}
template<>
inline std::unordered_map<int, std::string> Deserializer::LoadData<std::unordered_map<int, std::string>>(std::ifstream& file)
{
	std::unordered_map<int, std::string> data;
	size_t count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		int tempInt = LoadData<int>(file);
		std::string tempString = LoadData<std::string>(file);
		data[tempInt] = tempString;
	}
	/*for (auto it = data.begin(); it != data.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}*/
	return data;
}
template<>
inline std::unordered_map<std::string, std::unordered_set<int>> Deserializer::LoadData<std::unordered_map<std::string, std::unordered_set<int>>>(std::ifstream& file)
{
	std::unordered_map<std::string, std::unordered_set<int>> data;
	size_t count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		std::string tempString = LoadData<std::string>(file);
		std::unordered_set<int> tempIntSet = LoadData<std::unordered_set<int>>(file);
		data[tempString] = tempIntSet;
	}
	/*for (auto it = data.begin(); it != data.end(); it++)
	{
		std::cout << it->first << " ";
		for (const auto& num : it->second) {
			std::cout << num << std::endl;
		}
	}*/
	return data;
}

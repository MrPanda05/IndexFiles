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

class Serializer {
	private:
		int _fileCounter = 0;
		template <typename T> void SaveData(std::ostream& file, T data);
		std::unordered_map<std::string, std::unordered_set<int>> _convertedMap;
		void ConvertMap(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt);
		void TextSerialization(std::unordered_map<int, std::string>& fileNamesInt);
	public:
		void Serialize(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::unordered_map<int, std::string>& fileNamesInt);
		void TestSerialize();
};

template<typename T>
inline void Serializer::SaveData(std::ostream& file, T data)
{
	//std::cout << "Serializing: " << data << std::endl;
	file.write(reinterpret_cast<char*>(&data), sizeof(data));
}
template <>
inline void Serializer::SaveData<std::string>(std::ostream& file, std::string data) 
{
	//std::cout << "Serializing complex string data, value: " << data << std::endl;
	size_t len = data.size();
	file.write(reinterpret_cast<char*>(&len), sizeof(len));//Escreve primeiro o tamanho da string
	file.write(data.c_str(), len);//escreve o arr dos caracteres
}
template <>
inline void Serializer::SaveData<std::unordered_set<std::string>>(std::ostream& file, std::unordered_set<std::string> data)
{
	/*std::cout << "Serializing complex set of string, value: ";
	for (auto x : data)
		std::cout << x << " ";
	std::cout << std::endl;*/
	size_t setSize = data.size();
	file.write(reinterpret_cast<char*>(&setSize), sizeof(setSize));
	for (const auto& str : data) {
		SaveData(file, str);
	}
}
template <>
inline void Serializer::SaveData<std::unordered_set<int>>(std::ostream& file, std::unordered_set<int> data)
{
	/*std::cout << "Serializing complex set of string, value: ";
	for (auto x : data)
		std::cout << x << " ";
	std::cout << std::endl;*/
	size_t setSize = data.size();
	file.write(reinterpret_cast<char*>(&setSize), sizeof(setSize));
	for (const auto& num : data) {
		SaveData(file, num);
	}
}
template <>
inline void Serializer::SaveData<std::unordered_map<int, std::string>>(std::ostream& file, std::unordered_map<int, std::string> data)
{
	size_t mapSize = data.size();
	file.write(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
	for (auto it = data.begin(); it != data.end(); it++)
	{
		//std::cout << it->first << " : " << it->second << std::endl;
		SaveData(file, it->first);
		SaveData(file, it->second);
	}
}
template <>
inline void Serializer::SaveData<std::unordered_map<std::string, std::unordered_set<int>>>(std::ostream& file, std::unordered_map<std::string, std::unordered_set<int>> data)
{
	size_t mapSize = data.size();
	file.write(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
	for (auto it = data.begin(); it != data.end(); it++)
	{
		//std::cout << it->first << " ";
		SaveData(file, it->first);
		SaveData(file, it->second);
		//for (const auto& num : it->second) {
		//	std::cout << num << std::endl;
		//}
	}
}

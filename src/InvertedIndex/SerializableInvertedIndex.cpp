#include "SerializableInvertedIndex.hpp"
//
//SerializableInvertedIndex::SerializableInvertedIndex(std::unordered_map<int, std::string> intMap, std::unordered_map<std::string, std::unordered_set<std::string>> keys)
//{
//	for (auto it = keys.begin(); it != keys.end(); it++)
//	{
//		//std::cout << it->first << std::endl;
//		for (const auto& fileName : it->second)
//		{
//			int test = 0;
//			//std::cout << fileName << std::endl;
//			for (auto nums = intMap.begin(); nums != intMap.end(); nums++) {
//				if (nums->second == fileName) {
//					//std::cout << nums->second << " has id: " << nums->first << std::endl;
//					wordMap[it->first].insert(nums->first);
//					break;
//				}
//			}
//		}
//	}
//	/*for (auto it = wordMap.begin(); it != wordMap.end(); it++)
//	{
//		std::cout << it->first << ": ";
//		for (const auto& fileName : it->second)
//		{
//			std::cout << fileName << " ";
//		}
//		std::cout << std::endl;
//	}*/
//}

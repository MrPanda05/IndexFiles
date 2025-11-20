#include "FileManager.hpp"

int FileManager::HowMuchContent(fs::path dirPath)
{
    int count = 0;
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }){
        //std::cout << dir_entry.path() << std::endl;
        count++;
    }
    return count;
}

int FileManager::HowMannyFiles(fs::path dirPath)
{
    int count = 0;
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }) {
        if (dir_entry.path().has_extension()) {
            count++;
        }
    }
    return count;
}

bool FileManager::FileUseExtension(fs::path filePath, std::string fileExtension)
{
    return filePath.extension() == fileExtension;
}

fs::path FileManager::FindFile(fs::path dirPath, std::string fileName)
{
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }) {
        if (dir_entry.path().stem() == fileName) return dir_entry;
    }
    return "";
}

fs::recursive_directory_iterator FileManager::GetIterator(fs::path dirPath)
{
    return fs::recursive_directory_iterator{ dirPath };
}

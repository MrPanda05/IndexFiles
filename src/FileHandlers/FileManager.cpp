#include "FileManager.hpp"
/// <summary>
/// retorna quantos diretorios existem
/// </summary>
/// <param name="dirPath"></param>
/// <returns></returns>
int FileManager::HowMuchContent(fs::path dirPath)
{
    int count = 0;
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }){
        //std::cout << dir_entry.path() << std::endl;
        count++;
    }
    return count;
}
/// <summary>
/// Retorna quantos arquivos existem
/// </summary>
/// <param name="dirPath"></param>
/// <returns></returns>
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
/// <summary>
/// Checka se arquivo tem extensao
/// </summary>
/// <param name="filePath"></param>
/// <param name="fileExtension"></param>
/// <returns></returns>
bool FileManager::FileUseExtension(fs::path filePath, std::string fileExtension)
{
    return filePath.extension() == fileExtension;
}
/// <summary>
/// Achar um arquivo por nome
/// </summary>
/// <param name="dirPath"></param>
/// <param name="fileName"></param>
/// <returns></returns>
fs::path FileManager::FindFile(fs::path dirPath, std::string fileName)
{
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }) {
        if (dir_entry.path().stem() == fileName) return dir_entry;
    }
    return "";
}
/// <summary>
/// Achar um arquivo com nome e extensao
/// </summary>
/// <param name="dirPath"></param>
/// <param name="fileName"></param>
/// <returns></returns>
fs::path FileManager::FindFileFullName(fs::path dirPath, std::string fileName)
{
    for (auto const& dir_entry : fs::recursive_directory_iterator{ dirPath }) {
        if (dir_entry.path().filename().string() == fileName) return dir_entry;
    }
    return "";
}
/// <summary>
/// retorna um iterator recursivo de um diretorio
/// </summary>
/// <param name="dirPath"></param>
/// <returns></returns>
fs::recursive_directory_iterator FileManager::GetIterator(fs::path dirPath)
{
    return fs::recursive_directory_iterator{ dirPath };
}

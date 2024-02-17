#include "savecontroller.h"
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

const string DEFAULT_PATH = "C:/TrucoG7/";

SaveController::SaveController() {
    std::filesystem::create_directories(DEFAULT_PATH);
}

int SaveController::SaveGame(/*GameRulesModel *regra, std::vector<std::string> nomes*/) {
    try {

        std::ofstream outFile(DEFAULT_PATH + "trucoInfos.txt", std::ios::binary);

        if (!outFile.is_open())
            return 0;

        /*for(int i=0; i<nomes.size(); i++){
            outFile.write(reinterpret_cast<const char*>(&nomes.at(i)), sizeof(nomes.at(i)));
        }*/
        outFile.close();
        return 1;
    }

    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

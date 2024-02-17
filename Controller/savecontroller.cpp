#include "savecontroller.h"

SaveController::SaveController() {
    directory_ = "C:/G7TrucoGame/";
    std::filesystem::create_directories(directory_);
}

int SaveController::SaveGame(const std::string& nickname) {
    try {

        std::ofstream outFile(directory_ + "save.txt");

        if (!outFile.is_open())
            return 5;

        outFile.write(nickname.c_str(), nickname.size());
        outFile.close();
        return 1;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Erro de E/S: " << e.what() << std::endl;
        return 2;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Erro de alocação de memória: " << e.what() << std::endl;
        return 3;
    }
    catch (const std::bad_cast& e) {
        std::cerr << "Erro de conversão de tipo: " << e.what() << std::endl;
        return 4;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro genérico: " << e.what() << std::endl;
        return 0;
    }
}

int SaveController::LoadGame(std::string* nickname) {
    try {
        std::ifstream inFile(directory_ + "save.txt");

        if (!inFile.is_open())
            return 1;

        inFile.seekg(0, std::ios::end);
        nickname->reserve(inFile.tellg());
        inFile.seekg(0, std::ios::beg);

        nickname->assign((std::istreambuf_iterator<char>(inFile)),
                   std::istreambuf_iterator<char>());
        inFile.close();
        return 2;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Erro de E/S: " << e.what() << std::endl;
        return 3;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Erro de alocação de memória: " << e.what() << std::endl;
        return 4;
    }
    catch (const std::bad_cast& e) {
        std::cerr << "Erro de conversão de tipo: " << e.what() << std::endl;
        return 5;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro genérico: " << e.what() << std::endl;
        return 6;
    }
}

bool SaveController::ThereIsALoad()
{
    return std::filesystem::exists(directory_ + "save.txt");
}

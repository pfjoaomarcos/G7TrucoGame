#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include "../Model/gamerulesmodel.h"

class SaveController
{
public:
    SaveController();
    int SaveGame(/*GameRulesModel *regra, std::vector<std::string> nomes*/);
};

#endif // SAVECONTROLLER_H


#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>

class SaveController
{
public:
    SaveController();
    ~SaveController();
    int SaveGame(const std::string &nickname);
    int LoadGame(std::string* nickname);
    bool ThereIsALoad();

private:
    std::string directory_;
};

#endif // SAVECONTROLLER_H

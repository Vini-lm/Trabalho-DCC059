#ifndef TRABALHO_DCC059_UTILS_H
#define TRABALHO_DCC059_UTILS_H

#include<fstream>
#include<cstring>
#include "Grafo.h"


class Utils
{
private:

public:
    Utils();
    ~Utils();

    static Grafo* readAndCreate(string filePath);
};



#endif
#ifndef FILEIMPORT_H
#define FILEIMPORT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include "Obj3d.h"

class FileImport
{
public:
    static void loadObj(const std::string &path, std::vector<Obj3d *> &obj3ds, vertices_t &vertices);

private:
    static long getLineFromStr(char *src, char *dest, long destSize);

};

#endif // FILEIMPORT_H

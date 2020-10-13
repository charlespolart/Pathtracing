#ifndef FILEIMPORT_H
#define FILEIMPORT_H

#include <FreeImage.h>
#include <QFileInfo>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include "Obj3d.h"

class FileImport
{
public:
    static bool loadObj(const std::string &path, std::vector<Obj3d *> &obj3ds, vertices_t &vertices, std::map<std::string, Material *> &materials, Material *defaultMaterial);

private:
    static long getLineFromStr(char *src, char *dest, long destSize);
    static bool loadTexture(const std::string &path, texture_t *texture);
    static bool loadMtl(const std::string &path, std::map<std::string, Material *> &materials);
};

#endif // FILEIMPORT_H

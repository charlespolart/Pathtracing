#include "FileImport.h"

long FileImport::getLineFromStr(char *src, char *dest, long destSize)
{
    long i = 0, t = 0;

    while (src[i] != '\n' && src[i] != '\0')
    {
        if (i < destSize)
        {
            dest[t] = src[i];
            t++;
        }
        i++;
    }
    dest[t] = '\0';
    return (i);
}

void FileImport::loadObj(const std::string &path, std::vector<Obj3d *> &obj3ds, vertices_t &vertices)
{
    FILE *fd = std::fopen(path.c_str(), "r");
    char *file;
    char line[128];
    long size = 0;

    fseek(fd, 0L, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0L, SEEK_SET);
    file = new char[size];
    std::fread(file, sizeof(char), size, fd);
    for (long i = 0; i < size; ++i)
    {
        i += getLineFromStr(file+i, line, sizeof(line));
        if (std::strncmp(line, "o", 1) == 0)
        {
            char name[128];
            obj3ds.emplace_back(new Obj3d());
            obj3ds.back()->vertices = &vertices;
            std::sscanf(line+1, "%s\n", name);
            obj3ds.back()->name = name;
        }
        else if (std::strncmp(line, "v ", 2) == 0)
        {
            Vector3d vect;
            std::sscanf(line+1, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            vertices.v.push_back(vect);
        }
        else if (std::strncmp(line, "vt ", 3) == 0)
        {
            Vector3d vect;
            std::sscanf(line+2, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            vertices.vt.push_back(vect);
        }
        else if (std::strncmp(line, "vn ", 3) == 0)
        {
            Vector3d vect;
            std::sscanf(line+2, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            vertices.vn.push_back(vect);
        }
        else if (std::strncmp(line, "f ", 2) == 0)
        {
            face3_t face;

            if (obj3ds.empty())
            {
                obj3ds.emplace_back(new Obj3d());
                obj3ds.back()->vertices = &vertices;
            }
            if (std::sscanf(line+2, "%d//%d %d//%d %d//%d\n", &face.indexV[0], &face.indexVn[0], &face.indexV[1], &face.indexVn[1], &face.indexV[2], &face.indexVn[2]) != 6)
                std::sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face.indexV[0], &face.indexVt[0], &face.indexVn[0], &face.indexV[1], &face.indexVt[1], &face.indexVn[1], &face.indexV[2], &face.indexVt[2], &face.indexVn[2]);
            obj3ds.back()->faces3.push_back(face);
        }
    }
    delete [] file;
    std::fclose(fd);
}

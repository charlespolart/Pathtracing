#include "FileImport.h"

void FileImport::loadObj(const std::string &path, std::vector<Obj3d *> &obj3ds, vertices_t &vertices)
{
    std::ifstream file(path);
    std::string line, code;

    while (std::getline(file, line))
    {
        std::stringstream sstream(line);
        sstream >> code;
        if (code == "o")
        {
            obj3ds.emplace_back(new Obj3d());
            obj3ds.back()->vertices = &vertices;
            sstream >> obj3ds.back()->name;
        }
        else if (code == "v")
        {
            Vector3d vect;
            sstream >> vect.x >> vect.y >> vect.z;
            vertices.v.push_back(vect);
        }
        else if (code == "vt")
        {
            Vector3d vect;
            sstream >> vect.x >> vect.y >> vect.z;
            vertices.vt.push_back(vect);
        }
        else if (code == "vn")
        {
            Vector3d vect;
            sstream >> vect.x >> vect.y >> vect.z;
            vertices.vn.push_back(vect);
        }
        else if (code == "f")
        {
            face3_t face;
            std::string line;

            if (obj3ds.empty())
            {
                obj3ds.emplace_back(new Obj3d());
                obj3ds.back()->vertices = &vertices;
            }
            for (int i = 0; sstream >> line && i < 3; ++i)
            {
                std::string index;
                std::stringstream tmpstream(line);
                for (int t = 0; getline(tmpstream, index, '/') && t < 3; ++t)
                {
                    if (t == 0)
                        std::stringstream(index) >> face.indexV[i];
                    if (t == 1)
                        std::stringstream(index) >> face.indexVt[i];
                    if (t == 2)
                        std::stringstream(index) >> face.indexVn[i];
                }
            }
            obj3ds.back()->faces3.push_back(face);
        }
    }
}

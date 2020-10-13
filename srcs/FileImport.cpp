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

bool FileImport::loadTexture(const std::string &path, texture_t *texture)
{
    size_t width = 0, height = 0;
    uint8_t *pixels = nullptr, *tmp = nullptr;
    FIBITMAP *img = nullptr;

    if (!(img = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str())))
    {
        std::cout << "Failed to open " << path << std::endl;
        return (false);
    }
    FIBITMAP *imgTmp = FreeImage_ConvertTo24Bits(img);
    FreeImage_Unload(img);
    img = imgTmp;
    width = FreeImage_GetWidth(img);
    height = FreeImage_GetHeight(img);
    tmp = FreeImage_GetBits(img);
    pixels = new uint8_t[width*height*3];
    std::memcpy(pixels, tmp, width*height*3);
    FreeImage_Unload(img);
    texture->pixels = pixels;
    texture->x = static_cast<int>(width);
    texture->y = static_cast<int>(height);
    return (true);
}

bool FileImport::loadMtl(const std::string &path, std::map<std::string, Material *> &materials)
{
    FILE *fd = std::fopen(path.c_str(), "r");
    char *file;
    char line[1024];
    long size = 0;
    char newmtl[128];

    if (!fd)
        return (false);
    fseek(fd, 0L, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0L, SEEK_SET);
    file = new char[size];
    std::fread(file, sizeof(char), size, fd);
    for (long i = 0; i < size; ++i)
    {
        i += getLineFromStr(file+i, line, sizeof(line));
        if (std::strncmp(line, "newmtl ", 7) == 0)
        {
            std::sscanf(line+7, "%s\n", newmtl);
            materials[newmtl] = new Material();
            materials[newmtl]->_name = newmtl;
        }
        else if (std::strncmp(line, "Kd ", 3) == 0)
        {
            if (materials.find(newmtl) == materials.end())
                continue;
            Vector3d vect;
            std::sscanf(line+3, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            materials[newmtl]->_color = vect;
        }
        else if (std::strncmp(line, "map_Kd ", 7) == 0)
        {
            if (materials.find(newmtl) == materials.end())
                continue;
            std::string mapKd;
            texture_t texture;
            mapKd = line+7;
            mapKd = std::regex_replace(mapKd, std::regex(R"(\\\\)"), "/");
            mapKd = std::regex_replace(mapKd, std::regex(R"(\\)"), "/");
            if (mapKd.find('/') == std::string::npos)
                mapKd = QFileInfo(QString::fromStdString(path)).path().toStdString()+'/'+mapKd;
            if (FileImport::loadTexture(mapKd, &texture))
                materials[newmtl]->_texture = texture;
        }
    }
    delete [] file;
    std::fclose(fd);
    return (true);
}

bool FileImport::loadObj(const std::string &path, std::vector<Obj3d *> &obj3ds, vertices_t &vertices, std::map<std::string, Material *> &materials, Material *defaultMaterial)
{
    FILE *fd = std::fopen(path.c_str(), "r");
    char *file;
    char line[128];
    long size = 0;
    char usemtl[128];

    if (!fd)
        return (false);
    fseek(fd, 0L, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0L, SEEK_SET);
    file = new char[size];
    std::fread(file, sizeof(char), size, fd);
    for (long i = 0; i < size; ++i)
    {
        i += getLineFromStr(file+i, line, sizeof(line));
        if (std::strncmp(line, "mtllib ", 7) == 0)
        {
            QFileInfo fileInfo(QString::fromStdString(path));
            FileImport::loadMtl(fileInfo.path().toStdString()+'/'+std::string(line+7), materials);
        }
        else if (std::strncmp(line, "o ", 2) == 0)
        {
            char name[128];
            obj3ds.emplace_back(new Obj3d());
            obj3ds.back()->_vertices = &vertices;
            std::sscanf(line+2, "%s\n", name);
            obj3ds.back()->_name = name;
        }
        else if (std::strncmp(line, "v ", 2) == 0)
        {
            Vector3d vect;
            std::sscanf(line+2, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            vertices.v.push_back(vect);
        }
        else if (std::strncmp(line, "vt ", 3) == 0)
        {
            Vector2d vect;
            std::sscanf(line+3, "%lf %lf\n", &vect.x, &vect.y);
            vertices.vt.push_back(vect);
        }
        else if (std::strncmp(line, "vn ", 3) == 0)
        {
            Vector3d vect;
            std::sscanf(line+3, "%lf %lf %lf\n", &vect.x, &vect.y, &vect.z);
            vertices.vn.push_back(vect);
        }
        else if (std::strncmp(line, "usemtl ", 7) == 0)
        {
            std::sscanf(line+7, "%s\n", usemtl);
        }
        else if (std::strncmp(line, "f ", 2) == 0)
        {
            face3_t face;

            if (obj3ds.empty())
            {
                obj3ds.emplace_back(new Obj3d());
                obj3ds.back()->_vertices = &vertices;
            }
            if (std::sscanf(line+2, "%d//%d %d//%d %d//%d\n", &face.indexV[0], &face.indexVn[0], &face.indexV[1], &face.indexVn[1], &face.indexV[2], &face.indexVn[2]) != 6)
                std::sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face.indexV[0], &face.indexVt[0], &face.indexVn[0], &face.indexV[1], &face.indexVt[1], &face.indexVn[1], &face.indexV[2], &face.indexVt[2], &face.indexVn[2]);
            face.indexV[0] = std::abs(face.indexV[0]); face.indexV[1] = std::abs(face.indexV[1]); face.indexV[2] = std::abs(face.indexV[2]);
            face.indexVt[0] = std::abs(face.indexVt[0]); face.indexVt[1] = std::abs(face.indexVt[1]); face.indexVt[2] = std::abs(face.indexVt[2]);
            face.indexVn[0] = std::abs(face.indexVn[0]); face.indexVn[1] = std::abs(face.indexVn[1]); face.indexVn[2] = std::abs(face.indexVn[2]);
            if (materials.find(usemtl) != materials.end())
            {
                face.material = materials[usemtl];
                size_t i = 0;
                for (; i < obj3ds.back()->_materials.size(); ++i)
                    if (obj3ds.back()->_materials[i]->_name == usemtl) break;
                if (i >= obj3ds.back()->_materials.size())
                    obj3ds.back()->_materials.push_back(materials[usemtl]);
            }
            else
                face.material = defaultMaterial;
            obj3ds.back()->_faces3.push_back(face);
        }
    }
    delete [] file;
    std::fclose(fd);
    if (!obj3ds.size())
        return (false);
    return (true);
}

#pragma once
#include "MyStudyHeaders.h"
#include "Vertex.h"
#include <vector>
using namespace std;

template <class T>
class Mesh
{
public:
    typedef Mesh<T> type;
    vector<Vertex3D<T>> vertices;
    vector<TextureUVCoord2D<T>> textureCoords;
    vector<unsigned int> faces;
    Mesh()=default;
    Mesh(const type &other)=default;
    Mesh(type &&other)
    {
        MY_LOG_DEBUG("Mesh move constuctor\n");
        this->vertices = move(other.vertices);
        this->textureCoords = move(other.textureCoords);
        this->faces = move(other.faces);
    }
    type &operator=(type &&other)
    {
        MY_LOG_DEBUG("Mesh move operator=\n");
        this->vertices = move(other.vertices);
        this->textureCoords = move(other.textureCoords);
        this->faces = move(other.faces);
        return *this;
    }
};

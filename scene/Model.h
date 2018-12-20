//
// Created by ldoublej on 18-12-19.
//

#ifndef SIMPLE_OGL_MODEL_H
#define SIMPLE_OGL_MODEL_H

#include <glm/glm.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdio.h>
#include <../graph/VertexArray.h>

namespace scene
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 Texcoords;
    };

    class Mesh
    {
    private:
        const aiScene * _scene;
        aiMesh * _mesh;
        graph::VertexArray * _vao;
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
    public:
        Mesh(aiMesh * mesh ,const aiScene * scene):_mesh(mesh),_scene(scene),_vao(nullptr){ProcessMesh();ApplyVertex();}
        void ProcessMesh();
        void ApplyVertex();
        void Draw();
    };
    class Model
    {
    private:
        std::vector<Mesh *> _meshes;
        void LoadModel(const char * path);
    public:
        explicit Model(const char * path){LoadModel(path);};
        void Draw();
    };
}

#endif //SIMPLE_OGL_MODEL_H

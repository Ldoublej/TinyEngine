//
// Created by ldoublej on 18-12-19.
//

#ifndef SIMPLE_OGL_MODEL_H
#define SIMPLE_OGL_MODEL_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdio.h>
#include <../graph/VertexArray.h>
#include "../graph/Program.h"
#include <vector>
#include "../graph/Texture2D.h"
#include "../resource/Image2D.h"
#include "../graph/Helper.h"

namespace scene
{
    using namespace graph;
    using namespace resource;
    /*
     * Vertex
     * */
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 Texcoords;
    };
    struct Material
    {
        Texture2D * Diffuse;
        Texture2D * Normal;
    };
    /*
     * Mesh
     * */
    class Model;
    class Mesh
    {
        friend Model;
    private:
        const aiScene * _scene;
        aiMesh * _mesh;
        Model * _model;
        Material  _material;
        graph::VertexArray * _vao;
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;

    private:
        Mesh(aiMesh * mesh ,const aiScene * scene,Model * model);
        void ProcessMesh();
        void ApplyVertex();
        void Draw();
    };

    /*
     * Model
     * */
    class Model
    {
    private:
        std::vector<Mesh *> _meshes;
        std::vector<Material> _materials;
        Program * _shader;

    public:
        explicit Model(const char * path,Program * p);
        void SetProgram(Program * p);
        Program * GetShader() const;
        void Draw();
        Material GetMaterial(std::vector<Material>::size_type index) const;

    private:
        void LoadModel(const char * path);
        Texture2D * LoadTexture(const aiMaterial * mataerial,aiTextureType type);
    };
}

#endif //SIMPLE_OGL_MODEL_H

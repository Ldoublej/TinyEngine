//
// Created by ldoublej on 18-12-19.
//

#include "Model.h"

namespace scene
{

    void Model::LoadModel(const char *path)
    {
        using namespace Assimp;
        Importer import;
        const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate );
        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            printf("ERROR::ASSIMP::");
            return;
        }
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh * aiMesh = scene->mMeshes[i];
            Mesh * mesh = new Mesh(aiMesh,scene);
            this->_meshes.push_back(mesh);
        }
    }

    void Model::Draw()
    {
        for(unsigned int i = 0; i < _meshes.size(); ++i)
        {
            _meshes[i]->Draw();
        }
    }

    void Mesh::ProcessMesh()
    {
        for (unsigned int i = 0; i < _mesh->mNumVertices; ++i)
        {
            Vertex vertex = Vertex();
            vertex.Position.x = _mesh->mVertices[i].x;
            vertex.Position.y = _mesh->mVertices[i].y;
            vertex.Position.z = _mesh->mVertices[i].z;
            vertex.Normal.x = _mesh->mNormals[i].x;
            vertex.Normal.y = _mesh->mNormals[i].y;
            vertex.Normal.z = _mesh->mNormals[i].z;
            if (_mesh->mTextureCoords[0])
            {
                vertex.Texcoords.x = _mesh->mTextureCoords[0][i].x;
                vertex.Texcoords.y = _mesh->mTextureCoords[0][i].y;
            }
            else
            {
                vertex.Texcoords = glm::vec2(0.0f, 0.0f);
            }
            _vertices.push_back(vertex);

        }
        for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
        {
            const  aiFace & face = _mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
            {
                unsigned int s = face.mIndices[j];
                _indices.push_back(s);
            }
        }

    }

    void Mesh::ApplyVertex()
    {
        using namespace graph;
        ElementBuffer * ebo = ElementBuffer::Create();
        ebo->SetData(sizeof(unsigned int)*_indices.size(),&_indices[0],GL_STATIC_DRAW);
        _vao = VertexArray::Create(GL_LINE, ebo);

        VertexBuffer * vertexdata = VertexBuffer::Create();
        vertexdata->SetData(sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
        vertexdata->AddAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
        vertexdata->AddAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(glm::vec3)));
        vertexdata->AddAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(glm::vec3)));
        _vao->AddVertexBuffer(vertexdata);
        _vao->ApplyVertexAttributes();
    }

    void Mesh::Draw()
    {
        glBindVertexArray(_vao->GetBufferID());
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid *)0);
        glBindVertexArray(0);
    }
}
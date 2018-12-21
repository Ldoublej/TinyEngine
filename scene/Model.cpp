//
// Created by ldoublej on 18-12-19.
//

#include "Model.h"

namespace scene
{

    /*
     * ---------------------------------------------------Model---------------------------------------------
     * */
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
        for(unsigned int i = 0; i< scene->mNumMaterials;++i)
        {
            const aiMaterial * material = scene->mMaterials[i];
            Material mat = Material();
            unsigned int diffseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
            unsigned int normalCount = material->GetTextureCount(aiTextureType_HEIGHT);
            if(diffseCount > 0)
            {
                mat.Diffuse = LoadTexture(material,aiTextureType_DIFFUSE);
            }
            if(normalCount > 0)
            {
                mat.Normal = LoadTexture(material,aiTextureType_HEIGHT);
            }
            _materials.push_back(mat);
        }
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh * aiMesh = scene->mMeshes[i];
            Mesh * mesh = new Mesh(aiMesh,scene,this);
            this->_meshes.push_back(mesh);
        }

    }
    Texture2D * Model::LoadTexture(const aiMaterial * material,aiTextureType type)
    {
        aiString texturePath;
        if(material->GetTexture(type,0,&texturePath) == AI_SUCCESS)
        {
            std::string fullPath;
            std::string temp = "models/sponza/";
            fullPath = temp + texturePath.data;


            auto * image = new Image2D(fullPath.c_str());
            image->Load();
            Texture2D * tex = Texture2D::Create(GL_RGBA,GL_LINEAR_MIPMAP_LINEAR);

            helper::SetImageData(image,tex);
            tex->EnableMipMap();
            image->Release();
            return tex;
        }
    }
    void Model::Draw()
    {
        glUseProgram(_shader->GetBufferID());
        for(unsigned int i = 0; i < _meshes.size(); ++i)
        {
            _meshes[i]->Draw();
        }
        glUseProgram(0);
    }
    /*
     * ---------------------------------------------------Mesh---------------------------------------------
     * */
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
        _material = _model->GetMaterial(_mesh->mMaterialIndex);
    }

    void Mesh::ApplyVertex()
    {
        using namespace graph;
        ElementBuffer * ebo = ElementBuffer::Create();
        ebo->SetData(sizeof(unsigned int)*_indices.size(),&_indices[0],GL_STATIC_DRAW);
        _vao = VertexArray::Create(ebo);
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
        if(_material.Diffuse != nullptr)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,_material.Diffuse->GetBufferID());
        }
        if(_material.Normal != nullptr)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D,_material.Normal->GetBufferID());
        }
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid *)0);
        if(_material.Diffuse != nullptr)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,0);
        }
        if(_material.Normal != nullptr)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D,0);
        }

    }


}
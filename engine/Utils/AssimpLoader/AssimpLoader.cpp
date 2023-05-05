#include "AssimpLoader.h"

#include "engine/Meshs/Mesh/Mesh.h"
#include "engine/Materials/Material.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h> 

void AssimpLoader::LoadAssimp(const string& _assimpPath, vector<Mesh*>& _meshs, vector<Material*>& _materials)
{
    Assimp::Importer _importer;
    const aiScene* _aiScene = _importer.ReadFile(_assimpPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if(!_aiScene) return;

    string _texturesPath = _assimpPath.substr(0,_assimpPath.find_last_of('/'))+"/Textures/";
    LoadNodeMeshesMaterials(_texturesPath, _aiScene, _aiScene->mRootNode, aiMatrix4x4(), _meshs, _materials);
}

mat4 AssimpLoader::ASSIMP_To_GLM(const aiMatrix4x4& _matrix)
{
    return mat4(
        (double)_matrix.a1, (double)_matrix.b1, (double)_matrix.c1, (double)_matrix.d1,
        (double)_matrix.a2, (double)_matrix.b2, (double)_matrix.c2, (double)_matrix.d2,
        (double)_matrix.a3, (double)_matrix.b3, (double)_matrix.c3, (double)_matrix.d3,
        (double)_matrix.a4, (double)_matrix.b4, (double)_matrix.c4, (double)_matrix.d4
    );
}
void AssimpLoader::LoadNodeMeshesMaterials(const string& _texturesPath, const aiScene* _aiScene, const aiNode* _node, const aiMatrix4x4& _parentTransformation, vector<Mesh*>& _meshes, vector<Material*>& _materials)
{
    unsigned int* _meshesInNode =_node->mMeshes;
    unsigned int _nbMeshesInNode =_node->mNumMeshes;
    aiMatrix4x4 _localTransformationASSIMP = _node->mTransformation * _parentTransformation;
    mat4 _localTransformationGLM = ASSIMP_To_GLM(_localTransformationASSIMP);

    for(unsigned int i = 0; i<_nbMeshesInNode; ++i)
    {
        Mesh* _mesh = new Mesh();
        _mesh->ClearMeshBuffers();

        aiMesh* _loadedMesh = _aiScene->mMeshes[_meshesInNode[i]];

        unsigned int _nbVertices = _loadedMesh->mNumVertices;
        for(unsigned int i = 0; i<_nbVertices; ++i)
        {
            aiVector3D _position = _loadedMesh->mVertices[i];
            vec4 _positionV4 = _localTransformationGLM * vec4(_position.x,_position.y,_position.z,1);
            _mesh->mPositions.push_back(vec3(_positionV4.x,_positionV4.y,_positionV4.z));

            aiVector3D _uv = _loadedMesh->mTextureCoords[0][i];
            _mesh->mUVs.push_back(vec2(_uv.x,_uv.y));

            aiVector3D _normal = _loadedMesh->mNormals[i];
            _mesh->mNormales.push_back(vec3(_normal.x,_normal.y,_normal.z));
        }

        unsigned int _nbTriangles = _loadedMesh->mNumFaces;
        for(unsigned int i = 0; i<_nbTriangles; ++i)
        {
            aiFace _triangle = _loadedMesh->mFaces[i];
            for (unsigned int j = 0; j < 3; j++) {
                _mesh->mIndices.push_back(_triangle.mIndices[j]);
            }
        }

        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);

        _meshes.push_back(_mesh);

        aiMaterial* _aiMaterial = _aiScene->mMaterials[_loadedMesh->mMaterialIndex];
        _materials.push_back(LoadMaterialAssimp(_texturesPath, _aiMaterial));
    }
    
    aiNode** _nodeChildren = _node->mChildren;
    unsigned int _nbNodeChildren = _node->mNumChildren;
    for(unsigned int i = 0; i<_nbNodeChildren; ++i)
        LoadNodeMeshesMaterials(_texturesPath, _aiScene, _nodeChildren[i], _localTransformationASSIMP, _meshes, _materials);
}

Material* AssimpLoader::LoadMaterialAssimp(const string& _texturesPath, const aiMaterial* _aiMaterial)
{
    Material* _material = new Material();

    aiString _texturePath;
    _aiMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &_texturePath);
    string _path = string(_texturePath.C_Str());
    string _textureName = _path.substr(_path.find_last_of('/')+1);
    if(_textureName != "") _material->SetTexture(TEXTURE_SLOT::ALBEDO, _texturesPath+_textureName);

    return _material;
}
#pragma once

#include <vector>
#include <string>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include <assimp/matrix4x4.h>

class Mesh;
class Material;
class aiScene;
class aiNode;
class aiMaterial;

class AssimpLoader
{
public:
    static void LoadAssimp(const string& _assimpPath, vector<Mesh*>& _meshs, vector<Material*>& _materials);
    static mat4 ASSIMP_To_GLM(const aiMatrix4x4& _matrix);

private:
    static void LoadNodeMeshesMaterials(const string& _texturesPath, const aiScene* _aiScene, const aiNode* _node, const aiMatrix4x4& _parentTransformation, vector<Mesh*>& _meshes, vector<Material*>& _materials);
    static Material* LoadMaterialAssimp(const string& _texturesPath, const aiMaterial* _aiMaterial);
};
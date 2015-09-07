#ifndef ASSIMP_CONVERTER_HPP
#define	ASSIMP_CONVERTER_HPP






#include <stdafx.h>





/**
Using Assimp to convert from varius formats to engine's format (.aao)
*/
class AssimpConverter
{




public:


	/**
	If valid file referenced, the function creates a .aao file representing the model
	*/
	bool ConvertModel(const std::string& Filename);


private:


	/**
	Initializing Assimp on file
	*/
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	/**
    Filling mesh data
	*/
	void InitMesh(GLuint MeshIndex,
		const aiMesh* paiMesh,
		std::vector<glm::vec3>& Positions,
		std::vector<glm::vec3>& Normals,
		std::vector<glm::vec2>& TexCoords,
		std::vector<GLuint>& Indices);





#define INVALID_MATERIAL 0xFFFFFFFF




	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};


	std::vector<MeshEntry> m_Entries;



	const aiScene* m_pScene;
	Assimp::Importer m_Importer;


};


#endif	


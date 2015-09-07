#ifndef SKY_RENDER
#define SKY_REDNER





#include <stdafx.h>




/**


Skydome implementation


*/
class SkyRender : public Shader
{


	std::vector<GLuint> m_textures;
	Aa_model * model;



public:



	/**
	Calls Init()
	*/
	SkyRender() : Shader() { Init(); }
	/**
	Calls Clean()
	*/
	~SkyRender();
	/**
	Inits model
	*/
	void Init();
	/**
	Cleans model and textures
	*/
	void Clean();
	/**
	Loads a cube map and stores it
	*/
	void LoadCube(const char *Directory,
		const char *PosXFilename,
		const char *NegXFilename,
		const char *PosYFilename,
		const char *NegYFilename,
		const char *PosZFilename,
		const char *NegZFilename);

	/**
	Renders to scene
	*/
	void Enable();



};

#endif
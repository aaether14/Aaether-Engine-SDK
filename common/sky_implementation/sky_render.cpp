#include <stdafx.h>






void SkyRender::Init()
{


	model = new Aa_model();
	model->Load("data/objects/sphere/skybox.aao");



	Add("data/shaders/skybox_vert.txt", GL_VERTEX_SHADER);
	Add("data/shaders/skybox_frag.txt", GL_FRAGMENT_SHADER);
	Link();


	AddVariable("MVP");
	AddVariable("MV");
	AddVariable("cube");
	AddVariable("fog_color");



}




SkyRender::~SkyRender()
{
	Clean();
}




void SkyRender::Clean()
{


	Shader::Clean();


	glDeleteTextures(m_textures.size(), &m_textures[0]);

	if (model)
	delete model;


}




void SkyRender::LoadCube(const char *Directory,
	const char *PosXFilename,
	const char *NegXFilename,
	const char *PosYFilename,
	const char *NegYFilename,
	const char *PosZFilename,
	const char *NegZFilename){

	GLuint temp = TextureObject::load_cube_texture(Directory,
		PosXFilename,
		NegXFilename,
		PosYFilename,
		NegYFilename,
		PosZFilename,
		NegZFilename);


	if (temp > 0)
	{
		this->m_textures.push_back(temp);
		printf("%s: %i\n", "Done loading skybox", temp);
	}


}





void SkyRender::Enable()
{


	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);


	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures[0]);
	model->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);
}








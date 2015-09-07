#include <stdafx.h>





void MeshShader::Init()
{


	Add("data/shaders/mesh_vert.txt", GL_VERTEX_SHADER);
	Add("data/shaders/mesh_frag.txt", GL_FRAGMENT_SHADER);
	Link();



	AddVariable("LightMatrix");
	AddVariable("M");
	AddVariable("V");
	AddVariable("P");
	AddVariable("N");
	AddVariable("texture_material");
	AddVariable("Bones[0]");
    AddVariable("specular_intensity");
	AddVariable("specular_power");
	AddVariable("shadow_map");
	AddVariable("ssao_map");
	AddVariable("has_ssao");


	m_light = new Light(this);



}



void MeshShader::Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 NormalMatrix)
{

	Set("M", ModelMatrix);
	Set("V", ViewMatrix);
	Set("P", ProjectionMatrix); 
	Set("N", NormalMatrix);

}



void MeshShader::Clean()
{


	Shader::Clean();
	if (m_light)
	delete m_light;


}





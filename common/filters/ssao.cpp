#include <stdafx.h>




void SSAOImplementation::Init(GLuint width, GLuint height)
{


	//SSAO filter


	this->ssao_shader = new Shader();
	this->ssao_shader->Add("data/shaders/ssao_vert.txt", GL_VERTEX_SHADER);
	this->ssao_shader->Add("data/shaders/ssao_frag.txt", GL_FRAGMENT_SHADER);
	this->ssao_shader->Link();


	this->ssao_shader->AddVariable("gDepthMap");
	this->ssao_shader->AddVariable("gNormalMap");
	this->ssao_shader->AddVariable("gNoiseMap");
	this->ssao_shader->AddVariable("gSampleRad");
	this->ssao_shader->AddVariable("gProj");
	this->ssao_shader->AddVariable("gKernel[0]");
	this->ssao_shader->AddVariable("gAspectRatio");
	this->ssao_shader->AddVariable("gTanHalfFOV");
	this->ssao_shader->AddVariable("gPower");
	this->ssao_shader->AddVariable("gNumSamples");



	this->window_width = width;
	this->window_height = height;


	this->ssao_texture = new TextureObject(1);
	this->ssao_texture->CreateTexture(COLOR_TYPE,GL_TEXTURE_2D, this->window_width, this->window_height, GL_RED, GL_RGBA,
		GL_FLOAT, 0, GL_NEAREST, GL_CLAMP_TO_EDGE);


	this->ssao_temp_texture = new TextureObject(1);
	this->ssao_temp_texture->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, this->window_width, this->window_height, GL_RED, GL_RGBA, 
		GL_FLOAT, 0, GL_NEAREST, GL_CLAMP_TO_EDGE);





	this->Use();
	this->GenKernel();
	this->GenerateNoiseTexture(4);


	//SSAO blur


	this->ssao_blur = new Shader();
	this->ssao_blur->Add("data/shaders/ssao_blur_vert.txt", GL_VERTEX_SHADER);
	this->ssao_blur->Add("data/shaders/ssao_blur_frag.txt", GL_FRAGMENT_SHADER);
	this->ssao_blur->Link();


	this->ssao_blur->AddVariable("texture");


	//Geometry Pass

	this->geometry_pass = new Shader();
	this->geometry_pass->Add("data/shaders/geometry_pass_vert.txt", GL_VERTEX_SHADER);
	this->geometry_pass->Add("data/shaders/geometry_pass_frag.txt", GL_FRAGMENT_SHADER);
	this->geometry_pass->Link();


	this->geometry_pass->AddVariable("MVP");
	this->geometry_pass->AddVariable("MV");
	this->geometry_pass->AddVariable("Bones[0]");
	this->geometry_pass->AddVariable("on_mesh_render");


	this->geometry_pass_texture = new TextureObject(1);
	this->geometry_pass_texture->CreateTexture(G_TYPE,
		GL_TEXTURE_2D,
		window_width, window_height,
		GL_RGB,
		GL_RGBA,
		GL_FLOAT,
		0,
		GL_NEAREST,
		GL_CLAMP_TO_EDGE);
	this->geometry_pass_texture->CreateTexture(DEPTH_TYPE,
		GL_TEXTURE_2D,
		window_width,
		window_height,
		GL_DEPTH_COMPONENT,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		0,
		GL_NEAREST,
		GL_CLAMP_TO_EDGE);




}


void SSAOImplementation::GenKernel()
{

	glm::vec3 kernel[KERNEL_SIZE];

	for (GLuint i = 0; i < KERNEL_SIZE; ++i)
	{
		kernel[i] = glm::vec3(
			Math::randomf(-1.0f, 1.0f),
			Math::randomf(-1.0f, 1.0f),
			Math::randomf(0.0f, 1.0f));
		glm::normalize(kernel[i]);


		GLfloat scale = (GLfloat)i / (GLfloat)(KERNEL_SIZE);
		kernel[i] *= (0.1f + 0.9f * scale * scale);


	}

	this->ssao_shader->Set("gKernel[0]", kernel, KERNEL_SIZE);

}

void SSAOImplementation::SetUniforms(glm::mat4 proj, GLfloat radius, GLfloat aspect, GLfloat tan_fov, GLfloat power, GLint num_samples)
{


	this->ssao_shader->Set("gProj", proj);
	this->ssao_shader->Set("gSampleRad", radius);
	this->ssao_shader->Set("gAspectRatio", aspect);
	this->ssao_shader->Set("gTanHalfFOV", tan_fov);
	this->ssao_shader->Set("gPower", power);
	this->ssao_shader->Set("gNumSamples", num_samples);
	

}


void SSAOImplementation::GenerateNoiseTexture(GLuint size)
{

	glm::vec3 *noise = new glm::vec3[size*size];

	for (int i = 0; i < size*size; ++i) 
	{
		noise[i] = glm::vec3(
			Math::randomf(-1.0f, 1.0f),
			Math::randomf(-1.0f, 1.0f),
			0.0f
			);
		glm::normalize(noise[i]);
	}

	glGenTextures(1, &noise_texture);
	glBindTexture(GL_TEXTURE_2D, noise_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, size, size, 0, GL_RGBA, GL_FLOAT, &noise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);



}



void SSAOImplementation::SetGeometryPassUniforms(glm::mat4 MVP, glm::mat4 MV)
{

	this->geometry_pass->Set("MVP", MVP);
	this->geometry_pass->Set("MV", MV);


}



void SSAOImplementation::BindSSAOTexture()
{


	SetTex2();
	GetGeometryPassTexture()->BindTexture(0, GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE2);
	SetTex3();
	glBindTexture(GL_TEXTURE_2D, GetNoiseTexture());
	SetTex1();

}



void SSAOImplementation::Clean()
{


	if (ssao_shader)
	delete ssao_shader;

	if (ssao_blur)
	delete ssao_blur;


	if (geometry_pass)
	delete geometry_pass;


	if (ssao_texture)
	delete ssao_texture;

	if (ssao_temp_texture)
	delete ssao_temp_texture;


	if (geometry_pass_texture)
	delete geometry_pass_texture;


	glDeleteTextures(1, &noise_texture);


}
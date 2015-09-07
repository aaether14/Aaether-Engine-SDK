#include <stdafx.h>








void FXAAImplementation::Init()
{


	fxaa_shader = new Shader();
	fxaa_shader->Add("data/shaders/fxaa_vert.txt", GL_VERTEX_SHADER);
	fxaa_shader->Add("data/shaders/fxaa_frag.txt", GL_FRAGMENT_SHADER);
	fxaa_shader->Link();


	fxaa_shader->AddVariable("R_filterTexture");
	fxaa_shader->AddVariable("R_fxaaSpanMax");
	fxaa_shader->AddVariable("R_fxaaReduceMin");
	fxaa_shader->AddVariable("R_fxaaReduceMul");




}





void FXAAImplementation::Clean()
{


	if (fxaa_shader)
	delete fxaa_shader;



}




void FXAAImplementation::SetUniforms(GLfloat span_max, GLfloat reduce_min, GLfloat reduce_mul)
{


	fxaa_shader->Set("R_fxaaSpanMax", span_max);
	fxaa_shader->Set("R_fxaaReduceMin", reduce_min);
	fxaa_shader->Set("R_fxaaReduceMul", reduce_mul);


}
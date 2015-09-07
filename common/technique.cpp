#include <stdafx.h>







bool Techniques::Create(GLuint window_width, GLuint window_height, 
	GLuint shadow_width, GLuint shadow_height,
	GLuint dof_width, GLuint dof_height,
	GLuint bright_width, GLuint bright_height)
{




	basic_filter_implementation = new BasicFilterImplementation();
	ssao_implementation = new SSAOImplementation(window_width, window_height);
    esm_implementation = new ESMImplementation(shadow_width, shadow_height);
	blur_implementation = new BlurImplementation();
	dof_implementation = new DofImplementation(dof_width, dof_height);
	hdr_implementation = new HdrImplementation(bright_width, bright_height);
	fxaa_implementation = new FXAAImplementation();
	g_buffer = new GBuffer(window_width, window_height);





	return true;
	
}







void Techniques::Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height)
{


	tex_target->WriteTexture(width, height);
	this->RunProgram(prog_target);


}



void Techniques::Unbind()
{


	esm_implementation->SetShadowPass(false);
	ssao_implementation->SetGeometryPass(false);


	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);


	g_buffer->GetBuffer()->SetViewport();


}





void Techniques::ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height)
{



	this->Bind(prog_target, tex_target, width, height);



	switch (prog_target)
	{
	case NULL_FILTER:
		basic_filter_implementation->BindNullTexture();
		break;
	case GAUS_BLUR_SHADER :
		blur_implementation->BindGausBlurTexture1();
		break;
	case GAUS_BLUR_SHADER2 :
		blur_implementation->BindGausBlurTexture2();
		break;
	case BRIGHT_FILTER :
		hdr_implementation->BindBrightTexture();
		break;
	case SSAO_FILTER :
		ssao_implementation->BindSSAOTexture();
		break;
	case SSAO_BLUR :
	    ssao_implementation->BindBlurTexture();
		break;
	case GAMMA_CORRECTION_FILTER : 
	    basic_filter_implementation->BindGammaTexture();
		break;
	case FXAA_FILTER :
	    fxaa_implementation->BindFxaaTexture();
		break;
	}



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_source);
		GetBasic()->GetQuad()->Render();




}





void Techniques::RunProgram(GLuint prog_target)
{


	switch (prog_target)
	{


	case DEPTH_SHADER :
			esm_implementation->Use();
			break;
	case NULL_FILTER :
			basic_filter_implementation->GetNullFilter()->Enable();
			break;
	case GAUS_BLUR_SHADER :
			blur_implementation->GetGausBlur1()->Enable();
			break;
	case GAUS_BLUR_SHADER2 :
			blur_implementation->GetGausBlur2()->Enable();
			break;
	case BRIGHT_FILTER : 
			hdr_implementation->GetBrightShader()->Enable();
			break;
	case SSAO_FILTER :
			ssao_implementation->Use();
			break;
	case SSAO_BLUR : 
			ssao_implementation->UseBlur();
			break;
	case GAMMA_CORRECTION_FILTER :
			basic_filter_implementation->GetGammaFilter()->Enable();
			break;
	case GEOMETRY_PASS :
			ssao_implementation->UseGeometryPass();
			break;
	case FXAA_FILTER :
			fxaa_implementation->GetFxaaFilter()->Enable();
			break;


	}


}





void Techniques::Clean()
{



	delete basic_filter_implementation;
	delete ssao_implementation;
	delete esm_implementation;
	delete blur_implementation;
	delete dof_implementation;
	delete hdr_implementation;
	delete fxaa_implementation;
	delete g_buffer;




}




void Techniques::Init()
{





}




void Techniques::Enable()
{




}
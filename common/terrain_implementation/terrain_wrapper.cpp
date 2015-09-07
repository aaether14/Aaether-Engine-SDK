#include <stdafx.h>




void TerrainWrapper::Init()
{


	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));



	terra = new Terrain();
	terra->LoadChunks(res->GetTerrainFile());
	terra->LoadColorFiles(res->GetColorFile(),
		res->GetTFile(),
		res->GetNFile(),
		res->GetAFile());






}


void TerrainWrapper::ManagePlayerCollision(Controller*ctrl, bool null_gravity)
{



	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));



	GLfloat terrain_height = HeightAt(terra,
		camera->GetInfo()->getCameraPos().x,
		camera->GetInfo()->getCameraPos().z);



	if (camera->GetInfo()->getCameraPos().y < terrain_height)
		camera->GetInfo()->SetCameraY(terrain_height);


	if (!null_gravity)
		camera->GetInfo()->SetCameraY(terrain_height);




}



void TerrainWrapper::Enable()
{




	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



	Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
	ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
	Environment * env = static_cast<Environment*>(res->Get("Environment"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
	View * view = camera->GetView();
	ViewInfo * info = camera->GetInfo();



	Shader::Enable();
	Shader::Set("myTextureSampler", 0);
	Shader::Set("myTextureSampler2", 1);
	Shader::Set("myTextureSampler3", 2);
	Shader::Set("shadow_map", 3);
	TerrainShader::SendTextureAttributes(terra->GetTextureAttributes(), 4);


	/**
	Raising to power for gamma correction
	*/
	getLight()->SetFog(glm::pow(env->fog_color, glm::vec3(2.2)), env->fog_density);
	getLight()->SetDirectionalLight(env->terrain_bright*
		glm::pow(env->sun_color, glm::vec3(2.2)),
		env->sun_dir,
		env->terrain_ambient,
		env->terrain_diffuse);





	Set("LightMatrix", Math::GetBiasMatrix()*
		tech->GetShadow()->GetDirectionalShadow(env, info, view));



	tech->GetShadow()->GetShadowMap()->BindTexture(0, GL_TEXTURE3);
	tech->GetShadow()->GetShadowMap()->ResetTextureState();




	ManagePlayerCollision(ctrl, false);



}





void TerrainWrapper::Render()
{




	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


	Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
	ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
	Environment * env = static_cast<Environment*>(res->Get("Environment"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
	View * view = camera->GetView();
	ViewInfo * info = camera->GetInfo();





	if (tech->GetSSAO()->OnGeometryPass())
	{


		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera(),
			view->getViewMatrix());


	}
	else if (tech->GetShadow()->OnShadowPass())
	{

		tech->GetShadow()->UniformMVP(tech->GetShadow()->GetDirectionalShadow(env, info, view));


	}
	else
	{


		Space(glm::mat4(1.0), view);


	}



	terra->Render(camera->GetFrustum(), false);




}



void TerrainWrapper::Clean()
{


	TerrainShader::Clean();


	if (terra)
		delete terra;



}



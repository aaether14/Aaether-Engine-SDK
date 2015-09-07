#include <stdafx.h>






void SkyWrapper::Init()
{





	LoadCube("data/objects/sphere/dusk/",
		"px.jpg",
		"nx.jpg",
		"py.jpg",
		"ny.jpg",
		"pz.jpg",
		"nz.jpg");



}

void SkyWrapper::Clean()
{

	SkyRender::Clean();


}







void SkyWrapper::Enable()
{
	


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));




	ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
	Environment * env = static_cast<Environment*>(res->Get("Environment"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
	ViewInfo * info = camera->GetInfo();
	View * view = camera->GetView();





	glm::mat4 m_rot = Math::Rotate(0, glfwGetTime() / 150.0, 0);
	glm::mat4 ModelMatrix = Math::Translation(info->getCameraPos() - info->getDirection()*info->getDistance())*
		m_rot*
		Math::Scale(glm::vec3(info->getRenderDistance()));




	Shader::Enable();
	Shader::Set("cube", 0);
    Shader::Set("MVP", view->getCamera()*ModelMatrix);
	Shader::Set("MV", view->getViewMatrix() * ModelMatrix);
	glm::vec4 f = glm::vec4(env->fog_color, 1.0);
	Shader::Set("fog_color", f);



	SkyRender::Enable();
	Shader::Stop();



}
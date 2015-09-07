#include <stdafx.h>







void Application::Init()
{



	SetManager(this);


	Add("Controller", new Controller());
	Add("DataManager", new DataManager());
	Add("RootUI", new RootUI());
	Add("Pipeline", new Pipeline());






}






void Application::Enable()
{



	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);




	Controller * ctrl = static_cast<Controller*>(Get("Controller"));


	do{


		Get("Controller")->Enable();
		Get("DataManager")->Enable();
		Get("Pipeline")->Enable();
		Get("RootUI")->Enable();



		glfwSwapBuffers(ctrl->GetWindow());
		glfwPollEvents();



	} while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
		!glfwWindowShouldClose(ctrl->GetWindow()));


}





void Application::Clean()
{


	CleanModule();


}





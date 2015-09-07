#include <stdafx.h>





GLuint ControllerSource::keys[] = { 0 };



GLuint ControllerSource::fullscreen_key = 0;
GLboolean ControllerSource::fullscreen = false;

GLint ControllerSource::window_width = 0;
GLint ControllerSource::window_height = 0;
GLchar *ControllerSource::title = 0;


GLuint ControllerSource::opengl_major_version = 0;
GLuint ControllerSource::opengl_minor_version = 0;
GLFWwindow*ControllerSource::window = 0;



glm::vec2 ControllerSource::mouse_position = glm::vec2(0.0f, 0.0f);
GLuint ControllerSource::mouse_buttons[] = { 0 };
GLdouble ControllerSource::wheel_offset = 0.0;
std::vector<std::string> ControllerSource::drop_files;






GLboolean ControllerSource::CreateWindowContext(GLuint window_width, GLuint window_height,
	GLboolean fullscreen,
	char * title,
	GLuint opengl_major_version,
	GLuint opengl_minor_version)
{






	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	ControllerSource::window_width = window_width;
	ControllerSource::window_height = window_height;
	ControllerSource::fullscreen = fullscreen;
	ControllerSource::opengl_major_version = opengl_major_version;
	ControllerSource::opengl_minor_version = opengl_minor_version;
	ControllerSource::title = new GLchar[strlen(title)];
	strcpy(ControllerSource::title, title);





	ControllerSource::window = glfwCreateWindow(window_width, window_height,
		title, (fullscreen == true) ? glfwGetPrimaryMonitor() : NULL, NULL);




	if (ControllerSource::window == NULL){
		fprintf(stderr, "Failed to open GLFW window!\n");
		glfwTerminate();
		return -1;
	}



	glfwMakeContextCurrent(ControllerSource::window);
	glfwSwapInterval(1);


	glewExperimental = true;



	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}





	ControllerSource::InitCallbacks();



	

}




void ControllerSource::Init()
{



	srand(time(NULL));
	this->fps = new FPS();




}




void ControllerSource::InitCallbacks()
{


	glfwSetKeyCallback(ControllerSource::window, ControllerSource::key_callback);
	glfwSetCharCallback(ControllerSource::window, ControllerSource::char_callback);
	glfwSetMouseButtonCallback(ControllerSource::window, ControllerSource::mouse_callback);
	glfwSetCursorPosCallback(ControllerSource::window, ControllerSource::cursor_callback);
	glfwSetWindowSizeCallback(ControllerSource::window, ControllerSource::resize_callback);
	glfwSetScrollCallback(ControllerSource::window, ControllerSource::scroll_callback);
	glfwSetDropCallback(ControllerSource::window, ControllerSource::drop_callback);


}




void ControllerSource::Clean()
{


	glfwDestroyWindow(this->window);
	glfwTerminate();


}








void ControllerSource::Enable()
{



	this->fps->FirstPass();
	this->fps->Compute();




}

void FPS::FirstPass()
{



	GLdouble currentTime = glfwGetTime();
	deltaTime = returnable_deltaTime = GLfloat(currentTime - lastTime2);
	lastTime2 = glfwGetTime();



}



void FPS::Compute(){



	frames++;
	GLdouble currentTime = glfwGetTime();
	deltaTime = GLfloat(currentTime - lastTime);


	if (deltaTime > 1.0f)
	{

		fps = GLfloat(frames) / deltaTime;
		lastTime = currentTime;
		frames = 0;
		lastTime = currentTime;

	}



}



GLvoid ControllerSource::key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods)
{



	CEGUI::Key::Scan ceguiKey = UI_UTIL::GlfwToCeguiKey(key);
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();


	if (action > 0)
	{
		keys[key]++;
		context.injectKeyDown(ceguiKey);
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = 0;
		context.injectKeyUp(ceguiKey);
	}





}



GLvoid ControllerSource::char_callback(GLFWwindow * window, GLuint code)
{


	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	if (context.injectChar(code))
	{
		keys[code + 'A' - 'a'] = 0;
		keys[code] = 0;
	}


}




GLvoid ControllerSource::mouse_callback(GLFWwindow* window, GLint button, GLint action, GLint mods)
{


	CEGUI::MouseButton ceguiMouseButton = UI_UTIL::GlfwToCeguiMouseButton(button);
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();



	if (action > 0)
	{
		mouse_buttons[button]++;
		context.injectMouseButtonDown(ceguiMouseButton);
	}
	else if (action == GLFW_RELEASE)
	{
		mouse_buttons[button] = 0;
		context.injectMouseButtonUp(ceguiMouseButton);
	}



}


GLvoid ControllerSource::cursor_callback(GLFWwindow* window, GLdouble x, GLdouble y)
{


	ControllerSource::mouse_position = glm::vec2(x, y);


	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectMousePosition(GLfloat(x), GLfloat(y));



}


GLvoid ControllerSource::resize_callback(GLFWwindow* window, GLint width, GLint height)
{

	glViewport(0, 0, width, height);
	ControllerSource::window_width = width;
	ControllerSource::window_height = height;

}



GLvoid ControllerSource::scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{

	wheel_offset = yoffset;

}




GLvoid ControllerSource::drop_callback(GLFWwindow* window, GLint count, const GLchar ** paths)
{

	for (GLuint i = 0; i < count; i++)
		drop_files.push_back(paths[i]);

}
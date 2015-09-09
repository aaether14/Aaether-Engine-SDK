#ifndef CONTROLS_SOURCE_HPP
#define CONTROLS_SOURCE_HPP





#include <stdafx.h>





typedef char GLchar;




/**


Class used to calculate framerate and time between frames


*/
class FPS
{


    GLfloat fps;
    GLint frames;
    GLdouble lastTime;
    GLdouble lastTime2;
    GLdouble deltaTime, returnable_deltaTime;




public:



    /**
    Returns current framerate
    */
    inline GLfloat Get()
    {
        return fps;
    }
    /**
    Returns current time between frames
    */
    inline GLdouble Delta()
    {
        return this->returnable_deltaTime;
    }
    /**
    Needs to be called at the begining of each frame
    */
    void FirstPass();
    /**
    Needs to be called the end of each frame - computes required data
    */
    void Compute();



};






/**


Base class for controller
Used to acces window and input


*/
class ControllerSource : public AModule
{



    /**
    Pointer the window to be handled by GLFW
    */
    static GLFWwindow* window;


    /**
    Window data
    */
    static GLint window_width, window_height;
    /**
    Window data
    */
    static GLboolean fullscreen;
    /**
    Window data
    */
    static GLchar * title;
    /**
    Data regarding OpenGL context version
    */
    static GLuint opengl_major_version;
    /**
    Data regarding OpenGL context version
    */
    static GLuint opengl_minor_version;


    //---


    /**
    Pointer to FPS counter
    */
    FPS * fps;



    /**
    Callback to return key presses
    */
    static GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
    /**
    Callback to return key presses (ASCI information)
    */
    static GLvoid char_callback(GLFWwindow * window, GLuint code);
    static GLuint keys[512];
    static GLuint fullscreen_key;


    /**
    Mouse buttons press
    */
    static GLvoid mouse_callback(GLFWwindow* window, GLint button, GLint action, GLint mods);
    static glm::vec2 mouse_position;
    static GLuint mouse_buttons[8];



    static std::vector<std::string> drop_files;
    /**
    Get list of files dropped on window
    */
    static GLvoid drop_callback(GLFWwindow* window, GLint count, const GLchar ** paths);
    /**
    Cursor movement
    */
    static GLvoid cursor_callback(GLFWwindow* window, GLdouble x, GLdouble y);
    /**
    Recives resize information
    */
    static GLvoid resize_callback(GLFWwindow* window, GLint width, GLint height);
    /**
    Mouse wheel information
    */
    static GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset);
    static GLdouble wheel_offset;



    /**
    Initialize callbacks
    */
    static void InitCallbacks();




public:


    /**
    Check if key with 'code' is being pressed
    */
    inline GLuint GetKey(GLuint code)
    {
        return ControllerSource::keys[code];
    }
    /**
    Check if key with 'code' has been pressed once
    */
    inline GLuint GetKeyOnce(GLuint code)
    {
        GLuint result = (ControllerSource::keys[code] == 1);
        if (result)ControllerSource::keys[code]++;
        return result;
    }



    /**
    Return mouse position
    */
    inline glm::vec2 GetMousePosition()
    {
        return ControllerSource::mouse_position;
    }
    /**
    Check is mouse button with 'code' was clicked
    */
    inline GLuint GetMouseButton(GLuint code)
    {
        return ControllerSource::mouse_buttons[code];
    }
    /**
    Check is mouse button with 'code' was clicked once
    */
    inline GLuint GetMouseButtonOnce(GLuint code)
    {
        GLuint result = (ControllerSource::mouse_buttons[code] == 1);
        if (result)ControllerSource::mouse_buttons[code]++;
        return result;
    }
    /**
    Return wheel offset
    */
    inline GLdouble GetWheelOffset()
    {
        return wheel_offset;
    }
    /**
    Reset wheel offset
    */
    inline GLvoid ResetWheelOffset()
    {
        wheel_offset = 0.0;
    }


    /**
    Get pointer to FPS counter
    */
    inline FPS*GetFpsPointer()
    {
        return this->fps;
    }
    /**
    Return window size
    */
    inline glm::ivec2 GetWindowSize()
    {
        return glm::ivec2(this->window_width, this->window_height);
    }
    /**
    Return window size
    */
    inline GLint GetWindowWidth()
    {
        return this->window_width;
    }
    /**
    Return window size
    */
    inline GLint GetWindowHeight()
    {
        return this->window_height;
    }
    /**
    Set the key to be used for switching to fullscreen
    */
    inline void SetFullscreenKey(GLuint key)
    {
        this->ControllerSource::fullscreen_key = key;
    }
    /**
    Get pointer to GLFW window
    */
    inline GLFWwindow * GetWindow()
    {
        return this->window;
    }


    /**
    Get current list of files dropped inside window
    */
    inline std::vector<std::string> GetDropFiles()
    {
        return drop_files;
    }

    /**
    Reset list of files dropped inside window
    */
    inline void ResetDropList()
    {
        drop_files.clear();
    }



    /**
    Calls Init()
    */
    inline ControllerSource()
    {
        this->Init();
    }
    /**
    Get current framerate
    */
    inline GLfloat returnFps()
    {
        return this->fps->Get();
    }


    /**
    Create window out of 'window_window', 'window_height', 'fullscreen', 'title' and OpenGL context version
    */
    static GLboolean CreateWindowContext(GLuint window_width, GLuint window_height,
                                         GLboolean fullscreen,
                                         char * title,
                                         GLuint opengl_major_version,
                                         GLuint opengl_minor_version);



    /**
    Initialize data
    */
    void Init();
    /**
    Compute data
    */
    void Enable();



    /**
    Clean data
    */
    void Clean();
    /**
    Calls Clean()
    */
    inline  ~ControllerSource()
    {
        this->Clean();
    }




};




#endif

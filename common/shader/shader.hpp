#ifndef SHADER_HPP
#define SHADER_HPP





#include <stdafx.h>





/**


Shader class for which makes for easy uniform management using std::map


*/
class Shader : public AModule
{


	GLuint program;
	std::map<std::string, GLuint> uniforms;


public:



	/**
	Calls Init()
	*/
	inline Shader(){ this->Init(); }
	/**
	Calls Clean()
	*/
	inline ~Shader(){ this->Clean(); }
	/**
	Creates a shader program in OpenGL memory
	*/
	inline void Init(){this->program = glCreateProgram(); }
	/**
	Deletes shader program from OpenGL memory and clears uniforms
	*/
	void Clean(){ glDeleteProgram(this->program); this->uniforms.clear(); }


	/**
	Adds a certain shader type from provided path
	*/
	void Add(char * path, GLenum type);
	/**
	Links current shaders in program
	*/
	void Link();
	/**
	OpenGL context is bound to using this program
	*/
	inline void Enable(){ glUseProgram(program); }
	/**
	OpenGL context is no longer bound to a shader program
	*/
	inline void Stop(){ glUseProgram(0); }


	/**
	Link a certain variable to an uniform from the shader source
	*/
	inline void AddVariable(char * name)	{ this->uniforms[name] = glGetUniformLocation(this->program, name); }
	/**
	Set an integer to uniform unit
	*/
	inline void Set(char * name, GLint v){ glUniform1i(this->uniforms[name], v); }
	/**
	Set a float to uniform unit
	*/
	inline void Set(char * name, GLfloat v){ glUniform1f(this->uniforms[name], v); }
	/**
	Set a double to uniform unit
	*/
	inline void Set(char * name, GLdouble v){ glUniform1d(this->uniforms[name], v); }
	/**
	Set a 3D vector to uniform unit
	*/
	inline void Set(char * name, glm::vec3 v){ glUniform3f(this->uniforms[name], v.x, v.y, v.z); }
	/**
	Set a 3D vector to uniform unit
	*/
	inline void Set(char * name, GLfloat x, GLfloat y, GLfloat z){ glUniform3f(this->uniforms[name], x, y, z); }
	/**
	Set a number ('n') of 3D vectors to uniform unit
	*/
	inline void Set(char * name, glm::vec3 * v, GLuint n){ glUniform3fv(this->uniforms[name], n, (const GLfloat*)&v[0]); }
	/**
	Set a 4D vector to uniform unit
	*/
	inline void Set(char * name, glm::vec4 v){ glUniform4f(this->uniforms[name], v.x, v.y, v.z, v.w); }
	/**
	Set a 4D vector to uniform unit
	*/
	inline void Set(char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w){ glUniform4f(this->uniforms[name], x, y, z, w); }
	/**
	Set a 4x4 matrix to uniform unit
	*/
	inline void Set(char * name, glm::mat4 v){ glUniformMatrix4fv(this->uniforms[name], 1, GL_FALSE, &v[0][0]); }



	//Debug stuff


	/**
	Print uniform location - will be 0 if something went wrong
	*/
	inline void Print(char * name){ printf("%i\n", this->uniforms[name]); }


};





#endif

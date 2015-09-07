#ifndef LIGHT
#define LIGHT






#include <stdafx.h>





#define MAX_POINT_LIGHTS 2
#define MAX_SPOT_LIGHTS 2





/**


Storing light uniforms for passing light data
Provides support for directional, point and spot lights


*/
class Light
{



	
	Shader * shader;



	/**
	Initialize directional light uniforms
	*/
	void InitDirectionalLight();
	/**
	Initialize point lights uniforms
	*/
	void InitPointLights();
	/**
	Initialize spot lights uniforms
	*/
	void InitSpotLights();
	/**
	Initialize fog uniforms
	*/
	void InitFog();




public:


	/**
	Calls Init()
	*/
	Light(Shader * shader);
	/**
	Initialize data on a given shader
	*/
	void Init(Shader * shader);


	/**
	Calls Clean()
	*/
	inline ~Light(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Provide data for directional light
	*/
	void SetDirectionalLight(glm::vec3 color, glm::vec3 direction ,float a_intensity, float d_intensity);
	/**
	Provide data for point lights
	*/
	void SetPointLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp);
	/**
	Provide data for spot lights
	*/
	void SetSpotLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp, glm::vec3 direction, GLfloat Cutoff);
	/**
	Provide data for fog
	*/
	void SetFog(glm::vec3 color, GLfloat density);


};

#endif
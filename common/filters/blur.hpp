#ifndef BLUR_HPP
#define BLUR_HPP




#include <stdafx.h>





/**


Basic gaussian blur and logarithmic blur


*/
class BlurImplementation
{



	Shader * gaus_blur1;
	Shader * gaus_blur2;




public:



	/**
	Calls Init()
	*/
	inline BlurImplementation(){ this->Init(); }
	/**
	Initialize data
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~BlurImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Get pointer to gaussian blur shader
	*/
	inline Shader * GetGausBlur1(){ return this->gaus_blur1; }
	/**
	Get pointer to logarithmic blur shader
	*/
	inline Shader * GetGausBlur2(){ return this->gaus_blur2; }


	/**
	Bind texture unit for gaussian blur shader
	*/
	inline void BindGausBlurTexture1(){ this->gaus_blur1->Set("texture", 0); }
	/**
	Bind texture unit for logaritmhic blur shader
	*/
	inline void BindGausBlurTexture2(){ this->gaus_blur2->Set("texture", 0); }


	/**
	Set blur axis for gaussian blur shader
	*/
	inline void SetBlurScale1(glm::vec3 scale){ this->gaus_blur1->Set("blur_scale", scale); }
	/**
	Set blur axis for logarithmic blur shader
	*/
	inline void SetBlurScale2(glm::vec3 scale){ this->gaus_blur2->Set("blur_scale", scale); }





};




#endif
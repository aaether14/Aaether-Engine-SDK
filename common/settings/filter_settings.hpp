#ifndef FILTER_SETTINGS_HPP
#define FILTER_SETTINGS_HPP





#include <stdafx.h>





/**



Storing various settings for filters



*/
class FilterSettings : public AStateSaver
{



public:


	struct SSAOData
	{

		GLboolean Enabled;
		GLfloat Radius;
		GLfloat Power;
		GLint NumSamples;
	}SSAO;


	struct DoFData
	{
		GLboolean Enabled;
	}DoF;



	struct HDRData
	{

		struct BloomData
		{
			GLboolean Enabled;
			GLfloat Whitepoint;
		}Bloom;

	}HDR;



	struct FXAAData
	{

		GLboolean Enabled;
		GLfloat span_max;
		GLfloat reduce_min;
		GLfloat reduce_mul;

	}FXAA;




	/**
	Call Init()
	*/
	inline FilterSettings(char * path){ this->Init(path); }
	/**
	Initialize state saver with the path of the file it will affect
	*/
	void Init(char *path);



	/**
	Reset data
	*/
	void Reset();
	/**
	Save data to file
	*/
	void Save();
	/**
	Load data from file
	*/
	void Load();



};




#endif
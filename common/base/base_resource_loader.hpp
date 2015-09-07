#ifndef BASE_RESOURCE_LOADER_HPP
#define BASE_RESOURCE_LOADER_HPP





#include <stdafx.h>






/**


Can be derived to store any state changers
for centralised save/load


*/
class BaseResourceLoader : public AModule
{


private:





protected:




public:



	/**
	Initializes data
	*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Enables module to affect scene
	*/
	void Enable();




	/**
	Iterates through all state changer map and use their save function
	*/
	void SaveChanges();
	/**
	Iterates through all state changer map and use their load function
	*/
	void LoadChanges();
	/**
	Iterates through all state changer map and use their reset function
	*/
	void NoChanges();



};





#endif
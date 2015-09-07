#ifndef APPLICATION
#define APPLICATION





#include <stdafx.h>




/**
Manager node holding the application's branches
*/
class Application : public AModule
{




public:


	/**
	Calls Init()
	*/
	inline Application() { Init(); }
	/**
	Calls Clean()
	*/
	inline ~Application() { Clean(); }


	/**
	Initializes branches
	*/
	void Init();
	/**
	Cleans branches data
	*/
	void Clean();

	/**
	Enables app
	*/
	void Enable();


};




#endif
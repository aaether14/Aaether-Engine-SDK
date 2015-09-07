#ifndef UI_MANAGER
#define UI_MANAGER




#include <stdafx.h>




/**


CEGUI initialisation


*/
class UIManager : public AModule
{




public:



	/**
	Calls Init()
	*/
	inline UIManager(){ this->Init(); }
	/**
	Initializes CEGUI
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~UIManager(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Renders UI to scene 
	*/
	void Enable();




};






#endif
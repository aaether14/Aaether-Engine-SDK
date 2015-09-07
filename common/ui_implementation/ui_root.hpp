#ifndef ROOT_UI_HPP
#define ROOT_UI_HPP




#include <stdafx.h>






/**


Accesing UI through UIManager and getting pointer of window root


*/
class RootUI : public UIManager
{



	CEGUI::Window* Root;
	RootSettings * root_settings;
	TopRoot * top_root;



public:



	/**
	Calls Init()
	*/
	inline RootUI() : UIManager() { }
	/**
	Initializes UI layouts
	*/
	void Init();





	/**
	Calls Clean()
	*/
	inline ~RootUI(){ this->Clean(); }
	/**
	Cleans UI layouts data
	*/
	void Clean();



	/**
	Renders all layouts to screen
	*/
	void Enable();



};




#endif
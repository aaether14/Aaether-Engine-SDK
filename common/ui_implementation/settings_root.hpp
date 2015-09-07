#ifndef SETTINGS_ROOT_HPP
#define SETTINGS_ROOT_HPP




#include <stdafx.h>





/**


Storing settings on ui side


*/
class RootSettings
{


	GLboolean is_inside_window;



	
	/**
	Callback to check if cursor lies inside the window
	*/
	inline bool MouseInside(const CEGUI::EventArgs& args)
	{
		is_inside_window = true;
		return true;
	}


	/**
	Callback to check if cursor lies outside the window
	*/
	inline bool MouseOutside(const CEGUI::EventArgs& args)
	{
		is_inside_window = false;
		return true;
	}


	/**
	Handles clicking on 'x'
	*/
	inline bool CloseWindow(const CEGUI::EventArgs& e)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Frame")->hide();
		return 1;
	}
	




	ui_LightingRoot * ui_lighting_root;
	ui_FilterRoot * ui_filter_root;





public:



	/**
	Calls Init()
	*/
	inline RootSettings(ResourceLoader * res, CEGUI::Window * Root){ this->Init(res, Root); }
	/**
	Initializes data
	*/
	void Init(ResourceLoader * res, CEGUI::Window * Root);



	/**
	Calls Clean()
	*/
	inline ~RootSettings(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Renders UI layouts to screen
	*/
	void Render(Controller * ctrl, CEGUI::Window * Root);




};




#endif
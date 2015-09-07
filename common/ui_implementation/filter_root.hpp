#ifndef FILTER_ROOT_HPP
#define FILTER_ROOT_HPP




#include <stdafx.h>




/**


Filter settings ui layout management


*/
class ui_FilterRoot
{



	FilterSettings * filter_settings;
	CEGUI::Window * Root;


	/**
	Reset to initial state
	*/
	void Reset();


	/**
	Reset SSAO state
	*/
	void ResetSSAO(std::string def);
	/**
	Reset HDR state
	*/
	void ResetHDR(std::string def);
	/**
	Reset FXAA state
	*/
	void ResetFXAA(std::string def);
	/**
	Reset DoF state
	*/
	void ResetDoF(std::string def);
	/**
	Sync SSAO state
	*/
	void SyncSSAO(std::string def);
	/**
	Sync HDR state
	*/
	void SyncHDR(std::string def);
	/**
	Sync FXAA state
	*/
	void SyncFXAA(std::string def);
	/**
	Sync DoF state
	*/
	void SyncDoF(std::string def);


public:



	/**
	Calls Init()
	*/
	inline ui_FilterRoot(FilterSettings * filter_settings, CEGUI::Window * Root){ this->Init(filter_settings, Root); }
	/**
    Initialize data from UI layout
	*/
	void Init(FilterSettings * filter_settings, CEGUI::Window * Root);


	
	/**
	Calls Clean()
	*/
	inline ~ui_FilterRoot(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Call all sync routines when requested
	*/
	void SyncUI();



};



#endif
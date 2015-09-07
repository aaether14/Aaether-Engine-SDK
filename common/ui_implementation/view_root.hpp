#ifndef VIEW_ROOT_HPP
#define VIEW_ROOT_HPP





#include <stdafx.h>






/**


View tab to control which framewindows are openend


*/
class ui_ViewRoot
{



	CEGUI::Window * Root;




	/**
	Handles openening of the transform tab
	*/
	inline bool ViewTransform(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame3")->show();
		return 1;
	}
	


	/**
	Handles openening of the settings tab
	*/
	inline bool ViewSettings(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame")->show();
		return 1;
	}



	/**
	Handles openening of the scene outliner tab
	*/
	inline bool ViewSceneOutliner(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame2")->show();
		return 1;
	}



public:



	/**
	Calls Init()
	*/
	inline ui_ViewRoot(CEGUI::Window * Root){ this->Init(Root); }
	/**
	Initializes data and sets callbacks
	*/
	void Init(CEGUI::Window * Root);


	/**
	Calls Clean()
	*/
	inline ~ui_ViewRoot(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Sync UI side to internal data side
	*/
	void SyncUI();



};




#endif
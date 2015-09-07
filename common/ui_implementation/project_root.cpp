#include <stdafx.h>





void ui_ProjectRoot::Init(DataManager * dm, CEGUI::Window * Root)
{



	this->dm = dm;
	this->Root = Root;




	Root->getChild("Menubar/MenuItem/PopupMenu/MenuItem")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ProjectRoot::SaveProject, this));


	Root->getChild("Menubar/MenuItem/PopupMenu/MenuItem2")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ProjectRoot::LoadProject, this));


	Root->getChild("Menubar/MenuItem/PopupMenu/MenuItem3")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ProjectRoot::ResetProject, this));




}




void ui_ProjectRoot::Clean()
{




}




void ui_ProjectRoot::SyncUI()
{




}


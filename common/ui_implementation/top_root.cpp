#include <stdafx.h>






void TopRoot::Init(DataManager * dm, CEGUI::Window * Root)
{

    ui_project_root = new ui_ProjectRoot(dm, Root);
    ui_view_root = new ui_ViewRoot(Root);


}




void TopRoot::Clean()
{



    delete ui_project_root;
    delete ui_view_root;


}




void TopRoot::Render(Controller * ctrl, CEGUI::Window * Root)
{


    ui_project_root->SyncUI();
    ui_view_root->SyncUI();


}

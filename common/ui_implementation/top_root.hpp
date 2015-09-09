#ifndef TOP_ROOT_HPP
#define TOP_ROOT_HPP





#include <stdafx.h>






/**


Top bar ui layout management


*/
class TopRoot
{


    ui_ProjectRoot * ui_project_root;
    ui_ViewRoot * ui_view_root;


public:



    /**
    Calls Init()
    */
    inline TopRoot(DataManager * dm, CEGUI::Window * Root)
    {
        this->Init(dm, Root);
    }
    /**
    Initializes top bar layout
    */
    void Init(DataManager * dm, CEGUI::Window * Root);


    /**
    Calls Clean()
    */
    inline ~TopRoot()
    {
        this->Clean();
    }
    /**
    Cleans data
    */
    void Clean();



    /**
    Renders top bar ui layout to screen
    */
    void Render(Controller * ctrl, CEGUI::Window * Root);



};



#endif

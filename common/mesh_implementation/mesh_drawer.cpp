#include <stdafx.h>





void MeshDrawer::Init()
{


    Add("EntityManager", new EntityManager());
    Add("EntityPalette", new EntityPalette());



}




void MeshDrawer::Clean()
{



    CleanModule();



}






void MeshDrawer::Enable()
{




    EntityPalette * entity_palette = static_cast<EntityPalette*>(Get("EntityPalette"));


    entity_palette->ManagePaletteInput();
    entity_palette->ManageEntityPlacing();
    entity_palette->ManageSceneOutliner();




}




void MeshDrawer::Render()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
    MeshShader * shader = static_cast<MeshShader*>((GetManager()->Get("Pipeline"))->Get("MeshWrapper"));
    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    EntityManager * entity_manager = static_cast<EntityManager*>(Get("EntityManager"));
    EntityPalette * entity_palette = static_cast<EntityPalette*>(Get("EntityPalette"));




    shader->SetSpecular(0.0f, 1.0f);
    if (tech->GetShadow()->OnShadowPass())
    {
        glCullFace(GL_FRONT);
        entity_manager->Enable();
        entity_palette->Enable();
        glCullFace(GL_BACK);
    }
    else
    {
        entity_manager->Enable();
        entity_palette->Enable();
    }









}



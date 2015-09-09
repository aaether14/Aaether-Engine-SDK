#include <stdafx.h>







void EntityPalette::Init()
{


    ui_scene_outliner = new ui_SceneOutliner();
    ui_transform_tab = new ui_TransformTab();



    visible = false;
    entity_counter = 0;




    SceneInfo * scene_info = static_cast<SceneInfo*>(GetManager()->Get("DataManager")->Get("Resources")->Get("Entities"));
    current_entity = scene_info->GetEntity(entity_counter);
    InfoComponent * ic = static_cast<InfoComponent*>(current_entity->GetComponent("InfoComponent"));



    current_instance = new EntityInstance();
    current_instance->AddInformation("TransformInfo", new TransformInfo());
    current_instance->SetEntityName(ic->GetInfo()->entity_name);




}



void EntityPalette::Clean()
{


    delete ui_scene_outliner;
    delete ui_transform_tab;


    CleanModule();


}




glm::mat4 EntityPalette::GetMatrix(Entity *entity)
{


    InfoComponent * ic = static_cast<InfoComponent*>(entity->GetComponent("InfoComponent"));




    glm::mat3 trans = ui_transform_tab->GetPInfo()->trans;
    glm::mat4 model_matrix;


    if (ic)
    {
        trans[1] += ic->GetInfo()->base_rot;
        trans[2] *= ic->GetInfo()->base_scale;
    }


    model_matrix = Math::Translation(trans[0])*
                   Math::Rotate(trans[1])*
                   Math::Scale(trans[2]);


    return model_matrix;

}





std::string EntityPalette::GetInstanceName(SceneInfo * scene_info)
{


    std::string instance_name = current_instance->GetEntityName();
    GLuint number_sufix = 2;
    while (scene_info->InstanceExists(instance_name + std::to_string(number_sufix)))
        number_sufix++;
    instance_name += std::to_string(number_sufix);



    return instance_name;




}




void EntityPalette::Enable()
{






    SceneInfo * scene_info = static_cast<SceneInfo*>(GetManager()->Get("DataManager")->Get("Resources")->Get("Entities"));
    current_entity = scene_info->GetEntity(entity_counter);
    InfoComponent * ic = static_cast<InfoComponent*>(current_entity->GetComponent("InfoComponent"));
    current_instance->SetEntityName(ic->GetInfo()->entity_name);




    TransformInfo * info = static_cast<TransformInfo*>(current_instance->GetInformation("TransformInfo"));
    info->matrix = GetMatrix(current_entity);



    if (visible)
        current_entity->Render(GetManager(), current_instance);



}


void EntityPalette::ManagePaletteInput()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    SceneInfo * scene_info = static_cast<SceneInfo*>(GetManager()->Get("DataManager")->Get("Resources")->Get("Entities"));
    Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));



    //applying transform & making visible


    if (ctrl->GetKey(GLFW_KEY_LEFT_ALT))
    {
        ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
        ui_transform_tab->UpdateData();
        visible = true;
    }



    //switching trough the palette


    if (entity_counter > 0 && ctrl->GetKeyOnce(GLFW_KEY_Q))
    {
        entity_counter--;
        ui_transform_tab->GetPInfo()->Reset();
        ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
        ui_transform_tab->UpdateData();
    }
    if (entity_counter < scene_info->GetNumberOfEntities() - 1 && ctrl->GetKeyOnce(GLFW_KEY_E))
    {
        entity_counter++;
        ui_transform_tab->GetPInfo()->Reset();
        ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
        ui_transform_tab->UpdateData();
    }





    //erase entities from scene



    if (ctrl->GetKeyOnce(GLFW_KEY_DELETE))
    {





    }






}



void EntityPalette::ManageEntityPlacing()
{


    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
    Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));


    InfoComponent * ic = static_cast<InfoComponent*>(current_entity->GetComponent("InfoComponent"));








    if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
    {



        visible = false;




        EntityInstance *new_instance = new EntityInstance();
        new_instance->AddInformation("TransformInfo", new TransformInfo());
        TransformInfo * info = static_cast<TransformInfo*>(new_instance->GetInformation("TransformInfo"));
        new_instance->SetEntityName(ic->GetInfo()->entity_name);



        info->matrix = GetMatrix(current_entity);
        info->pos = ui_transform_tab->GetPInfo()->trans[0];
        info->rot = ui_transform_tab->GetPInfo()->trans[1];
        info->scale = ui_transform_tab->GetPInfo()->trans[2];



        if (ic)
        {
            info->rot += ic->GetInfo()->base_rot;
            info->scale *= ic->GetInfo()->base_scale;
        }





        ui_scene_outliner->AddItem(new_instance);
        scene_info->AddInstance(GetInstanceName(scene_info), new_instance);




    }

}




void EntityPalette::ManageSceneOutliner()
{





    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));






    if (scene_info->ShouldReset())
    {


        GetSceneOutliner()->ClearItems();



        std::map<std::string, boost::shared_ptr<EntityInstance> >::iterator it;
        for (it = scene_info->GetFirstInstance(); it != scene_info->GetLastInstance(); it++)
            GetSceneOutliner()->AddItem(it->second.get());



        scene_info->SetShouldReset(false);


    }





}










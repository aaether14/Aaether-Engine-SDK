#include <stdafx.h>






void MeshWrapper::Init()
{


    AModule::Add("MeshDrawer", new MeshDrawer());


}




void MeshWrapper::Enable()

{



    Get("MeshDrawer")->Enable();



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    Environment * env = static_cast<Environment*>(res->Get("Environment"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));
    Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
    View * view = camera->GetView();




    Shader::Enable();
    Shader::Set("texture_material", 0);
    Shader::Set("shadow_map", 1);
    Shader::Set("ssao_map", 2);
    Shader::Set("has_ssao", GLfloat(f_settings->SSAO.Enabled));




    getLight()->SetFog(glm::pow(env->fog_color, glm::vec3(2.2)), env->fog_density);
    getLight()->SetDirectionalLight(env->model_bright*
                                    glm::pow(env->sun_color, glm::vec3(2.2)),
                                    glm::vec3(glm::normalize(-view->getViewMatrix() * glm::vec4(env->sun_dir, 0.0))),
                                    env->model_ambient,
                                    env->model_diffuse);




    tech->GetShadow()->GetShadowMap()->BindTexture(0, GL_TEXTURE1);
    tech->GetSSAO()->GetSSAOTexture()->BindTexture(0, GL_TEXTURE2);
    tech->GetShadow()->GetShadowMap()->ResetTextureState();


}




void MeshWrapper::Render()
{


    static_cast<MeshDrawer*>(Get("MeshDrawer"))->Render();


}


void MeshWrapper::Clean()
{


    MeshShader::Clean();
    CleanModule();


}







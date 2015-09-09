#include <stdafx.h>







void Pipeline::Init()
{



    Add("MeshWrapper", new MeshWrapper());
    Add("TerrainWrapper", new TerrainWrapper());
    Add("SkyWrapper", new SkyWrapper());
    Add("ScreenRender", new ScreenRender());



}



void Pipeline::GeometryPass()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    MeshWrapper * mesh_wrapper = static_cast<MeshWrapper*>(Get("MeshWrapper"));
    TerrainWrapper * terrain_wrapper = static_cast<TerrainWrapper*>(Get("TerrainWrapper"));



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tech->GetSSAO()->GetGeometryPassTexture()->WriteTexture(ctrl->GetWindowWidth(), ctrl->GetWindowHeight());
    tech->GetSSAO()->UseGeometryPass();
    tech->GetSSAO()->SetGeometryPass(true);
    tech->GetSSAO()->SetOnMeshRender(0.0);
    terrain_wrapper->Render();
    tech->GetSSAO()->SetOnMeshRender(1.0);
    mesh_wrapper->Render();
    tech->Unbind();




}



void Pipeline::LightPass()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));




    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
    View * view = camera->GetView();
    ViewInfo * info = camera->GetInfo();



    MeshWrapper * mesh_wrapper = static_cast<MeshWrapper*>(Get("MeshWrapper"));
    TerrainWrapper * terrain_wrapper = static_cast<TerrainWrapper*>(Get("TerrainWrapper"));
    SkyWrapper * sky_wrapper = static_cast<SkyWrapper*>(Get("SkyWrapper"));




    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tech->GetGBuffer()->GetBuffer()->WriteTexture(ctrl->GetWindowWidth(), ctrl->GetWindowHeight());








    sky_wrapper->Enable();
    terrain_wrapper->Enable();
    terrain_wrapper->Render();
    mesh_wrapper->Enable();
    mesh_wrapper->Render();





    tech->ApplyFilter(GAMMA_CORRECTION_FILTER,
                      tech->GetGBuffer()->GetBuffer()->GetTexture()[0],
                      tech->GetGBuffer()->GetColorTextures()[0],
                      ctrl->GetWindowWidth(),
                      ctrl->GetWindowHeight());





    tech->Unbind();




}




void Pipeline::ShadowPass()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ESMImplementation * esm_shadow = tech->GetShadow();
    MeshWrapper * mesh_wrapper = static_cast<MeshWrapper*>(Get("MeshWrapper"));



    esm_shadow->GetShadowMap()->WriteTexture(ShadowMapWidth, ShadowMapHeight);
    esm_shadow->SetShadowPass(true);
    esm_shadow->Use();



    mesh_wrapper->Render();



    this->ApplyGausBlur(0,
                        esm_shadow->GetTempShadowMap(),
                        esm_shadow->GetShadowMap(),
                        ShadowMapWidth,
                        ShadowMapHeight,
                        0.3f);



    tech->Unbind();



}



void Pipeline::HandleDoF()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    if (f_settings->DoF.Enabled)
    {




        DofImplementation * dof = tech->GetDof();



        tech->ApplyFilter(NULL_FILTER,
                          tech->GetGBuffer()->GetTexture()->GetTexture()[0],
                          dof->GetDofTexture(),
                          dof->GetDofTexture()->GetWidth(),
                          dof->GetDofTexture()->GetHeight());



        GLuint blur_passes = 3;
        for (GLuint i = 0; i < blur_passes; i++)
            this->ApplyGausBlur(1,
                                dof->GetDofTempTexture(),
                                dof->GetDofTexture(),
                                dof->GetDofTexture()->GetWidth(),
                                dof->GetDofTexture()->GetHeight(),
                                2.5 * pow(2, i));




        tech->Unbind();



    }


}



void Pipeline::HandleBloom()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    if (f_settings->HDR.Bloom.Enabled)
    {




        HdrImplementation * hdr = tech->GetHdr();



        tech->RunProgram(BRIGHT_FILTER);
        hdr->SetUniforms(f_settings->HDR.Bloom.Whitepoint);



        tech->ApplyFilter(BRIGHT_FILTER,
                          tech->GetGBuffer()->GetColorTextures()[0]->GetTexture()[0],
                          hdr->GetBrightTexture(),
                          hdr->GetBrightTexture()->GetWidth(),
                          hdr->GetBrightTexture()->GetHeight());



        GLuint blur_passes = 3;
        for (GLuint i = 0; i < blur_passes; i++)
            this->ApplyGausBlur(1,
                                hdr->GetBrightTextureTemp(),
                                hdr->GetBrightTexture(),
                                hdr->GetBrightTexture()->GetWidth(),
                                hdr->GetBrightTexture()->GetHeight(),
                                2.5 * pow(2, i));




        tech->GetBasic()->AddTextures(
            tech->GetGBuffer()->GetOtherTexture(),
            tech->GetGBuffer()->GetTexture()->GetTexture()[0],
            hdr->GetBrightTexture()->GetTexture()[0],
            ctrl->GetWindowSize());


        tech->GetGBuffer()->Switch();
        tech->Unbind();


    }



}




void Pipeline::HandleFXAA()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    if (f_settings->FXAA.Enabled)
    {



        FXAAImplementation * fxaa = tech->GetFXAA();




        tech->RunProgram(FXAA_FILTER);
        tech->GetFXAA()->SetUniforms(f_settings->FXAA.span_max, f_settings->FXAA.reduce_min, f_settings->FXAA.reduce_mul);



        tech->ApplyFilter(FXAA_FILTER,
                          tech->GetGBuffer()->GetTexture()->GetTexture()[0],
                          tech->GetGBuffer()->GetOtherTexture(),
                          ctrl->GetWindowWidth(),
                          ctrl->GetWindowHeight());



        tech->GetGBuffer()->Switch();
        tech->Unbind();





    }




}





void Pipeline::HandleSSAO()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    if (f_settings->SSAO.Enabled)
    {



        Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
        View * view = camera->GetView();
        ViewInfo * info = camera->GetInfo();
        SSAOImplementation * ssao = tech->GetSSAO();



        tech->RunProgram(SSAO_FILTER);


        ssao->SetUniforms(view->getProjectionMatrix(), f_settings->SSAO.Radius,
                          info->getRatio(), info->getTanHalfFov(), f_settings->SSAO.Power, f_settings->SSAO.NumSamples);


        tech->ApplyFilter(SSAO_FILTER, ssao->GetGeometryPassTexture()->GetDepth(),
                          ssao->GetSSAOTempTexture(),
                          ctrl->GetWindowWidth(),
                          ctrl->GetWindowHeight());



        tech->ApplyFilter(SSAO_BLUR,
                          ssao->GetSSAOTempTexture()->GetTexture()[0],
                          ssao->GetSSAOTexture(),
                          ctrl->GetWindowWidth(),
                          ctrl->GetWindowHeight());



        tech->Unbind();




    }

}


void Pipeline::Enable()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
    ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    this->GeometryPass();
    this->HandleSSAO();


    this->ShadowPass();
    this->LightPass();


    tech->GetGBuffer()->Reset();


    this->HandleDoF();
    this->HandleBloom();
    this->HandleFXAA();



    static_cast<ScreenRender*>(Get("ScreenRender"))->Render(
        tech->GetGBuffer()->GetTexture()->GetTexture()[0],
        tech->GetGBuffer()->GetBuffer()->GetDepth(),
        tech->GetDof()->GetDofTexture()->GetTexture()[0],
        GLfloat(f_settings->DoF.Enabled),
        f_settings->HDR.Bloom.Whitepoint,
        ctrl->GetWindowSize());

}




void Pipeline::Clean()
{

    CleanModule();

}




void Pipeline::ApplyGausBlur(GLuint type,
                             TextureObject * tex_source, TextureObject * tex_target,
                             GLuint width, GLuint height,
                             GLfloat blur_amount)
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
    Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));



    if (type == 0)
    {
        tech->RunProgram(GAUS_BLUR_SHADER);
        tech->GetBlur()->SetBlurScale1(glm::vec3(0.0f, 1.0f / width * blur_amount, 0.0f));
        tech->ApplyFilter(GAUS_BLUR_SHADER, tex_target->GetTexture()[0], tex_source, width, height);
        tech->GetBlur()->SetBlurScale1(glm::vec3(1.0f / width * blur_amount, 0.0f, 0.0f));
        tech->ApplyFilter(GAUS_BLUR_SHADER, tex_source->GetTexture()[0], tex_target, width, height);
    }
    else if (type == 1)
    {
        tech->RunProgram(GAUS_BLUR_SHADER2);
        tech->GetBlur()->SetBlurScale2(glm::vec3(0.0f, 1.0f / width * blur_amount, 0.0f));
        tech->ApplyFilter(GAUS_BLUR_SHADER2, tex_target->GetTexture()[0], tex_source, width, height);
        tech->GetBlur()->SetBlurScale2(glm::vec3(1.0f / width * blur_amount, 0.0f, 0.0f));
        tech->ApplyFilter(GAUS_BLUR_SHADER2, tex_source->GetTexture()[0], tex_target, width, height);
    }

}






///----------------



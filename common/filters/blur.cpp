#include <stdafx.h>




void BlurImplementation::Init()
{


    this->gaus_blur1 = new Shader();
    this->gaus_blur1->Add("data/shaders/gaus_blur_vert.txt", GL_VERTEX_SHADER);
    this->gaus_blur1->Add("data/shaders/gaus_blur_frag.txt", GL_FRAGMENT_SHADER);
    this->gaus_blur1->Link();


    this->gaus_blur1->AddVariable("texture");
    this->gaus_blur1->AddVariable("blur_scale");



    this->gaus_blur2 = new Shader();
    this->gaus_blur2->Add("data/shaders/gaus_blur_vert2.txt", GL_VERTEX_SHADER);
    this->gaus_blur2->Add("data/shaders/gaus_blur_frag2.txt", GL_FRAGMENT_SHADER);
    this->gaus_blur2->Link();


    this->gaus_blur2->AddVariable("texture");
    this->gaus_blur2->AddVariable("blur_scale");



}




void BlurImplementation::Clean()
{

    if (gaus_blur1)
        delete gaus_blur1;


    if (gaus_blur2)
        delete gaus_blur2;


}

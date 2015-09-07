#include <stdafx.h>





void Entity::Render(AModule * manager, AEntityInstance * entity_instance)
{




	TransformInfo * transform_info = static_cast<TransformInfo*>(entity_instance->GetInformation("TransformInfo"));



	if (transform_info)
	{



		DataManager * dm = static_cast<DataManager*>(manager->Get("DataManager"));
		Camera * cam = static_cast<Camera*>(manager->Get("Controller")->Get("Camera"));


		ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
		Techniques * tech = static_cast<Techniques*>(dm->Get("Techniques"));
		MeshShader * shader = static_cast<MeshShader*>(manager->Get("Pipeline")->Get("MeshWrapper"));



		View * view = cam->GetView();
		ViewInfo * info = cam->GetInfo();








		ModelComponent * model_component = static_cast<ModelComponent*>(GetComponent("ModelComponent"));



		if (model_component)
		{


			Environment * env = static_cast<Environment*>(res->Get("Environment"));
			InfoComponent * info_component = static_cast<InfoComponent*>(GetComponent("InfoComponent"));


			if (tech->GetSSAO()->OnGeometryPass())
				tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * transform_info->matrix,
				view->getViewMatrix() *  transform_info->matrix);
			else if (tech->GetShadow()->OnShadowPass())
				tech->GetShadow()->UniformMVP(
				tech->GetShadow()->GetDirectionalShadow(env, info, view)
				* transform_info->matrix);
			else
			{





				shader->Space(transform_info->matrix, view);


				glm::mat4 biasMatrix(
					0.5, 0.0, 0.0, 0.0,
					0.0, 0.5, 0.0, 0.0,
					0.0, 0.0, 0.5, 0.0,
					0.5, 0.5, 0.5, 1.0
					);





				shader->Set("LightMatrix", biasMatrix*
					tech->GetShadow()->GetDirectionalShadow(env, info, view)* transform_info->matrix);

			}




			if (!(tech->GetSSAO()->OnGeometryPass() && !info_component->GetInfo()->affected_by_ssao))
			{


				if (!info_component->GetInfo()->cull)
				{
					glDisable(GL_CULL_FACE);
					model_component->GetModel()->Render();
					glEnable(GL_CULL_FACE);
				}
				else
					model_component->GetModel()->Render();

			}



		}



	}



}



 


void Entity::Clean()
{


	components.clear();


}



vector<Model> model_mesh_memory;
vector<Mover> mover_memory;

enum Entity_Component_Type {
	COMPONENT_MESH,
	COMPONENT_PRIMITIVE,
	COMPONENT_MOVER
};

struct component_mesh_renderer {
	ui32 data_id;
};

struct component_mover {
	ui32 data_id;
};

struct Entity {
	ui32 id;
	Transform transform;
	vector<component_mesh_renderer> mesh_components;
	vector<component_mover> mover_components;
};

vector<Entity> entities;
void attach_component(Entity &e, Entity_Component_Type type, Model &mesh_data)
{
	switch(type)
	{
		case COMPONENT_MESH: 
		{
			component_mesh_renderer t;
			t.data_id = e.mesh_components.size();
			e.mesh_components.push_back(t);
			mesh_data.transform.r = mat4(1.0f);
			model_mesh_memory.push_back(mesh_data);
			
			//assert(t.data_id == model_mesh_memory.size()-1);
		} break;
		
		case COMPONENT_MOVER:
		{
			component_mover t;
			t.data_id = e.mover_components.size();
			e.mover_components.push_back(t);
			Mover m = {};
			mover_memory.push_back(m);
			
			//assert(t.data_id == mover_memory.size()-1);
		} break;
		
		case COMPONENT_PRIMITIVE:
		{
			
		} break;
		
		default: cout << "no type was recognized" << endl; e.id = -1;
	}
}

void push_entity(Entity &e)
{
	e.id = entities.size();
	entities.push_back(e);
}

void delete_entity(ui32 id)
{
	if(id < entities.size()) 
	{
		cout << "trying to delete non existant entity at: " << id << endl;
	}
	else
	{
		entities.erase(entities.begin() + index);
	}
}

void delete_component(ui32 entity_index, Entity_Component_Type type)
{
	switch(type)
	{
		case COMPONENT_MESH: 
		{
			if(entity_index <= entities.size())
			{
				if(entities[entity_index].mesh_components.size() > 0)
				{
					int index = entities[entity_index].mesh_components.size();
					entities[entity_index].mesh_components.erase(entities[entity_index].mesh_components.begin() + index);
					model_mesh_memory.erase(model_mesh_memory.begin() + index);
				}
			}
		} break;
		
		case COMPONENT_MOVER:
		{
			if(entity_index <= entities.size())
			{
				if (entities[entity_index].mover_components.size() > 0)
				{
					ui32 index = entities[entity_index].mover_components.size();
					entities[entity_index].mover_components.erase(entities[entity_index].mover_components.begin() + index);
					mover_memory.erase(mover_memory.begin() + index);
				}
				
			}
			
		} break;
		
		case COMPONENT_PRIMITIVE:
		{
			
		} break;
		
		default: cout << "no type was recognized." << endl;
	}
}

void process_entities()
{
	for(ui32 eid = 0; eid < entities.size(); eid++)
	{
		Entity *e = &entities[eid];
		
		if(e->id == -1)
		{
			cout << "skipped entity id: " << e->id << endl;
			continue;
		}
		if(e->mesh_components.size() > 0)
		{
			//e->transform.translate(vec3(sinf(time_state.seconds_passed)*eid, cosf(time_state.seconds_passed)*eid, 0.0f) * (eid * time_state.dt));
			ui32 index = e->mesh_components[e->mesh_components.size()-1].data_id;
			render_model(model_mesh_memory[index], e->transform, &camera, &default_shader);
		}
		if(e->mover_components.size() == 1)
		{
			ui32 index = e->mover_components[e->mover_components.size()-1].data_id;
			update_movers(e->transform, 1.0f, input_state, time_state);
		}
	}
}









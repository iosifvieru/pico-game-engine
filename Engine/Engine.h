#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>
#include "Engine/Entity/Entity.h"
#include "Engine/Systems/System.h"

/*
Engine is a singleton class that centralizes systems and entities.
*/
class Engine {
private:
    std::vector<System*> systems;
    std::vector<Entity*> entities;
    std::vector<Entity*> deleted_entities;

    Engine();
    ~Engine();

    Engine(const Engine& e) = delete;

    static Engine* instance;

    void delete_entities();
    
public:
    static Engine& getInstance() {
        if(instance == nullptr){
            instance = new Engine();
            instance->init();
        }
        return *instance;
    }
    
    /*
        Initializes the engine.
        the reserve function allocates in advance some memory for better performance.
    */
    void init(){
        this->systems.reserve(MAX_NO_SYSTEMS);
        this->entities.reserve(MAX_NO_ENTITIES);
    };

    /* adds an entity to the list. */
    void add_entity(Entity* entity);

    /* removes an entity from the list. */
    void remove_entity(Entity* entity);

    /* returns the entities. */
    const std::vector<Entity*>& get_entities() const{
        return this->entities;
    }

    /* adds a system to the list. */
    void add_system(System* system);
    
    /* removes a system */
    void remove_system(System* system);

    /* 
        update function
        this function calls every system's update function.
    */
    void update();


    void run(uint8_t framerate);

    void clear() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    
        for (Entity* entity : deleted_entities) {
            delete entity;
        }
        deleted_entities.clear();
    
        for (System* system : systems) {
            delete system;
        }
        systems.clear();
    }
    
};

#endif
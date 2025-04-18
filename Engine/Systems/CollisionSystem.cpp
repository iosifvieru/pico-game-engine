#include "Engine/Systems/CollisionSystem.h"
#include "Engine/Components/PositionComponent.h"
#include "Engine/Components/SquareComponent.h"
#include "Engine/Components/VelocityComponent.h"

#include "Engine/Logger/Logger.h"

/*
this is the update function of the collision system.
this function iterates through every entity and checking if two collide.

it is only responsible for detecting collision. it DOES NOT handle it in some way.
*/
void CollisionSystem::update(const std::vector<Entity*>& entities) {
    for(const auto& entity1 : entities){
        /* pointer to square component. */
        SquareComponent* square_component1 = (SquareComponent*) entity1->get_component("SquareComponent");
        if(square_component1 == nullptr) continue;

        /* pointer to position component. */
        PositionComponent* position1 = (PositionComponent*) entity1->get_component("PositionComponent");
        if(position1 == nullptr) continue;

        /* resetting all the flags. */
        square_component1->collided = false;

        /* TODO:
            find a better way to check for collisions.
            so far the implementation is a O(n^2)..
            which is really slow.. but for now it looks good.
        */
        for(const auto& entity2: entities){
            /* skipping if comparing the entity with itself. */
            if(entity1 == entity2) continue;

            SquareComponent* square_component2 = (SquareComponent*) entity2->get_component("SquareComponent");
            if(square_component2 == nullptr) continue;

            /*
            COLLISION BUG FIXED!!!!!!!

            the problem was that i was not breaking the loop and i was further
            checking for collisions, setting the collided variable to false
            because the implementation looked like this:
            
            square_component1->collided = square_component1->has_collided(...);
            */

            if(has_collided(square_component1, square_component2)){
                square_component1->collided = true;
                break;
            }
        }
        
        /* modifing the collision square's position. */
        square_component1->set_x(position1->x);
        square_component1->set_y(position1->y);
    }
}

/* this function takes two square components as input and returns true if collided. */
bool has_collided(SquareComponent* e1, SquareComponent* e2){
    if(e1->get_max_x() < e2->get_x() || e1->get_x() > e2->get_max_x()) {
        return false;
    }

    if(e1->get_max_y() < e2->get_y() || e1->get_y() > e2->get_max_y()){
        return false;
    }

    /* the object has collided */
    return true;
}
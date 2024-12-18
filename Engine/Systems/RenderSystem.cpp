#include "Engine/Systems/RenderSystem.h"
#include "Engine/Logger/Logger.h"
#include "Engine/Components/PositionComponent.h"
#include "Engine/Components/SpriteComponent.h"

RenderSystem::RenderSystem(Canvas& canvas, Display& display): canvas(canvas), display(display) {
    //

}

RenderSystem::~RenderSystem(){
    //
}

void RenderSystem::update(std::list<Entity*> entities){
    /* clears the canvas*/
    canvas.fill(0x0000);

    /* redraws everything. */
    for(auto& entity : entities){
        if(entity == nullptr) continue;

        PositionComponent* p = (PositionComponent*) entity->get_component("PositionComponent");
        if(p == nullptr) continue;

        SpriteComponent* sprite = (SpriteComponent*) entity->get_component("SpriteComponent");
        if(sprite == nullptr) continue;
        
        canvas.draw_sprite(p->x, p->y, sprite->width, sprite->height, sprite->sprite);

        /* hardcoding some stuff for now. */
        /*
        if(entity->has_component("SquareCollider")){
            SquareCollider *sq = (SquareCollider*) entity->get_component("SquareCollider");

            if(sq == nullptr){
                continue;
            }

            if(sq->is_visible == false){
                continue;
            }

            SquareComponent sqc = *sq->square_collider;
            
            canvas.draw_rect(sqc.max_x, sqc.max_y, sqc.min_x, sqc.min_y, 0x001f);
            //canvas.draw_rect(50, 50, 100, 100, 0xffff);
        } */
    }

    /* flushes to display. */
    display.flush(canvas.get_buffer());
}
#include "pico/stdlib.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "Engine/Drivers/DisplayDriver/ST7735.h"
#include "Engine/Canvas/BufferedCanvas.h"
#include "Engine/Canvas/BasicCanvas.h"

#include "Engine/Systems/MovementSystem.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Engine.h"
#include "Engine/Drivers/InputDriver/Keyboard.h"
#include "Engine/Systems/RenderSystem.h"
#include "Engine/Systems/CollisionSystem.h"

#include "Engine/Components/PositionComponent.h"
#include "Engine/Components/SpriteComponent.h"

#include "Games/TestEntity.h"
#include "Games/Enemy.h"

#include <stdlib.h>

#define FRAME_TIME_US (1000000 / 60)
int main() { 
    stdio_init_all();

    Keyboard& keyboard = Keyboard::getInstance();
    Display& display = ST7735::getInstance();
    Canvas *canvas = new BufferedCanvas(display.get_width(), display.get_height());
    RenderSystem r(*canvas, display);
    
    MovementSystem mv_system;
    CollisionSystem collision_system;

    Engine& engine = Engine::getInstance();
    
    keyboard.config(13);

    engine.add_system(&mv_system);
    engine.add_system(&r);
    engine.add_system(&collision_system);

    TestEntity* test_entity = new TestEntity();
    engine.add_entity(test_entity);

    for(int i = 0; i < 200; i++){
        int x = (rand() % 120) + 5;
        int y = (rand() % 100) + 5;

        Enemy* enemy = new Enemy(x, y);
        engine.add_entity(enemy);
    }

    for (;;) {
        engine.update();
    }
    return 0;
}
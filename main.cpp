#include "pico/stdlib.h"
#include <time.h>
#include <stdio.h>

#include "Engine/Drivers/DisplayDriver/ST7735.h"
#include "Engine/Canvas/BufferedCanvas.h"
#include "Engine/Renderer/BasicRenderer.h"

uint16_t x = 10;
uint16_t y = 10;


int main() {
    stdio_init_all();

    gpio_init(8);
    gpio_set_dir(8, GPIO_IN);
    gpio_pull_up(8);

    gpio_init(14);
    gpio_set_dir(14, GPIO_IN);
    gpio_pull_up(14);

    Display& display = ST7735::getInstance();
    Canvas* canvas = new BufferedCanvas(display.get_width(), display.get_height());

    /* test sprite */
    const uint16_t sprite[8] = {
        0xffff, 0xf10f,
        0xabc1, 0x11fb,
        0x1111, 0x1212,
        0x1444, 0x1BCA
    };

    canvas->fill(0xf800);

    canvas->draw_sprite(78, 78, 4, 2, sprite);

    Canvas* canvas2 = new BufferedCanvas(display.get_width(), display.get_height());

    const uint16_t spritee[9] = {
        0x1B33, 0x1B33, 0x1B33,
        0x1B33, 0x1B33, 0x1B33,
        0x1B33, 0x1B33, 0x1B33
    };

    Renderer* renderer = new BasicRenderer(display);
    renderer->add_layer(canvas);
    renderer->add_layer(canvas2);

    for (;;) {
        bool is_pressed_x = !gpio_get(8);
        bool is_pressed_y = !gpio_get(14);

        if (is_pressed_x) {
            x += 5;
            x = x % display.get_width();
        }

        if(is_pressed_y){
            y += 5;
            y = y % display.get_height();
        }

        renderer->Render();

    }

    return 0;
}
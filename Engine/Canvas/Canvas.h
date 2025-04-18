#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <cstdint>

/* 
Abstract canvas class.
*/
class Canvas {
protected:
    uint16_t width, height;
public:
    Canvas(uint16_t width, uint16_t height) : width(width), height(height) {};
    ~Canvas() = default;

    /* returns height of canvas */
    uint16_t get_height(){
        return this->height;
    }

    /* returns width of canvas */
    uint16_t get_width(){
        return this->width;
    }

    /* returns the canvas buffer */
    virtual const uint16_t* get_buffer() = 0;

    /* fills the canvas with a certain color */
    virtual void fill(uint16_t color) = 0;

    /* sets a certain pixel's color */
    virtual void set_pixel(uint16_t x, uint16_t y, uint16_t color) = 0;

    /* gets the color of a pixel */
    virtual uint16_t get_pixel(uint16_t x, uint16_t y) = 0;

    /* draws a sprite to a certain x, y position. */
    virtual void draw_sprite(uint16_t x, uint16_t y, uint16_t sprite_width, uint16_t sprite_height, const uint16_t* sprite) = 0;

    /* draw a line to the canvas */
    virtual void draw_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color) = 0;

    /* draws a rect to canvas */
    virtual void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) = 0;

    /* clears the canvas */
    virtual void clear() = 0;
};

#endif
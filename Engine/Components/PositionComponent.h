#ifndef _POSITION_COMPONENT_H_
#define _POSITION_COMPONENT_H_

#include "Engine/Components/Component.h"
#include "pico/stdlib.h"

class PositionComponent : public Component {
public:
    float x = 0;
    float y = 0;
    uint16_t z = 0;
    uint16_t angle = 0;

    PositionComponent() {};
    PositionComponent(float x, float y){
        this->x = x;
        this->y = y;
        this->z = 0;
        this->angle = 0;

        Logger::log("PositionComponent(uint x, uint y);");
    }
    PositionComponent(float x, float y, uint16_t z, uint16_t angle) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->angle = angle;
        Logger::log("PositionComponent()");
    };

    ~PositionComponent(){
        Logger::log("~PositionComponent()");
    };

    PositionComponent(const PositionComponent& other){
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->angle = other.angle;
    };

    PositionComponent operator=(const PositionComponent& other){
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->angle = other.angle;

        return *this;
    }

    const char* get_component_name() const {
        return "PositionComponent";
    }
};


#endif
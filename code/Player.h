//
// Created by loren on 09/02/2021.
//

#ifndef BASICS_HEXAGON_PLAYER_H
#define BASICS_HEXAGON_PLAYER_H

#include <basics/internal/Point.hpp>
#include <basics/internal/Size.hpp>
#include <basics/internal/Canvas.hpp>
#include <basics/internal/Rotation.hpp>
#include <basics/internal/Translation.hpp>
#include <basics/internal/Matrix.hpp>

#include "Color.h"
#include "Playfield.h"

using basics::Point2f;
using basics::Size2f;
using basics::Canvas;

namespace sh
{
    class Playfield;
    class Player
    {
    public:
        float angle;
        float separation;
        float length;
        float shadow;
        Color color;
        Point2f position;
        Playfield * playfield;

        Player(const Size2f & canvas_size, Playfield * pf)
        {
            float ref  = std::min (canvas_size.width, canvas_size.height);
            angle      = 0.f;
            separation = ref * 0.200f;
            length     = ref * 0.025f;
            shadow     = ref * 0.005f;
            color      = { 1.f, 1.f, 1.f };
            position   = { separation, 0 };
            playfield  = pf;

        }

        void spin (float amount)
        {
            // Si el ángulo que adquiere el jugador es un ángulo mayor o igual al equivalente al dar 6 vueltas, se reinicia a 0.
            if(abs(angle / 1.047197) >= 6) angle = 0;
            angle += amount;

        }

        void render (Canvas & canvas);
    };
}


#endif //BASICS_HEXAGON_PLAYER_H

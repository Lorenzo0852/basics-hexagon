//
// Created by loren on 09/02/2021.
//

#ifndef BASICS_HEXAGON_PLAYFIELD_H
#define BASICS_HEXAGON_PLAYFIELD_H

#include <basics/internal/Canvas.hpp>
#include <basics/internal/Size.hpp>
#include <basics/internal/Vector.hpp>
#include <basics/internal/Point.hpp>
#include <list>
#include "Color.h"

using basics::Canvas;
using basics::Size2f;
using basics::Vector2f;
using basics::Point2f;
using basics::Vector4f;

namespace sh
{

    class Playfield
    {
        ///Número de pistas por las que avanzan los obstáculos
        static constexpr unsigned track_count = 6;      // Debe ser un número par (para que haya colores alternos) mayor que 2

        ///Colores de las pistas
        Color current_color_a;
        Color current_color_b;
        ///Ángulo de la pista
        float field_angle;

    public:
        ///Lineas que conforman las pista
        Point2f lines[6];

    private :

        int i = 0;

    public:
        Playfield()
        {
            current_color_a = { 0.50f, 0.50f, 0.50f };
            current_color_b = { 0.75f, 0.75f, 0.75f };
            field_angle     =   0.f;
        }

        ///Método que renderiza la pista
        void render (Canvas & canvas, const Size2f & canvas_size);

        void rotate (float amount)
        {
            field_angle += amount;
        }

        float get_angle()
        {
            return field_angle;
        }

    };
}



#endif //BASICS_HEXAGON_PLAYFIELD_H

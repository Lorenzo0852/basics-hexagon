//
// Created by loren on 09/02/2021.
//

#include "Player.h"
namespace sh
{
    void Player::render(Canvas &canvas)
    {
        //transform del punto superior del vértice
        canvas.apply_transform (basics::Rotation2f(angle));
        canvas.apply_transform (basics::Translation2f(separation, 0.f));

        //X
        //transformed_vertex[0][0];

        //Y
        //transformed_vertex[0][1];

        canvas.set_color (0.f, 0.f, 0.f);
        canvas.fill_triangle
                (
                        { -shadow,          -shadow },
                        { -shadow - length, -shadow - length * 0.5f },
                        { -shadow - length, -shadow + length * 0.5f }
                );


        canvas.set_color (color.r (), color.g (), color.b ());
        canvas.fill_triangle
                (
                        { 0.f, 0.f },
                        { -length, -length * 0.5f },
                        { -length, +length * 0.5f }
                );

        basics::Matrix31f point(basics::Matrix31f::identity);

        // Se modifica la transformación del playfield combinándola con la del player:
        auto transform =  basics::Translation2f(640.f, 360.f) * basics::Rotation2f(angle + playfield->get_angle()) * basics::Translation2f(separation, 0.f);
        auto transformed_vertex = basics::Matrix33f (transform) * point;
        position = {(float)transformed_vertex[0][0], (float)transformed_vertex[0][1]};

        canvas.set_transform(basics::Transformation2f{});
        canvas.set_color (1.f, 0.f, 0.f);
        canvas.fill_rectangle({transformed_vertex[0][0], transformed_vertex[0][1]}, {10.f,10.f});
    }
}
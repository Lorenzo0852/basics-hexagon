//
// Created by loren on 09/02/2021.
//

#include "Playfield.h"
namespace sh
{
    void Playfield::render (Canvas & canvas, const Size2f & canvas_size)
    {
        /// Se rellena el fondo completo:

        canvas.set_color (current_color_a.r (), current_color_a.g (), current_color_a.b ());
        canvas.fill_rectangle ({ 0.f, 0.f }, canvas_size);

        /// Se aplica un giro y se centra en la pantalla cualquier cosa que haya en la escena:

        canvas.set_transform
                (
                        basics::rotate_then_translate_2d
                                (
                                        field_angle,
                                        Vector2f{ canvas_size.width, canvas_size.height } * 0.5f
                                )
                );

        /// Se dibuja solo la mitad de las pistas (el resto se queda con el color de fondo):

        canvas.set_color (current_color_b.r (), current_color_b.g (), current_color_b.b ());

        float angle_delta = 6.2831852f / float(track_count);
        float edge_length = std::max (canvas_size.width, canvas_size.height) * 2.f;

        for (float angle = 0.f; angle < 6.2831852f; )
        {
            ///Determina el punto final de la primera recta a evaluar
            Point2f point_a{ cos (angle) * edge_length, sin (angle) * edge_length };
            angle += angle_delta;

            lines[i] = point_a;

            ///Determina el punto final de la segunda recta a evaluar
            Point2f point_b{ cos (angle) * edge_length, sin (angle) * edge_length };
            angle += angle_delta;

            lines[i + 1] = point_b;

            canvas.set_color (current_color_b.r (), current_color_b.g (), current_color_b.b ());
            canvas.fill_triangle ({ 0.f, 0.f }, point_a, point_b);



            i = i+2;
        }

    }
}
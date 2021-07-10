//
// Created by loren on 09/02/2021.
//

#ifndef BASICS_HEXAGON_COLOR_H
#define BASICS_HEXAGON_COLOR_H


namespace sh
{
    struct Color
    {
        float components[3];

        float & r () { return components[0]; }
        float & g () { return components[1]; }
        float & b () { return components[2]; }

        const float & r () const { return components[0]; }
        const float & g () const { return components[1]; }
        const float & b () const { return components[2]; }

        static Color mix (const Color & a, const Color & b, float t = 0.5f)
        {
            return
                    {
                            (a.r () + b.r ()) * t,
                            (a.g () + b.g ()) * t,
                            (a.b () + b.b ()) * t
                    };
        }
    };
}

#endif //BASICS_HEXAGON_COLOR_H

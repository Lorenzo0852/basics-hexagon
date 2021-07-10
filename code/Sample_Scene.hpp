/*
 * SAMPLE SCENE
 * Copyright © 2020+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include <memory>
#include <vector>
#include <basics/Canvas>
#include <basics/Rotation>
#include <basics/Scene>
#include <basics/Size>
#include <basics/Translation>
#include <basics/Vector>
#include "Color.h"
#include "Playfield.h"
#include "Player.h"
#include "Track.h"
#include "Sprite.h"

namespace sh
{

    using    std::shared_ptr;
    using    std::vector;
    using basics::Canvas;
    using basics::Point2f;
    using basics::Size2f;
    using basics::Vector2f;
    using basics::Vector3f;
    using sh::Color;
    using sh::Player;
    using sh::Playfield;

    class Sample_Scene : public basics::Scene
    {

        typedef std::shared_ptr< basics::Texture_2D > Texture_Handle;
        typedef std::shared_ptr<Sprite> Sprite_Handle;

    private:
        enum
        {
            UNINITIALIZED, LOADING, READY, ERROR
        }
                status;

        bool      suspended;                       ///< true cuando la aplicación está en segundo plano
        unsigned  canvas_width;                    ///< Resolución virtual del display
        unsigned  canvas_height;

        Playfield playfield;
        Player    player;

        float     playfield_rotation_speed;
        float     player_spin_speed;
        float     track_speed;
        Track     track;


        Point2f pause_menu_starting_point;
        Point2f pause_menu_size;

        Texture_Handle pause_button_texture;
        Sprite_Handle pause_sprite;
        Texture_Handle retry_button_texture;
        Sprite_Handle retry_sprite;
        Texture_Handle mainmenu_button_texture;
        Sprite_Handle mainmenu_sprite;

        bool is_game_paused = false;

    public:

        Sample_Scene();
        ~Sample_Scene()
        {
            int x = 0;
        }

        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        bool initialize () override;
        void finalize   () override;
        void suspend    () override;
        void resume     () override;

        void showPauseMenu();

        void handle (basics::Event & event) override;
        void update (float delta) override;
        void render (basics::Graphics_Context::Accessor & context) override;

    private:

        void load       ();

    };

}

/*
 * SAMPLE SCENE
 * Copyright © 2020+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Sample_Scene.hpp"
#include "Menu_Scene.h"

#include <basics/Application>
#include <basics/Canvas>
#include <basics/Display>
#include <basics/Director>
#include <basics/Log>
#include <basics/Window>
#include <fstream>

using namespace basics;
using namespace std;
using namespace sh;

namespace sh
{

    Sample_Scene::Sample_Scene()
            :
            canvas_width (1280),
            canvas_height( 720),
            player({ canvas_width, canvas_height }, &playfield)
    {
        status = UNINITIALIZED;

        playfield_rotation_speed = 1; //1.f;             // radianes por segundo
        player_spin_speed = 0.f;                    // radianes por segundo
        track_speed = 0.07f;
    }

    bool Sample_Scene::initialize ()
    {
        suspended = false;

        display.set_prevent_sleep (true);

        //Guardamos los puntos identificativos del menú de pausa para poder localizar luego elementos dentro de él
        pause_menu_starting_point={std::max(canvas_width, canvas_height)*0.1, std::min(canvas_width, canvas_height) * 0.1};
        pause_menu_size = {std::max(canvas_width, canvas_height) * 0.8, std::min(canvas_width, canvas_height) * 0.8};

        status = LOADING;

        return true;
    }

    void Sample_Scene::finalize ()
    {
        display.set_prevent_sleep (false);
    }

    void Sample_Scene::suspend ()
    {
        suspended = true;

        display.set_prevent_sleep (false);
    }

    void Sample_Scene::resume ()
    {
        suspended = false;

        display.set_prevent_sleep (true);
    }

    void Sample_Scene::handle (basics::Event & event)
    {
        if (!suspended && status == READY)
            switch (event.id)
            {
                case ID(touch-started):
                {
                    float x = *event[ID(x) ].as< var::Float > ();
                    float y = *event[ID(y) ].as< var::Float > ();

                    // Manejamos el movimiento del jugador alrededor del centro según donde el usuario toque.
                    if(x < std::max(canvas_width, canvas_height) * 0.5f)
                    {

                        player_spin_speed = 2.0f;
                    } else
                    {
                        player_spin_speed = -2.0f - playfield_rotation_speed;
                    }

                    // Manejamos la pausa y sus elementos interiores.
                    if(pause_sprite->contains({x,y}))
                    {
                        showPauseMenu();
                    }
                    if(is_game_paused)
                    {
                        //Funciones de los botones del menú de pausa
                        if(retry_sprite->contains({x,y}))       director.run_scene (shared_ptr< Scene >(new Sample_Scene));
                        if(mainmenu_sprite->contains({x,y}))    director.run_scene (shared_ptr< Scene >(new Menu_Scene));
                    }

                    break;
                }
                case ID(touch-moved):
                {
                    float x = *event[ID(x) ].as< var::Float > ();
                    float y = *event[ID(y) ].as< var::Float > ();

                    // Manejamos el movimiento del jugador alrededor del centro según donde el usuario arrastre el dedo.
                    // Es necesario manejar esto además del punto inicial, ya que el usuario puede deslizar el dedo de un lado a otro de la pantalla, cambiando la trayectoria.
                    if(x < canvas_width * 0.5f)
                    {
                        player_spin_speed = 2.0f;
                    } else
                    {
                        player_spin_speed = -2.0f - playfield_rotation_speed;
                    }

                    break;
                }

                case ID(touch-ended):
                {
                    //Paramos el jugador si no se registra ningún toque.
                    player_spin_speed = 0;
                    break;
                }
            }
    }

    void Sample_Scene::load()
    {
        if(!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if(context)
            {
                pause_button_texture = Texture_2D::create(ID(pause), context, "game-scene/pause_button.png");
                mainmenu_button_texture = Texture_2D::create(ID(mainmenu), context, "game-scene/stop_button.png");
                retry_button_texture = Texture_2D::create(ID(retry), context, "game-scene/newgame_button.png");
            }

            if(pause_button_texture && mainmenu_button_texture && retry_button_texture)
            {
                context->add(pause_button_texture);
                context->add(mainmenu_button_texture);
                context->add(retry_button_texture);

                pause_sprite = make_shared<Sprite>(pause_button_texture.get());
                mainmenu_sprite = make_shared<Sprite>(mainmenu_button_texture.get());
                retry_sprite = make_shared<Sprite>(retry_button_texture.get());

                pause_sprite->set_position({canvas_width - canvas_width/10, canvas_height - canvas_height/10});
                mainmenu_sprite->set_position({pause_menu_starting_point.coordinates.x() + pause_menu_size.coordinates.x()*0.7f, pause_menu_starting_point.coordinates.y() + pause_menu_size.coordinates.y()*0.5f});
                retry_sprite->set_position({pause_menu_starting_point.coordinates.x() + pause_menu_size.coordinates.x() * 0.35f, pause_menu_starting_point.coordinates.y() + pause_menu_size.coordinates.y() * 0.5f});

                pause_sprite->set_scale(0.2f);
                mainmenu_sprite->set_scale(0.4f);
                retry_sprite->set_scale(0.4f);

                status = READY;
            }

        }
    }

    void Sample_Scene::update (float delta)
    {

        switch(status){
            case READY:
                //Enviamos la misma información al jugador y a la zona de juego, necesario para el cálculo de colisiones entre ellos.
                playfield.rotate(playfield_rotation_speed * delta);

                //Nos encargamos del movimiento del usuario y de los "tracks"
                track.move(track_speed * delta);
                player.spin(player_spin_speed * delta);
                break;
            case LOADING:
                load();
                break;
        }


    }

    void Sample_Scene::render (basics::Graphics_Context::Accessor & context)
    {
        // Para renderizar si el juego está ACTIVO
        if (!suspended && !is_game_paused)
        {
            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));
            if (!canvas)
            {
                canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            if (canvas) {
                canvas->set_transform(basics::Transformation2f());

                track.setPlayer(&player);
                playfield.render(*canvas, {canvas_width, canvas_height});
                track.render(*canvas, playfield.lines);

                player.render(*canvas);

                Point2f playerPos = {0, 0.2f * (std::min(canvas_width, canvas_height))};

            }

            if(pause_sprite)
            {
                pause_sprite->render(*canvas);
            }
        }

        // Para renderizar si el juego está PAUSADO
        if (!suspended && is_game_paused)
        {
            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));
            if(is_game_paused)
            {
                canvas->set_color(0.2f,0.2f,0.2f);
                canvas->fill_rectangle({pause_menu_starting_point}, {pause_menu_size});
                mainmenu_sprite->render(*canvas);
                retry_sprite->render(*canvas);

            }
        }
    }

    void Sample_Scene::showPauseMenu()
    {
        is_game_paused = !is_game_paused;
    }
}


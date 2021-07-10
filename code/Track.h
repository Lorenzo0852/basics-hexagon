//
// Created by loren on 09/02/2021.
//

#ifndef BASICS_HEXAGON_TRACK_H
#define BASICS_HEXAGON_TRACK_H

#include <basics/Director>
#include <basics/internal/Log.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <queue>
#include <basics/internal/Vector.hpp>
#include <basics/internal/Canvas.hpp>

#include "Menu_Scene.h"
#include "Playfield.h"
#include "Player.h"

using basics::Canvas;

/**
 *  Estructura de solo lectura. Organiza la aparición de nuevas "Tracks" u obstáculos según su orden en el array.
 *  @param currentDistance          Indica la distancia a la que aparece contando desde el límite de la pantalla.
 *  @param selections               Array que indica qué obstáculos están seleccionados para salir o no.
 */
struct Band {
    float currentDistance;
    bool selections[6];
};


const Band spiral[6] = { //OPTION 0

        {-0.5f, {0,1,1,1,1,1}    },
        {-0.5f, {1,0,1,1,1,1}    },
        {-0.5f, {1,1,0,1,1,1}    },
        {-0.5f, {1,1,1,0,1,1}    },
        {-0.5f, {1,1,1,1,0,1}    },
        {-0.5f, {1,1,1,1,1,0}    },

};

const Band zigzag[6] = { //OPTION 1

        {-0.5f, {0,1,1,1,1,1}    },
        {-0.5f, {1,1,1,1,1,0}    },
        {-0.5f, {1,0,1,1,1,1}    },
        {-0.5f, {1,1,1,0,1,1}    },
        {-0.5f, {1,1,0,1,0,1}    },
        {-0.5f, {0,1,1,1,1,0}    },

};

const Band alt[6] = { //OPTION 2

        {-0.5f, {0,0,0,1,1,1}    },
        {-0.5f, {1,0,0,0,1,1}    },
        {-0.5f, {1,1,0,0,0,1}    },
        {-0.5f, {1,1,1,0,0,0}    },
        {-0.5f, {0,1,1,1,0,0}    },
        {-0.5f, {0,0,1,1,1,0}    },

};

class Track {

private:
    ///@param speed         Velocidad a la que se moverán los obstáculos hacia el jugador.
    float speed = 0.0001f;
    sh::Player * player;

public:

    Track();
    int currentSectionNumberIndex = 0;

    void move(float speedToMove)
    {
        speed = speedToMove;
    }

    ///Contador
    float timer;
    ///Banda que se está analizando actualmente
    int currentBand = 0;
    ///Lista de Bandas que guarda cuáles se verán después
    std::list<Band> bandList;

    void setPlayer(sh::Player * player_ref)
    {
        player = player_ref;
    }

    void render(Canvas & canvas, Point2f (& lines)[6]);

private:

    /// Distancia a la que spawnearan los obstáculos, alejándose desde el centro en sentido negativo (menos es más lejos).
    float distance = -0.6f;
    ///Tamaño de cada obstáculo, contando desde el jugador hasta los bordes de la pantalla.
    float sectionSize = 0.03f;
    ///Posiciones calculadas para las rectas que forman los obstáculos.
    float x,y;
    Point2f bottom_right, top_right, bottom_left, top_left;

    /// Renderiza las bandas (selección de obstáculos)
    /// \param canvas       pinta las bandas
    /// \param band         estructura que guarda los datos
    /// \param lines        lineas que conforman el terreno de juego, necesarias para calcular los puntos de cada obstáculo
    /// \param position     necesario para saber la distancia en la que empezará a calcularse
    void renderBand(Canvas & canvas, Band band, Point2f (& lines)[6], float position);

    /// Puntos de cada triángulo que forma una sección, actualizados en cada render.
    void renderSection(Canvas & canvas, int sectionNumber, Point2f (& lines)[6], float currentDistance);

    };





#endif //BASICS_HEXAGON_TRACK_H

//
// Created by loren on 09/02/2021.
//

#include "Track.h"

Track::Track()
{
    std::srand(time(NULL));
}

void Track::render(Canvas & canvas, Point2f (& lines)[6])
{
    int randNumber = std::rand() % (2 + 1 - 0) + 0;
    timer += 0.01;
    if(timer >= 1.35)
    {
        timer = 0;
        if(currentBand >= 6)
        {
            //Aquí cambiaríamos de set por el siguiente. Por ejemplo, spiral por zigzag.

            randNumber = std::rand() % (1 + 1 - 0) + 0;

            currentBand = 0;
        } else
        {
            switch (randNumber)
            {
                case 0:
                    bandList.push_back(spiral[currentBand]);
                    break;
                case 1:
                    bandList.push_back(zigzag[currentBand]);
                    break;
                case 2:
                    bandList.push_back(alt[currentBand]);
                    break;
            }
            currentBand++;
        }
    }

    for(auto & band : bandList)
    {
        band.currentDistance -= speed;
        renderBand(canvas, band, lines, band.currentDistance);

        if(band.currentDistance < -1.02) bandList.pop_front();
    }

}
void Track::renderSection(Canvas &canvas, int sectionNumber, Point2f (&lines)[6], float currentDistance)
{

    canvas.set_color (1, 0, 0);
    bool even = sectionNumber % 2 == 0 ? true : false;

    switch (even){
        case true:
        {
            //Calculamos los tres primeros puntos del triángulo
            x = lines[sectionNumber].coordinates.x() + (currentDistance * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + (currentDistance * lines[sectionNumber].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_right = {x,y};

            x = lines[sectionNumber].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_right = {x,y};

            x = lines[sectionNumber+1].coordinates.x() + (currentDistance * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + (currentDistance * lines[sectionNumber+1].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_left = {x,y};

            //Dibujamos primer triángulo.
            canvas.fill_triangle({top_right},{bottom_right}, {bottom_left});

            //Calculamos un punto más, teniendo en cuenta que los otros dos son coincidentes.
            x = lines[sectionNumber+1].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_left = {x,y};

            //Dibujamos segundo triángulo, formando figura
            canvas.fill_triangle({top_right},{top_left}, {bottom_left});

            break;
        }
        case false:
        {

            //Calculamos los tres primeros puntos del triángulo
            x = lines[sectionNumber+1].coordinates.x() + (currentDistance * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + (currentDistance * lines[sectionNumber+1].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_right = {x,y};

            x = lines[sectionNumber+1].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_right = {x,y};

            x = lines[sectionNumber].coordinates.x() + (currentDistance * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + (currentDistance * lines[sectionNumber].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_left = {x,y};

            //Dibujamos primer triángulo.
            canvas.fill_triangle({top_right},{bottom_right}, {bottom_left});

            //Calculamos un punto más, teniendo en cuenta que los otros dos son coincidentes.
            x = lines[sectionNumber].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_left = {x,y};

            //Dibujamos segundo triángulo, formando figura
            canvas.fill_triangle({top_right},{top_left}, {bottom_left});

            break;
        }
    }



}
void Track::renderBand(Canvas & canvas, Band band, Point2f (& lines)[6], float position)

{
    currentSectionNumberIndex = 0;
    for(bool selected : band.selections)
    {
        switch (selected)
        {
            case true:
                renderSection(canvas, currentSectionNumberIndex, lines, position);

                /*if(player)
                {
                    detectCollisions(*player, currentSectionNumberIndex, lines, position);
                }*/

                break;

        }
        currentSectionNumberIndex++;
    }

}


// DEJO AQUÍ COMENTADO EL CÓDIGO QUE INTENTABA IMPLEMENTAR PARA LAS COLISIONES, LLEVO VARIOS DÍAS PERO NO SOY CAPAZ DE HACERLO FUNCIONAR DE NINGUNA FORMA:

/*
 *
 * void detectCollisions(sh::Player & player, int sectionNumber, Point2f (& lines)[6], float currentDistance)
{

    bool even = sectionNumber % 2 == 0 ? true : false;

    switch (even){
        case true:
        {
            //Calculamos los tres primeros puntos del triángulo
            x = lines[sectionNumber].coordinates.x() + (currentDistance * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + (currentDistance * lines[sectionNumber].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_right = {x,y};

            x = lines[sectionNumber].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_right = {x,y};

            x = lines[sectionNumber+1].coordinates.x() + (currentDistance * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + (currentDistance * lines[sectionNumber+1].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_left = {x,y};

            //Calculamos un punto más, teniendo en cuenta que los otros dos son coincidentes.
            x = lines[sectionNumber+1].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_left = {x,y};

            break;
        }
        case false:
        {

            //Calculamos los tres primeros puntos del triángulo
            x = lines[sectionNumber+1].coordinates.x() + (currentDistance * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + (currentDistance * lines[sectionNumber+1].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_right = {x,y};

            x = lines[sectionNumber+1].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.x());
            y = lines[sectionNumber+1].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber+1].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_right = {x,y};

            x = lines[sectionNumber].coordinates.x() + (currentDistance * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + (currentDistance * lines[sectionNumber].coordinates.y());
            if(distance < -1) x,y = 0;
            bottom_left = {x,y};


            //Calculamos un punto más, teniendo en cuenta que los otros dos son coincidentes.
            x = lines[sectionNumber].coordinates.x() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.x());
            y = lines[sectionNumber].coordinates.y() + ((currentDistance + sectionSize) * lines[sectionNumber].coordinates.y());
            if(distance+sectionSize < -1) x,y = 0;
            top_left = {x,y};


            //Utilizamos la ec. general de la recta para ver si el punto está encima o debajo de las líneas formadas por los puntos ya conocidos.

                if(
                        (bottom_left.coordinates.y() - bottom_right.coordinates.y() / bottom_left.coordinates.x() - bottom_right.coordinates.x())
                        - (bottom_right.coordinates.y() - player.position.coordinates.y()/  bottom_right.coordinates.x() - player.position.coordinates.x())  <   0)
                    basics::director.run_scene (std::shared_ptr< basics::Scene >(new sh::Menu_Scene));
                {
                    if(
                            (top_left.coordinates.y() - top_right.coordinates.y() / top_left.coordinates.x() - top_right.coordinates.x())
                            - (player.position.coordinates.y() - top_right.coordinates.y() / player.position.coordinates.x() - top_right.coordinates.x())  >   0)
                    {
                        //basics::director.run_scene (std::shared_ptr< basics::Scene >(new sh::Menu_Scene));
                        basics::log.e("DENTRO!!");
                    }
                }


            break;
        }
    }




}*/
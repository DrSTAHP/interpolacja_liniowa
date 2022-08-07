/* 
    32-bitowa implementacja interpolacji liniowej 
    pomiędzy dwoma punktami z dokładnością do 1/1000.

    Wynik działania programu znajduje się w pliku
    interp.txt w katalogu pliku wykonywalnego. 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>

#define _ENDL std::cout << '\n'
#define MOVE_PRECISION (float)0.001

struct vec2_t {
    float x, y;
};

/*  
    start   ->    Punkt, od którego zaczyna się interpolacja;
    end     ->    Punkt, na którym kończy się interpolacja;
    delta_x ->    Wartość, która spełnia n > 0, która jest przesunięciem osi X od start.x. Funkcja sama dokonuje zmiany kierunku w zależności od parametrów;
*/     
vec2_t interp(vec2_t& start, vec2_t& end, float delta_x)
{
    vec2_t lerp_point;  /* Interpolowany punkt */
    delta_x = fabsf(delta_x);

    if(!delta_x)
        return start;
    else
    {
        if(start.x > end.x) 
        {
            delta_x = -delta_x; /* Inkrementacja staje się dekrementacją. */
            if(start.x + delta_x <= end.x)
                return end;
        }
        else 
        {
            if(start.x + delta_x >= end.x)
                return end;
        }
        assert((end.x - start.x) != 0); /* Założenie dla bezpieczeństwa, w praktyce taka sytuacja nie może mieć miejsca, patrz poprzednie ify. */
        
        /* I nareszcie faktyczna interpolacja. */
        lerp_point.x = start.x + delta_x;
        lerp_point.y = start.y + (((end.y - start.y) / (end.x - start.x)) * (lerp_point.x - start.x));
    }
    return lerp_point;
}

int main(int argc, char** argv)
{
    vec2_t start, end, res;
    float flDeltaX = 0; 
    std::fstream pOutFile;
    
    if(argc < 5)
    {
        std::cout << "Start.x = ";
        std::cin >> start.x;
        _ENDL;

        std::cout << "Start.y = ";
        std::cin >> start.y;
        _ENDL;

        std::cout << "End.x = ";
        std::cin >> end.x;
        _ENDL;

        std::cout << "End.y = ";
        std::cin >> end.y;
        _ENDL;
    }
    else
    {
        start.x = (float)atof(argv[1]);
        start.y = (float)atof(argv[2]);
        end.x = (float)atof(argv[3]);
        end.y = (float)atof(argv[4]);
    }

    pOutFile.open("interp.txt", std::ios::out | std::ios::trunc);
    pOutFile << "Interpolacja liniowa dla: A( " << start.x << " , " << start.y << " ) | B( " << end.x << " , " << end.y << " )\n\n";

    while (res.x != end.x)
    {
        res = interp(start, end, flDeltaX);
        pOutFile << "( " << res.x << " , " << res.y << " )\n";
        flDeltaX += MOVE_PRECISION;
    }
    
    pOutFile.close();
    std::cout << "Koniec!\n\n";
    return 0;
}
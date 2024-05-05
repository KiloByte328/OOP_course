#include "main.h"

int main()
{
    int X, Y, degree;
    std::cout << "print X and Y" << std::endl;
    std::cin >> X >> Y;
    map** new_field = map_generate(X,Y);
    /* all_in new_all; */
    int max_x, max_y;
    new_field[0][0].get_size(&max_x, &max_y);
    generateEntireWorld(new_field/* , new_all */);
    int EXIT_CODE;
    while(EXIT_CODE != 0)
    {
        SceenRender(new_field, degree);
        std::cin >> EXIT_CODE;
    }
    for(int i = 0; i < Y; i++)
    {
        delete[] new_field[i];
    }
    delete[] new_field;
    return 0;
}
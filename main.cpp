#include "main.h"

int main()
{
    int X, Y, degree;
    std::cout << "print X and Y" << std::endl;
    std::cin >> X >> Y;
    for(; X < 10 || Y < 10;)
        {
            std::cout << "cant execute, minimal X = 10, Y = 10"<< std::endl;
            std::cin >> X >> Y;
        }
    map** new_field = map_generate(X,Y);
    int c = (X < Y) ? X : Y;
    Predator *pred_pack = new Predator[c];
    grass_eat *grass_pack = new grass_eat[c];
    Meat *meat_pack = new Meat[c];
    Fruit *fruit_pack = new Fruit[c];
    tree *trees_pack = new tree[c];
    int max_x, max_y;
    new_field[0][0].get_size(&max_x, &max_y);
    int p, g, n, m, f;
    generateEntireWorld(&p, &g, &n, &m, &f, new_field);
    spawn(p, g, n, m, f, new_field, pred_pack, grass_pack, meat_pack, fruit_pack, trees_pack);
    p--;
    g--;
    int EXIT_CODE = 1;
    while(EXIT_CODE != 0)
    {
        SceenRender(new_field, degree);
        for(int pred_c = 0; pred_c <= p; pred_c++)
        {
            pred_pack[pred_c].Live(new_field);
/*             SceenRender(new_field, degree); */
        }
        for(int gras_c = 0; gras_c <= g; gras_c++)
        {
            grass_pack[gras_c].Live(new_field);
/*             SceenRender(new_field, degree); */
        }
        std::cin >> EXIT_CODE;
    }
    for(int i = 0; i < Y; i++)
    {
        delete[] new_field[i];
    }
    delete[] pred_pack;
    delete[] grass_pack;
    delete[] meat_pack;
    delete[] fruit_pack;
    delete[] trees_pack;
    delete[] new_field;
    return 0;
}
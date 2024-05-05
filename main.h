#pragma once
#include <iostream>
#include <stdlib.h>

void ScreenClear()
{
    system("cls");
};

/* int checking (int *mass, int mass_size_X)
{
        for(int i = 0; i <= mass_size_X;i++)
        {
            if(mass[i] == 1)
                return 1;
        }
    return 0;
}; */

class entity
{
    public:
    int x_pos, y_pos, Stat;
    void pos_set(int newX, int newY)
    {
        this->x_pos = newX;
        this->y_pos = newY;
    };
    entity(){};
    entity(int new_stat){this->Stat = new_stat;};
    void pos_get (int *X, int *Y)
    {
        *X = this->x_pos;
        *Y = this->y_pos;
    };
    void set_status (){};
    void get_status(int* get)
    {
        *get = this->Stat;
    };
};


class map
{
    private:
    int x, y;
    int sizeOfX, sizeOfY;
    entity creature;
        void set_pos(int X, int Y)
    {
        this->x = X;
        this->y = Y;
    };
        void set_size (int newSizeX, int newSizeY)
    {
        this->sizeOfX = newSizeX;
        this->sizeOfY = newSizeY;
    };
    void set_creature(entity new_creature)
    {
        creature = new_creature;
    };
    public:
    virtual void get_postion(int getX, int getY)
    {
        getX = this->x;
        getY = this->y;
    };
    void get_whatOn(int *getWhatOn)
    {
        creature.get_status(getWhatOn);
    };
    void get_size(int* getSizeX, int* getSizeY)
    {
        *getSizeX = this->sizeOfX;
        *getSizeY = this->sizeOfY; 
    };
    virtual void Map_update(entity new_ent)
    {
        this->set_creature(new_ent);
    }
    virtual void Map_update(int newX, int newY)
    {
        this->set_pos(newX, newY);
    }
    virtual void Map_update(int newX, int newY, int new_sizeX, int new_sizeY, entity creat)
    {
        this->set_pos(newX, newY);
        this->set_size(new_sizeX, new_sizeY);
        this->set_creature(creat);
    }
};

class NotAlive : public entity
{
    private:
    int Stat;
    public:
};

class Air : public entity
{
    private:
    int Stat = 0;
    public:
    Air():Stat(0){};
};

map** map_generate(int X, int Y)
{
    map** new_map = new map*[Y+1];
    Air new_air;
        for(int h = 0; h <= Y; h++)
        {
            new_map[h] = new map[X+1];
            for(int f = 0; f <= X; f++)
            {
                new_map[h][f].Map_update(f,h,X,Y, new_air);
            }
        }
    return new_map;
};


class Fruit : private NotAlive
{
    private:
    int Stat = 5;
    public:
    Fruit(int X, int Y, map **World):Stat(5)
    {
        entity new_entity_fruit(this->Stat);
        World[Y][X].Map_update(new_entity_fruit);
        this->pos_set(X,Y); 
    };
    Fruit(){this->Stat = 5;};
};

class Meat : private NotAlive
{
    private:
    int Stat = 6;
    public:
    Meat(int X, int Y, map **World):Stat(6)
    {
        entity new_entity_meat(this->Stat);
        World[Y][X].Map_update(new_entity_meat);
        this->pos_set(X,Y); 
    };
    Meat(){this->Stat = 6;};
};

class rock : private NotAlive
{
    private:
    int Stat = 7;
    public:
    rock(int X, int Y, map **World):Stat(5)
    {
        entity new_entity_fruit(this->Stat);
        World[Y][X].Map_update(new_entity_fruit);
        this->pos_set(X,Y); 
    };
    void get_stat(int * get){*get = this->Stat;};
};

class tree : private NotAlive
{
    private:
    int Stat = 8;
    public:
    tree(int X, int Y, map **World):Stat(5)
    {
        entity new_entity_fruit(this->Stat);
        World[Y][X].Map_update(new_entity_fruit);
        this->pos_set(X,Y); 
    };
    void get_stat(int * get){*get = this->Stat;};
};

class Alive : public entity
{
    public:
    int Look_out[3];
    int hungry = 100;
    virtual void live (){};
    virtual void walk (int nav, map **World){};
    virtual void Look(int nav, map** EntireWorld){};
    virtual void print__what_see(){};
    virtual void eat(int nav, map** World){};
};

class grass_eat : private Alive
{
    private:
    int Stat = 1;
    virtual void eat()
    {

    };
    public:
    grass_eat(int X, int Y, map **World)
    {
        entity new_entity_grass(this->Stat);
        World[Y][X].Map_update(new_entity_grass);
        this->pos_set(X,Y); 
    };
    grass_eat()
    {
        this->Stat = 1;
    };
    private:
    virtual void walk (int nav, map **World)
    {
        int maxX, maxY;
        int myXpos, myYpos;
        Air new_air;
        this->pos_get(&myXpos, &myYpos);
        World[0][0].get_size(&maxX, &maxY);
        switch (nav)
        {
        case 0:
            if(myYpos -1 < 0)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos-1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos-1);
            return;
            break;
        case 1:
            if(myXpos+1 > maxX)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos][myXpos+1].Map_update(*this);
            this->pos_set(myXpos+1, myYpos);
            return;
            break;
        case 2:
            if (myYpos+1 > maxY)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos+1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos+1);
            return;
            break;
        case 3:
            if(myXpos-1 < 0)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos][myXpos-1].Map_update(*this);
            this->pos_set(myXpos-1, myYpos);
            return;
            break;
        default:
            break;
        }
    };
    virtual void eat(int nav, map** World)
    {
        Air new_air;
        int check;
        switch (nav)
        {
            case 0: 
            World[y_pos-1][x_pos].get_whatOn(&check);
            if(check == 5 || check == 8)
                World[y_pos-1][x_pos].Map_update(new_air);
                if(check == 8)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 1: 
            World[y_pos][x_pos+1].get_whatOn(&check);
            if(check == 5 || check == 8)
                World[y_pos][x_pos+1].Map_update(new_air);
                if(check == 8)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 2: 
            World[y_pos+1][x_pos].get_whatOn(&check);
            if(check == 5 || check == 8)
                World[y_pos+1][x_pos].Map_update(new_air);
                if(check == 8)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 3: 
            World[y_pos][x_pos-1].get_whatOn(&check);
            if(check == 5 || check == 8)
                World[y_pos][x_pos-1].Map_update(new_air);
                if(check == 8)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            default:
            break;
        }
    };
    /*  first iteration of look
    virtual void Look(int nav, map** EntireWorld)
    {
        int Xmax, Ymax;
        int curX, curY;
        int count = 0;
        this->pos_get(&curX, &curY);
        EntireWorld[0][0].get_size(&Xmax, &Ymax);
         switch (nav)
        {
        case 0:
        for(int temp_cur = curY;curY != 0 && curY != temp_cur-3;)
        {
            curY--;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 1:
        for(int temp_cur = curX;curX != Xmax && curX != temp_cur+3;)
        {
            curX++;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 2:
        for(int temp_cur = curY;curY != Ymax && curY != temp_cur+3;)
        {
            curY++;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 3:
        for(int temp_cur;curX != 0 && curX != temp_cur-3;)
        {
            curX--;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        default:
            break;
        }
    }; */
    /* virtual void print__what_see()
    {
        for(int i = 0; i != 3; i++)
        {
            std::cout << "see in range " << i << ": " << this->Look_out[i];
        }
    }; */
};

class Predator : private Alive
{
    private:
    int Stat = 2;
    void attack(int nav, map** World)
    {
        Air new_air;
        int check;
        switch (nav)
        {
            case 0: 
            World[y_pos-1][x_pos].get_whatOn(&check);
            if(check == 1 || check == 6)
                World[y_pos-1][x_pos].Map_update(new_air);
                if(check == 1)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 1: 
            World[y_pos][x_pos+1].get_whatOn(&check);
            if(check == 1 || check == 6)
                World[y_pos][x_pos+1].Map_update(new_air);
                if(check == 1)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 2: 
            World[y_pos+1][x_pos].get_whatOn(&check);
            if(check == 1 || check == 6)
                World[y_pos+1][x_pos].Map_update(new_air);
                if(check == 1)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            case 3: 
            World[y_pos][x_pos-1].get_whatOn(&check);
            if(check == 1 || check == 6)
                World[y_pos][x_pos-1].Map_update(new_air);
                if(check == 1)
                    this->hungry = this->hungry + 20;
                this->hungry = hungry + 20;
            break;
            default:
            break;
        }
    };
    public:
    Predator(int X, int Y, map **World)
    {
        entity new_entity_pred(this->Stat);
        World[Y][X].Map_update(new_entity_pred);
        this->pos_set(X,Y); 
    };
    Predator()
    {
        this->Stat = 2;
    };
    private:
    virtual void walk (int nav, map **World)
    {
        int maxX, maxY;
        int myXpos, myYpos;
        Air new_air;
        this->pos_get(&myXpos, &myYpos);
        World[0][0].get_size(&maxX, &maxY);
        switch (nav)
        {
        case 0:
            if(myYpos -1 < 0)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos-1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos-1);
            return;
            break;
        case 1:
            if(myXpos+1 > maxX)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos][myXpos+1].Map_update(*this);
            this->pos_set(myXpos+1, myYpos);
            return;
            break;
        case 2:
            if (myYpos+1 > maxY)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos+1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos+1);
            return;
            break;
        case 3:
            if(myXpos-1 < 0)
                return;
            World[myYpos][myXpos].Map_update(new_air);
            World[myYpos][myXpos-1].Map_update(*this);
            this->pos_set(myXpos-1, myYpos);
            return;
            break;
        default:
            break;
        }
        return;
    };
   /*  first iteration of look
    virtual void Look(int nav, map** EntireWorld)
    {
        int Xmax, Ymax;
        int curX, curY;
        int count = 0;
        this->pos_get(&curX, &curY);
        EntireWorld[0][0].get_size(&Xmax, &Ymax);
         switch (nav)
        {
        case 0:
        for(int temp_cur = curY;curY != 0 && curY != temp_cur-3;)
        {
            curY--;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 1:
        for(int temp_cur = curX;curX != Xmax && curX != temp_cur+3;)
        {
            curX++;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 2:
        for(int temp_cur = curY;curY != Ymax && curY != temp_cur+3;)
        {
            curY++;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        case 3:
        for(int temp_cur;curX != 0 && curX != temp_cur-3;)
        {
            curX--;
            EntireWorld[curY][curX].get_whatOn(&this->Look_out[count]);
            count++;
        }
            break;
        default:
            break;
        }
    }; */
    /* virtual void print__what_see(map** World)
    {
        int mX, mY;
        int myX, myY;
        this->pos_get(&myX,&myY);
        World[0][0].get_size(&mX,&mY);
        int count;
        if(mX < 3 || mY < 3)
            count = (mX < mY) ? mX-myX : mY-myY;
        else
            count = 3;
        for(int i = 0; i != count; i++)
        {
            std::cout << "see in range " << i+1 << ": " << this->Look_out[i] << " ";
        }
        std::cout << std::endl;
    }; */
};
/* 
class all_ent : private Air, private Predator, private Fruit, private Meat, private grass_eat
{
    private:
    int Stat;
    void set_stat(int new_stat){this->Stat = new_stat;};
    public:
    void get_stat(int *get){*get = this->Stat;};
    all_ent(int Stat){this->set_stat(Stat);};
}; */

/* class all_in
{
    private:
    int pred_max = 0; int grass_max = 0; int meat_max = 0;int fruit_max = 0; int trees_max = 0;
    Predator **pred_pack;
    grass_eat **grass_pack;
    Meat **meat_pack;
    Fruit **fruit_pack;
    tree **trees_pack;
    void set_max(int p, int g, int m, int f, int t)
    {
        pred_max = p;
        for(int count = pred_max;;)
        grass_max = g;
        meat_max = m;
        fruit_max = f;
        trees_max = t;
    };
    void set_new_pred(Predator *new_pred)
    {
        pred_pack[pred_max+1] = new_pred;
        pred_max++;
    };
    void set_new_grass(grass_eat *new_grass)
    {
        grass_pack[grass_max+1] = new_grass;
        grass_max++;
    };
    void set_new_meat(Meat *new_meat)
    {
        meat_pack[meat_max+1] = new_meat;
        meat_max++;
    };
    void set_new_fruit(Fruit *new_fuit)
    {
        fruit_pack[fruit_max+1] = new_fuit;
        fruit_max++;
    };
    void set_new_tree(tree *new_tree)
    {
        trees_pack[trees_max+1] = new_tree;
        trees_max++;
    };
    public:
    all_in(int p, int g, int m, int f, int t)
    {

    }
    void get_pred(int get,Predator *get_pred)
    {
        get_pred = this->pred_pack[get];
    };
    void get_grass(int get,grass_eat *get_grass)
    {
        get_grass = this->grass_pack[get];
    };
    void get_meat(int get,Meat *get_meat)
    {
        get_meat = this->meat_pack[get];
    };
    void get_fruit(int get,Fruit *get_fruit)
    {
        get_fruit = this->fruit_pack[get];
    };
    void get_tree(int get,tree *get_tree)
    {
        get_tree = this->trees_pack[get];
    };
    virtual void all_in_update(Predator *new_pred){this->set_new_pred(new_pred);};
    virtual void all_in_update(grass_eat *new_grass){this->set_new_grass(new_grass);};
    virtual void all_in_update(Meat *new_meat){this->set_new_meat(new_meat);};
    virtual void all_in_update(Fruit *new_fruit){this->set_new_fruit(new_fruit);};
    virtual void all_in_update(tree *new_tree){this->set_new_tree(new_tree);};
};
 */
int SceenRender(map** map_render, int degree)
{
    int whaton, sizeX, sizeY;
    map_render[0][0].get_size(&sizeX, &sizeY);
    ScreenClear();
    /*int x, y;
    switch(degree)
    {
    default:
        for(y = 0; y < sizeY; y++){
            for (x = 0; x <sizeX; x++){
                map_render[y][x].get_whatOn(whaton);
        switch (whaton)
            {
            case 1:
                std::cout << "a";
                break;

            default:
                std::cout << ".";
                break;
            }
            }
            std::cout << "\n";
            }
        break;
    case (1):
        for (x = 0; x < sizeX; x++)
        {
            for (y = 0; y < sizeY; y++)
            {
            map_render[y][x].get_whatOn(whaton);
        switch (whaton)
            {
            case 1:
                std::cout << "a";
                break;

            default:
                std::cout << ".";
                break;
            }
            }
        }
            std::cout << "\n";
        break;
    case (2):
    for(y = sizeY; y != 0; y--)
    {
        for (x = 0; x < sizeX; x++){
        map_render[y][x].get_whatOn(whaton);
        switch (whaton)
            {
            case 1:
                std::cout << "a";
                break;

            default:
                std::cout << ".";
                break;
            }
            }
    }
            std::cout << "\n";
        break;
    case (3):
    for(x = sizeX; x != 0; x--)
    {
        for (y = sizeY; y != 0; y--)
        {
        map_render[y][x].get_whatOn(whaton);
        switch (whaton)
            {
            case 1:
                std::cout << "a";
                break;

            default:
                std::cout << ".";
                break;
            }
            }
            std::cout << "\n";
    break;
    }
    return 0;
    }*/
    for(int j = 0; j <= sizeY; j++)
    {
        for(int i = 0; i <= sizeX; i++)
        {
        map_render[j][i].get_whatOn(&whaton);
        switch (whaton)
            {
            case 1:
                std::cout << "G ";
                break;
            case 2:
                std::cout << "P ";
                break;
            case 3:
                std::cout << "B ";
                break;
            case 6:
                std::cout << "M ";
                break;
            case 5:
                std::cout << "F ";
                break;
            case 7:
                std::cout << "R ";
                break;
            case 8:
                std::cout << "T ";
                break;
            default:
                std::cout << ". ";
                break;
            }
        }
            std::cout << "\n";
        }
    return 0;
};

void generateEntireWorld(map **WorldMap/* , all_in new_all*/)
{
    int sizeX, sizeY;
    WorldMap[0][0].get_size(&sizeX, &sizeY);
    int Predators, Alive, NAL;
    Predators = (sizeX % 10) + (sizeY % 10);
    if (Predators == 0)
        Predators = 1;
    Alive = (sizeX % 3) + (sizeY % 3);
    if (Alive == 0)
        Alive = 1;
    int meats = Predators * 3;
    int fruits = Alive * 2;
    NAL = ((sizeX % 7) + (sizeY % 7));
    if (NAL == 0)
        NAL = 2;
    int **dis = new int*[sizeY];
    for(int j = 0; j <= sizeX; j++)
    {
        dis[j] = new int[sizeX+1];
    }
        for(int i = 0; i <= sizeY;i++)
        {
            for(int k = 0; k <= sizeX;k++)
            {
                dis[i][k] = 0;
            }
        }
    int count = 0;
    while (true)
    {
        if (Predators != 0)
        {
            int X, Y;
            X = rand() % sizeX;
            Y = rand() % sizeY;
            for(;dis[Y][X] == 1;)
                {
                    Y = rand() % sizeY;
                    X = rand() % sizeX;
                }
            dis[Y][X] = 1;
            Predator new_pred(X,Y,WorldMap);
            /* all.all_in_update(&new_pred); */
            Predators--;
            count++;
        }
        if (Alive != 0)
        {
            int X, Y;
            X = rand() % sizeX;
            Y = rand() % sizeY;
            for(;dis[Y][X] == 1;)
                {
                    Y = rand() % sizeY;
                    X = rand() % sizeX;
                }
            dis[Y][X] = 1;
            grass_eat new_grass(X,Y,WorldMap);
           /*  all.all_in_update(&new_grass); */
            Alive--;
            count++;
        }
        if(NAL != 0)
        {
            int X, Y;
            X = rand() % sizeX;
            Y = rand() % sizeY;
            for(;dis[Y][X] == 1;)
                {
                    Y = rand() % sizeY;
                    X = rand() % sizeX;
                }
            dis[Y][X] = 1;
            if(NAL % 2 == 0)
                rock new_rock(X, Y, WorldMap);
            else
                {
                    tree new_tree(X, Y, WorldMap);
                    /* all.all_in_update(&new_tree); */
                }
            NAL--;
            count++;
        }
        if(meats != 0)
        {
            int X, Y;
            X = rand() % sizeX;
            Y = rand() % sizeY;
            for(;dis[Y][X] == 1;)
                {
                    Y = rand() % sizeY;
                    X = rand() % sizeX;
                }
            dis[Y][X] = 1;
            Meat new_meat(X, Y, WorldMap);
            /* all.all_in_update(&new_meat); */
            meats--;
            count++;
        }
        if(fruits != 0)
        {
            int X, Y;
            X = rand() % sizeX;
            Y = rand() % sizeY;
                for(;dis[Y][X] == 1;)
                {
                    Y = rand() % sizeY;
                    X = rand() % sizeX;
                }
            dis[Y][X] = 1;
            Fruit new_fruit(X, Y, WorldMap);
            /* all.all_in_update(&new_fruit); */
            fruits--;
            count++;
        }
        if (Predators == 0 && Alive == 0 && NAL == 0 && meats == 0 && fruits == 0)
            return ;
    }
};
#pragma once
#include <iostream>
#include <stdlib.h>

void ScreenClear()
{
    system("cls");
};

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
    void get_creature (entity *get){get = &creature;};
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
    rock(int X, int Y, map **World):Stat(7)
    {
        entity new_entity_fruit(this->Stat);
        World[Y][X].Map_update(new_entity_fruit);
        this->pos_set(X,Y); 
    };
    rock(){this->Stat = 7;};
    void get_stat(int * get){*get = this->Stat;};
};

class tree : private NotAlive
{
    private:
    int Stat = 8;
    public:
    tree(int X, int Y, map **World):Stat(8)
    {
        entity new_entity_fruit(this->Stat);
        World[Y][X].Map_update(new_entity_fruit);
        this->pos_set(X,Y); 
    };
    tree(){this->Stat = 8;};
    void get_stat(int * get){*get = this->Stat;};
};

class Alive : public entity
{
    public:
    int Look_out[3];
    int nav;
    int hungry = 100;
    virtual void live (){};
    virtual void walk (int nav, map **World){};
    virtual void Look(int nav, map** EntireWorld){};
    virtual void print__what_see(){};
    virtual void eat(int nav, map** World){};
    virtual void starvation(int starve){};
    void Live(map **World){};
    virtual void nav_set(int new_nav){};
    virtual void av_get(int *get){};
};

class grass_eat : private Alive
{
    private:
    int Stat = 1;
    int died = 0;
    int FindFood = 0;
    int momento = 0;
    public:
    grass_eat(int X, int Y, map **World)
    {
        entity new_entity_grass(this->Stat);
        World[Y][X].Map_update(new_entity_grass);
        this->pos_set(X,Y); 
    };
    grass_eat(){this->Stat = 1;};
    virtual void pos_get(int *X, int *Y){*X = this->x_pos; *Y = this->y_pos;};
    virtual void Live(map **World)
    {
        switch (momento)
        {
            case 0:
            {
        for(int i = 0; i <= 3; i++)
        {
            if(this->hungry <= 5)
            {
                this->died = 1;
                break;
            }
            this->Look(i,World);
            this->starvation(1);
            for(int h = 0; h <= 3; h++)
            {
            if(this->Look_out[h] == 5 || this->Look_out[h] == 8)
                {
                    FindFood = 1;
                    break;
                }
            }
        }
        if(died == 1)
            break;
        momento = 1;
        break;
        }
        case 1:
        {
        if(FindFood == 0)
        {
            if(hungry <= 10)
            {
                died = 1;
                break;
            }
            int new_navig = rand()%4;
            this->walk(new_navig, World);
            this->Look(nav,World);
            this->starvation(2);
            for(int h = 0; h <= 3; h++)
            {
            if(this->Look_out[h] == 5 || this->Look_out[h] == 8)
            {
                FindFood = 1;
                    break;
            }
            }
        }
        if(FindFood == 1)
        {
            if(hungry <= 10)
            {
                died = 1;
                break;
            }
            this->walk(nav, World);
            this->Look(nav, World);
            this->starvation(2);
            if(this->Look_out[0] == 5 || this->Look_out[0] == 8)
            {
                this->eat(nav,World);
                momento = 0;
            }
        }
        if(died == 1)
            break;
        }
        break;
        }
    };
    private:
    virtual void starvation(int starve){this->hungry = hungry-starve;};
    virtual void nav_set(int new_nav){this->nav = nav;};
    virtual void nav_get(int *get){*get = this->nav;};
    virtual void walk (int nav, map **World)
    {
        int maxX, maxY;
        int myXpos, myYpos;
        entity replace;
        this->pos_get(&myXpos, &myYpos);
        this->nav_set(nav);
        World[0][0].get_size(&maxX, &maxY);
        switch (nav)
        {
        case 0:
            if(myYpos -1 < 0)
                return;
            World[myYpos-1][myXpos].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos-1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos-1);
            return;
            break;
        case 1:
            if(myXpos+1 > maxX)
                return;
            World[myYpos][myXpos+1].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos][myXpos+1].Map_update(*this);
            this->pos_set(myXpos+1, myYpos);
            return;
            break;
        case 2:
            if (myYpos+1 > maxY)
                return;
            World[myYpos+1][myXpos].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos+1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos+1);
            return;
            break;
        case 3:
            if(myXpos-1 < 0)
                return;
            World[myYpos][myXpos-1].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos][myXpos-1].Map_update(*this);
            this->pos_set(myXpos-1, myYpos);
            return;
            break;
        default:
            break;
        }
        return;
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
    virtual void Look(int nav, map** EntireWorld)
    {
        int Xmax, Ymax;
        int curX, curY;
        int count = 0;
        this->pos_get(&curX, &curY);
        this->nav_set(nav);
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
    };
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
    int died = 0;
    int FindFood = 0;
    int momento = 0;
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
    Predator(){this->Stat = 2;};
    virtual void pos_get(int *X, int *Y){*X = this->x_pos; *Y = this->y_pos;};
    virtual void Live(map **World)
    {
        switch (momento)
        {
            case 0:
            {
        for(int i = 0; i <= 3; i++)
        {
            if(this->hungry <= 5)
            {
                this->died = 1;
                break;
            }
            this->Look(i,World);
            this->starvation(1);
            for(int h = 0; h <= 3; h++)
            {
            if(this->Look_out[h] == 1 || this->Look_out[h] == 6)
                {
                    FindFood = 1;
                    break;
                }
            }
        }
        if(died == 1)
            break;
        momento = 1;
        break;
        }
        case 1:
        {
        if(FindFood == 0)
        {
            if(hungry <= 10)
            {
                died = 1;
                break;
            }
            this->starvation(2);
            int new_navig = rand()%4;
            this->walk(new_navig, World);
            this->Look(nav,World);
            for(int h = 0; h <= 3; h++)
            {
            if(this->Look_out[h] == 1 || this->Look_out[h] == 6)
            {
                FindFood = 1;
                    break;
            }
            }
        }
        if(FindFood == 1)
        {
            if(hungry <= 10)
            {
                died = 1;
                break;
            }
            this->starvation(2);
            this->walk(nav, World);
            this->Look(nav, World);
            if(this->Look_out[0] == 1 || this->Look_out[0] == 6)
            {
                this->attack(nav,World);
                momento = 0;
            }
        }
        if(died == 1)
            break;
        }
        break;
        }
    };
    private:
    virtual void search(map **World)
    {
        for(int i = 0; i <= 3; i++)
        {
            if(this->hungry <= 5)
            {
                this->died = 1;
                break;
            }
            this->Look(i,World);
            this->starvation(5);
            for(int h = 0; h <= 3; h++)
            {
            if(this->Look_out[h] == 1 || this->Look_out[h] == 6)
            {
                FindFood = 1;
                    break;
            }
            }
        }
        };
    virtual void nav_set(int new_nav){this->nav = new_nav;};
    virtual void nav_get(int *get){*get = this->nav;};
    virtual void starvation(int starve){this->hungry = hungry-starve;};
    virtual void walk (int nav, map **World)
    {
        int maxX, maxY;
        int myXpos, myYpos;
        entity replace;
        this->pos_get(&myXpos, &myYpos);
        this->nav_set(nav);
        World[0][0].get_size(&maxX, &maxY);
        switch (nav)
        {
        case 0:
            if(myYpos -1 < 0)
                return;
            World[myYpos-1][myXpos].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos-1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos-1);
            return;
            break;
        case 1:
            if(myXpos+1 > maxX)
                return;
            World[myYpos][myXpos+1].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos][myXpos+1].Map_update(*this);
            this->pos_set(myXpos+1, myYpos);
            return;
            break;
        case 2:
            if (myYpos+1 > maxY)
                return;
            World[myYpos+1][myXpos].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos+1][myXpos].Map_update(*this);
            this->pos_set(myXpos, myYpos+1);
            return;
            break;
        case 3:
            if(myXpos-1 < 0)
                return;
            World[myYpos][myXpos-1].get_creature(&replace);
            World[myYpos][myXpos].Map_update(replace);
            World[myYpos][myXpos-1].Map_update(*this);
            this->pos_set(myXpos-1, myYpos);
            return;
            break;
        default:
            break;
        }
        return;
    };
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
    };
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

void generateEntireWorld(int *pred, int *Al, int *notAl, int *meat, int *fukt, map** WorldMap)
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
    *pred = Predators;
    *Al = Alive;
    *notAl = NAL;
    *meat = meats;
    *fukt = fruits;
};

void spawn(int P, int A, int N_A_L, int _meats, int _fruits, map **WorldMap, Predator *predats, grass_eat *grassets, Meat *mmeats, Fruit *ffruits, tree *treees)
{
    int sizeX, sizeY;
    int Predators = P;
    int Alive = A;
    int NAL = N_A_L;
    int meats = _meats;
    int fruits = _fruits;
    WorldMap[0][0].get_size(&sizeX, &sizeY);
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
    int count_pred = 0;
    int count_Alive = 0;
    int count_meats = 0;
    int count_fruits = 0;
    int count_tres = 0;
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
            predats[count_pred] = new_pred;
            Predators--;
            count_pred++;
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
            grassets[count_Alive] = new_grass;
            Alive--;
            count_Alive++;
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
                    treees[count_tres] = new_tree;
                    count_tres++;
                }
            NAL--;
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
            mmeats[count_meats] = new_meat;
            meats--;
            count_meats++;
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
            ffruits[count_fruits] = new_fruit;
            fruits--;
            count_fruits++;
        }
        if (Predators == 0 && Alive == 0 && NAL == 0 && meats == 0 && fruits == 0)
            return ;
    }
}
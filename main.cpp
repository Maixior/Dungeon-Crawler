#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<time.h>
#include "stuff.h"
#include "mapa.h"

void conCursor(HANDLE hConsole,bool hide) {
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = hide;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void setConCursor(int x, int y, HANDLE hConsole);

int findPlayerX(int mapa[5][5]);
int findPlayerY(int mapa[5][5]);

bool placeFree(int mapa[5][5],  int xx, int yy);
void keyHandle(int key);
void movePlayer(int dir, int way);

void setStuffToRender(int x, int y, int mapa[5][5], int dir);
void sendStufftoRender();
void drawMap(int render[15][20]);

void setStuffToRender(int x, int y, int mapa[5][5], int dir);
void sendStufftoRender();
void drawMap(int render[15][20], HANDLE hConsole);
void renderClear();
void drawGUI(HANDLE hConsole);
void c_menu_set(int a);


bool run = true;
bool reload = true;
bool c_menu = false;
bool rotate_r = false;
bool rotate_l = false;
int dir = 0;
int hp = 10;
int mp = 10;
int lvl = 1;
int exp = 1;

std::string name = "Maixior";

int main()
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    conCursor(hConsole, false);

    while(run) { //game loop
        if(reload){
            renderClear();
            setStuffToRender(findPlayerX(mapa), findPlayerY(mapa), mapa, dir);
            sendStufftoRender();
            drawMap(render, hConsole);
            drawGUI(hConsole);
        }
        keyHandle(getch());

    }

    return 0;
}

int findPlayerX(int mapa[5][5]) {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if(mapa[i][j] == 2) {
                return i;
            }
        }
    }
}

int findPlayerY(int mapa[5][5]) {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if(mapa[i][j] == 2) {
                    return j;
            }
        }
    }
}

bool placeFree(int mapa[5][5],  int xx, int yy) {
    if(mapa[xx][yy] == 0) {
        return true;
    } else {
        return false;
    }
}

void keyHandle(int key) {
    switch(key) {
    case 'w':
    case 'W':
        if(!c_menu) {
           movePlayer(dir, 1);
        } else {
            c_menu_set(1);
        }
        break;
    case 's':
    case 'S':
        if(!c_menu) {
            movePlayer(dir, 2);
        } else {
            c_menu_set(2);
        }
        break;
    case 'a':
    case 'A':
        if(!c_menu) {
            movePlayer(dir, 3);
        }
        break;
    case 'd':
    case 'D':
        if(!c_menu) {
            movePlayer(dir, 4);
        }
        break;

    case 'q':
    case 'Q':
        if(!c_menu) {
            if(dir>0) {
                dir--;
            } else {
                dir = 3;
            }
            rotate_l = true;
            reload = true;
        }
        break;
    case 'e':
    case 'E':
        if(!c_menu) {
            if(dir<3) {
                dir++;
            } else {
                dir = 0;
            }
            rotate_r = true;
            reload = true;
        }
        break;
    case 27:
        if(!c_menu) {
            c_menu = true;
            reload = true;
        }else{
            c_menu = false;
            reload = true;
        }
        //run = false;
        break;

    case '\r':
        if(c_menu) {
            int xx;
            for(int i=0; i<4; i++) {
                if(c_menu_chose[i] == '<') {
                    xx = i;
                }
            }
            switch(xx) {
            case 0:
                //restart
                break;
            case 1:
                //zapis
                break;
            case 2:
                //zaladowanie
                break;
            case 3:
                run = false;
                break;
            }
        }
    default:
        break;
    }
}

void movePlayer(int dir, int way) {
int a = 1;
int xx = findPlayerX(mapa);
int yy = findPlayerY(mapa);

    switch(dir) {
        case 0:
            a = 1;
            switch(way) {
            case 1:
                if(placeFree(mapa,xx-(1*a), yy)){
                    mapa[xx-(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 2:
                if(placeFree(mapa,xx+(1*a), yy)){
                    mapa[xx+(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 3:
                if(placeFree(mapa,xx, yy-(1*a))){
                    mapa[xx][yy-(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 4:
                if(placeFree(mapa,xx, yy+(1*a))){
                    mapa[xx][yy+(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            }
            break;
        case 1:

            a = 1;
            switch(way) {
            case 1:
                if(placeFree(mapa,xx, yy+(1*a))){
                    mapa[xx][yy+(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 2:
                if(placeFree(mapa,xx, yy-(1*a))){
                    mapa[xx][yy-(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 3:
                if(placeFree(mapa,xx-(1*a), yy)){
                    mapa[xx-(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 4:
                if(placeFree(mapa,xx+(1*a), yy)){
                    mapa[xx+(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            }
            break;
        case 2:

            a = -1;
            switch(way) {
            case 1:
                if(placeFree(mapa,xx-(1*a), yy)){
                    mapa[xx-(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 2:
                if(placeFree(mapa,xx+(1*a), yy)){
                    mapa[xx+(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 3:
                if(placeFree(mapa,xx, yy-(1*a))){
                    mapa[xx][yy-(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 4:
                if(placeFree(mapa,xx, yy+(1*a))){
                    mapa[xx][yy+(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            }
            break;
        case 3:

            a = -1;
            switch(way) {
            case 1:
                if(placeFree(mapa,xx, yy+(1*a))){
                    mapa[xx][yy+(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 2:
                if(placeFree(mapa,xx, yy-(1*a))){
                    mapa[xx][yy-(1*a)] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 3:
                if(placeFree(mapa,xx-(1*a), yy)){
                    mapa[xx-(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            case 4:
                if(placeFree(mapa,xx+(1*a), yy)){
                    mapa[xx+(1*a)][yy] = 2;
                    mapa[xx][yy] = 0;
                    reload = true;
                }
                break;
            }
            break;
    }


}

void setStuffToRender(int x, int y, int mapa[5][5], int dir){

    int a;

    switch(dir) {
        case 0:
            a = 1;

            if(mapa[x-(1*a)][y]==1) {
                sciana_b = true;
            } else {
                sciana_b = false;
            }

            if(!sciana_b) {
                if(mapa[x-(1*a)][y+(1*a)]==1) {
                    sciana_r_b = true;
                } else {
                    sciana_r_b = false;
                }
                if(mapa[x-(1*a)][y-(1*a)]==1) {
                    sciana_l_b = true;
                } else {
                    sciana_l_b = false;
                }
                if(mapa[x-(2*a)][y]==1) {
                    sciana_b_b = true;
                } else {
                    sciana_b_b = false;
                }

                if(!sciana_b_b) {
                    sciana_b_b_b = true;
                } else {
                    sciana_b_b_b = false;
                }
            }

            if(mapa[x][y-(1*a)]==1) {
                sciana_l = true;
            } else {
                sciana_l = false;
            }

            if(mapa[x][y+(1*a)]==1) {
                sciana_r = true;
            } else {
                sciana_r = false;
            }
            break;

        case 1:
            a = -1;

            if(mapa[x][y-(1*a)]==1) {
                sciana_b = true;
            } else {
                sciana_b = false;
            }

            if(!sciana_b) {
                if(mapa[x-(1*a)][y-(1*a)]==1) {
                    sciana_r_b = true;
                } else {
                    sciana_r_b = false;
                }
                if(mapa[x+(1*a)][y-(1*a)]==1) {
                    sciana_l_b = true;
                } else {
                    sciana_l_b = false;
                }
                if(mapa[x][y-(2*a)]==1) {
                    sciana_b_b = true;
                } else {
                    sciana_b_b = false;
                }

                if(!sciana_b_b) {
                    sciana_b_b_b = true;
                } else {
                    sciana_b_b_b = false;
                }
            }

            if(mapa[x+(1*a)][y]==1) {
                sciana_l = true;
            } else {
                sciana_l = false;
            }

            if(mapa[x-(1*a)][y]==1) {
                sciana_r = true;
            } else {
                sciana_r = false;
            }
            break;
        case 2:
            a = -1;

            if(mapa[x-(1*a)][y]==1) {
                sciana_b = true;
            } else {
                sciana_b = false;
            }

            if(!sciana_b) {
                if(mapa[x-(1*a)][y+(1*a)]==1) {
                    sciana_r_b = true;
                } else {
                    sciana_r_b = false;
                }
                if(mapa[x-(1*a)][y-(1*a)]==1) {
                    sciana_l_b = true;
                } else {
                    sciana_l_b = false;
                }
                if(mapa[x-(2*a)][y]==1) {
                    sciana_b_b = true;
                } else {
                    sciana_b_b = false;
                }

                if(!sciana_b_b) {
                    sciana_b_b_b = true;
                } else {
                    sciana_b_b_b = false;
                }
            }

            if(mapa[x][y-(1*a)]==1) {
                sciana_l = true;
            } else {
                sciana_l = false;
            }

            if(mapa[x][y+(1*a)]==1) {
                sciana_r = true;
            } else {
                sciana_r = false;
            }
            break;

        case 3:
            a = 1;

            if(mapa[x][y-(1*a)]==1) {
                sciana_b = true;
            } else {
                sciana_b = false;
            }

            if(!sciana_b) {
                if(mapa[x-(1*a)][y-(1*a)]==1) {
                    sciana_r_b = true;
                } else {
                    sciana_r_b = false;
                }
                if(mapa[x+(1*a)][y-(1*a)]==1) {
                    sciana_l_b = true;
                } else {
                    sciana_l_b = false;
                }
                if(mapa[x][y-(2*a)]==1) {
                    sciana_b_b = true;
                } else {
                    sciana_b_b = false;
                }

                if(!sciana_b_b) {
                    sciana_b_b_b = true;
                } else {
                    sciana_b_b_b = false;
                }
            }

            if(mapa[x+(1*a)][y]==1) {
                sciana_l = true;
            } else {
                sciana_l = false;
            }

            if(mapa[x-(1*a)][y]==1) {
                sciana_r = true;
            } else {
                sciana_r = false;
            }
            break;
    }


}

void sendStufftoRender() {
    for(int i=0; i<15; i++) {
        for(int j=0; j<20; j++) {
            if(ground[i][j] != 0) {
                buffor[i][j] = ground[i][j];
            }
        }
    }

    if(sciana_b_b_b) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_back_back_back[i][j] != 0) {
                    buffor[i][j] = wall_back_back_back[i][j];
                }
            }
        }
    }


    if(sciana_b_b) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_back_back[i][j] != 0) {
                    buffor[i][j] = wall_back_back[i][j];
                }
            }
        }
    }



    if(sciana_l_b) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_left_back[i][j] != 0) {
                    buffor[i][j] = wall_left_back[i][j];
                }
            }
        }
    }

    if(sciana_r_b) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_right_back[i][j] != 0) {
                    buffor[i][j] = wall_right_back[i][j];
                }
            }
        }
    }

    if(sciana_b) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_back[i][j] != 0) {
                    buffor[i][j] = wall_back[i][j];
                }
            }
        }
    }
    if(sciana_l) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_left[i][j] != 0) {
                    buffor[i][j] = wall_left[i][j];
                }
            }
        }
    }



    if(sciana_r) {
        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                if(wall_right[i][j] != 0) {
                    buffor[i][j] = wall_right[i][j];
                }
            }
        }
    }


        for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                    render[i][j] = buffor[i][j];
            }
        }

}

void drawMap(int render[15][20], HANDLE hConsole) {
for(int i=0; i<15; i++) { for(int j=0; j<20; j++) {
    switch(render[i][j]) {
        case 1: //ciemny czerwony
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
            break;
        case 2: //jasny czerwony
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY);
            break;
        case 3://ciemny ¿ó³ty
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED);
            break;
        case 4://jasny ¿ó³ty
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
            break;
        default: //czarny
            SetConsoleTextAttribute(hConsole, 0);
            break;
        }
    printf(" ");
} printf("\n"); }
    SetConsoleTextAttribute(hConsole, 15);
}

void renderClear() {
    for(int i=0; i<15; i++) {
            for(int j=0; j<20; j++) {
                render[i][j] = 0;
                buffor[i][j] = 0;
            }
    }
    system("cls");
    reload = false;
}

void setConCursor(int x, int y, HANDLE hConsole) {
    COORD coordDest;
    coordDest.X = x;
    coordDest.Y = y;
    SetConsoleCursorPosition(hConsole, coordDest);
}

void drawGUI(HANDLE hConsole) {
    int gx = 20;
    int gy = 0;
    for(int i=0; i<15; i++) {
        setConCursor(gx, gy+i, hConsole);
        std::cout<<menu[i];
    }

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            setConCursor(44+i, 2+j, hConsole);
            switch(mapa[j][i]) {
                case 0: //ciemny czerwony
                    SetConsoleTextAttribute(hConsole, 0);
                    break;
                case 1: //jasny czerwony
                    SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY);
                    break;
                case 2://ciemny ¿ó³ty
                    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
                    break;
                default: //czarny
                    SetConsoleTextAttribute(hConsole, 0);
                    break;
            }
            if(mapa[j][i] == 2) {
                switch(dir) {
                        case 0:
                            printf("^");
                            break;
                        case 1:
                            printf(">");
                            break;
                        case 2:
                            printf("V");
                            break;
                        case 3:
                            printf("<");
                            break;
                }
            } else {
                printf(" ");
            }
        }
        SetConsoleTextAttribute(hConsole, 0);
    }
    setConCursor(gx+8,gy+1, hConsole);
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<name;
    setConCursor(gx+6,gy+2, hConsole);
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_INTENSITY);
    for(int i=0; i<hp; i++) {
        printf(" ");
    }
    setConCursor(gx+6,gy+3, hConsole);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    for(int i=0; i<hp; i++) {
        printf(" ");
    }
    setConCursor(gx+7,gy+4, hConsole);
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<lvl;
    setConCursor(gx+2,gy+6, hConsole);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED);
    for(int i=0; i<16; i++) {
        printf(" ");
    }
    setConCursor(gx+2,gy+6, hConsole);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    for(int i=0; i<exp; i++) {
        printf(" ");
    }

    if(c_menu) {

        for(int i=0; i<9; i++) {
            for(int j=0; j<21; j++) {
            setConCursor(gx+j,i+3, hConsole);
                if(i==0 || i == 8 || j == 0 || j == 20) {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED);
                    printf(" ");
                } else {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
                    printf(" ");
                }
            }

            setConCursor(gx+10-2,4,hConsole);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
            printf("MENU");
            for(int i=0; i<4; i++) {
                setConCursor(gx+5,6+i,hConsole);
                std::cout<<c_menu_option[i]<<" "<<c_menu_chose[i];
            }
        }

    }

    setConCursor(0, 15, hConsole);
    SetConsoleTextAttribute(hConsole, 15);
}

void c_menu_set(int a) {
    int xx;
    for(int i=0; i<4; i++) {
        if(c_menu_chose[i] == '<') {
            xx = i;
        }
    }
    c_menu_chose[xx] = ' ';

    switch(a) {
    case 1:

        if(xx == 0) {
            c_menu_chose[3] = '<';
        } else {
            c_menu_chose[xx-1] = '<';
        }
        break;
    case 2:
        if(xx == 3) {
            c_menu_chose[0] = '<';
        } else {
            c_menu_chose[xx+1] = '<';
        }
        break;
    }
    reload = true;
}


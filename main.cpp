#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h> 
#include <cmath>
using namespace std;

class Robot{
    public:
        pair<int,int> coordinate;
        long long panjang_senjata;
        int health;
        int kecoa_killed;
        void init(int senjata, int input_health){ 
            coordinate=make_pair(0,0);
            panjang_senjata = senjata;
            health = input_health;
            kecoa_killed=0;
        }
        void killed_kecoa(){
            kecoa_killed++;
        }
        void robot_attacked(){
            health--;
        }
};

class Kecoa{
    public:
        pair<int,int> coordinate;
        int health;
        int attack_radius;
        void init(pair<int,int> mapsize,pair<int,int> robot_coordinate, int radius, int level_health ){
            srand ( time(NULL) );
            pair<int,int>current_coordinate = coordinate;
            while(coordinate == current_coordinate || coordinate == robot_coordinate){
                coordinate.first = rand() % mapsize.first;
                coordinate.second = rand() % mapsize.second;
            }
            attack_radius = radius;
            health = level_health;
        }
};

class Game{
    public:
        Robot *robot;
        Kecoa *kecoa;
        int level;
        pair<int,int> size;
        void init(Robot *input_robot,Kecoa *input_kecoa){
            int size_x,size_y,senjata, health;
            cout << 
            "====================" << endl <<   
            "Welcome to the Game!" << endl << 
            "====================" << endl;
            cout << "Masukkan besar map:\n1. Lebar: "; cin >> size_x;
            cout << "2. Tinggi: "; cin >> size_y; 
            size = make_pair(size_x,size_y);
            cout << "Masukkan panjang senjata: "; cin >> senjata;
            cout << "Masukkan banyak health awal robot: "; cin >> health;
            gerak("help");
            level = 1;
            robot = &(*input_robot);
            kecoa = &(*input_kecoa);
            (*kecoa).init(size,make_pair(0,0),1,1);
            (*robot).init(senjata,health);
        }
        void showMap(){            
            cout << endl;
            for(int i = size.second;i>=-1;i--){
                for(int j = -1;j<=size.first;j++){
                    if(j == (*robot).coordinate.first && i == (*robot).coordinate.second){
                        cout << "# ";
                        continue;
                    }else if(j == (*kecoa).coordinate.first && i == (*kecoa).coordinate.second){
                        cout << "X ";
                    } else if(j == size.first || i == size.second || i == -1 || j==-1){
                        cout << "O ";
                    } else{
                        cout << "_ ";
                    }
                }
                cout << endl;
            }
        }
        string gerak(string gerak){
            int *x = &((*robot).coordinate.first);
            int *y = &((*robot).coordinate.second);
            if(gerak == "kanan"){
                if(
                    *x == size.first-1 
                    || 
                        (*x == (*kecoa).coordinate.first-1
                        &&
                        *y == (*kecoa).coordinate.second) 
                ) return "Menabrak sesuatu\n";
                *x += 1; 
            } else if(gerak == "kiri") {
                if(
                    *x == 0 
                    || 
                        (*x == (*kecoa).coordinate.first+1
                        &&
                        *y == (*kecoa).coordinate.second)
                ) return "Menabrak sesuatu\n";
                *x -= 1;
            } else if(gerak=="atas") {
                if(
                    *y == size.second-1 
                    || 
                        (*y == (*kecoa).coordinate.second-1
                        &&
                        *x == (*kecoa).coordinate.first
                        )
            ) return "Menabrak sesuatu\n";
                *y += 1;
            } else if(gerak=="bawah"){
                if(*y == 0 || (*y == (*kecoa).coordinate.second+1 && *x == (*kecoa).coordinate.first)) return "Menabrak sesuatu\n";
                *y -= 1;
            } else if(gerak=="serang") {
                long long jarak = sqrt(pow((*robot).coordinate.first - (*kecoa).coordinate.first,2) + pow((*robot).coordinate.second - (*kecoa).coordinate.second,2));
                if(jarak <= (*robot).panjang_senjata){
                    (*robot).killed_kecoa();
                    return "win";
                } else {
                    return "jarak";
                }
            } else if(gerak=="help") {
                cout << endl <<
                "Commands : "          << endl <<
                "1. type kanan to move right" << endl <<
                "2. type kiri to move left" << endl <<
                "3. type atas to move up" << endl <<
                "4. type bawah to move down" << endl << 
                "5. type help to show all the commands list" << endl <<
                "6. type status to show map, current distance to kecoa, and robot health" << endl << endl;
            } else if(gerak == "status"){
                showMap();
                int x =  kecoa->coordinate.first- robot->coordinate.first;
                int y =  kecoa->coordinate.second- robot->coordinate.second;
                cout << "Robot health : " << robot->health << endl;
                cout << "Jarak dari kecoa : " << endl << "X: " << x << endl << "Y: " << y << endl;
            }else {
                return "Input tidak valid!\n";
            }
            return "";
        }
        void continue_game(){
            level++;
            (*kecoa).init(size,robot->coordinate,level,level);
        }
        int in_radius(){
            long long jarak = sqrt(pow((*robot).coordinate.first - (*kecoa).coordinate.first,2) + pow((*robot).coordinate.second - (*kecoa).coordinate.second,2));
            if(jarak<kecoa->attack_radius){
                cout << "Kecoa attacked robot! robot loses 1 heart!" << endl;
                robot->robot_attacked();
            }
            return robot->health;
        }
};


int main(){
    Robot anu;
    Kecoa kecoa;
    Game game;
    game.init(&anu,&kecoa);
    while(true){
        string input;
        cout << "Masukkan Command : ";
        cin >> input;
        string feedback = game.gerak(input);
        cout << endl;
        if(feedback != ""){
            if(feedback == "win") {
                int answer;
                cout << "Level beated!\n";
                cout << "Kecoa killed : " << game.robot->kecoa_killed << endl << endl;
                cout << "Do you want to continue?" << endl << "1 = Yes" << endl << "2 = No" << endl << "answer : ";
                cin >> answer;
                if (answer == 1){
                    game.continue_game();
                } else {
                    break;
                }
            } else if(feedback == "jarak") {
                cout << "Senjata tidak bisa menjangkau kecoa!" << endl; 
            } else if(feedback == "none") {
                continue;
            } else {
                cout << feedback << endl;
            }
        }
        int health_status;
        if(input != "showmap") health_status = game.in_radius();
        if(health_status == 0){
            cout << "Robot died!\nGame over!" << endl;
            break;
        }
    } 
}

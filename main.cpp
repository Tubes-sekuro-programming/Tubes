#include<iostream>
#include<vector>
#include<algorithm>
#include <time.h>
#include <stdlib.h> 
#include<cmath>
using namespace std;

class Robot{
    public:
        pair<int,int> coordinate;
        long long panjang_senjata;
        void init(int senjata){ 
            coordinate=make_pair(0,0);
            panjang_senjata = senjata;
        }
};

class Kecoa{
    public:
        pair<int,int> coordinate;
        pair<int,int> init(pair<int,int> mapsize){
            srand ( time(NULL) );
            while(coordinate == make_pair(0,0)){
                coordinate.first = rand() % mapsize.first;
                coordinate.second = rand() % mapsize.second;
            }
            return coordinate;
        }
};

class Game{
    public:
        Robot *robot;
        Kecoa *kecoa;
        pair<int,int> size;
        void init(Robot *input_robot,Kecoa *input_kecoa){
            cout << 
            "====================" << endl <<   
            "Welcome to the Game!" << endl << 
            "====================" << endl;
            int size_x,size_y,senjata;
            cout << "Masukkan besar map:\n1. Lebar: "; cin >> size_x;
            cout << "2. Tinggi: "; cin >> size_y; 
            size = make_pair(size_x,size_y);
            cout << "Masukkan panjang senjata: "; cin >> senjata;
            gerak("help");
            robot = &(*input_robot);
            kecoa = &(*input_kecoa);
            (*kecoa).init(size);
            (*robot).init(senjata);
            showMap();
        }
        void showMap(){
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
            cout << endl;
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
                    return "win";
                } else {
                    return "jarak";
                }
            } else if(gerak=="help") {
                cout << 
                "Commands : "          << endl <<
                "1. type kanan to move right" << endl <<
                "2. type kiri to move left" << endl <<
                "3. type atas to move up" << endl <<
                "4. type bawah to move down" << endl << 
                "5. type help to show all the commands list" << endl <<
                "6. type showmap to show the map if necessary" << endl;
            } else if(gerak == "showmap"){
                showMap();
            } else {
                return "Input tidak valid!\n";
            }
            return "";
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
        if(feedback != ""){
            if(feedback == "win") {
                cout << "Game over!\nYou won!";
                break;
            } else if(feedback == "jarak") {
                cout << "Senjata tidak bisa menjangkau kecoa!" << endl; 
            } else if(feedback == "none") {
                continue;
            } else {
                cout << feedback << endl;
            }
        } else {
            game.showMap();
        }
    } 
}

    
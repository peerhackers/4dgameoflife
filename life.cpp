#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

const int boardsize = 20;//board length/width/height/otherthing ///BUGG CURRENTLY BREAKS AT >17 ***********************
class cell{
  bool alive;
  int i,j,k,l = -1;
  int i2,j2,k2,l2 = 2;
  bool uninitialized = true;
public:
  cell(){
    alive = false;
  }
  bool isalive(){
    return alive;
  }
  void kill(){
    alive = false;
  }
  void birth(){
    alive = true;
  }
};//endofcell~~~~
class boardclass{
  cell cells[boardsize][boardsize][boardsize][boardsize];
  cell copiedcells[boardsize][boardsize][boardsize][boardsize];
  int overpopulate;//kill
  int underpopulate;//kill
  int reproducelow;//create cell
  int reproducehigh;
public:
  boardclass(int underpopulatein = 10, int overpopulatein = 40, int reproducelowin = 30, int reproducehighin = 39){
    overpopulate   = overpopulatein;
    underpopulate  =  underpopulatein;
    reproducelow   = reproducelowin;
    reproducehigh  =  reproducehighin;
  }
  void testpop(){
    cells[4][6][8][2].birth();
  }
  void birthshape();//do some premade shape stuff
  void populate(bool blanknotrandom = true){
    for(int x1 = 0; x1 < boardsize; x1++){
      for(int x2 = 0; x2 < boardsize; x2++){
        for(int x3 = 0; x3 < boardsize; x3++){
          for(int x4 = 0; x4 < boardsize; x4++){
            if(blanknotrandom) cells[x1][x2][x3][x4].kill();
            else if(rand()%2 == 1) cells[x1][x2][x3][x4].birth();
            else cells[x1][x2][x3][x4].kill();
          }
        }
      }
    }// end of for hell
  }//end of populaterandom
  void printconsole(){
  for(int x1 = 0; x1 < boardsize; x1++){
    for(int x2 = 0; x2 < boardsize; x2++){
      bool cellhere = false;
      for(int x3 = 0; x3 < boardsize; x3++){
        for(int x4 = 0; x4 < boardsize; x4++){
          if (cells[x1][x2][x3][x4].isalive()){
            cellhere = true;
          }
        }
      }
      if(cellhere)cout << "@";
      else cout << " ";
    }
    cout << endl;
  }//end of for-hell
}//end of printconsole
  int fulltick(){//currently checks neighboors and kills/births as if a tick happened
    memcpy(copiedcells, cells, sizeof(cells));
    for(int x1 = 0; x1 < boardsize; x1++){
      for(int x2 = 0; x2 < boardsize; x2++){
        for(int x3 = 0; x3 < boardsize; x3++){
          for(int x4 = 0; x4 < boardsize; x4++){//beggining for-hell
              int neighboors = 0;
              int i,j,k,l = -1;
              int i2,j2,k2,l2 = 2;
              if (x1 == 0)i++;
              if (x2 == 0)j++;
              if (x3 == 0)k++;
              if (x4 == 0)l++;
              if (x1 == boardsize)i2--;
              if (x2 == boardsize)j2--;
              if (x3 == boardsize)k2--;
              if (x4 == boardsize)l2--;
              for(i;i < i2; i++){//begginnng main for-hell
                for(j;j < j2; j++){
                  for(k;k < k2; k++){
                    for(l;l < l2; l++){
                      if (copiedcells[x1+i][x2+j][x3+k][x4+l].isalive()) neighboors++;
                    }
                  }
                }
              }//end of main for-hell
              if (cells[x1][x2][x3][x4].isalive()) neighboors -= 1;
              if (neighboors>overpopulate) cells[x1][x2][x3][x4].kill();
              if (neighboors<underpopulate) cells[x1][x2][x3][x4].kill();
              if (neighboors>reproducelow && neighboors<reproducehigh) cells[x1][x2][x3][x4].birth();
              return neighboors;
          }
        }
      }
    }//end of begginning for-hell
  }//end of fulltick
};
///END OF CLASSES///
void game(){
  const int neighboors = 81; //(3^n ) 1 is the actual point
  //cell board[boardsize][boardsize][boardsize][boardsize];
  //filllife();
  boardclass board;
  board.populate(false);//makes blank if true sent, random if false sent
  //board.testpop(); tests single cell specified in function
  board.printconsole();
  while(true){
    board.fulltick();
    board.printconsole();
    string pause;
    cin >> pause;
  }//endofwhile
}//endofgame~~~~
//END OF FUNCS//
int main(){
  srand(time(NULL));//random seed
  //vector<vector<vector<vector<bool>>>>board; //resize vector around current cells (bad at high size), I cannot figure that shit out
  game();
}//endofmain~~~~

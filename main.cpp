//
//  main.cpp
//  MazeGame
//
//  Created by 00 on 5/6/15.
//  Copyright (c) 2015 00. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <vector>
#include <ctime>




using namespace std;

class position{
public:
    int x= 0;
    int y= 0;

    int index(){
        int value = (this->x * 8) + this->y;
        return value;
    }


};



class Maze {
public:

    // you can modify the characters in this array to draw new mazes, 'x' is the agent, 'm' is a wall and 'G' is the goal that 'x' will try and reach
    char MazeSpace[8][8] =
    {
        {'x',' ',' ',' ',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ','m',' ','m',' ','m',' ',' '},
        {' ',' ',' ','m',' ',' ',' ','G'},
    };




//    char MazeSpace[8][8] =
//    {
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ',' '},
//        {' ',' ',' ',' ',' ',' ',' ','G'},
//    };

    void makeMove(position);
    bool canMove(position);
    void setPiece(position, char);
    char getPiece(position);
    void printMaze();
    bool foundExit();
    position findPosOfPlayer();
    position findPosOfGoal();
};
class qLearner{
public:
//    int qTable[8][8] = //this tells the agent what move to take next from what position on the board
//    {
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0},
//    };

    float qTable[64][4];
    float rewardSpace[64][4]; //this tells the agent the expected reward from this position, 64 states with 4 possible actions
    // 0 is down, 1 is up , 2 is left, 3 is right
    void qLearn(Maze, int, float);
    void printQTable();
    void printRewardSpace();

};

void Maze::setPiece(position pos, char piece){
    this->MazeSpace[pos.x][pos.y] = piece;
}
char Maze::getPiece(position pos){
    char piece = this->MazeSpace[pos.x][pos.y];
    return piece;
}
position Maze::findPosOfPlayer(){
    position to_check;
    position of_player;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            to_check.x = i;
            to_check.y = j;
            if (getPiece(to_check) == 'o') {
                of_player = to_check;
                break;
            }
        }
    }
    return of_player;
}
position Maze::findPosOfGoal(){
    position to_check;
    position of_goal;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            to_check.x = i;
            to_check.y = j;
            if (getPiece(to_check) == 'G') {
                of_goal = to_check;
                break;
            }
        }
    }
    return of_goal;
}
void Maze::makeMove(position pos){
    if(canMove(pos)){

        setPiece(findPosOfPlayer(), ' ');
        setPiece(pos, 'o');
    }
    else{
        cout << "cant move" << endl;
        cout << pos.x << endl;
        cout << pos.y << endl;
        cout << findPosOfPlayer().x << endl;
        cout << findPosOfPlayer().y << endl;
    }
};
bool Maze::canMove(position pos){
    if( ((((pos.x- findPosOfPlayer().x == 1) || (pos.x- findPosOfPlayer().x == -1))&&
        ((pos.y- findPosOfPlayer().y == 0)))||
       (((pos.y- findPosOfPlayer().y == 1) || (pos.y- findPosOfPlayer().y == -1))&&
        ((pos.x- findPosOfPlayer().x == 0))))&&
        (pos.x <= 7 && pos.x >= 0)&&
        (pos.y <= 7 && pos.y >= 0)&&
        (getPiece(pos) == ' ' ||getPiece(pos) == 'G')){
        return true;

    }
    else{
        return false;
    }
}
bool Maze:: foundExit(){
    position to_check;
    bool found_goal = true;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            to_check.x = i;
            to_check.y = j;
            if (getPiece(to_check) == 'G') {
                found_goal = false;
                break;
            }
        }
    }
    return found_goal;
}

void Maze::printMaze(){
    std::cout << "  |0|1|2|3|4|5|6|7|"<<std::endl;
    std::cout << "|0|"<<this->MazeSpace[0][0]<<"|"<<this->MazeSpace[0][1]<<"|"<<this->MazeSpace[0][2]<<"|"<<this->MazeSpace[0][3]<<"|"<<this->MazeSpace[0][4]<<"|"<<this->MazeSpace[0][5]<<"|"<<this->MazeSpace[0][6]<<"|"<<this->MazeSpace[0][7]<<"|\n";
    std::cout << "|1|"<<this->MazeSpace[1][0]<<"|"<<this->MazeSpace[1][1]<<"|"<<this->MazeSpace[1][2]<<"|"<<this->MazeSpace[1][3]<<"|"<<this->MazeSpace[1][4]<<"|"<<this->MazeSpace[1][5]<<"|"<<this->MazeSpace[1][6]<<"|"<<this->MazeSpace[1][7]<<"|\n";
    std::cout << "|2|"<<this->MazeSpace[2][0]<<"|"<<this->MazeSpace[2][1]<<"|"<<this->MazeSpace[2][2]<<"|"<<this->MazeSpace[2][3]<<"|"<<this->MazeSpace[2][4]<<"|"<<this->MazeSpace[2][5]<<"|"<<this->MazeSpace[2][6]<<"|"<<this->MazeSpace[2][7]<<"|\n";
    std::cout << "|3|"<<this->MazeSpace[3][0]<<"|"<<this->MazeSpace[3][1]<<"|"<<this->MazeSpace[3][2]<<"|"<<this->MazeSpace[3][3]<<"|"<<this->MazeSpace[3][4]<<"|"<<this->MazeSpace[3][5]<<"|"<<this->MazeSpace[3][6]<<"|"<<this->MazeSpace[3][7]<<"|\n";
    std::cout << "|4|"<<this->MazeSpace[4][0]<<"|"<<this->MazeSpace[4][1]<<"|"<<this->MazeSpace[4][2]<<"|"<<this->MazeSpace[4][3]<<"|"<<this->MazeSpace[4][4]<<"|"<<this->MazeSpace[4][5]<<"|"<<this->MazeSpace[4][6]<<"|"<<this->MazeSpace[4][7]<<"|\n";
    std::cout << "|5|"<<this->MazeSpace[5][0]<<"|"<<this->MazeSpace[5][1]<<"|"<<this->MazeSpace[5][2]<<"|"<<this->MazeSpace[5][3]<<"|"<<this->MazeSpace[5][4]<<"|"<<this->MazeSpace[5][5]<<"|"<<this->MazeSpace[5][6]<<"|"<<this->MazeSpace[5][7]<<"|\n";
    std::cout << "|6|"<<this->MazeSpace[6][0]<<"|"<<this->MazeSpace[6][1]<<"|"<<this->MazeSpace[6][2]<<"|"<<this->MazeSpace[6][3]<<"|"<<this->MazeSpace[6][4]<<"|"<<this->MazeSpace[6][5]<<"|"<<this->MazeSpace[6][6]<<"|"<<this->MazeSpace[6][7]<<"|\n";
    std::cout << "|7|"<<this->MazeSpace[7][0]<<"|"<<this->MazeSpace[7][1]<<"|"<<this->MazeSpace[7][2]<<"|"<<this->MazeSpace[7][3]<<"|"<<this->MazeSpace[7][4]<<"|"<<this->MazeSpace[7][5]<<"|"<<this->MazeSpace[7][6]<<"|"<<this->MazeSpace[7][7]<<"|\n";
    std::cout << "\n";
}
void qLearner::qLearn(Maze board, int episodes, float discountFactor){

    srand(time(0)); //this seeds my random numbers with truly random numbers
    
    
    //fills out reward table and gives us an encoding of the board space that can be utilized directly by q learning
    for (int i = 0; i < 64; i++) {
        position pos;
        pos.x = i/8;
        pos.y = i%8;
        position downMove = pos;
        if (downMove.x<7) {
            downMove.x += 1;
        }
        // bounds check these.....
        position upMove = pos;
        if(upMove.x>0){
        upMove.x -= 1;
        }
        position leftMove = pos;
        if(leftMove.y>0){
        leftMove.y -= 1;
        }
        position rightMove = pos;
        if(rightMove.y<7){
        rightMove.y += 1;
        }
        if ((board.getPiece(pos) == ' ' )) { // if it's a viable space to move from

            //for down moves, [x][0] part of reward array
            if (board.getPiece(downMove) == 'G'  && (downMove.x < 8 )) {//bounds check
                this->rewardSpace[i][0] = 100; // 100 for a down move to goal
            }
            else if ((board.getPiece(downMove) == ' ')   && (downMove.x < 8 )) {//bounds check
                this->rewardSpace[i][0] = 0; // 0 for a down move to viable piece
            }
            else{
                this->rewardSpace[i][0] = -1; //everything else is not a viable action
            }
            //for UP MOVES, [x][1] part of reward of array
            if (board.getPiece(upMove) == 'G'  && (upMove.x >= 0 )) {//bounds check
                this->rewardSpace[i][1] = 100; // 100 for a up move to goal
            }
            else if ((board.getPiece(upMove) == ' ' )   && (upMove.x >= 0 )) {//bounds check
                this->rewardSpace[i][1] = 0; // 0 for a up move to viable piece
            }
            else{
                this->rewardSpace[i][1] = -1; //everything else is not a viable action
            }


            //for LEFT MOVES, [x][2] part of reward of array
            if (board.getPiece(leftMove) == 'G'  && (leftMove.y >= 0 )) {//bounds check
                this->rewardSpace[i][2] = 100; // 100 for a left move to goal
            }
            else if ((board.getPiece(leftMove) == ' ' )   && (leftMove.y >= 0 )) {//bounds check
                this->rewardSpace[i][2] = 0; // 0 for a left move to viable piece
            }
            else{
                this->rewardSpace[i][2] = -1; //everything else is not a viable action
            }


            //for RIGHT MOVES, [x][3] part of reward of array
            if (board.getPiece(rightMove) == 'G'  && (rightMove.y < 8 )) {//bounds check
                this->rewardSpace[i][3] = 100; // 100 for a right move to goal
            }
            else if ((board.getPiece(rightMove) == ' ' )   && (rightMove.y < 8 )) {//bounds check
                this->rewardSpace[i][3] = 0; // 0 for a right move to viable piece
            }
            else{

                //cout << "YOU BROKE IT WITH THIS" << endl;

                this->rewardSpace[i][3] = -1;

            }
        }
        else{
            this->rewardSpace[i][0] = -1; //everything else is not a viable action
            this->rewardSpace[i][1] = -1;
            this->rewardSpace[i][2] = -1;
            this->rewardSpace[i][3] = -1;
        }


        }


    //variables used in processing
    bool validStartState = false;
    bool validMoveToTake = false;
    int randomMove = 0;
    float maxActionValue = -10;
    position startingPos;
    position nextState;
    position checkPiece;
    int initialState;


    //this is how many trials the agent is going to train for
    while(episodes >= 0){

        //cout << "THis Happened" << endl;
        while(validStartState == false) {
            initialState = rand()%64;
            //cout << "start value to be validified is : " << initialState <<endl;



            checkPiece.x = initialState/8;
            checkPiece.y = initialState%8;



            if (board.getPiece(checkPiece) == ' ') {

                startingPos.x = initialState/8; //this math derives x and y from the index value of state; i swear it works
                startingPos.y = initialState%8;
                //cout << "validStartState value is : " << initialState <<endl;
                validStartState = true;
            }

        }




        //this loops the learning process until the agent reaches a terminal state
        while(board.getPiece(startingPos) != 'G'){
            //now we have a valid position to start from
            //this starts the agent in a random place on the 8x8 board


            //this loops until we get a valid move from the moveList implied by the reward table
            while(validMoveToTake == false){
                    randomMove = rand()%4;
                    //randomMove = 0;
                    //cout << "Starting Position.index function returns " << startingPos.index() <<endl;
                //cout << "random move at this point is " << randomMove <<endl;
                    if(this->rewardSpace[startingPos.index()][randomMove] != -1){//this means that the move can be taken and returns a reward
                        validMoveToTake = true;
                        //cout << "got a valid move to take" << endl;

                    }
                }
                //cout << "got out of valid start state loop" << endl;
                //cout << "randomMove is: " << randomMove <<endl;


                if (randomMove == 0) { // down move
                    if(startingPos.x < 7){ //need this so the array does not try and access an out of bounds location
                        nextState.x = startingPos.x + 1;
                        nextState.y = startingPos.y;
                    }
                    //this for loop steps through the four actions of the next state to find the maxActionValue
                    for (int i = 0; i < 4; i++) {
                        if(this->qTable[nextState.index()][i] > maxActionValue){
                            maxActionValue = this->qTable[nextState.index()][i];
                        }
                    }
                    this->qTable[startingPos.index()][0] = this->rewardSpace[startingPos.index()][0] + (discountFactor * maxActionValue);
                    startingPos.x = nextState.x; // this updates the startState to be the nextState, then we start over the process
                    startingPos.y = nextState.y;
                    maxActionValue = -10; //reset maxaction value
                }
                else if (randomMove == 1) { // up move
                    if(startingPos.x > 0){
                        nextState.x = startingPos.x - 1;
                        nextState.y = startingPos.y;
                    }
                    //this for loop steps through the four actions of the next state to find the maxActionValue
                    for (int i = 0; i < 4; i++) {
                        if(this->qTable[nextState.index()][i] > maxActionValue){
                            maxActionValue = this->qTable[nextState.index()][i];
                        }
                    }
                    this->qTable[startingPos.index()][1] = this->rewardSpace[startingPos.index()][1] + (discountFactor * maxActionValue);
                    startingPos.x = nextState.x;// this updates the startState to be the nextState, then we start over the process
                    startingPos.y = nextState.y;
                    maxActionValue = -10; //reset maxaction value
                }
                else if (randomMove == 2) {// left move
                    if(startingPos.y > 0){
                        nextState.x = startingPos.x;
                        nextState.y = startingPos.y - 1;
                    }
                    //this for loop steps through the four actions of the next state to find the maxActionValue
                    for (int i = 0; i < 4; i++) {
                        if(this->qTable[nextState.index()][i] > maxActionValue){
                            maxActionValue = this->qTable[nextState.index()][i];
                        }
                    }
                    this->qTable[startingPos.index()][2] = this->rewardSpace[startingPos.index()][2] + (discountFactor * maxActionValue);
                    startingPos.x = nextState.x;// this updates the startState to be the nextState, then we start over the process
                    startingPos.y = nextState.y;
                    maxActionValue = -10; //reset maxaction value
                }
                else if (randomMove == 3) {//right move
                    if(startingPos.y < 7){
                        nextState.x = startingPos.x;
                        nextState.y = startingPos.y + 1;
                    }
                    //this for loop steps through the four actions of the next state to find the maxActionValue
                    for (int i = 0; i < 4; i++) {
                        if(this->qTable[nextState.index()][i] > maxActionValue){
                            maxActionValue = this->qTable[nextState.index()][i];
                        }
                    }
                    this->qTable[startingPos.index()][3] = this->rewardSpace[startingPos.index()][3] + (discountFactor * maxActionValue);
                    startingPos.x = nextState.x;// this updates the startState to be the nextState, then we start over the process
                    startingPos.y = nextState.y;
                    maxActionValue = -10; //reset maxaction value
                }
                else{
                    std::cout << "broke it..." << std::endl;
                }

                validMoveToTake = false;//reset the in move validifier so that it tries to find another random move other than just going one direction

        }

        //cout << "reached a valid terminal state, ready for loop" << endl;
        validStartState = false;
        episodes--;
    }

}

void qLearner::printQTable(){

    for(int i = 0; i < 64; i++){
        cout << "State: " << i << endl;
        cout << "   up move score: " << this->qTable[i][0] << endl;
        cout << "   down move score: " << this->qTable[i][1] << endl;
        cout << "   left move score: " << this->qTable[i][2] << endl;
        cout << "   right move score: " << this->qTable[i][3] << endl;
        cout << endl;
        cout << "**************************"<< endl;
        cout << endl;
        cout << endl;

    }


}

void qLearner::printRewardSpace(){

    for(int i = 0; i < 64; i++){
        cout << "State: " << i << endl;
        cout << "   up reward: " << this->rewardSpace[i][0] << endl;
        cout << "   down reward: " << this->rewardSpace[i][1] << endl;
        cout << "   left reward: " << this->rewardSpace[i][2] << endl;
        cout << "   right reward: " << this->rewardSpace[i][3] << endl;
        cout << endl;
        cout << "**************************"<< endl;
        cout << endl;
        cout << endl;

    }


}
position keyPress(char key, Maze board){
    position move;

    if (key == 'w') {// up
        move.x = board.findPosOfPlayer().x - 1;
        move.y = board.findPosOfPlayer().y;

    }
    else if (key == 's') {// down
        move.x = board.findPosOfPlayer().x + 1;
        move.y = board.findPosOfPlayer().y;

    }
    else if (key == 'a') { // left
        move.x = board.findPosOfPlayer().x;
        move.y = board.findPosOfPlayer().y-1;

    }
    else if (key == 'd') {// right
        move.x = board.findPosOfPlayer().x;
        move.y = board.findPosOfPlayer().y+1;

    }
    else{//means invalid keypress
        move.x = -1;
        move.y = -1;
    }
    return move;
}





int main(int argc, const char * argv[]) {

//    while(foundExit()){
//        printMaze();
//
//    }
    Maze board;
    position move;
    qLearner solveMaze;
    
    //this will use 10 trials to train the age and then print the results
    solveMaze.qLearn(board, 10, 0.5);
    solveMaze.printRewardSpace();
    solveMaze.printQTable();
    //this will use 100 trials to train the age and then print the results
    solveMaze.qLearn(board, 100, 0.8);
    solveMaze.printRewardSpace();
    solveMaze.printQTable();
    //this will use 1000 trials to train the age and then print the results
    solveMaze.qLearn(board, 1000, 0.1);
    solveMaze.printRewardSpace();
    solveMaze.printQTable();
    //this will use 100,000,000 trials to train the age and then print the results
    solveMaze.qLearn(board, 100000000, 0.1);
    solveMaze.printRewardSpace();
    solveMaze.printQTable();



//    char i = 'w';
//    int stupidAI = 0;
//    board.printMaze();
//    int timeSteps = 0;
//    int totalTimeSteps = 0;
//    int runs = 0;
//    while(runs < 100){
//    while (!board.foundExit()) {
//
//        if (board.scoreSpace) {
//            <#statements#>
//        }
//        //random move AI
//        stupidAI = rand() % 4;
//        if(stupidAI == 0){
//            i = 'w';
//        }
//        else if(stupidAI == 1){
//            i = 'a';
//        }
//        else if(stupidAI == 2){
//            i = 's';
//        }
//        else if(stupidAI == 3){
//            i = 'd';
//        }
//        move = keyPress(i, board);


//        cout << "Use WASD to move your agent";
//        cin >> i;
//        cout << "The value you entered is " << i;
//        move = keyPress(i, board);
//        while(move.x == -1){
//            cout << "USE WASD JERK";
//            cin >> i;
//            move = keyPress(i, board);
//
//        };



//        board.makeMove(move);
//        board.printMaze();
//        timeSteps++;
//    }//end inner while
//        runs++;
//        totalTimeSteps += timeSteps;
//}



    std::cout << "YOU WON CONGRATS" << endl;
        //std::cout << "It only took you on average:"<< totalTimeSteps/runs << "key presses" << endl;
    return 0;
}

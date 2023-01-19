#include<string>
#include<vector>
#include<iostream>
#include<cmath>
#include<stdlib.h>  /* to use exit */
using namespace std;


class state{
  public:
    string items;  // made up of 1, 2, and 3 going from 111 to 333
    string camefrom; // the parent o the solution path
    int g;   // cost so far
    double h;   // estimated cost to the goal
    double f;   // g+h
};

// Major data structures:
vector<state> frontier;  // Frontier nodes - will pick one of these to expand
vector<state> beenThere; // already expanded nodes

bool complete = false;

// ========== Utility Functions ===================
// utility to add x to the beenthere
void addtoBeenThere(state x){beenThere.push_back(x);}


// utility to add x to the frontier
void addtoFrontier(state x){frontier.push_back(x);}


// to remove state x from the frontier when it has been expanded
void removefromFrontier(state x){  
  vector<state> newfrontier;
  for (int k = 0; k < frontier.size(); k++)
    if (frontier[k].items != x.items)
      newfrontier.push_back(frontier[k]);

  frontier = newfrontier;
}


//Determines if the state has been visited before.
bool visited(state next){
  bool found = false;
  for(state s: beenThere){
    if(next.items == s.items){
      found = true;
      break;
    }
  }
  return found;
}


//Determines if the state is unsafe or not
bool unsafe(string current, string next){
    bool unsafe = false;

      if(current[1] != next[1]){//medium disk moved
          if(current[0] == next[1]){
              unsafe = true;
          }
      }

      if(current[2] != next[2]){//large disk moved
          if(current[0] == next[2]){
              unsafe = true;
          }

          if(current[1] == next[2]){
              unsafe = true;
          }
      }

  return unsafe;
}

//This function displays a nicer looking output for showing where each item is relative to the river.
void visualizeState(const string state){
  string peg1 = "";
  string peg2 = "";
  string peg3 = "";
  char item = ' ';



  //This determines the item by the position in items.
  for(int i = 0; i < state.size(); i++){
    switch(i){
      case 0:
        item = 'S';
        break;
      case 1:
        item = 'M';
        break;
      case 2:
        item = 'L';
        break;
      default:
        cout<<"VisualizeState Went past number of existing items.";
        break;  
    }

    //Place the item on the correct side of the river.
    if(state[i] == '1'){
        peg1.push_back(item);
    }
    else if (state[i] == '2'){
        peg2.push_back(item);
    }
    else{
        peg3.push_back(item);
    }
  }

  if(peg1 == ""){
      peg1 = "0";
  }

  if(peg2 == ""){
      peg2 = "0";
  }

    if(peg3 == ""){
      peg3 = "0";
    }
  //Display the visualization of the scene
 cout<<"["+peg1+","+peg2+","+peg3+"]";
}


//This function displays a nicer looking output for showing where each item is relative to the river.
void visualizeIllegalState(const string oldState, const string newState){
    string peg1 = "";
    string peg2 = "";
    string peg3 = "";
    char item = ' ';
    bool smallDiskMoved = false;
    bool mediumDiskMoved = false;
    bool largeDiskMoved = false;

    if(oldState[0] != newState[0]){smallDiskMoved = true;}
    if(oldState[1] != newState[1]){mediumDiskMoved = true;}
    if(oldState[2] != newState[2]){largeDiskMoved = true;}



    //This determines the item by the position in items.
    for(int i = 0; i < oldState.size(); i++){
        switch(i){
            case 0:
                if(smallDiskMoved){continue;}
                item = 'S';
                break;
            case 1:
                if(mediumDiskMoved){continue;}
                item = 'M';
                break;
            case 2:
                if(largeDiskMoved){continue;}
                item = 'L';
                break;
            default:
                cout<<"VisualizeState Went past number of existing items.";
                break;
        }

        //Place the item on the correct side of the river.
        if(oldState[i] == '1'){
            peg1.push_back(item);
        }
        else if (oldState[i] == '2'){
            peg2.push_back(item);
        }
        else{
            peg3.push_back(item);
        }
    }

    if(peg1 == ""){peg1 = "0";}
    if(peg2 == ""){peg2 = "0";}
    if(peg3 == ""){peg3 = "0";}

    if(smallDiskMoved){
        if(newState[0] == '1'){peg1.insert(0, "S");}
        else if(newState[0] == '2'){peg2.insert(0, "S");}
        else if(newState[0] == '3'){peg3.insert(0, "S");}
    }
    else if(mediumDiskMoved){
        if(newState[1] == '1'){peg1.insert(0, "M");}
        else if(newState[1] == '2'){peg2.insert(0, "M");}
        else if(newState[1] == '3'){peg3.insert(0, "M");}
    }
    else if(largeDiskMoved){
        if(newState[2] == '1'){peg1.insert(0, "L");}
        else if(newState[2] == '2'){peg2.insert(0, "L");}
        else if(newState[2] == '3'){peg3.insert(0, "L");}
    }
    //Display the visualization of the scene
    cout<<"["+peg1+","+peg2+","+peg3+"]";
}


//Gets the score for the disk on peg 3.
double getPeg3Score(int disk){
    double score = 0.0;
    switch (disk) {
        case 0:
            score = .5;
            break;
        case 1:
            score = .25;
            break;
        case 2:
            score = .125;
            break;
    }
    return score;
}


//============= At the Very End ====================
void tracePath(state goal){
  if(goal.items != "111"){
    cout<<"Path Node: {";
    cout << "{ State: ";
    visualizeState(goal.items);
    cout<<", ";

    cout<<"Came-From: ";  
    visualizeState(goal.camefrom);
    cout<<", ";

    cout << "g: " <<goal.g << " ";
    cout << "h: " <<goal.h << " ";
    cout << "f: " <<goal.f << " }\n"; 

    state parentState;
    for(state s: beenThere){
        if(s.items == goal.camefrom){
            parentState = s;
            break;
        }
    }
      tracePath(parentState);
  }
  else{
      //This will display the starting state info and unravel the recursion.
      cout<<"Path Node: {";
      cout << "{ State: ";
      visualizeState(goal.items);
      cout<<", ";

      cout<<"Came-From: ";
      visualizeState(goal.camefrom);
      cout<<", ";

      cout << "g: " <<goal.g << " ";
      cout << "h: " <<goal.h << " ";
      cout << "f: " <<goal.f << " }\n";
      return;
  }
  
}// end of tracePath  


//======= For Generating a new state to add to Frontier  =============
bool inFrontier(state next){
  
  bool found = false;
  // state foundState;
  for(int i = 0; i < frontier.size(); i++){
    if(frontier[i].items == next.items){//We found an state that is in the frontier
      found = true;

      if(next.f < frontier[i].f){//Update the state in the frontier with the higher f value.
        cout<<"Found a better F value.";
        frontier[i] = next;
      }

      break;
    }
  }
  return found;
}// end of inFrontier


// Try to add next to frontier but stop if LLLL (called from generateAll)
void generate(string current, state next){
    if(unsafe(current, next.items)){
        cout << "Trying to add: ";
        visualizeIllegalState(current, next.items);
        cout<<" ... State is illegal.\n";
        return;
    }else{
        cout << "Trying to add: ";
        visualizeState(next.items);
    }

    
    if(visited(next)){
        cout<<" ... Already been here.\n";
        return;
    }

    if (next.items  == "333"){// the goal is reached
        cout << ">>Reached: " << next.items << endl;
        tracePath(next);  // display the solution path
        exit(0);
    }//done



  // else compute h and then f for next
  int sumPeg2 = 3;
  double productPeg3 = 0.0;
  double h = 0;// start point for h; g is already set

  // ** update h and then f
  for(int i = 0; i < next.items.size(); i++){
    if(next.items[i] == '2'){
        sumPeg2--;
    }else if(next.items[i] == '3'){
        if(productPeg3 == 0.0){ productPeg3 = getPeg3Score(i);}
        else{ productPeg3 *= getPeg3Score(i);}
    }
  }

  if(sumPeg2 == 0){ sumPeg2 = 1;}
  if(productPeg3 == 0.0){ productPeg3 = 1.0;}

  h = sumPeg2 * productPeg3;
  
  //updating the next states h value.
  next.h = h;

  //updating the next states f value.
  next.f = next.h + next.g;
  
  if (!inFrontier(next)){
      cout<<" ... Success.\n";
      addtoFrontier(next); // add next to Frontier
  }else{
      cout<<"...Already in Frontier.\n";
  }

}// end of generate   


// Generate all new states from current (called from main)
void generateAll(state current){
  state next;  // a generated one

  // each next will be modified from current for ease
  current.g = current.g + 1; // to update g to be used for next
  // storing the parent so that we can produce the solution path
  current.camefrom = current.items;

  //Check to see what peg the small is on
  next=current;
  if(current.items[0] == '1'){//If small disk is on peg 1
    next.items[0] = '2';//move small disk to peg 2
    generate(current.items, next);

    next=current;

    next.items[0] = '3';//move small disk to peg 3
    generate(current.items, next);
  }

  next=current;
  if(current.items[0] == '2'){//If small disk is on peg 2
      next.items[0] = '1';//move small disk to peg 1
      generate(current.items, next);

      next=current;

      next.items[0] = '3';//move small disk to peg 3
      generate(current.items, next);
  }

  next=current;
  if(current.items[0] == '3'){//If small disk is on peg 3
      next.items[0] = '1';//move small disk to peg 1
      generate(current.items, next);

      next=current;

      next.items[0] = '2';//move small disk to peg 2
      generate(current.items, next);
  }

  //Check to see which peg the medium disk is on.
    next=current;
    if(current.items[1] == '1' && current.items[0] != '1'){//If medium disk is on peg 1 & small disk isn't on peg 1.
        next.items[1] = '2';//move medium disk to peg 2
        generate(current.items, next);

        next=current;

        next.items[1] = '3';//move medium disk to peg 3
        generate(current.items, next);
    }

    next=current;
    if(current.items[1] == '2' && current.items[0] != '2'){//If medium disk is on peg 2 & small disk isn't on peg 2.
        next.items[1] = '1';//move medium disk to peg 1
        generate(current.items, next);

        next=current;

        next.items[1] = '3';//move medium disk to peg 3
        generate(current.items, next);
    }

    next=current;
    if(current.items[1] == '3' && current.items[0] != '3'){//If medium disk is on peg 3 & small disk isn't on peg 3.
        next.items[1] = '1';//move medium disk to peg 1
        generate(current.items, next);

        next=current;

        next.items[1] = '2';//move medium disk to peg 2
        generate(current.items, next);
    }


    //Check to see which peg the large disk is on.
    next=current;
    if(current.items[2] == '1' && current.items[0] != '1' && current.items[1] != '1'){//If large disk is on peg 1 & small disk & medium disk isn't on peg 1.
        next.items[2] = '2';//move large disk to peg 2
        generate(current.items, next);

        next=current;

        next.items[2] = '3';//move large disk to peg 3
        generate(current.items, next);
    }

    next=current;
    if(current.items[2] == '2' && current.items[0] != '2' && current.items[1] != '2'){//If large disk is on peg 2 & small disk & medium disk isn't on peg 2.
        next.items[2] = '1';//move large disk to peg 1
        generate(current.items, next);

        next=current;

        next.items[2] = '3';//move large disk to peg 3
        generate(current.items, next);
    }

    next=current;
    if(current.items[2] == '3' && current.items[0] != '3' && current.items[1] != '3'){//If large disk is on peg 3 & small disk & medium disk isn't on peg 3.
        next.items[2] = '1';//move large disk to peg 1
        generate(current.items, next);

        next=current;

        next.items[2] = '2';//move large disk to peg 2
        generate(current.items, next);
    }
}// end of generateAll


// Find the best f state out of the frontier and return it (called from main)
state bestofFrontier(){ 
  // **** add code here
  state bestChoice = frontier[0];
  for(state s: frontier){
    if(bestChoice.f > s.f){
      bestChoice = s;
    }
  }

  return bestChoice;
}//end of bestofFrontier


// Display the states in the frontier  (called from main)
void displayFrontier(){
  for (int k = 0; k < frontier.size(); k++){
    cout << "{ State: ";
    visualizeState(frontier[k].items);
    cout<<", ";

    cout<<"Came-From: ";  
    visualizeState(frontier[k].camefrom);
    cout<<", ";

    cout << "g: " <<frontier[k].g << " ";
    cout << "h: " <<frontier[k].h << " ";
    cout << "f: " <<frontier[k].f << " }\n"; 
  }
}// end of displayFrontier

//================= Main ===========================

int main(){

  state  current = {"111","", 0, 7, 7};  // initial
  addtoFrontier(current);
  //int run = 0;
  char ans;
  while ( ans != 'n'){
    //Transfer the chosen state from frontier to been there.
    removefromFrontier(current);
    addtoBeenThere(current);

    //Display the current state
    cout << ">>>Expand:" << current.items <<" or ";
    visualizeState(current.items);
    cout<<endl;

    //Find the available states to go to
    generateAll(current);  // new states are added to frontier

    //Available Frontier
    cout << "Frontier is:" << endl;
    displayFrontier();

    //The chosen path to find
    current = bestofFrontier(); // pick the best state out of frontier
    cout<<"Best F: { ";
    visualizeState(current.items);
    cout<<", Came-From: ";
    visualizeState(current.camefrom);
    cout<<", g: "<<current.g<<" h: "<<current.h<<" f: "<<current.f;
    cout<<" }\n";
    cin >> ans;


  }// end while

}//end of main


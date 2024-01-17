// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include "Pack.hpp"
#include "Card.hpp"
#include "Player.hpp"
using namespace std;

void print_failure_message ();

//game class where the game is run
//this is where the overall game is created
class Game {
private:
    vector<Player*> players;
    Pack pack;
    int team_1_points;
    int team_2_points;
    int team_1_tricks;
    int team_2_tricks;
    int points_to_win;
    int num_hands;
    int dealer;
    int player_on_offense;
    string shuffle;
    Card current_upcard;
    Suit current_trump;

public:
  Game (){};

  
  Game (const string &shuffle_cards, const int &points_to_win_in, 
  const vector<Player*> p){
    //Setting up everything for the game
    //players, card deck, etc
    players = p;
    team_1_points = 0;
    team_2_points = 0;
    num_hands = 0;
    dealer = 0;

    points_to_win = points_to_win_in;

    pack = Pack();
    pack.reset();

    shuffle = shuffle_cards;
    play();

    for (int i = 0; i < 4; i++){
      delete players[i];
    }
}



  void play () {
      int i = 0;

      //this is the loop that runs the game 
      //while a team still hasn't hit the points to win
      while (i < points_to_win){
        shuffle_cards();
        deal ();
        make_trump();
        play_hand();
        if (team_1_points > team_2_points){
          i = team_1_points;
        }
        else {
          i = team_2_points;
        }
        if (dealer == 3){
          dealer = 0;
        }
        else {
          dealer++;
        }
      }
    find_and_print_winner();
  }

  //shuffles the deck of cards
  void shuffle_cards() {
    pack.reset();
    if (shuffle == "shuffle"){
      pack.shuffle();
    }
    else {
      pack.reset();
    }
  }

    //deals cards to all four players based off the dealer
    void deal() {
        team_1_tricks = 0;
        team_2_tricks = 0;

        cout << "Hand " << num_hands << endl;
        num_hands++;
        cout << players[dealer]->get_name() << " deals" << endl;
        // first person (3)
        players[(dealer + 1) % 4]->add_card(pack.deal_one());
        players[(dealer + 1) % 4]->add_card(pack.deal_one());
        players[(dealer + 1) % 4]->add_card(pack.deal_one());
        
        // second person (2)
        players[(dealer + 2) % 4]->add_card(pack.deal_one());
        players[(dealer + 2) % 4]->add_card(pack.deal_one());
        
        // third person (3)
        players[(dealer + 3) % 4]->add_card(pack.deal_one());
        players[(dealer + 3) % 4]->add_card(pack.deal_one());
        players[(dealer + 3) % 4]->add_card(pack.deal_one());
        
        // dealer (2)
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        
        // first person (2)
        players[(dealer + 1) % 4]->add_card(pack.deal_one());
        players[(dealer + 1) % 4]->add_card(pack.deal_one());
        
        // second person (3)
        players[(dealer + 2) % 4]->add_card(pack.deal_one());
        players[(dealer + 2) % 4]->add_card(pack.deal_one());
        players[(dealer + 2) % 4]->add_card(pack.deal_one());
        
        // third person (2)
        players[(dealer + 3) % 4]->add_card(pack.deal_one());
        players[(dealer + 3) % 4]->add_card(pack.deal_one());

        // dealer (3)
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        players[dealer]->add_card(pack.deal_one());
        
        players[0]->get_name();
        players[1]->get_name();
        players[2]->get_name();
        players[3]->get_name();


    }

  //Loops until a player orders up a suit, picks a suit, or sticks the dealer
  //sets the current_trump
  void make_trump(){
    int round = 1;
    Card upcard = pack.deal_one();
    int i = dealer;
    int x = 0;
    bool is_dealer = false;
    Suit order_up_suit = upcard.get_suit();

    if (i == 3){
        i = 0;
    }
    else {
      i++;
    }
    cout << upcard << " turned up" << endl;


    //looping through all the players until trump is ordered up
    while (x < 8){
      if (i == dealer) {
        is_dealer = true;
      }

      if (players[i % 4]->make_trump(upcard, is_dealer, 
      round, order_up_suit) == true) {
          current_trump = order_up_suit;
          cout << *players[(i)] << " orders up " << current_trump<< endl;

          if (round == 1) {
            players[dealer]->add_and_discard(upcard);
          }
          player_on_offense = (i%4);

          x = 9;

      }
      else {
        cout << players[(i) % 4]->get_name() << " passes" << endl;

      }
      i++;
      x++;
      is_dealer = false;


      if (i > 3){
        i = 0;
      }
      if (x > 3){
        round = 2;
      }

    }
    cout << endl;
  
  }


  //Each player plays a single card until all cards have been played
  //and a winner of the trick has been determined
  void play_hand(){
    int z = 0;

    int fake_dealer = dealer + 1;
    int temp_trick_winner;

    int p0_tricks = 0;
    int p1_tricks = 0;
    int p2_tricks = 0;
    int p3_tricks = 0;

    while (z < 5){

      //the players playing their cards
      Card lead_card = players[(fake_dealer) % 4]->lead_card(current_trump);
      cout << lead_card << " led by " << 
      players[(fake_dealer) % 4]->get_name() << endl;
      
      Card card_one = players[(fake_dealer + 1) % 4]->play_card(lead_card, current_trump);
      cout << card_one << " played by " << 
      players[(fake_dealer + 1)% 4]->get_name() << endl;

      Card card_two = players[(fake_dealer + 2) % 4]->play_card(lead_card, current_trump);
      cout << card_two << " played by " << 
      players[(fake_dealer + 2)% 4]->get_name() << endl;

      Card card_three = players[(fake_dealer + 3) % 4]
      ->play_card(lead_card, current_trump);
      cout << card_three << " played by " << 
      players[(fake_dealer + 3)% 4]->get_name() << endl;

      //checking to see who won
      temp_trick_winner = highest_card(lead_card, card_one, card_two, card_three);

      //printing out the winner
      cout << players[(fake_dealer + temp_trick_winner) % 4]
      ->get_name() << " takes the trick" << endl;

      int i = 0;
      while (players[(fake_dealer + temp_trick_winner) % 4]
      ->get_name() != players[i]->get_name()){
        i++;
      }

      //scoring
      if (i == 0){
        p0_tricks++;
        fake_dealer = 0;
      }
      if (i == 1){
        p1_tricks++;
        fake_dealer = 1;
      }
      if (i == 2){
        p2_tricks++;
        fake_dealer = 2;
      }
      if (i == 3){
        p3_tricks++;
        fake_dealer = 3;
      }
         
      cout << endl;
      z++;
    }
    //end of while loop

    //checking to see who took the hand
    trick_winner_calculator(p0_tricks, p1_tricks, p2_tricks, p3_tricks);

      
    }

  //checks to see which card will win the trick
  //returns the card that won the trick
  int highest_card  (const Card &lead_card, const Card &card_one, 
  const Card &card_two, const Card &card_three) {

        
        if (Card_less(lead_card, card_one, lead_card, current_trump) == false &&
            Card_less(lead_card, card_three, lead_card, current_trump) == false && 
            Card_less(lead_card, card_two, lead_card, current_trump) == false){
            //cout << lead_card << " takes the trick" << endl;
            //cout << players[0]->get_name() << " won the trick" << endl;
            return 0;
          }

        //checking if the second player won
        else if (Card_less(card_one, lead_card, lead_card, current_trump) == false &&
            Card_less(card_one, card_two, lead_card, current_trump) == false && 
            Card_less(card_one, card_three, card_one, current_trump) == false){
            //cout << players[1]->get_name() << " won the trick" << endl;
            return 1;
          }

        //checking if the third player won
        else if (Card_less(card_two, card_one, lead_card, current_trump) == false &&
            Card_less(card_two, card_three, lead_card, current_trump) == false &&
            Card_less(card_two, lead_card, card_two, current_trump) == false){
            //cout << players[2]->get_name() << " won the trick" << endl;
            return 2;
          }

        
        //checking if the fourth player won
        else if (Card_less(card_three, lead_card, lead_card, current_trump) == false &&
            Card_less(card_three, card_two, lead_card, current_trump) == false &&
            Card_less(card_three, card_one, card_three, current_trump) == false){
            //cout << players[3]->get_name() << " won the trick" << endl;
            return 3;
          }


      cout << " nothing matches" << endl;
      return 0;
  }

  //this takes the input of the number of tricks each player won, and outputs
  //which player won the hand.
  //it also increments the total score of the two teams
  void trick_winner_calculator (int &p0, int &p1, int &p2, int &p3) {
    if ((p0 + p2) > (p1 + p3)){
      cout << players[0]->get_name() << " and " <<
      players[2]->get_name() << " win the hand" << endl; 
      
      if (0 != player_on_offense && 2 != player_on_offense){
        cout << "euchred!" << endl;
        team_1_points = team_1_points + 2;
      }
      else if ((p0 + p2) == 5){
        cout << "march!" << endl;
        team_1_points = team_1_points + 2;
      }
      else {
        team_1_points = team_1_points + 1;
      }

    }
    else {
      cout << players[1]->get_name() << " and " <<
      players[3]->get_name() << " win the hand" << endl; 
      
      if (1 != player_on_offense && 3 != player_on_offense){
        cout << "euchred!" << endl;
        team_2_points = team_2_points + 2;
      }
      else if ((p1 + p3) == 5){
        cout << "march!" << endl;
        team_2_points = team_2_points + 2;
      }
      else {
        team_2_points = team_2_points + 1;
      }
    }

    // printing out the total points for team 1
    cout << players[0]->get_name() << " and " <<
    players[2]->get_name() << " have " << 
    team_1_points << " points" << endl;

    //printing out the total points for team 2
    cout << players[1]->get_name() << " and " <<
    players[3]->get_name() << " have " << 
    team_2_points << " points" << endl;

    cout << endl;
  }

  //this prints out the winner of the game
  void find_and_print_winner (){
    if (team_1_points > team_2_points){
      cout << players[0]->get_name() << " and " <<
      players[2]->get_name() << " win!" << endl;
    }
    else {
      cout << players[1]->get_name() << " and " <<
      players[3]->get_name() << " win!" << endl;      
    }
  }
  
    
};

int main(int argc, char *argv[]) {
  //cout << "Hello World!\n";

  if (!(argc == 12 )){
    print_failure_message();
    return -1;
  }

  string filename = argv[1], shuffle = argv[2];
  int points_to_win = atoi(argv[3]);
  
  ifstream f_input(filename);

  vector<Player*> players;

  string type0 = argv[5], type1 = argv[7],type2 = argv[9], type3 = argv[11];

  if ((type0 == "Simple" || type0 == "Human") &&
    (type1 == "Simple" || type1 == "Human") &&
    (type2 == "Simple" || type2 == "Human") &&
    (type3 == "Simple" || type3 == "Human")) {}
  else {
    print_failure_message();
    return -1;
  }


  //checking to make sure everything is formatted correctly
  if (points_to_win < 1 || points_to_win > 100 ){
    print_failure_message();
    return -1;
  } else if (shuffle != "shuffle" || shuffle != "noshuffle"){}
  else {
    print_failure_message();
    return -1;}




  if (!f_input.is_open()){
  cout << "Error opening " << filename << endl;
    return -1;}

  for (int z = 0; z < 12; z++){
    cout << argv[z] << " ";
  }
  cout << endl;

  players.push_back(Player_factory(argv[4], argv[5]));
  players.push_back(Player_factory(argv[6], argv[7]));
  players.push_back(Player_factory(argv[8], argv[9]));
  players.push_back(Player_factory(argv[10], argv[11]));


  Game game (shuffle, points_to_win, players);

  f_input.close();
}

//couts the failure message
void print_failure_message (){
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
  << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
  << "NAME4 TYPE4" << endl;
}
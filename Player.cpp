#include "Player.hpp"
#include "Card.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Simple : public Player {
private:
    string name;
    vector<Card> hand;


    
public:

    Simple (){}

    Simple(const string& name_input) {
        name = name_input;
    }



    //EFFECTS returns player's name
    const string & get_name() const override {
        return name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);

    sort(hand.begin(), hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
bool make_trump(const Card &upcard, bool is_dealer,
      int round, Suit &order_up_suit) const override {
    assert(round == 1 || round == 2);
        
    if(round == 1) {
        Card fake_card(string_to_rank("Ten"), upcard.get_suit());    
        int count = 0;

        for(int i = 0; i < hand.size(); i++) {
            if(Card_less(fake_card, hand[i], fake_card.get_suit()) == true) {
                count++;
            }

        }
            
        if(count >= 2) {
            order_up_suit = upcard.get_suit();
            return true;
        }
        else {
            return false;
        }
    }
    if(round == 2) {
        Card fake_card(string_to_rank("Ten"), Suit_next(upcard.get_suit()));
            
        int count = 0;
        for(int i = 0; i < hand.size(); i++) {
             if(Card_less(fake_card, hand[i], fake_card.get_suit())) {
                count++;
                    
            }
        }
        if(count >= 1 || is_dealer) {
            order_up_suit = fake_card.get_suit();
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  //virtual void add_and_discard(const Card &upcard){
  void add_and_discard(const Card &upcard) override{

    Suit current_trump = upcard.get_suit();

    hand.push_back(upcard);
    sort(hand.begin(), hand.end());


    int i = 0;
    int x = 0;
    Card current_card;
    Card smallest_card;

    
    while (i < hand.size()){
         current_card = hand[i];
         smallest_card = hand[x];
         if (Card_less(current_card, smallest_card, current_trump) == true){
            x = i;
         }

        i++;
    }

    hand.erase(hand.begin()+x);




    sort(hand.begin(), hand.end());
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  //virtual Card lead_card(Suit trump){
  Card lead_card(Suit trump) override{

    Card temp_card;
    int tr = 0;
    int i = 0;
    int x = 0;



    if (hand.size() == 1){
        temp_card = hand[0];
        hand.erase(hand.begin()+x);
        return temp_card;
    }

    while (i < hand.size()){
        if (hand[i].get_suit(trump) == trump){
            tr = tr + 1;
        }
        i++;
    }

    i = 0;
    int t = 0;



    if (tr == hand.size()){
        temp_card = hand[0];
        i++;
        while (i < hand.size()){
            if (Card_less(temp_card, hand[i], trump) == true){
                temp_card = hand[i];
                x = i;
            }
            i++;
        }
    }
    else {
        i = 0;
        t = 0;
        while (i < hand.size()){
            if (t == 0 && hand[i].get_suit(trump) != trump){
                temp_card = hand[i];
                t++;
                x = i;
            }
            else if (hand[i].get_suit(trump) != trump
            && Card_less(temp_card, hand[i], trump) == true){
                   temp_card = hand[i];
                x = i;
                          
            }
            i++;
        }
    }


    hand.erase(hand.begin()+x);
    return temp_card;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  //virtual Card play_card(const Card &led_card, Suit trump){
  Card play_card(const Card &led_card, Suit trump) override{

    Card temp_card;
    int i = 0;
    int x = 0;
    int suit_in_hand = 0;
    // int trump_in_hand = 0;
    int first_loop = 0;
    Suit current_suit = led_card.get_suit(trump);

    while (i < hand.size()){
        if (hand[i].get_suit(trump) == trump){
            // trump_in_hand++;
            continue;
        }
        if (hand[i].get_suit(trump) == current_suit){
            suit_in_hand++;
        }
        i++;
    }


    i = 0;
    if (suit_in_hand > 0){
        while (i < hand.size()){
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)
            && first_loop == 0){
                temp_card = hand[i];
                x = i;
                first_loop++;
            }
            else if (hand[i].get_suit(trump) == led_card.get_suit(trump)
            && Card_less(temp_card, hand[i], trump) == true){
                temp_card = hand[i];
                x = i;
            }
        i++;
        }
    }
    
    else {
        temp_card = hand[0];
        while (i < hand.size()){
            if (Card_less(hand[i], temp_card, trump) == true){
                temp_card = hand[i];
                x = i;
            }
            i++;
        }
    }


    hand.erase(hand.begin()+x);
    return temp_card;
    }
  

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  // Needed to avoid some compiler errors
  //virtual ~Player() {}
};




//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
//everything below this is the human player


class Human : public Player {
private:
    string name;
    vector<Card> hand;

    void print_hand()const{
        vector<Card> temp_hand;
        temp_hand = hand;

        sort(temp_hand.begin(), temp_hand.end());

        for (size_t i = 0; i < hand.size(); ++i){
            cout << "Human player " << name << "'s hand: "
                << "[" << i << "] " << temp_hand[i] << "\n";
        }

    }
    
public:

Human (){}

Human(const string & name_input){
    name = name_input;
}

    //EFFECTS returns player's name
    const string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);

    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override {
        assert(round == 1 || round == 2);
        
        if(round == 1) {
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
            
            string decision;
            cin >> decision;

            if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;
            }
            else {
                return false;
            }


        }
        if(round == 2) {

        if (is_dealer == true){
            print_hand();
            cout << "Human player " << name << ", please enter a suit.\n";
            
            string decision;
            cin >> decision;
            order_up_suit = string_to_suit(decision);   
        }
        
        else {
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
            
            string decision;
            cin >> decision;

            if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;
            }
            else {
                return false;
            }


        }
            
        }
        return false;
    }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  //virtual void add_and_discard(const Card &upcard){
  void add_and_discard(const Card &upcard) override{

    int x;
    
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    cin >> x;

        sort(hand.begin(), hand.end());


    if (x == -1){

    }
    else {
        hand.erase(hand.begin()+x);
        add_card(upcard);
        sort(hand.begin(), hand.end());
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  //virtual Card lead_card(Suit trump){
  Card lead_card(Suit trump) override{
    Card temp_card;
    int x;

    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    cin >> x;

    sort(hand.begin(), hand.end());

    temp_card = hand[x];

    hand.erase(hand.begin()+x);


    return temp_card;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  //virtual Card play_card(const Card &led_card, Suit trump){
  Card play_card(const Card &led_card, Suit trump) override{

    Card temp_card;
    int x;


    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    cin >> x;
    sort(hand.begin(), hand.end());
    
    temp_card = hand[x];
    
    hand.erase(hand.begin()+x);

    return temp_card;
  }



  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  // Needed to avoid some compiler errors
  //virtual ~Player() {}

};



//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){

    if (strategy == "Simple"){
        return new Simple(name);
    }
    else {
        return new Human(name);
    }
    assert(false);
    
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}


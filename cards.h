struct Card
{
    int suit;
    int value;
    int score;
};

struct Deck
{
    int total_cards;
    int top_of_deck;
    struct Card *cards[40];
};

typedef struct Deck Deck; 
typedef struct Card Card;

char SUIT[4] = {'H','C','S','D'};
char VALUE[10] = {'2','4','5','6','7','J','Q','K','3','A'};
int POINTS[10] = {0,0,0,0,0,2,3,4,10,11};

void display_card(Card *card);
void display_deck(Deck *deck);
void shuffle_deck(Deck *deck, int inclusive_start, int inclusive_end);
Card *take_top_card(Deck *deck);
Deck *create_deck();


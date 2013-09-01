#ifndef H_CARDS
#define H_CARDS
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

void display_card(Card *card);
void display_deck(Deck *deck);
void shuffle_deck(Deck *deck, int inclusive_start, int inclusive_end);
Card *take_top_card(Deck *deck);
Deck *create_deck();
#endif

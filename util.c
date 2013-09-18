#include "util.h"

int random_range(int min, int max)
{
    int r;
    max = max+1;
    const int range = max - min;
    const int buckets = RAND_MAX / range;
    const int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);

}

void shuffle_deck(Card *cards, int inclusive_start, int inclusive_end)
{
    int newLocation;
    Card *tmp;
    for (int i = inclusive_start; i <= inclusive_end; i++)
    {
        newLocation = random_range(i,inclusive_end);
        tmp = cards[i];
        cards[i] = cards[newLocation];
        cards[newLocation] = tmp;
    }
}



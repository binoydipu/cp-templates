// Returns true if the first player wins
bool nim_game(const vector<int>& piles, bool misere = false) {
    int xorsum = 0, ones = 0;
    for (int pile : piles) {
        xorsum ^= pile;
        ones += (pile == 1);
    }
    if(!misere) return xorsum != 0;

    // Misere Nim: if last player to pick stone loses the game
    bool all_ones = (ones == (int)piles.size());
    return all_ones ? (ones % 2 == 0) : (xorsum != 0);
}
void menuSwitch(int switcher);

void menu();

// This method returns the users chosen "rule number" as an int
int rule();

// This method returns a pointer to an array that contains the binary equivilant of the decimal rule the user choose.
bool * decToBinary(int choice);

void celAut(bool *pRule, bool *pUserGen, int size, int gens);

void celAutConfig(bool *pRule);

void gameOfLife(char initialSeed[15][15]);

void lifeConfig();

void decToBinaryNoR();

int binaryToDecimal();
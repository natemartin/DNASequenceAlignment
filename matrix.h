typedef struct
{
    int values[24][24];
} ScoringMatrix;

int indexForBase(char a);
ScoringMatrix getMatrixFromFile(char* filename);

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

int indexForBase(char a) {
  switch (a) {
    case 'a':
    case 'A':
      return 0;
    case 'r':
    case 'R':
      return 1;
    case 'n':
    case 'N':
      return 2;
    case 'd':
    case 'D':
      return 3;
    case 'c':
    case 'C':
      return 4;
    case 'q':
    case 'Q':
      return 5;
    case 'e':
    case 'E':
      return 6;
    case 'g':
    case 'G':
      return 7;
    case 'h':
    case 'H':
      return 8;
    case 'i':
    case 'I':
      return 9;
    case 'l':
    case 'L':
    case 'o':
    case 'O':
    case 'j':
    case 'J':
      return 10;
    case 'k':
    case 'K':
      return 11;
    case 'm':
    case 'M':
      return 12;
    case 'f':
    case 'F':
      return 13;
    case 'p':
    case 'P':
      return 14;
    case 's':
    case 'S':
      return 15;
    case 't':
    case 'T':
      return 16;
    case 'w':
    case 'W':
      return 17;
    case 'y':
    case 'Y':
      return 18;
    case 'v':
    case 'V':
      return 19;
    case 'b':
    case 'B':
      return 20;
    case 'z':
    case 'Z':
      return 21;
    case 'x':
    case 'X':
      return 22;
    default:
      return 23;
  }
}

ScoringMatrix getMatrixFromFile(char* filename) {
  FILE* inputFile = fopen(filename, "r");
  if (inputFile) {
    ScoringMatrix matrix;

    char line[BUFFER_SIZE];
    char ch;
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x,
        y;
    int currentLine = 0;
    while (fgets(line, sizeof(line), inputFile)) {
      if (sscanf(line,
                 "%c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
                 "%d %d %d %d %d",
                 &ch, &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n,
                 &o, &p, &q, &r, &s, &t, &u, &v, &w, &x) == 25) {
        matrix.values[currentLine][0] = a;
        matrix.values[currentLine][1] = b;
        matrix.values[currentLine][2] = c;
        matrix.values[currentLine][3] = d;
        matrix.values[currentLine][4] = e;
        matrix.values[currentLine][5] = f;
        matrix.values[currentLine][6] = g;
        matrix.values[currentLine][7] = h;
        matrix.values[currentLine][8] = i;
        matrix.values[currentLine][9] = j;
        matrix.values[currentLine][10] = k;
        matrix.values[currentLine][11] = l;
        matrix.values[currentLine][12] = m;
        matrix.values[currentLine][13] = n;
        matrix.values[currentLine][14] = o;
        matrix.values[currentLine][15] = p;
        matrix.values[currentLine][16] = q;
        matrix.values[currentLine][17] = r;
        matrix.values[currentLine][18] = s;
        matrix.values[currentLine][19] = t;
        matrix.values[currentLine][20] = u;
        matrix.values[currentLine][21] = v;
        matrix.values[currentLine][22] = w;
        matrix.values[currentLine][23] = x;

        currentLine++;
        continue;
      }
    }
    if (currentLine != 24) {
      printf("Error loading scoring matrix\n");
      exit(-1);
    }
    return matrix;
  } else {
    perror(filename);
    exit(-1);
  }
}

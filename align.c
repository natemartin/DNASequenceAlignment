#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

int score(char i, char j, ScoringMatrix* matrix) {
  return matrix->values[indexForBase(i)][indexForBase(j)];
}

float max2(float a, float b) {
  if (a > b) return a;
  return b;
}

float max3(float a, float b, float c) { return max2(a, max2(b, c)); }

void reverse(char s[]) {
  int c, i, j;
  int len = strlen(s) - 1;
  for (i = 0, j = len; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void printMatrix(float** matrix, int s1len, int s2len) {
  int i, j;
  for (i = 0; i < s1len + 1; i++) {
    for (j = 0; j < s2len + 1; j++) {
      printf("%f ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

float sequence(char* s1, char* s2, float gapOpen, float gapExtend,
               float zeroShift, ScoringMatrix* matrix) {
  // Setup
  float maximalScore;
  int s1len = strlen(s1);
  int s2len = strlen(s2);
  float** V;
  float** G;
  float** E;
  float** F;
  V = (float**)malloc((s1len + 1) * sizeof(float*));
  G = (float**)malloc((s1len + 1) * sizeof(float*));
  E = (float**)malloc((s1len + 1) * sizeof(float*));
  F = (float**)malloc((s1len + 1) * sizeof(float*));
  int i, j;
  for (i = 0; i < strlen(s1) + 1; i++) {
    V[i] = (float*)malloc((s2len + 1) * sizeof(float));
    G[i] = (float*)malloc((s2len + 1) * sizeof(float));
    E[i] = (float*)malloc((s2len + 1) * sizeof(float));
    F[i] = (float*)malloc((s2len + 1) * sizeof(float));
  }
  for (i = 0; i < s1len + 1; i++)
    for (j = 0; j < s2len + 1; j++)
      V[i][j] = G[i][j] = E[i][j] = F[i][j] = -100000;

  for (i = 0; i < s1len + 1; i++)
    V[i][0] = E[i][0] = -1 * (gapOpen + i * gapExtend);
  for (i = 0; i < s2len + 1; i++)
    V[0][i] = F[0][i] = -1 * (gapOpen + i * gapExtend);
  V[0][0] = 0;
  // DP
  for (i = 1; i < s1len + 1; i++) {
    for (j = 1; j < s2len + 1; j++) {
      G[i][j] =
          V[i - 1][j - 1] + score(s1[i - 1], s2[j - 1], matrix) + zeroShift;
      E[i][j] = max2(E[i][j - 1], V[i][j - 1] - gapOpen) - gapExtend;
      F[i][j] = max2(F[i - 1][j], V[i - 1][j] - gapOpen) - gapExtend;
      V[i][j] = max3(G[i][j], F[i][j], E[i][j]);
    }
  }
  printf("Maximum Alignment Score: %f\n", V[--i][--j]);
  maximalScore = V[i][j];
  // Traceback
  char* alignment1 = (char*)malloc(i + j);
  char* alignment2 = (char*)malloc(i + j);
  int pos1 = 0;
  int pos2 = 0;
  while (i > 0 && j > 0) {
    if (V[i][j] == G[i][j]) {
      alignment1[pos1++] = s1[--i];
      alignment2[pos2++] = s2[--j];
    } else if (V[i][j] == E[i][j]) {
      alignment1[pos1++] = '.';
      alignment2[pos2++] = s2[--j];
      if (i == 0 || j == 0) break;
      while (E[i][j] == E[i][j + 1] + gapExtend) {
        alignment1[pos1++] = '.';
        alignment2[pos2++] = s2[--j];
        if (i == 0 || j == 0) break;
      }
    } else if (V[i][j] == F[i][j]) {
      alignment1[pos1++] = s1[--i];
      alignment2[pos2++] = '.';
      if (i == 0 || j == 0) break;
      while (F[i][j] == F[i + 1][j] + gapExtend) {
        alignment1[pos1++] = s1[--i];
        alignment2[pos2++] = '.';
        if (i == 0 || j == 0) break;
      }
    }
  }
  while (i > 0) {
    alignment1[pos1++] = s1[--i];
    alignment2[pos2++] = '.';
  }
  while (j > 0) {
    alignment1[pos1++] = '.';
    alignment2[pos2++] = s2[--j];
  }
  alignment1[pos1] = '\0';
  alignment2[pos2] = '\0';
  reverse(alignment1);
  reverse(alignment2);
  printf("%s\n%s\n", alignment1, alignment2);
  return maximalScore;
}

int main(int argc, char* argv[]) {
  if (argc < 7) {
    printf(
        "Use : AlignSequence <scoringmatrix> <sequence1> <sequence2> "
        "<gapOpenCost> <gapExtensionCost> <zeroShiftCost>\n");
    return -1;
  }
  // parse scoring matrix
  ScoringMatrix scorematrix = getMatrixFromFile(argv[1]);

  char* s1 = argv[2];
  char* s2 = argv[3];
  float zeroShift = atof(argv[6]);
  float gapOpen = atof(argv[4]);
  float gapExtent = atof(argv[5]);
  sequence(s1, s2, gapOpen, gapExtent, zeroShift, &scorematrix);
}

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/types.h>
#include <locale.h>

typedef enum mks_piece
{
  none=0x0,
  wEmpty=0x25A0, wKing=0x2654, wQueen=0x2655, wRook=0x2656, wBishop=0x2657, wKnight=0x2658, wPawn=0x2659,
  bEmpty=0x25A1, bKing=0x265A, bQueen=0x265B, bRook=0x265C, bBishop=0x265D, bKnight=0x265E, bPawn=0x265F,
} piece_t;

typedef enum mks_squarename
{
  a1=56, b1=57, c1=58, d1=59, e1=60, f1=61, g1=62, h1=63,
  a2=48, b2=49, c2=50, d2=51, e2=52, f2=53, g2=54, h2=55,
  a3=40, b3=41, c3=42, d3=43, e3=44, f3=45, g3=46, h3=47,
  a4=32, b4=33, c4=34, d4=35, e4=36, f4=37, g4=38, h4=39,
  a5=24, b5=25, c5=26, d5=27, e5=28, f5=29, g5=30, h5=31,
  a6=16, b6=17, c6=18, d6=19, e6=20, f6=61, g6=22, h6=23,
  a7= 8, b7= 9, c7=10, d7=11, e7=12, f7=13, g7=14, h7=15,
  a8= 0, b8= 1, c8= 2, d8= 3, e8= 4, f8= 5, g8= 6, h8= 7,
} squarename_t;

piece_t* initaliseBoard()
{
  piece_t* res = (piece_t*)malloc(64 * sizeof(piece_t));
  unsigned char i = 0;
  // piece_t emptyColor = bEmpty;
  res[a1] = wRook; res[b1] = wKnight; res[c1] = wBishop; res[d1] = wQueen; res[e1] = wKing; res[f1] = wBishop; res[g1] = wKnight; res[h1] = wRook;
  for (i = a2; i < a1; i++) res[i] = wPawn;
  for (i = a6; i < a2; i++)
  {
    // VIRGIN READABLE, STRAIGHT FORWARD CODE
    // res[i] = emptyColor;
    // if (((i+1)%8) && emptyColor == bEmpty) emptyColor = wEmpty;
    // else if (((i+1)%8) && emptyColor == wEmpty) emptyColor = bEmpty;
    // CHAD HIGH PERFORMANCE OBFUSCATED CODE
    res[i] = (0xAA55AA55AA55AA55 >> i) & 1 ? bEmpty : wEmpty;
  }
  for (i = a7; i < a6; i++) res[i] = bPawn;
  res[a8] = bRook; res[b8] = bKnight; res[c8] = bBishop; res[d8] = bQueen; res[e8] = bKing; res[f8] = bBishop; res[g8] = bKnight; res[h8] = bRook;

  return res;
}

int main()
{
  setlocale(LC_CTYPE, "");
  piece_t* board = initaliseBoard();
  wchar_t input[10];

  for (unsigned char i = 0; i < 64; i ++)
  {
    wprintf(L"%lc ", (wchar_t)board[i]);
    if (!((i+1)%8)) wprintf(L"\n");
  }

  wprintf(L"Gives us a move aye: ");
  wscanf(L"%ls", input);
  wprintf(L"you said: %ls\n", input);

  return 0;
}
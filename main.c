#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

typedef enum mks_piece
{
  none=0x0,
  wEmpty=0x25A0, wKing=0x2654, wQueen=0x2655, wRook=0x2656, wBishop=0x2657, wKnight=0x2658, wPawn=0x2659,
  bEmpty=0x25A1, bKing=0x265A, bQueen=0x265B, bRook=0x265C, bBishop=0x265D, bKnight=0x265E, bPawn=0x265F,
} piece_t;

typedef enum mks_squarename
{
  unknown=-1,
  a1=56, b1=57, c1=58, d1=59, e1=60, f1=61, g1=62, h1=63,
  a2=48, b2=49, c2=50, d2=51, e2=52, f2=53, g2=54, h2=55,
  a3=40, b3=41, c3=42, d3=43, e3=44, f3=45, g3=46, h3=47,
  a4=32, b4=33, c4=34, d4=35, e4=36, f4=37, g4=38, h4=39,
  a5=24, b5=25, c5=26, d5=27, e5=28, f5=29, g5=30, h5=31,
  a6=16, b6=17, c6=18, d6=19, e6=20, f6=61, g6=22, h6=23,
  a7= 8, b7= 9, c7=10, d7=11, e7=12, f7=13, g7=14, h7=15,
  a8= 0, b8= 1, c8= 2, d8= 3, e8= 4, f8= 5, g8= 6, h8= 7,
} squarename_t;

piece_t* mks_initaliseBoard()
{
  piece_t* res = (piece_t*)malloc(64 * sizeof(piece_t));
  size_t i = 0;
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

void mks_printBoard(piece_t* board)
{
  wprintf(L"8 ");
  for (size_t i = 0; i < 64; i ++)
  {
    wprintf(L"%lc ", (wchar_t)board[i]);
    if (!((i+1)%8)) wprintf(L"\n%d ", 7 - (i)/8);
  }
  wprintf(L"\33[2K\r  A B C D E F G H\n\n");
}

void mks_getMove(wchar_t* buffer, bool* whitesTurn, unsigned int* turn)
{
  if (*whitesTurn) wprintf(L"(Turn %u) White plays: ", *turn);
  else wprintf(L"(Turn %u) Black plays: ", *turn);
  wscanf(L"%ls", buffer);
}

squarename_t mapWcharToSquarename(wchar_t* buffer)
{
  // LOOK
  // I KNOW I SHOULD BE USING A MAP OR HASH TABLE HERE
  // IM NOT DUMB
  // I JUST DONT WANT TO USE EXTERNAL LIBRARIES
  // AND I DONT WANT TO IMPLEMENT MY OWN MAP RN
  // I WILL FIX THIS LATER, I PROMISE
  //
  // todo: Investigate why buffer: "ee\0" maps to b8 (1)
  if (!wcscmp(L"a1", buffer)) return a1;
  else if (!wcscmp(L"a2", buffer)) return a2;
  else if (!wcscmp(L"a3", buffer)) return a3;
  else if (!wcscmp(L"a4", buffer)) return a4;
  else if (!wcscmp(L"a5", buffer)) return a5;
  else if (!wcscmp(L"a6", buffer)) return a6;
  else if (!wcscmp(L"a7", buffer)) return a7;
  else if (!wcscmp(L"a8", buffer)) return a8;
  else if (!wcscmp(L"b1", buffer)) return b1;
  else if (!wcscmp(L"b2", buffer)) return b2;
  else if (!wcscmp(L"b3", buffer)) return b3;
  else if (!wcscmp(L"b4", buffer)) return b4;
  else if (!wcscmp(L"b5", buffer)) return b5;
  else if (!wcscmp(L"b6", buffer)) return b6;
  else if (!wcscmp(L"b7", buffer)) return b7;
  else if (!wcscmp(L"b8", buffer)) return b8;
  else if (!wcscmp(L"c1", buffer)) return c1;
  else if (!wcscmp(L"c2", buffer)) return c2;
  else if (!wcscmp(L"c3", buffer)) return c3;
  else if (!wcscmp(L"c4", buffer)) return c4;
  else if (!wcscmp(L"c5", buffer)) return c5;
  else if (!wcscmp(L"c6", buffer)) return c6;
  else if (!wcscmp(L"c7", buffer)) return c7;
  else if (!wcscmp(L"c8", buffer)) return c8;
  else if (!wcscmp(L"d1", buffer)) return d1;
  else if (!wcscmp(L"d2", buffer)) return d2;
  else if (!wcscmp(L"d3", buffer)) return d3;
  else if (!wcscmp(L"d4", buffer)) return d4;
  else if (!wcscmp(L"d5", buffer)) return d5;
  else if (!wcscmp(L"d6", buffer)) return d6;
  else if (!wcscmp(L"d7", buffer)) return d7;
  else if (!wcscmp(L"d8", buffer)) return d8;
  else if (!wcscmp(L"e1", buffer)) return e1;
  else if (!wcscmp(L"e2", buffer)) return e2;
  else if (!wcscmp(L"e3", buffer)) return e3;
  else if (!wcscmp(L"e4", buffer)) return e4;
  else if (!wcscmp(L"e5", buffer)) return e5;
  else if (!wcscmp(L"e6", buffer)) return e6;
  else if (!wcscmp(L"e7", buffer)) return e7;
  else if (!wcscmp(L"e8", buffer)) return e8;
  else if (!wcscmp(L"f1", buffer)) return f1;
  else if (!wcscmp(L"f2", buffer)) return f2;
  else if (!wcscmp(L"f3", buffer)) return f3;
  else if (!wcscmp(L"f4", buffer)) return f4;
  else if (!wcscmp(L"f5", buffer)) return f5;
  else if (!wcscmp(L"f6", buffer)) return f6;
  else if (!wcscmp(L"f7", buffer)) return f7;
  else if (!wcscmp(L"f8", buffer)) return f8;
  else if (!wcscmp(L"g1", buffer)) return g1;
  else if (!wcscmp(L"g2", buffer)) return g2;
  else if (!wcscmp(L"g3", buffer)) return g3;
  else if (!wcscmp(L"g4", buffer)) return g4;
  else if (!wcscmp(L"g5", buffer)) return g5;
  else if (!wcscmp(L"g6", buffer)) return g6;
  else if (!wcscmp(L"g7", buffer)) return g7;
  else if (!wcscmp(L"g8", buffer)) return g8;
  else if (!wcscmp(L"h1", buffer)) return h1;
  else if (!wcscmp(L"h2", buffer)) return h2;
  else if (!wcscmp(L"h3", buffer)) return h3;
  else if (!wcscmp(L"h4", buffer)) return h4;
  else if (!wcscmp(L"h5", buffer)) return h5;
  else if (!wcscmp(L"h6", buffer)) return h6;
  else if (!wcscmp(L"h7", buffer)) return h7;
  else if (!wcscmp(L"h8", buffer)) return h8;
  else return unknown;
}

void mks_parseMove(wchar_t* buffer, size_t* bufferLen, piece_t* newBoard, piece_t* oldBoard, bool* running)
{
  if (!wcscmp(L"exit", buffer)) { *running = false; return; }

  wchar_t* src_test = (wchar_t*)malloc(3 * sizeof(wchar_t));
  wchar_t* dest_test = (wchar_t*)malloc(3 * sizeof(wchar_t));
  wchar_t* promo_test = (wchar_t*)malloc(2 * sizeof(wchar_t));

  memset(src_test, 0, 3 * sizeof(wchar_t));
  memset(dest_test, 0, 3 * sizeof(wchar_t));
  memset(promo_test, 0, 2 * sizeof(wchar_t));

  memcpy(src_test, buffer, 2 * sizeof(wchar_t));
  memcpy(dest_test, &(buffer[2]), 2 * sizeof(wchar_t));
  memcpy(promo_test, &(buffer[4]), 1 * sizeof(wchar_t));

  squarename_t src, dest;
  src = mapWcharToSquarename(src_test);
  dest = mapWcharToSquarename(dest_test);

  memcpy((void*)oldBoard, (void*)newBoard, 64 * sizeof(piece_t));
  newBoard[dest] = oldBoard[src];
  newBoard[src] = (0xAA55AA55AA55AA55 >> src) & 1 ? bEmpty : wEmpty;

  if (newBoard[dest] == wPawn && dest < a7)
  {
    if (!wcscmp(L"q", promo_test)) newBoard[dest] = wQueen;
    else if (!wcscmp(L"n", promo_test)) newBoard[dest] = wKnight;
    else if (!wcscmp(L"b", promo_test)) newBoard[dest] = wBishop;
    else if (!wcscmp(L"r", promo_test)) newBoard[dest] = wRook;
  } 
  else if (newBoard[dest] == bPawn && dest > h7)
  {
    if (!wcscmp(L"q", promo_test)) newBoard[dest] = bQueen;
    else if (!wcscmp(L"n", promo_test)) newBoard[dest] = bKnight;
    else if (!wcscmp(L"b", promo_test)) newBoard[dest] = bBishop;
    else if (!wcscmp(L"r", promo_test)) newBoard[dest] = bRook;
  }

  free(src_test);
  free(dest_test);
  free(promo_test);
}

void mks_validateMove(piece_t* newBoard, piece_t* oldBoard, bool* whitesTurn, unsigned int* turn)
{
  *whitesTurn = !*whitesTurn;
  if(*whitesTurn) (*turn)++;
}

int main()
{
  setlocale(LC_CTYPE, "");
  bool running = true;
  bool whitesTurn = true;
  unsigned int turnNumber = 1;
  size_t inputSize = 10;
  wchar_t* input = (wchar_t*)malloc(inputSize * sizeof(wchar_t));
  piece_t* oldBoard = mks_initaliseBoard();
  piece_t* newBoard = mks_initaliseBoard();

  while (running)
  {
    system("clear");
    mks_printBoard(oldBoard);
    mks_getMove(input, &whitesTurn, &turnNumber);
    mks_parseMove(input, &inputSize, oldBoard, newBoard, &running);
    mks_validateMove(oldBoard, newBoard, &whitesTurn, &turnNumber);
  }

  free(input);
  free(oldBoard);
  free(newBoard);

  return 0;
}

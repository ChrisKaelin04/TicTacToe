//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "TicTacToe.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1* Form1;
char currentPlayerSymbol = 'X';
int movesMade = 0; //to minimize calls to checkWin()
bool winState = false; //identify if game may continue
int board[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
//Basic check, updates winState as needed
void TForm1::checkWin()
{
    bool daDub = false;
	if (Button1->Text == Button2->Text && Button2->Text == Button3->Text &&
        Button3->Text != '-')
    {
        daDub = true;
    } else if (Button1->Text == Button4->Text &&
               Button4->Text == Button7->Text && Button7->Text != '-')
	{
		daDub = true;
    } else if (Button1->Text == Button5->Text &&
               Button5->Text == Button9->Text && Button9->Text != '-')
    {
        daDub = true;
	} else if (Button2->Text == Button5->Text &&
               Button5->Text == Button8->Text && Button8->Text != '-')
    {
        daDub = true;
    } else if (Button3->Text == Button5->Text &&
               Button5->Text == Button7->Text && Button7->Text != '-')
	{
        daDub = true;
    } else if (Button3->Text == Button6->Text &&
               Button6->Text == Button9->Text && Button9->Text != '-')
    {
        daDub = true;
	} else if (Button4->Text == Button5->Text &&
               Button5->Text == Button6->Text && Button6->Text != '-')
    {
        daDub = true;
    } else if (Button7->Text == Button8->Text &&
               Button8->Text == Button9->Text && Button9->Text != '-')
	{
        daDub = true;
    } else {
        daDub = false;
    }
    winState = daDub;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
    currentPlayerSymbolLabel->Text = currentPlayerSymbol;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonClick(TObject* Sender)
{
    TButton* clickedBtn = dynamic_cast<TButton*>(Sender);
    if (clickedBtn->Text == '-' && !winState) {
        clickedBtn->Text = currentPlayerSymbol;
		updateArr(clickedBtn);
        movesMade++;
        if (movesMade >= 5)
            checkWin();
        if (winState) {
            labelWinner->Text = (String)currentPlayerSymbol + " WINS!";
			return;
        }
        if (movesMade == 9) {
            labelWinner->Text = "DRAW!";
        }
        //prevent player from clicking until AI has made move
		Button1->Enabled = false;
        Button2->Enabled = false;
        Button3->Enabled = false;
        Button4->Enabled = false;
        Button5->Enabled = false;
        Button6->Enabled = false;
		Button7->Enabled = false;
        Button8->Enabled = false;
        Button9->Enabled = false;

        if (currentPlayerSymbol == 'X') {
            currentPlayerSymbol = 'O';
			makeMoveO();
        } else {
            currentPlayerSymbol = 'X';
        }
        currentPlayerSymbolLabel->Text = currentPlayerSymbol;

		Button1->Enabled = true;
        Button2->Enabled = true;
        Button3->Enabled = true;
        Button4->Enabled = true;
        Button5->Enabled = true;
        Button6->Enabled = true;
		Button7->Enabled = true;
        Button8->Enabled = true;
        Button9->Enabled = true;
    }
}
//--------------------------------------------------------------------------
void TForm1::updateArr(TButton* button)
{
    int player;
    if (currentPlayerSymbol == 'X')
        player = 1;
    else
		player = 2;

    //now we update the array
    if (button->Name == "Button1")
        board[0][0] = player;
    else if (button->Name == "Button2")
		board[0][1] = player;
    else if (button->Name == "Button3")
        board[0][2] = player;
    else if (button->Name == "Button4")
        board[1][0] = player;
    else if (button->Name == "Button5")
		board[1][1] = player;
    else if (button->Name == "Button6")
        board[1][2] = player;
    else if (button->Name == "Button7")
        board[2][0] = player;
    else if (button->Name == "Button8")
		board[2][1] = player;
    else if (button->Name == "Button9")
        board[2][2] = player;
}
int TForm1::evalArr(int board[3][3])
{
	for (int i = 1; i <= 2; i++) {
		if ((board[0][0] == i && board[0][1] == i && board[0][2] == i) ||
			(board[1][0] == i && board[1][1] == i && board[1][2] == i) ||
			(board[2][0] == i && board[2][1] == i && board[2][2] == i)) {
			if(i == 1) return 1; return -1;
		}
		if ((board[0][0] == i && board[1][0] == i && board[2][0] == i) ||
			(board[0][1] == i && board[1][1] == i && board[2][1] == i) ||
			(board[0][2] == i && board[1][2] == i && board[2][2] == i)) {
			if(i == 1) return 1; return -1;
		}
		if ((board[0][0] == i && board[1][1] == i && board[2][2] == i) ||
			(board[2][0] == i && board[1][1] == i && board[0][2] == i)) {
			if(i == 1) return 1; return -1;
		}
	}
	return 0;
}
int TForm1::miniMax(int board[3][3], int depth, bool isMax){
    int score = evalArr(board);

    if (score == 1)
        return 10 * score - depth;  // Maximizer win (should be AI - O)

    if (score == -1)
        return 10 * score + depth;  // Minimizer win (should be Player - X)

    if (!isMovesLeft(board))
        return 0;

    if (isMax) { // AI's turn (O - represented by 2)
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 2; // AI's move
                    best = std::max(best, miniMax(board, depth + 1, !isMax));
                    board[i][j] = 0;
                }
            }
        }
        return best;
    } else { // Player's turn (X - represented by 1)
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 1; // Player's move
                    best = std::min(best, miniMax(board, depth + 1, isMax));
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}
bool TForm1::isMovesLeft(int board[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == 0)
				return true;
	return false;
}
void TForm1::makeMoveO() {
	int bestVal = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    // Traverse all cells, evaluate minimax function for all empty cells.
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == 0) {
                // Make the move
				board[i][j] = 1;

                // Compute evaluation function for this move.
                int moveVal = miniMax(board, 0, false);

                // Undo the move
				board[i][j] = 0;

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
				}
            }
        }
    }

    // Make the best move
	int bestMove = bestMoveRow * 10 + bestMoveCol;
	switch (bestMove) {
		case 0:
			ButtonClick(Button1);
			break;
		case 1:
			ButtonClick(Button2);
			break;
		case 2:
			ButtonClick(Button3);
			break;
		case 10:
			ButtonClick(Button4);
			break;
		case 11:
			ButtonClick(Button5);
			break;
		case 12:
			ButtonClick(Button6);
			break;
		case 20:
			ButtonClick(Button7);
			break;
		case 21:
			ButtonClick(Button8);
			break;
		case 22:
			ButtonClick(Button9);
			break;
	default:
		break;
	}
}


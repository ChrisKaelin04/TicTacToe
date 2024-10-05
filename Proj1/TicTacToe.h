//---------------------------------------------------------------------------

#ifndef TicTacToeH
#define TicTacToeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button9;
	TButton *Button8;
	TButton *Button7;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label1;
	TLabel *currentPlayerSymbolLabel;
	TLabel *labelWinner;
	void __fastcall ButtonClick(TObject *Sender);
private:    void checkWin(); void makeMoveO(); void updateArr(TButton*);
 int evalArr(int board[3][3]);int miniMax(int board[3][3], int depth, bool isMax);
 bool isMovesLeft(int board[3][3]);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

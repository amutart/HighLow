#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define MAXSHUFFLE 1000
#define INITGOLD 10000

int Betting(int nGold);
int Answer();
int *CardShuffle(int* pCard);// Shuffle 52 cards
int Judge(int nCard, int nSelect, int nBet, int *nGold);// Judge who is the winner.
int PopCard(int* pCard, int* pIndex);// Pop one card
void TransNumToCard(int nNumber);// Show the number with the shape of card
void DisplayCardStack(int* pCardStack);// Show the content of the card stack
void DisplayHiddenCard(int* pIndex);// How many hidden card is there
void InsertCard(int* pCardStack, int nCard);// Insert card to the queue
void Init(int* pCardDeck, int* pCardStack, int *pIndex);// Initialize

int main(void)
{
	// Variable
	int nGold=INITGOLD;
	int nBet=0;
	int nSelect=0;
	int nCardDeck[52]={0,};
	int CardStack[5]={0,};
	int nCloseCard=0;
	int nIndex=0;
	int *pIndex=NULL;

	pIndex = &nIndex;

	srand((unsigned int)time(NULL));

	Init(nCardDeck, CardStack, pIndex);

	while(true)
	{
		cout << "====================================" << endl;
		DisplayHiddenCard(pIndex);
		DisplayCardStack(CardStack);
		cout << "====================================" << endl;

		nCloseCard = PopCard(nCardDeck, pIndex);

		if(!nCloseCard)
		{
			cout << "Ready to the new deck" << endl;
			Init(nCardDeck, CardStack, pIndex);
			continue;
		}

		nBet = Betting(nGold);
		nSelect = Answer();

		if(Judge(nCloseCard, nSelect, nBet, &nGold) != 0)
		{
			cout << "You Win!" << endl << endl;
		}
		else
		{
			cout << "Sorry, you lose." << endl;
		}
		cout << "Card of CPU is" ;
		TransNumToCard(nCloseCard);
		cout << "." << endl << endl;

		InsertCard(CardStack, nCloseCard);

		if(nGold <= 0)
		{
			cout << "You Are BACKRUPT!!" << endl;
			break;
		}
	}

	return 0;
}


void Init(int* pCardDeck, int* pCardStack, int *pIndex)
{
	CardShuffle(pCardDeck);

	for (int i = 0 ; i < 5 ; i ++)
	{
		pCardStack[i] = 0;
	}

	*pIndex = 0;
}

int Betting(int nGold)
{
	int nInput;

	while(true)
	{
		cout << "Bet[Money: " << nGold << "]: ";
		cin >> nInput;

		if(0 < nInput && nInput <= nGold)
		{
			cin.clear();
			cin.ignore();
			return nInput;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Wrong betting. Bet again." << endl;
		}
	}
}

int Answer()
{
	int nInput;
	while(true)
	{
		cout << "Input the range of card[1. High, 2. Low, 3. Seven]: ";
		cin >> nInput;

		if( 0 >= nInput || nInput > 3)
		{
			cout << "Wrong input. Do it again." << endl;
			continue;
		}
		else if(nInput == 1)
		{
			cout << "You selected High (8 to K)." << endl << endl;
		}
		else if(nInput == 2)
		{
			cout << "You selected Low (A to 6)." << endl << endl;
		}
		else
		{
			cout << "You selected SEVEN (7)." << endl << endl;
		}
		return nInput;
	}
}

int *CardShuffle(int *pCard)
{
	int nSrc, nDest= 0;

	for (int i = 0 ; i < 52 ; i++)
	{
		pCard[i] = i + 1;
	}

	for (int i = 0 ; i < MAXSHUFFLE ; i++)
	{
		nDest = rand() % 52;
		nSrc = rand() % 52;
		swap(pCard[nDest], pCard[nSrc]);
	}
	return pCard;
}

void TransNumToCard(int nNumber)
{
	char *pSuit[4]= {"♠", "♥", "♦", "♣"};//[♠=0, ♥ = 1,♦ = 2, ♣=3]
	char *pNum[13]= {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

	int nSuit= (nNumber-1) / 13;
	int nNum= (nNumber-1) % 13;

	cout << "[" << pSuit[nSuit] << setw(2) <<pNum[nNum] << "]";
}
int Judge(int nCard, int nSelect, int nBet, int *nGold)
{
	int nNum= nCard % 13;
	int nJudge= 0;

	if(nNum == 0)
	{
		nNum = 13;
	}

	switch(nSelect)
	{
	case 1://HIGH 
		if(nNum > 7)
		{
			nJudge = 1;
			*nGold += (nBet * 2);
		}
		else
		{
			*nGold -= (nBet * 2);
		}
		break;
	case 2://LOW 
		if(nNum < 7)
		{
			nJudge = 1;
			*nGold += (nBet * 2);
		}
		else
		{
			*nGold -= (nBet * 2);
		}
		break;
	case 3:
		if(nNum ==7)
		{
			nJudge = 1;
			*nGold += (nBet * 10);
		}
		else
		{
			*nGold -= (nBet * 2);
		}
		break;
	}
	return nJudge;
}

int PopCard(int* pCard, int* pIndex)
{
	if (*pIndex >= 52)
	{
		*pIndex = 0;
		return 0;
	}
	return pCard[(*pIndex)++];
}

void DisplayCardStack(int* pCardStack)
{
	for (int i = 0 ; i < 5 ; i ++)
	{
		if(pCardStack[i] == 0)
		{
			cout << "[    ]";
			continue;
		}
		TransNumToCard(pCardStack[i]);
	}
	cout << endl;
}

void DisplayHiddenCard(int *pIndex)
{
	cout << "[  ? ]" << "\t" << "\t" << "Remain card: " << 52 - *pIndex << endl;
}

void InsertCard(int* pCardStack, int nCard)
{
	for (int i = 4 ; i > 0; i--)
	{
		pCardStack[i] = pCardStack[i-1];
	}

	pCardStack[0] = nCard; 
}

//Created by: Reilly Q. Curran
//last edited: 3/22/2017
//last compiled: 3/22/2017
//based on asciiman project developed by Reilly Q.

/*3/15/2017: the program seems to work fine except where it comes to correct letters, for some reason I do not quite
understand, guessing correct letters will reveal adjacent letters and guessing the final letter will cause a program crash
I have tried to fix this in several ways, but it seems that the problem is beyond my current understanding.*/

/*3/16/2017: Still can't figure out the problem but I reduced the printing to a single 
function call that takes the desired list as its input.  This brought down the complexity, and even made the printing 
of correct letters more consistent with the origional word (albeit after the first turn) I will likely end up submitting 
this version for grading and continue trying to solve the problem for no other reason than the fact that it is now 
entered the realm of "going to bug me untill it is fixed." hopefully that comes before the end of the semester.*/

/*3/22/2017: I have finally resolved the issue regarding the correct letters displaying correctly, by separtaing getNextItem into giveCurrent which returns the 
currentPos pointer, and shiftIndex which moves the adress of currentPos.  This change has allowed me to specifically make the program wait until a value has been
checked, and altered if required, before moving the index unlike before when getNextItem would simply move the pointer while it was still in use.  However, there still
seem to be some persistent logic issues regarding the win conditions which I will look at later.*/

#include<iostream>
#include<string>
#include <time.h>
#include "list.h"
#include "hangState.h"

//allows the word and hint to be indexed in the same place
struct randWord
{
	std::string word;
	std::string hint;
};

//creates an empty array of words for the program to initialize
randWord words[30];

//function prototypes for setWords and playGame
void setWords();
void playGame(int, int, int, int, int);
void printList(list printout);

int main()
{
	//tracker that allows the user to know the game is starting up
	std::cout << "Let's Play!" << std::endl;

	//sets the list of words that can be in play
	setWords();

	//--------------------------------
	int draw = 0; //the variable that will randomly pick the index
				  //will stop the game from using indexes it has already called in the last three games
	int prevI = -1;
	int prevII = -2;
	int prevIII = -3;
	// an initialized score for the function call
	int score = 0;
	srand(time(NULL));
	//----------------------------------

	//prevents a random number call from being the same as it was in the last three games
	while (draw == prevI || draw == prevII || draw == prevIII)
	{
		draw = rand() % 29 + 0;
		if (draw == prevI || draw == prevII || draw == prevIII)
		{
			draw = rand() % 29 + 0;
		}
	}

	//calls the game
	playGame(draw, prevI, prevII, prevII, score);

	return 0;
}

void playGame(int draw, int prevI, int prevII, int prevIII, int score)
{
	//************************
	std::string wordChosen; //the indexed word
	std::string guessWord = ""; //the word the player guesses if they choose to risk it all
	wordChosen = words[draw].word;

	std::string mystery = wordChosen; // what will be displayed to the player
									  //the letter by letter guess input
	char guess;
	//the user's input for if they want to risk the game to guess the whole word
	int risk = 0;
	//iterates when the user wins or looses
	int win = 0;
	int lose = 0;
	//a loop iterator that does not throw a warning if it is iterating by an undefined number (the length of a random word)
	size_t i = 0;
	//asks the user if they want to play again
	int continueGame;
	//iterates if the letter guessed does not equal the letter indexed by the checker
	int failCheck = 0;
	//value that confirms the user's guess has not been used already
	bool found = true;
	//*************************
	list word;
	list guessedLetters;
	itemType tempItem;
	hangState hanging = PLATFORM;
	slot temp;
	int checkRevealed = 0;
	//

	//displays the games the player has won
	std::cout << std::endl;
	std::cout << "Games Won: " << score << std::endl;

	while (i < wordChosen.length())
	{
		//sets the mystery word to a length of ascii characters equal in length to the word
		tempItem = slot(mystery[i], SYMBOL);
		//cout << tempItem.getLetter();

		word.Insert(tempItem);
		i++;
	}

	word.printlist();

	while (win != 1 && lose != 1)
	{
		failCheck = 0;
		//displays the mystery characters (for test purposes it displays the word right now)

		printList(word);

		std::cout << std::endl;

		//asks what the user would like to do
		std::cout << std::endl;

		printList(guessedLetters);

		std::cout << std::endl;

		std::cout << "Would you like to guess a letter or try to guess the word?" << std::endl;
		std::cout << "(1: guess a letter, 2: guess the word): ";
		std::cin >> risk; // user decides if they want to guess a word or letter

		switch (risk) //lets the user choose between playing normally, or risking the game on trying to guess the whole word
		{
		case 1: //Plays game as usual
			std::cout << std::endl;
			found = true;
			while (found == true)
			{
				std::cout << "Guess a letter (lowercase): ";
				std::cin >> guess;
				std::cout << "Level 1" << std::endl;

				temp = { guess, LETTER };

				found = guessedLetters.isThere(temp);
				if (found)
				{
					std::cout << "This letter has already been guessed." << std::endl;
					std::cout << std::endl;
				}
				std::cout << "Level 2" << std::endl;
			}

			
			guessedLetters.Insert(slot(guess, LETTER));
			
			word.ResetList();
			//compares the user's guess to the characters in the string
			while (word.hasNext() == true)
			{
				slot * l = word.giveCurrent();
				if (l->getLetter() == guess)
				{
					//(*word.getNextItem()) = (*word.getNextItem()).changeSlot(LETTER);
					(*word.giveCurrent()).changeSlot(LETTER);
					//the letter the user guessed is equal to the index
				}

				else
				{
					failCheck++;
					//the letter the user guessed does not equal the index
				}
				word.shiftIndex();
			}
			;
			//win, lose, continue conditions

			word.ResetList();

			while (word.hasNext() == true)
			{
				if ((*word.giveCurrent()).getDisplay() == LETTER)
				{
					checkRevealed++;
				}
				word.shiftIndex();
			}
			
			if (checkRevealed == wordChosen.length())//if the user has completed the word
			{
				std::cout << std::endl;
				std::cout << "Correct!  The word was " << wordChosen << ". " << std::endl;
				score++;
				win++;
			}
			else if (failCheck == word.getLength())//if the user guessed a wrong letter
			{
				std::cout << std::endl;
				std::cout << "That was not a correct letter." << std::endl;
				if (hanging == PLATFORM)
				{
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = BODY;
					break;
				}
				else if (hanging == BODY)
				{
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = LEFTLEG;
					break;
				}
				else if (hanging == LEFTLEG)
				{
					std::cout << "You seem to be having trouble, here's a hint!" << std::endl;
					std::cout << words[draw].hint << std::endl;
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "| /   " << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = RIGHTLEG;
					break;
				}
				else if (hanging == RIGHTLEG)
				{
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "| / \\" << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = RIGHTARM;
					break;
				}
				else if (hanging == RIGHTARM)
				{
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "|  |\\" << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "| / \\" << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = LEFTARM;
					break;
				}
				else if (hanging == LEFTARM)
				{
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|     " << std::endl;
					std::cout << "| /|\\" << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "| / \\" << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					hanging = HEAD;
					break;
				}
				else if (hanging == HEAD) // if the user lost
				{
					std::cout << "Sorry, but the correct word was " << wordChosen << std::endl;
					std::cout << std::endl;
					std::cout << "___   " << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "|  O  " << std::endl;
					std::cout << "| /|\\" << std::endl;
					std::cout << "|  |  " << std::endl;
					std::cout << "| / \\" << std::endl;
					std::cout << "|_____" << std::endl;
					std::cout << "|    |" << std::endl;
					std::cout << std::endl;
					lose++;
				}
			}
			break;
		case 2: //prompts the user to guess the full word
			std::cout << std::endl;
			std::cout << "Alright, what's the word?: ";
			std::cin >> guessWord;
			if (guessWord == wordChosen)
			{
				// the player gussed the correct word
				std::cout << std::endl;
				std::cout << "That is correct!  You Win!" << std::endl;
				score++;
				win++;
			}
			else
			{
				//the user guessed incorrectly
				std::cout << std::endl;
				std::cout << "Nope!  You Lose!" << std::endl;
				std::cout << std::endl;
				std::cout << "___   " << std::endl;
				std::cout << "|  |  " << std::endl;
				std::cout << "|  O  " << std::endl;
				std::cout << "| /|\\" << std::endl;
				std::cout << "|  |  " << std::endl;
				std::cout << "| / \\" << std::endl;
				std::cout << "|_____" << std::endl;
				std::cout << "|    |" << std::endl;
				std::cout << std::endl;
				lose++;
			}
			break;
		default: //prevents the user from choosing outside the given options
			std::cout << std::endl;
			std::cout << "I am sorry, this was not one of the given choices." << std::endl;
			break;
		}
	}
	//asks the user if they want to play again
	std::cout << std::endl;
	std::cout << "Would you like to play again (1 to play again, 2 to end the game)?" << std::endl;
	std::cout << "Play again: ";
	std::cin >> continueGame;


	//if the user wants to play again, the randomization process from int main() is repeated with this games index stored back one
	// and the game before that moved back one and so on and so forth.
	if (continueGame == 1)
	{
		prevIII = prevII;
		prevII = prevI;
		prevI = draw;
		while (draw == prevI || draw == prevII || draw == prevIII)
		{
			draw = rand() % 29 + 0;
			if (draw == prevI || draw == prevII || draw == prevIII)
			{
				draw = rand() % 29 + 0;
			}
		}
		//loops the game via recursion
		playGame(draw, prevI, prevII, prevIII, score);
	}
	//quits the game
	else
	{
		std::cout << std::endl;
		std::cout << "okay, thanks for playing!" << std::endl;
	}
}

void setWords() //establsihes the random words and hints
{
	words[0].word = "google";
	words[0].hint = "Have a question, try searching it!";

	words[1].word = "twitter";
	words[1].hint = "Sounds like a bird.";

	words[2].word = "facebook";
	words[2].hint = "Where you likely get all of your news";

	words[3].word = "reddit";
	words[3].hint = "There's a thread for everyone!";

	words[4].word = "youtube";
	words[4].hint = "COMMENTS!";

	words[5].word = "tumblr";
	words[5].hint = "Think, 'Not 4-chan'...";

	words[6].word = "github";
	words[6].hint = "Open Source FTW";

	words[7].word = "javascript";
	words[7].hint = "Programming language known for web based gaming";

	words[8].word = "python";
	words[8].hint = "Programming Language good for making a database search engine";

	words[9].word = "pearl";
	words[9].hint = "Programming Language, Everyone hates it";

	words[10].word = "minecraft";
	words[10].hint = "BLOCKS EVERYWHERE!";

	words[11].word = "darksouls";
	words[11].hint = "Prepare to Die...";

	words[12].word = "warcraft";
	words[12].hint = "World of...";

	words[13].word = "starcraft";
	words[13].hint = "Zerg Rush!";

	words[14].word = "bloodborne";
	words[14].hint = "kinda like darksouls";

	words[15].word = "playstation";
	words[15].hint = "There's four of them.";

	words[16].word = "nintendo";
	words[16].hint = "Plumbers, monsters, and heroes oh my!";

	words[17].word = "microsoft";
	words[17].hint = "Word, Excel, Powerpoint, etc...";

	words[18].word = "windows";
	words[18].hint = "Wait, doesn't 9 come before 10?";

	words[19].word = "pokemon";
	words[19].hint = "Sun and Moon";

	words[20].word = "mario";
	words[20].hint = "It's a me!";

	words[21].word = "halo";
	words[21].hint = "spartan";

	words[22].word = "kirby";
	words[22].hint = "Surprisingly dark for a pink marshmallow...";

	words[23].word = "zelda";
	words[23].hint = "The legend of...";

	words[24].word = "link";
	words[24].hint = "No, his name is not zelda.";

	words[25].word = "bowser";
	words[25].hint = "King koopa";

	words[26].word = "ganon";
	words[26].hint = "triforce of power";

	words[27].word = "saitama";
	words[27].hint = "ONE PUUUUUUUUUUUNCH!!!";

	words[28].word = "goku";
	words[28].hint = "The super saiyan";

	words[29].word = "superman";
	words[29].hint = "Faster than a speeding bullet...";
}

void printList(list printout)
{
	printout.ResetList();
	printout.printlist();
}

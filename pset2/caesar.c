#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rotate(string textInput, int rotateNumber); 
/*
declared my function
*/

int main(int argc, string argv[])
{
	/*
	if argument count is not equal to 2 it will yell at the user and
	tell them what to do to make it better. Return 1 quits the program 
	after
	*/
	if(argc != 2)
	{
		printf("please provide only 1 command line argument, non-negative integer: ");
		return 1;
	}

	int k = atoi(argv[1]);

	//printf("Give me some text: \n");
	string text = GetString();
	rotate(text, k);
}

void rotate(string textInput, int rotateNumber)
{
	for(int i = 0, n = strlen(textInput); i < n; i++)
	{
		//printf("%i\n", (int) textInput[i]);
	

		int letter = (int) textInput[i];

		if (letter >= 65 && letter < 91)
		{
			letter = letter - 65;
			letter = letter + rotateNumber;
			letter = letter % 26;
			letter = letter + 65;
		}	

		else if(letter >= 97 && letter < 123)
		{	
			letter = letter - 97;
			letter = letter + rotateNumber;
			letter = letter % 26;
			letter = letter + 97;
		}

		char newLetter = (char) letter;

		printf("%c", newLetter);
	}
	printf("\n");
}
/*
In the for loop I check is the given letter is a Capital letter or not. I subtract either 65 or 97 to let a be equal to 0
then I add the rotateNumber and use module 26 to make it possible to go from Z to A after that I add 65 or 97 again to give me the enciphered letter.
letter is still a number so I transfer it to a char giving it a new name newLetter. 
When the word is written I \n to make it look better when running the program.
*/

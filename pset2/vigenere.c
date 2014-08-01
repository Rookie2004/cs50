#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
declared my rotate function consisting of 2 arguments
*/

void rotate(string textInput, string key); 


int main(int argc, string argv[])
{
	
	if(argc != 2)
	{
		printf("please provide only 1 command line argument, non-negative integer: ");
		return 1;
	}

	string key = argv[1];

	for(int i = 0, n = strlen(key); i < n; i++)
	{
		if(!isalpha(key[i]))
		{
			printf("You need to give a string with only alphabetical letters\n");
			return 1;
		}
	}
	//printf("Give me some text: \n");
	string text = GetString();
	rotate(text, key);
}
	/* First I checked if there were no more aguments given than 1 (program name is the other)
	if argc was not equal to 2 the program stops giving some instructions.
	Secondly I checked if the input was a string consisting of alphabetical letters.
	I'v used isalpha for that. If not I gave the user a message how to handle.
	The user enters a string and I get that string using GetString ofcourse.
	I call my new function called rotate using key and text as arguments.
	*/
void rotate(string textInput, string key)
{
	for(int i = 0, j = 0, n = strlen(textInput); i < n; i++)
	{
		int rotateNumber = (int) key[j];
		
		if (rotateNumber >= 65 && rotateNumber < 91)
		{
			rotateNumber = rotateNumber - 65;
		} 

		else if(rotateNumber >= 97 && rotateNumber <123)
		{
			rotateNumber = rotateNumber - 97;
		}

		//printf("%i\n", rotateNumber);
	/*
	I made a for loop to go through every character in the given string text. Inside the for loop I made use of two if/else if
	constructions. 1 to check rotateNumber and 1 to check each letter. I'v used modulo in the second if/else if to be able to let the keyword
	start from the beginning again and again. The rest of the code is more or less like the caesar code.
	*/
		int letter = (int) textInput[i];

		if (letter >= 65 && letter < 91)
		{
			letter = letter - 65;
			letter = letter + rotateNumber;
			letter = letter % 26;
			letter = letter + 65;
			j++;
			j = j % strlen(key);
		}	

		else if(letter >= 97 && letter < 123)
		{	
			letter = letter - 97;
			letter = letter + rotateNumber;
			letter = letter % 26;
			letter = letter + 97;
			j++;
			j = j % strlen(key);
		}

		char newLetter = (char) letter;

		printf("%c", newLetter);
	}
	printf("\n");
}

//check50 2014/x/pset2/vigenere vigenere.c
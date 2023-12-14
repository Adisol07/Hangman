#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE(array) ( sizeof((array)) / sizeof((array[0])) )
#define RENDERING 1

#define BLACK "\e[0;30m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN "\e[0;36m"
#define GRAY "\e[0;90m"
#define WHITE "\e[0;37m"

char** words = NULL;
int wordCount = 0;
void AllocateWords()
{
	char* w[] = { "slovo", "vaclav nemec", "obsah nenalezen", "laska",
					"hodiny", "provaz", "postel", "advent", "php a c jsou spatne jazyky",
					"dovolena", "rucicky", "pes", "kocka", "kvetina", "vitamin",
					"terasa", "udirna", "gril", "pohadka", "zahrada", "pohoda",
					"darek", "pratelstvi", "dum", "obraz", "fotografie",
					"psychologie", "dejepis", "dite", "kalendar", "pantofle", "skola",
					"informace", "vanoce", "velikonoce", "snih", "bolest",
					"leto", "zima", "jaro", "podzim", "cesko", "film", "ceska republika",
					"ropa", "ozdoba", "bryle", "hreben", "zarovka", "papir", "sprcha",
					"mydlo", "penize", "vlasy", "jmeno", "letadlo", "nakup", "svet", "sedlo",
					"kun", "deka", "sedadlo", "rukojet", "mesic", "slunce", "galaxie", "vesmir",
					"krystaly", "vojak", "hvezda", "mars", "mozek", "jidelna", "kokos",
					"testo", "vzorec", "seminka", "balicek", "vlada", "trava", "tulipan",
					"sekacka", "zahradni domek", "moda", "covid", "kolotoc",
					"pratele", "rodina", "situace", "most", "slezsko", "manzelstvi", "leky",
					"cihla", "domov", "vetev", "strop", "pernicky", "praha", "zabava",
					"utery", "latka", "sourozenec", "vylet", "stavba", "inspirace", "dezert",
					"ryba", "akvarium", "pisek", "program", "jazyk", "tapeta", "zelezo",
					"mineraly", "vtip", "ostrov", "kytice", "rakovnik", "senomaty",
					"plzen", "hospoda", "restaurace", "system", "vyzdoba", "reproduktor",
					"krtek", "zirafa", "dlazba", "prezident", "opice", "okno",
					"zidle", "stul", "ovladac", "voda", "h2o", "nabijecka", "mamut", "dinosaurus",
					"kolo", "auto", "obleceni", "axolotl", "mramor", "jehlici", "jelen", "kralovstvi",
					"tristadvacetsest", "dvestesedesatjedna", "jedna", "c1", "csharp", "c", "cpp", "havel",
					"mikulas", "databaze", "server", "zvire", "sibenice", "morava", "slovensko", "nemecko",
					"polsko", "rakousko", "php", "hangman", "cool", "trdlo", "slanina", "les", "simpsonovi", "korunka",
					"notebook", "ruka", "klavesnice", "matematika", "kabat", "klobouk", "kostka", "kostky",
					"vaza", "zaluzie", "cinka", "knoflik", "nitka", "fotosynteza", "okap",
					"podnikatel", "majoneza", "ctverecek", "balon", "dira", "zirafa",
					"zlomenina", "orteza", "dluhy", "dluh", "platebni karta", "stekot",
					"priklad", "flaska", "plisen", "knirek", "strom", "praxe", "cas",
					"pocitac", "mys", "kabel", "kastan", "niva", "hermelin", "cislo" };

	words = (char**)realloc(words, ARRAY_SIZE(w) * sizeof(char*));
	wordCount = ARRAY_SIZE(w);
	for (int i = 0; i < ARRAY_SIZE(w); i++) {
		words[i] = strdup(w[i]);
	}
}

char* pokus1 = "-----";
char* pokus2 = " ___\n/___\\";
char* pokus3 = "  |\n  |\n _|_\n/___\\";
char* pokus4 = "  /---\n  |\n  |\n _|_\n/___\\";
char* pokus5 = "  /---\n  |  o\n  |\n _|_\n/___\\";
char* pokus6 = "  /---\n  |  o\n  |  O\n _|_\n/___\\";
char* pokus7 = "  /---\n  |  o\n  | \\O\n _|_\n/___\\";
char* pokus8 = "  /---\n  |  o\n  | \\O/\n _|_\n/___\\";
char* pokus9 = "  /---\n  |  o\n  | \\O/\n _|_/\n/___\\";
char* pokus10 = "  /---\n  |  o\n  | \\O/\n _|_/\\\n/___\\";

int currentWordIndex;
char* currentWord;
int attempts;
int guessed;
char* renderMessage;
int renderMessageType;
char* wrongGuesses;
char* guessedLetters;

void SetCursorPosition(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

void PrintFetchedWord(char guessedLetters[])
{
	for (int i = 0; i < strlen(currentWord); i++)
	{
		char letter = currentWord[i];
		char guessed = guessedLetters[i];
		if (letter == guessed)
		{
			printf("%c", letter);
		}
		else
		{
			printf("%c", '#');
		}
	}
}

void Render(char guessedLetters[])
{
	system("clear");
	SetCursorPosition(0,0);
	system("clear");
	printf(MAGENTA);
	printf("<- HANGMAN -> ");
	printf(GRAY);
	printf("(Type '?' for information)\n");
	printf(MAGENTA);
	printf("Word: ");
	printf(YELLOW);
	PrintFetchedWord(guessedLetters);
	printf(MAGENTA);
	printf("\nAttempts: %d", attempts);
	if (renderMessageType != -1)
	{
		switch (renderMessageType)
		{
			case 0:
				printf(RED);
				break;
			case 1:
				printf(GREEN);
				break;
			case 2:
				printf(BLUE);
				break;
			default:
				printf(WHITE);
				break;
		}
		printf("\n%s", renderMessage);
		renderMessage = "";
		renderMessageType = -1;
	}
	printf(BLUE);
	if (RENDERING)
	{
		switch (attempts)
		{
			case 0:
				printf("\n\n%s\n", pokus10);
				break;
			case 1:
				printf("\n\n%s\n", pokus9);
				break;
			case 2:
				printf("\n\n%s\n", pokus8);
				break;
			case 3:
				printf("\n\n%s\n", pokus7);
				break;
			case 4:
				printf("\n\n%s\n", pokus6);
				break;
			case 5:
				printf("\n\n%s\n", pokus5);
				break;
			case 6:
				printf("\n\n%s\n", pokus4);
				break;
			case 7:
				printf("\n\n%s\n", pokus3);
				break;
			case 8:
				printf("\n\n%s\n", pokus2);
				break;
			case 9:
				printf("\n\n%s\n", pokus1);
				break;
			default:
				break;
		}
	}
	if (wrongGuesses != NULL && strcmp(wrongGuesses, ""))
		printf("\nWrong guesses: %s", wrongGuesses);
}

void Generate()
{
	srand(time(NULL));
	renderMessageType = -1;
	renderMessage = "";
	currentWordIndex = rand() % wordCount;
	currentWord = words[currentWordIndex];
	guessedLetters = (char*)malloc(strlen(currentWord));
	wrongGuesses = (char*)malloc(0);
	guessed = 0;
}

int getNumberOfLetters(char letter)
{
	int result = 0;
	for (int i = 0; i < strlen(currentWord); i++)
	{
		if (letter == currentWord[i])
		{
			result++;
		}
	}
	return result;
}

void config()
{
	system("clear");
	printf(WHITE);
	printf("Configuration: \n");
	printf(" -> Type: 'set $words$' to set your own words(separate words by comma and use regular spaces for spaced words)\n");
	printf(" -> Type: 'attempts $num_of_attempts$' to set custom amount of attempts\n");
	printf(" : ");
	printf(GRAY);
	char* input = (char*)malloc(200);
	scanf(" %199[^\n]", input);

	char* word = strtok(input, " ");
	if (strcmp(word, "set") == 0) {
		for (int i = 0; i < wordCount; i++) {
			free(words[i]);
		}
		free(words);
		words = NULL;
		wordCount = 0;

		word = strtok(NULL, ",");
		while (word != NULL) {
			words = (char**)realloc(words, (wordCount + 1) * sizeof(char*));
			words[wordCount] = strdup(word);
			wordCount++;
			word = strtok(NULL, ",");
		}
	}
	else if (strcmp(word, "attempts") == 0) {
		char *token = strtok(NULL, " ");
		attempts = atoi(token);
	}

	free(input);
}
void information()
{
	system("clear");
	printf(WHITE);
	printf("Information:\n");
	printf(" -> Character '?' gets you here\n");
	printf(" -> Use '_' instead of spaces\n");
	printf(YELLOW);
	printf(" -> Type 'return' to return to guessing or type 'config' to change settings\n");
	printf(" : ");
	printf(GRAY);
	char* input = (char*)malloc(10);
	scanf(" %9[0-9a-zA-Z]", input);
	if (strcmp(input, "return") == 0) {
		free(input);
		return;
	}
	else if (strcmp(input, "config") == 0) {
		free(input);
		config();
		Generate();
		return;
	}
	information();
}

void replaceChar(char* str, char find, char replace)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == find)
		{
			str[i] = replace;
		}
	}
}

int main()
{
	AllocateWords();
again:
	attempts = 10;
	Generate();
	do
	{
		Render(guessedLetters);
		printf(MAGENTA);
		printf("\nType letter or whole word: ");
		printf(GRAY);
		char* input = (char*)malloc(100);
		scanf(" %99[0-9a-zA-Z-_? ]", input);
		//replaceChar(input, '_', ' ');
		if (strcmp(input, "?") == 0) {
			information();
		}
		else if (strlen(input) == 1)
		{
			char letter = input[0] == '_' ? ' ' : input[0];
			int contains = 0;
			int indexes[strlen(currentWord)];
			for (int i = 0; i < strlen(currentWord); i++)
			{
				if (letter == currentWord[i])
				{
					contains = 1;
					indexes[i] = 1;
				}
				else
				{
					indexes[i] = 0;
				}
			}
			if (contains)
			{
				renderMessageType = 1;
				renderMessage = "Correct!";
				for (int i = 0; i < strlen(currentWord); i++)
				{
					if (indexes[i] == 1)
						guessedLetters[i] = letter;
				}
			}
			else
			{
				contains = 0;
				for (int i = 0; i < strlen(wrongGuesses); i++)
				{
					if (letter == wrongGuesses[i])
					{
						contains = 1;
						break;
					}
				}
				if (contains)
				{
					renderMessageType = 2;
					renderMessage = "You have already typed this letter!";
				}
				else
				{
					renderMessageType = 0;
					renderMessage = "Incorrect!";
					wrongGuesses = (char*)realloc(wrongGuesses, strlen(wrongGuesses) + 2);
					wrongGuesses[strlen(wrongGuesses)] = letter;
					wrongGuesses[strlen(wrongGuesses) + 1] = '\0';
					attempts--;
				}
			}
		}
		else if (strcmp(input, currentWord) == 0)
		{
			guessed = 1;
			strcpy(guessedLetters, currentWord);
		}
		else
		{
			renderMessageType = 0;
			renderMessage = "Incorrect word!";
			attempts--;
		}
		free(input);
		if (strlen(guessedLetters) == strlen(currentWord))
			guessed = 1;


	} while (guessed == 0 && attempts != 0);

	if (guessed == 1)
	{
		Render(guessedLetters);
		char message[] = "\nCongratulations! \nYou guessed it!\nDo you want to play again? ";
		if (strcmp(currentWord, "husty") == 0 || strcmp(currentWord, "cool") == 0 ||
			strcmp(currentWord, "php a c jsou spatne jazyky") == 0 || strcmp(currentWord, "vaclav nemec") == 0) {
			for (int i = 0; i < strlen(message); i++) {
				char c = message[i];
				int r = rand() % 7;
				switch (r) {
					case 0:
						printf(RED);
						break;
					case 1:
						printf(GREEN);
						break;
					case 2:
						printf(YELLOW);
						break;
					case 3:
						printf(BLUE);
						break;
					case 4:
						printf(MAGENTA);
						break;
					case 5:
						printf(CYAN);
						break;
					case 6:
						printf(GRAY);
						break;
					default:
						printf(WHITE);
				}
				printf("%c", c);
			}
		}
		else {
			printf(GREEN);
			printf("%s", message);
		}
	}
	if (attempts == 0)
	{
		strcpy(guessedLetters, currentWord);
		renderMessageType = -1;
		renderMessage = "";
		Render(guessedLetters);
		printf(RED);
		printf("\nYou failed!\nDo you want to play again? ");
	}
	char* o = (char*)malloc(5);
	scanf("%4s", o);
	if (strcmp(o, "Y") == 0 || strcmp(o, "y") == 0 || strcmp(o, "yes") == 0 || strcmp(o, "Yes") == 0)
		goto again;

	free(o);
	return 0;
}

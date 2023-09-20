#include "shell.h"

/**
 * split_string - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string to be split.
 * @delimiters: The delimiter string used for splitting.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string(char *str, char *delimiters)
{
	int i, x, y, z, numwords = 0;
	char **words;

	/* Check if the input string is NULL or empty */
	if (str == NULL || str[0] == '\0')
		return (NULL);

	/* If delimiters are not provided, set the default delimiter to " " */
	if (!delimiters)
		delimiters = " ";

	/* Count the number of words by checking non-repeated delimiters */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiters) &&
			(is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
			numwords++;

	/* If no words are found, return NULL */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings to hold the words */
	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	/* Loop through the input string to extract the words */
	for (i = 0, x = 0; x < numwords; x++)
	{
		/* Skip delimiters to find the start of a word */
		while (is_delimiter(str[i], delimiters))
			i++;

		/* Find the length of the current word */
		y = 0;
		while (!is_delimiter(str[i + y], delimiters) && str[i + y])
			y++;

		/* Allocate memory for the word and copy it to the array */
		words[x] = malloc((y + 1) * sizeof(char));
		if (!words[x])
		{
			/* Free allocated memory in case of failure */
			for (y = 0; y < x; y++)
				free(words[y]);
			free(words);
			return (NULL);
		}

		for (z = 0; z < y; z++)
			words[x][z] = str[i++];

		/* Null-terminate the word */
		words[x][z] = '\0';
	}

	/* Null-terminate the array of words */
	words[x] = NULL;
	return (words);
}

/**
 * split_string2 - Splits a string into words using a given delimiter.
 * @str: The input string to be split.
 * @d: The delimiter character used for splitting.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string2(char *str, char d)
{
	int i, x, k, m, numwords = 0;
	char **string;

	/* Check if the input string is NULL or empty */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Count the number of words in the input string */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	/* If no words are found, return NULL */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	string = malloc((1 + numwords) * sizeof(char *));
	if (!string)
		return (NULL);

	/* Split the input string into words */
	for (i = 0, x = 0; x < numwords; x++)
	{
		/* Skip leading delimiters */
		while (str[i] == d && str[i])
			i++;

		/* Calculate the length of the current word */
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		/* Allocate memory for the current word */
		string[x] = malloc((k + 1) * sizeof(char));
		if (!string[x])
		{
			/* Free allocated memory on failure */
			for (k = 0; k < x; k++)
				free(string[k]);
			free(string);
			return (NULL);
		}

		/* Copy the current word into the array */
		for (m = 0; m < k; m++)
			string[x][m] = str[i++];
		string[x][m] = 0;
	}

	/* Set the last element of the array to NULL to mark the end */
	string[x] = NULL;
	return (string);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fleschIndex.h"

char * readFile ( char * filename) 
{

    int inputsize;
    FILE * fPointer;
    fPointer = fopen(filename, "r");            //open file for reading
    char * lines;

    if(fPointer == NULL)
    {
        printf("file DNE");             // if file is NULL, print this
    }

    else
    {
        fseek(fPointer,0, SEEK_END);                    // seek to end of file
        inputsize = ftell(fPointer);                    
        fseek(fPointer,0,SEEK_SET);                 // seek to beginning

        lines = malloc(sizeof(char) * inputsize);               // malloc based off input size

        fread(lines, inputsize, 1, fPointer);               // read into lines
    }

    fclose(fPointer);               // close pointer for memory maintenance
    
    //printf("%s", lines);

   return lines;
    }

int countWords(char * input)
{
    int wordcount = -1;                             
    int i = 0;
    
    do {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\0' || input[i] == '\n') 
        {                                                                                               // if a space or terminating char is reached at current char, follow if statement
            if( ( (i > 0) && (input[i-1] != ' ' && input[i-1] != '\t' && input[i-1] != '\0' ) ) || input[i-1] == '\n' )
            {
                wordcount++;                                                                            // if previous char was also a terminating char, increment word count
            }
        }
    } while(input[i++]);                        

   //printf("number of words: %d\n", wordcount);

    return wordcount;
}

int countSyllables(char * input)
{
    char * word;
    int syllables = 0;
    int i = 0;
    int j = 0;
    char searchvowels[] = {'a','e','i','o','u','y','A','E','I','O','U','Y','\0'}; // initialize array with vowels
    int countsyllables = 0;                 
    const char terminating[] = {' ', '\n', '\0'};               // store terminating chars
    
    word = strtok(input, terminating);                  // intialize word to strtok to any terminating chars

    for(i = 0; ; i++)
    {
        countsyllables = syllables;             // set flag countSyllables to syllables
        //printf("%d %s\n", i, word);

        for(j = 0; j < strlen(word); j++)       // loop for chars in word
        {
            if ( ( strchr(searchvowels, word[j]) != NULL) && ( (strchr(searchvowels, word[j+1]) == NULL) 
            || (word[j+1] == '.') || (word[j+1] == '!') || (word[j+1] == '?') || (word[j+1] == '\n') 
            || (word[j+1] == ',') || (word[j+1] == ' ') || (word[j+1] == '\0') || (word[j+1] == ';') 
            || (word[j+1] == ':') ) )               // check if vowel is found and if next element is a terminating or word ending char
            {
                syllables++;
                //printf("%d %c\n", i, word[j]);

                if ( ( (word[j] == 'e') || (word[j] == 'E') ) && ( (word[j+1] == '.') || (word[j+1] == '!') 
                || (word[j+1] == '?') || (word[j+1] == '\n') || (word[j+1] == ',') || (word[j+1] == ' ') 
                || (word[j+1] == '\0') || (word[j+1] == ';') || (word[j+1] == ':') ) )
                {                                               // check if e is at end of word, if it is subtract a syllable
                syllables--;
                //printf("%d remove %c\n", i, word[j]);
                }
            }
        }

        if(syllables == countsyllables)                     // increment syllables if syllable was never added to word
        {
            syllables++;
            //printf("%d added sylb \n", i);
        }
        
        word = strtok(NULL, terminating);                   // move to next word using strtok
        if (word == NULL)
        {
            break;
        }
    }

    //printf("total syllables: %d\n", syllables);

    return syllables;
    
}

int countSentences(char * input)
{
    int sentences = 0;
    int i = 0;
    char periods[] = {'.','?','!',':',';'};                         // initialize array with sentence terminators that will be searched 

    for(i=0; i < strlen(input); i++)                            // for loop lasts until input is cleared
    {
        if( (strchr(periods, input[i]) !=NULL)  && ((input[i+1] == ' ') || (input[i+1] == '\n') || (input[i+1] == '\0')) )          // if a terminating char is reached increment sentences
        {
            sentences++;
        }
    }

    //printf("number of sentences: %d\n", sentences);

    return sentences;
}

int calculateFleschIndex(int syllables, int words, int sentences)
{   
    float index;                    // initialize float index for calculations

    index = ( 206.835 - (84.6 * (syllables/words)) - (1.015 * (words/sentences)) );     // flesch formula
    
    int indexround = (int) (index + 0.5);

    return indexround;

}

void outputFormattedFleschScores(int syllables, int words, int fleshIndex, int sentences)
{
             //output
    printf("Flesch Index = %.0d\n", fleshIndex); 
    printf("Syllable Count = %d\n", syllables); 
    printf("Word Count = %d\n", words); 
    printf("Sentence Count = %d\n", sentences);
    
    
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fleschIndex.h"

int main(int argc, char * argv[])
{
    //readFile(argv[1]);
    int syllables = countSyllables(readFile(argv[1]));
    int words = countWords(readFile(argv[1]));
    int sentences = countSentences(readFile(argv[1]));
    int fleschIndex = calculateFleschIndex(syllables, words, sentences);
    outputFormattedFleschScores(syllables, words, fleschIndex, sentences);

}
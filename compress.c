#include "Node.h"

#include <stdio.h>
#include <string.h>

// print_usage_string() (void): prints the correct way of calling the
// executable to stout
void printUsageString();

// getChar(int i) (char): returns the ASCII character of the value i
char getChar(int i);

// getInt(char c) (int): returns the ASCII value of the character c
int getInt(char c);

int main(int argc, char * argv[]) {
	// read through the file to get the count of all numbers

    if (argc != 2) {
		printf("Incorrect number of arguments. See usage string:\n");
		printUsageString();
	}

    // file I/O
	char * fileName = argv[1];
    FILE * f = fopen(fileName, "r");
    if (!f) {
        printf("File not found in this directory. See usage string:\n");
        printUsageString();
    }

    // checking if filename.xyp exists in this directory already
    // to avoid overwriting any previously existing files
    // let the user name his or her own files later on
    if (strlen(fileName) > 4) {
        char * fileNameCut = malloc(strlen(fileName)*sizeof(char));
        strcpy(fileNameCut, fileName);
        fileNameCut[strlen(fileName)-4] = '\0';

        char * fileNameCutXyp = malloc((strlen(fileNameCut)+4)*sizeof(char));
        strncpy(fileNameCutXyp, fileNameCut, strlen(fileNameCut));
        fileNameCutXyp[strlen(fileNameCut)] = '.';
        fileNameCutXyp[strlen(fileNameCut)+1] = 'x';
        fileNameCutXyp[strlen(fileNameCut)+2] = 'y';
        fileNameCutXyp[strlen(fileNameCut)+3] = 'p';

        FILE * fCheck = fopen(fileNameCutXyp, "r");

        if (fCheck) {
            printf("%s already exists in this directory.\nRemove it and " 
                   "try again.\n", fileNameCutXyp);
            free(fileNameCut);
            free(fileNameCutXyp);
            fclose(f);
            fclose(fCheck);
            return 1;
        } else {
            free(fileNameCut);
            free(fileNameCutXyp);
        }
    }

    char * fileNameXyp = malloc((strlen(fileName)+4)*sizeof(char));
    strncpy(fileNameXyp, fileName, strlen(fileName));
    fileNameXyp[strlen(fileName)] = '.';
    fileNameXyp[strlen(fileName)+1] = 'x';
    fileNameXyp[strlen(fileName)+2] = 'y';
    fileNameXyp[strlen(fileName)+3] = 'p';

    FILE * fCheckFull = fopen(fileNameXyp, "r");
    if (fCheckFull) {
        printf("%s already exists in this directory.\nRemove it and " 
               "try again.\n", fileNameXyp);
        free(fileNameXyp);
        fclose(f);
        fclose(fCheckFull);
        return 1;
    } else {
        free(fileNameXyp);
    }



    // supports all ASCII characters
    int map[128] = {0};

    // go line-by-line, char-by-char and fill up the map
    char * line = NULL;
    size_t len;
    int nodeArrayLength = 0;
    while (getline(&line, &len, f) != -1) {
        long unsigned int i;
        for (i = 0 ; i < strlen(line) ; i++) {
            if (map[getInt(line[i])] == 0) {
                nodeArrayLength++;
            }
            map[getInt(line[i])]++;
        }
    }

    // fill up array with nodes for compressed representation
    struct Node * nodeArray[nodeArrayLength];
    int nodeArrayIt = 0;
    long unsigned int i;
    for (i = 0 ; i < 128 ; i++) {
        if (map[i] != 0) {
            nodeArray[nodeArrayIt] = malloc(sizeof(struct Node));
            nodeArray[nodeArrayIt]->c = getChar(i);
            nodeArray[nodeArrayIt]->count = map[i];
            nodeArrayIt++;
        }
    } 

    

    // merge into one overarching tree of nodes
    // O(N^2) - technically O(1) since we have
    // at most 128 nodes, though. to-do: implement
    // a priority queue to handle this later, maybe
    // as a heap? possible O(N*lg(N)) improvement
    int minis[2] = {-1, -1};
    struct Node * toMerge[128];
    int toMergeIt = 0;
    
     

    // free all space, close file, successful return
    for (i = 0 ; i < nodeArrayLength ; i++) {
        free(nodeArray[i]);
    }
    fclose(f);
	return 0;
}

void printUsageString() {
	printf("./binary_xyphos <input_file_name>\ninput_file_name should be the name of a text file.\n");
	exit(1);
}

char getChar(int i) {
    return (char) i;
}

int getInt(char c) {
    return (int) c;
}

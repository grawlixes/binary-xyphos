#include "Node.h"

#include <stdio.h>
#include <string.h>

// print_usage_string() (void): prints the correct way of calling the
// executable to stout void printUsageString();

// getChar(int i) (char): returns the ASCII character of the value i
char getChar(int i);

// getInt(char c) (int): returns the ASCII value of the character c
int getInt(char c);

void printUsageString();

void transformHelper(int map[128][3], struct Node * huffNode, int mapping, int ct);

void transformMap(int map[128][3], struct Node * huffTree);

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
    // let the user name his or her own files later on because
    // this is honestly a little inefficient lol
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
    int newMap[128][3] = {{0, 0, 0}};

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
    fclose(f);

    // fill up array with nodes for compressed representation
    struct Node * nodeArray[nodeArrayLength];
    int nodeArrayIt = 0;
    long unsigned int i;
    for (i = 0 ; i < 128 ; i++) {
        if (map[i] != 0) {
            newMap[i][2] = map[i];
            nodeArray[nodeArrayIt] = malloc(sizeof(struct Node));
            nodeArray[nodeArrayIt]->c = getChar(i);
            nodeArray[nodeArrayIt]->count = map[i];
            nodeArray[nodeArrayIt]->left = NULL;
            nodeArray[nodeArrayIt]->right = NULL;
            nodeArrayIt++;
        }
    }

    // merge into one overarching tree of nodes
    // O(N^2) - technically O(1) since we have
    // at most 128 nodes, though. also, the time is
    // really closer to 1/2 * N^2 since we have this
    // time complexity from the arithmetic series.

    // to-do: implement a priority queue to handle 
    // this later, maybe as a heap? possible 
    // O(N*lg(N)) improvement if this is done
    int minis[2] = {-1, -1};
    struct Node * toMerge[nodeArrayLength];
    int originalNodeArrayLength = nodeArrayLength;
    printf("%i\n", nodeArrayLength);
    while (nodeArrayLength > 1) {
        int it;
        for (it = 0 ; it < nodeArrayLength ; it++) {
            if (minis[0] == -1) {
                minis[0] = it;
            } else if (nodeArray[it]->count < nodeArray[minis[0]]->count) {
                minis[1] = minis[0];
                minis[0] = it;
            } else if (minis[1] == -1) {
                minis[1] = it;
            } else if (nodeArray[it]->count < nodeArray[minis[1]]->count) {
                minis[1] = it;
            }
            printf("%c %i | %i %i | \n", nodeArray[it]->c, nodeArray[it]->count, minis[0], minis[1]);
        }
        struct Node * mergedNode = malloc(sizeof(struct Node));
        mergedNode->left = nodeArray[minis[0]];
        mergedNode->right = nodeArray[minis[1]];
        mergedNode->c = '\0';
        mergedNode->count = mergedNode->left->count + mergedNode->right->count;
        printf("%c %i, %c %i \n  ",nodeArray[minis[0]]->c,nodeArray[minis[0]]->count, nodeArray[minis[1]]->c, nodeArray[minis[1]]->count);

        int choose = minis[0];
        int other = minis[1];
        if (minis[1] < minis[0]) {
            choose = minis[1];
            other = minis[0];
        }
        // this combines the two minimal nodes and essentially
        // stops considering them; does this by replacing one of
        // the minimal nodes with our merged node, replacing the
        // other with the final node in the window, and then 
        // decreases the window size by one. this effectively deletes
        // both of the minimal nodes without actually removing
        // them from the heap, which would destroy their data
        nodeArray[choose] = mergedNode;
        nodeArray[other] = nodeArray[nodeArrayLength-1];
        nodeArrayLength -= 1;
        minis[0] = minis[1] = -1;
        printf("\n");
    }
    // at this point, nodeArray[0] should be the final
    // Huffman tree that will tell us how to evaluate
    // each character in the compressed file. we're going
    // to write the compressed form of each character to
    // our <fileName>.xyp (compressed) file, as well as
    // the encoding from this tree so that the decompressor
    // can handle it when it is used on <fileName>.xyp

    // first decide how to name output file
    int success = 0;
    for (i = 0; i < strlen(fileName); i++) {
        if (fileName[i] == '.') {
            success = 1;
            break;
        }
    }

    char * newFileName;
    if (!success) {
        newFileName = malloc(strlen(fileName)+4);
        strncpy(newFileName, fileName, strlen(fileName));
        strcpy(newFileName+strlen(fileName), ".xyp");
    } else {
        newFileName = malloc(strlen(fileName));
        strncpy(newFileName, fileName, strlen(fileName)-4);
        strcpy(newFileName+strlen(fileName)-4, ".xyp");
    }

    // testing file output for now
    // need to write binary values to save space

    FILE * output;
    output = fopen(newFileName, "w");
    free(newFileName);


    /* this might work but I'll save it for later
    fwrite(map, sizeof(map), 1, output);
    */

    /* write char counts and recreate full binary
     * tree instead of trying to write the tree
     * itself, since building it doesn't take long 
     * */
    int first = 1;
    for (i = 0; i < 128; i++) {
        if (map[i] > 0) {
            if (!first) {
                char space = ' ';
                fwrite(&space, sizeof(char), 1, output);
             } else {
                first = 0;
             }

            int j;            
            if (i >= 100) { 
                j = 3;
            } else if (i >= 10) {
                j = 2;
            } else {
                j = 1;
            }

            char buf1[j+1];
            sprintf(buf1, "%lu", i);
            buf1[j] = ':';

            fwrite(buf1, sizeof(char), j+1, output);

            int secondBufSize = 1;
            int copy = map[i];
            while (copy/10 > 0) {
                copy /= 10;
                secondBufSize += 1;
            }
            int ogsbs = secondBufSize;

            char * buf = malloc(sizeof(char)*secondBufSize);
            while (secondBufSize > 0) {
                buf[secondBufSize-1] = '0' + (map[i] - (map[i]/10)*10);
                map[i] /= 10;
                secondBufSize -= 1;
            }

            fwrite(buf, sizeof(char), ogsbs, output);
            free(buf);
        }
    }     
    char newline = '\n';
    fwrite(&newline, sizeof(char), 1, output);

    /* now write the actual compressed contents */
    transformMap(newMap, nodeArray[0]); 

    // for each character we read, write its compressed
    // form to the output file by checking newMap
    FILE * input = fopen(fileName, "r");
    line = NULL;
    size_t lineLen;
    unsigned char curByte = 0;
    int curByteSize = 8;
    while (getline(&line, &lineLen, input) != -1) {
        int it;
        for (it = 0; it < strlen(line); it++) {
            char put = line[it];
            int encoding = newMap[put][0];
            int length = newMap[put][1];

            while (length > 0) {
                if (length <= curByteSize) {
                    int offset = curByteSize-length;
                    curByte |= (encoding << offset);
                    curByteSize -= length;
                    if (curByteSize == 0) {
                        fwrite(&curByte, 1, 1, output);
                        curByte = 0;
                        curByteSize = 8;
                    }
                    length = 0;
                } else {
                    // bits to store in the first byte
                    // mask however much of the encoding
                    // we can fit and store it in the 
                    // rest of the first section

                    int preCut = encoding & (((1 << curByteSize)-1) << 
                                            (length-curByteSize));
                    curByte |= (preCut >> (length-curByteSize));
                    encoding &= ((1 << curByteSize)-1);
                    length -= curByteSize;
                    fwrite(&curByte, 1, 1, output);
                    curByte = 0;
                    curByteSize = 8;
                }
            }
        }
    }

    if (curByteSize < 8) {
        fwrite(&curByte, 1, 1, output);
    }

    return 0;
}

void transformMap(int map[128][3], struct Node * huffTree) {
    if (huffTree->left != NULL) {
        transformHelper(map, huffTree->left, 0, 1);
    }
    if (huffTree->right != NULL) {
        transformHelper(map, huffTree->right, 1, 1);
    }

    if (huffTree->c != '\0') {
        map[huffTree->c][0] = 1;
        map[huffTree->c][1] = 1;
    }
}

void transformHelper(int map[128][3], struct Node * huffNode, int mapping, int ct) {
    if (huffNode->c != '\0') {
        map[huffNode->c][0] = mapping;
        map[huffNode->c][1] = ct;
    } else {
        if (huffNode->left != NULL) {
            transformHelper(map, huffNode->left, (mapping << 1), ct+1);
        }
        if (huffNode->right != NULL) {
            transformHelper(map, huffNode->right, ((mapping << 1)+1), ct+1);
        }
    }
}

void printUsageString() {
	printf("./binary_xyphos <input_file_name>\ninput_file_name should be the "
           "name of a text file, and <input_file_name>.xyp shouldn't exist\n");
	exit(1);
}

char getChar(int i) {
    return (char) i;
}

int getInt(char c) {
    return (int) c;
}

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Fill out this structure
struct HashType
{
    struct RecordType* records; // Array of records
    int* occupied; // Array to mark if an index is occupied or not
    int size; // Size of the hash table
};

// Compute the hash function
int hash(int x)
{
    // Your hash function implementation
    return x % 31; // Example hash function (using a constant size of 31)
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    printf("\nRecords in Hash Table:\n");
    for (int i = 0; i < hashSz; ++i)
    {
        if (pHashArray->occupied[i]) // Check if index is occupied
        {
            printf("Index %d -> %d %c %d\n", i, pHashArray->records[i].id, pHashArray->records[i].name, pHashArray->records[i].order);
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    
    // Your hash implementation
    // Create a hash table
    struct HashType hashTable;
    hashTable.size = recordSz; // Set the size of the hash table
    hashTable.records = pRecords; // Store the records in the hash table
    hashTable.occupied = (int*)malloc(recordSz * sizeof(int)); // Allocate memory for the 'occupied' array
    for (int i = 0; i < recordSz; ++i)
    {
        hashTable.occupied[i] = 1; // Initialize all indices as occupied
    }

    // Display records in the hash table
    displayRecordsInHash(&hashTable, recordSz);

    // Free memory allocated for the 'occupied' array
    free(hashTable.occupied);
    
    return 0;
}

#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* records;
};

// Compute the hash function
int hash(int x)
{
    int y = x % 15;
	return y;
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
	for (int i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].records != NULL)
        {
            printf("index %d:  ", i);
            int j = 0;
            while (pHashArray[i].records[j].id != 0)
            {
                printf(" ID: %d NAME: %c ORDER: %d || ", pHashArray[i].records[j].id, pHashArray[i].records[j].name, pHashArray[i].records[j].order);
                j++;
            }
            printf("\n");
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

    struct HashType *array = malloc(sizeof(struct HashType) * 15);
    for (int i = 0; i < 15; ++i)
    {
        array[i].records = NULL;
    }

    for (int i = 0; i < recordSz; ++i)
    {
        int j = 0;
        int k = hash(pRecords[i].order);
        while (array[k].records != NULL && array[k].records[j].id != 0)
        {
            j++;
        }
        array[k].records = (struct RecordType*)realloc(array[k].records, sizeof(struct RecordType) * (j + 2));
        array[k].records[j] = pRecords[i];
        array[k].records[j + 1].id = 0;
    }

    displayRecordsInHash(array, 15);

}

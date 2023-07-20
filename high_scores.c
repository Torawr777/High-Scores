#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ROWS 1000000
#define COLS 5
#define TCOLS 6

/* This program uses the command line as input (argv)
 * to choose standard or custom sort. Make sure to enter
 * 'standard' or 'custom' before running
 */

int compare(const void *a, const void *b) {
	return ( *(int*)b - *(int*)a );
}

// Find the biggest number 
int maxNum(int array[], int n) {
    int max = array[0];

    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

// Radix Sort
void radixsort(int array[], int n) {
    int largest = maxNum(array, n);
 
    // Perform counting sort on elements 
    for (int exp = 1; largest/exp > 0; exp *= 10) {

        // Store count of occurrences in count[]
        int output[n]; 
    	int i, bucket[10] = { 0 };
    	for (i = 0; i < n; i++) {
        	bucket[9-array[i] / exp % 10]++;
    	}
    	for (i = 1; i < 10; i++) {
        	bucket[i] += bucket[i - 1];
    	}
    	// Initialize output array
    	for (i = n-1; i >= 0; i--) {
        	output[--bucket[9-array[i] / exp % 10]] = array[i];
    	}
 
    	// Copy output array to temp
    	for (i = 0; i < n; i++) {
        	array[i] = output[i];
    	}
    }
}


int main(int argc, char const *argv[]) {

	// Check for 'standard' or 'custom' in command line (argv)
	if(strcmp(argv[1], "standard") == 0 || strcmp(argv[1], "custom") == 0) {
		;
	}
	else {
		printf("Invalid input! Enter 'standard' or 'custom'.\n");
		return 0;
	}

	int (*array)[TCOLS];
	array = malloc(sizeof(int[ROWS][TCOLS]));

	//Initialize array elements via stdin
	for(int r = 0; r < ROWS; r++) {
		for(int c = 0; c < COLS; c++) {
			scanf("%d", &array[r][c]);
		}
	}
	// Add all skill exp to get total exp
	int *temp1;
	temp1 = (int*)malloc(ROWS*sizeof(int));

	for(int r = 0; r < ROWS; r++) {
		int sum = 0;
		for(int c = 0; c < COLS; c++) {
			sum = sum + array[r][c];
		}
		temp1[r] = sum;
	}

	//Copy exp sums into array
	for(int r = 0; r < ROWS; r++) {
		array[r][COLS] = temp1[r];
	}
	free(temp1);

	int temp[ROWS];
	int timeStorage[TCOLS];
	for(int n = 0; n < TCOLS; n++) {

		//Time columns seperately
		clock_t start = clock();

		// Move a row into a temp 1d array then sort that
		for(int i = 0; i < ROWS; i++) {
			temp[i] = array[i][n];
		}
		//Determine sorting algorithm to use
		if(strcmp(argv[1], "standard") == 0) {
			qsort(temp, ROWS, sizeof(int), compare);
		}
		else if(strcmp(argv[1], "custom") == 0) {
			//mergeSort(temp, 0, ROWS);
			radixsort(temp, ROWS);
		}
		//Copy sorted temp into array
		for(int k = 0; k < ROWS; k++) {
			array[k][n] = temp[k];
		}
		//Record the time
		double seconds = (double)( clock() - start ) / CLOCKS_PER_SEC;
		double microseconds = seconds * 1000000.0;
		timeStorage[n] = microseconds;
	}

	// Calculate total time
	int total_time = 0;
	for(int k = 0; k < TCOLS; k++) {
		total_time += timeStorage[k];
	}

	FILE* fp = fopen("stdout_file", "w");

	//Chaos 
    //Print breakdancing xp
    fprintf(fp,"\nSKILL_BREAKDANCING\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][0]);
    }
    fprintf(fp,"time taken: %d\n", timeStorage[0]);

    //Print apiculture xp
    fprintf(fp, "\nSKILL_APICULTURE\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][1]);
    }
    fprintf(fp, "time taken: %d\n", timeStorage[1]);

    //Print basket xp
    fprintf(fp, "\nSKILL_BASKET\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][2]);
    }
    fprintf(fp, "time taken: %d\n", timeStorage[2]);

    //Print xbasket xp
    fprintf(fp, "\nSKILL_XBASKET\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][3]);
    }
    fprintf(fp, "time taken: %d\n", timeStorage[3]);

    //Print sword xp
    fprintf(fp, "\nSKILL_SWORD\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][4]);
    }
    fprintf(fp, "time taken: %d\n", timeStorage[4]);

    //Print total xp
    fprintf(fp, "\nTOTAL_XP\n");
    for(int r = 0; r < ROWS; r++) {
    	fprintf(fp, "%d\n", array[r][5]);
    }
    fprintf(fp, "time taken: %d\n", timeStorage[5]);

    fprintf(fp, "\ntotal time taken: %d", total_time);
	fclose(fp);

	free(array);
	return 0;
}

/**
 * @file predprey.cu
 * @brief Predator-prey model using CUDA programing.
 *
 * @author Bennett Lopez (blopez17@georgefox.edu)
 * 2020-11-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curand_kernel.h>
#define MAX_RANGE 64
#define DEFAULT_VAL 0

/**
 * @brief This updates the individual cell in the grid
 *
 * This function accepts grids, and updates a specified cell, using the rules
 * of the simulation.
 *
 * @param grid The grid that is to be compared
 * @param gridcc The carbon copy of the grid
 * @param width The width of the grid
 * @param height The height of the grid
 * @param CurrentCell The current cell
 * @param randNum The random number
 */

__device__ void updateCell(int* grid, int* gridCC, int* width, int* height,
                                                 int currentCell, int randNum) {
    int change = 0;
    int numPreyBreedingAge = 0;
    int numPredBreedingAge = 0;
    int numWhiteSpaces = 0;
    int numPrey = 0;
    int numPredator = 0;
    int modifier = 0;
    int numNeighbors = 0;
    int currentNeighbor;
    int currentSpace = *(grid + currentCell);
    int* currentCCSpace = (gridCC + currentCell);
    int currentSpaceY = currentCell / *width;
    int currentSpaceX = currentCell - (*width * currentSpaceY);
    int neighborColms[8] = {currentSpaceY + 1, currentSpaceY + 1, currentSpaceY + 1,
                            currentSpaceY, currentSpaceY, currentSpaceY - 1, 
                            currentSpaceY - 1, currentSpaceY - 1};
    int neighborRows[8] = {currentSpaceX - 1, currentSpaceX, currentSpaceX + 1, 
                            currentSpaceX + 1, currentSpaceX - 1, currentSpaceX - 1, 
                            currentSpaceX, currentSpaceX + 1};
    // Find the neighbors and the corresponding validity
    for (int i = 0; i < 8; i++) {
        if (neighborRows[i] <= (*width - 1) && neighborRows[i] >= 0 && 
                   neighborColms[i] <= (*height - 1) && neighborColms[i] >= 0) {
            // Get the neighbor type
            currentNeighbor = *(grid + neighborColms[i] * (*width) + 
                                                        neighborRows[i]);
            if (currentNeighbor > 0) {
                numPrey++;
                if (currentNeighbor >= 2) {
                    numPreyBreedingAge++;
                }
            }
            else if (currentNeighbor < 0) {
                numPredator++;
                if (currentNeighbor <= -3) {
                    numPredBreedingAge++;
                }
            }
            else {
                numWhiteSpaces++;
            }
            numNeighbors++;
        }
    } 
    // Get the amount of neighbors per-type
    if (numNeighbors == 3) {
        // is Corner
        modifier = 3;
    }
    else if (numNeighbors == 5) {
        // Is edge
        modifier = 2;
    }
    change = currentSpace;
    if (currentSpace == 0) {
        // If empty space
        if (numPrey >= (4 - modifier)) {
            if (numPreyBreedingAge >= (3 - modifier)) {
                if (numPredator < (4 - modifier)) {
                    // Change to prey if above conditions apply
                    change = 1;
                }
            }
        }
        if (numPredator >= (4 - modifier)) {
            if (numPredBreedingAge >= (3 - modifier)) {
                if (numPrey < (4 - modifier)) {
                    // Change to predator if above conditions apply
                    change = -1;
                }
            }
        }
    }
    else if (currentSpace > 0) {
         //If Prey
        if (numPredator >= (5 - modifier)) {
            change = 0;
        }
        else if (numPrey >= (8 - modifier)) {
            change = 0;
        }
        else {
            // Delete/Increment
            change = change + 1;
            // Die of old age condition
            if (currentSpace >= 10) {
                change = 0;
            }
        }
    }
    else {
        // If preditor
        if (numPredator >= (6 - modifier) && numPrey == 0) {
            change = 0;
        }
        else if (randNum == 1) {
            change = 0;
        }
        else {
            // Delete/Decrement
            (change)--;
            // Die of old age condition
            if ((currentSpace) <= -20) {
                change = 0;
            }
        }
    }
    *currentCCSpace = change;
}

/**
 * @brief This increments the generations, calling the logic to each suqare on
 * the grid
 *
 *
 * @param grid The initial state of the grid to compare the logic
 * @param gridcc The applied changes to the grid logic
 * @param width The max x width of the grid
 * @param height The max y height of the grid
 * @param seed The seed for the RNG
 * @param workPartition The division of the work for the grids
 * @param leftover The leftover from the division of the grids
 * @param numWorkers The number of workers
 */

__global__ void incrementGeneration(int* theGrid, int* workPartition, 
                                int* leftover, int* width, int* height, 
                                int* numWorkers, int* gridCC, int* seed) {
    // blockIdx: The ID of the individual block (0..N)
    // threadIdx: Which thread within the block (0..N)
    // blockDim: How many threads per block (1..N)
        // NOTE: The blockDim is not zero based, but blockIdx is.
    long ID = blockIdx.x * blockDim.x + threadIdx.x;
    long startingIdx = ID * *workPartition;
    long endingIdk = startingIdx + *workPartition - 1;
    long numNodes = *width * *height;
    curandState_t currentState;
    curand_init(*seed + ID, DEFAULT_VAL, DEFAULT_VAL, &currentState);
    int result = curand(&currentState) % MAX_RANGE;
    // If there are more workers than units, then exit
    if (numNodes >= *numWorkers) {
         if (ID + 1 == *numWorkers) {
            endingIdk = endingIdk + *leftover;
        }
        //Increment the generations
        for (int currentIndex = startingIdx; currentIndex <= endingIdk; 
                                                            currentIndex++) {
            updateCell(theGrid, gridCC, width, height, currentIndex, result);
            result = curand(&currentState) % MAX_RANGE;
        }
    }
    else {
        for (int currentIndex = 0; currentIndex <= *width * *height; 
                                                            currentIndex++) {
            *(theGrid + currentIndex) = 44;
        }
    }
}

/**
 * @brief Swaps two elements in the grid
 *
 * @param randX A random x index to swap
 * @param randY A random y index to swap
 * @param i The current x index
 * @param n The current y index
 * @param grid The grid of pred and prey
 * @param gridCC The copy of the grid
 * @param y The max width, used for accessing elements
 */

void swap(int randX, int randY, int i, int n, int* grid, int* gridCC, int y) {
    int element1 = *((grid + randX * (y) ) + randY);
    int element2 = *((grid + i * (y) ) + n);
    *((grid + randX * (y) ) + randY) = element2;
    *((grid + i * (y) ) + n) = element1;
    *((gridCC + randX * (y) ) + randY) = element2;
    *((gridCC + i * (y) ) + n) = element1;
}

/**
 * @brief This function shuffles the populated array
 *
 * @param grid The grid of predators and prey
 * @param gridCC The copy of the grid
 * @param x The max len of the grid
 * @param y The max height of the grid
 */

void shuffleArray(int *grid, int* gridCC, int x, int y) {
    int randX;
    int randY;
    for (int i = 0; i < x; i++) {
        for (int n = 0; n < y; n++) {
            // Get random index and swap;
            randX = (rand() % x);
            randY = (rand() % y);
            swap(randX, randY, i, n, grid, gridCC, y);
        }
    }
}

/**
 * @brief Determines if type is a valid float
 *
 * @param c_float
 * @return If the value is valid float
 */
int isFloat(char* c_float) {
    int isValid = 1;
    int len;
    float tmp;
    int returnValid = sscanf(c_float, "%f %n", &tmp, &len);
    if (returnValid != 1 || c_float[len]) {
        isValid = 0;
    }
    return isValid;
}

/**
 * @brief Determines if type is a valid int
 *
 * @param value
 * @return If the value is valid int
 */
int validInt(char* value) {
    int isValid = 1;
    char *letter;
    int argument = strtol(value, &letter, 10);
    if ((*(letter) != '\0') || argument < 0) {
        isValid = 0;
    }
    return isValid;
}

/**
 * @brief This function validate the input
 *
 * This function does not validate the correctness of CLA, but the type.
 * See initializeVars for content validation.
 *
 * @param numArguments The number of CLA plus one
 * @param arguments The CLA arguments plus the name of the file
 * @return Whether or not the inputs are validated
 */

int inputType(int numArguments, char* arguments[]) {
    int isValid = 1;
    int counter = 1;
    // Go through each CLA and determine if it is the right type
    if (numArguments >= 7 && numArguments <= 9) {
        while (counter < 7 && isValid) {
            if (counter == 1 || counter == 2 || counter == 5 || counter == 6) {
                isValid = validInt(arguments[counter]);
                counter = counter + 1;
            }
            else {
                if (!isFloat(arguments[counter])) {
                    isValid = 0;
                }
                counter = counter + 1;
            }
        }
        // Check to see if there is an optional input, then validate it
        if (numArguments >= 8) {
            isValid = validInt(arguments[7]);
        }
        if (numArguments >= 9) {
            isValid = validInt(arguments[8]);
        }
    }
    else {
        isValid = 0;
    }
    return isValid;
}

/**
 * @brief This method validates the input of the CLI
 *
 * This method takes in the CLI parameters, and validates the content.
 * It then assigns the variables in an array to a more descriptive variable.
 * See validateInput to validate the type
 *
 * @param width The width of the grid
 * @param height The height of the grid
 * @param predProb The probability of predators in the initial grid
 * @param preyProb The probability of prey in the initial grid
 * @param totalGen The total generations to be cycles though
 * @param displayInterval The intervals to display the grid
 * @param arguments The array of CLI arguments.
 * @param numThreads The number of threads
 * @param numBlocks The number of blocks
 * @param numArguments The number of arguments
 * @return The validity of the input
 */

int validateInputValues(int* width, int* height, float* predProb, float* preyProb,
                    int* totalGen, int* displayInterval, int* numThreads, 
                    int* numBlocks, char* arguments[], int numArguments) {
    char* pEnd;
    int returnValue = 1;
    if (inputType(numArguments, arguments)) {
        // Set the variables
        *width = strtol(arguments[1],&pEnd,10);
        *height = strtol(arguments[2],&pEnd,10);
        *predProb = strtof(arguments[3],&pEnd);
        *preyProb = strtof(arguments[4],&pEnd);
        *totalGen = strtol(arguments[5],&pEnd,10);
        *displayInterval = strtol(arguments[6],&pEnd,10);
        if (numArguments >= 7) {
            *numThreads = strtol(arguments[7],&pEnd,10);
        }
        else {
            *numThreads = 1;
        }
        if (numArguments >= 8) {
            *numBlocks = strtol(arguments[8],&pEnd,10);
        }
        else {
            *numBlocks = 1;
        }
        if (*numBlocks <= 0 || *numThreads <= 0) {
            perror("BLOCKS/THREADS BAD VALUE: >= 2");
            returnValue = 0;
        }
        if (*width < 2 || *height < 2) {
            perror("BAD INPUT FOR X and Y: >= 2");
            returnValue = 0;
        }
        if (*preyProb > 1.0 || *predProb > 1.0 || (*preyProb + *predProb) > 1.0) {
            perror("BAD Pred/Prey Probability: > 0.0 && Prey + Pred <= 1.0");
            returnValue = 0;
        }
        if (*totalGen <= 1) {
            perror("Bad Generation Simulation: > 0");
            returnValue = 0;
        }
        if (*displayInterval < 0) {
            perror("Bad Display interval: >= 0");
            returnValue = 0;
        }
    }
    else {
        returnValue = 0;
    }
    return returnValue;
}

/**
 * @brief This method assignes the positions in the initial grid
 *
 * The options are either 0 for empty, 1 for prey and -1 for predator.
 * The probability for each is initially determined by the CLA.
 *
 * @param grid The 2D array to assign the values to
 * @param gridMirror The 2D array that keeps the updates of the grid
 * @param x The max width
 * @param y The max height
 * @param predProb The probability of the predator
 * @param preyProb The probability of the prey
 */

void setupGrid(int *grid, int *gridCC, int x, int y, float *predProb, 
                                                        float *preyProb) {
    int numPrey = (x * y) * *preyProb;
    int numPred = (x * y) * *predProb;
    for (int i = 0; i < x; i++) {
        for (int n = 0; n < y; n++) {
            if (numPrey > 0) {
                *((grid + i * (y) ) + n) = 1;
                *((gridCC + i * (y) ) + n) = 1;
                numPrey = numPrey - 1;
            }
            else if (numPred > 0) {
                *((grid + i * (y) ) + n) = -1;
                *((gridCC + i * (y) ) + n) = -1;
                numPred = numPred - 1;
            }
            else {
                *((grid + i * (y) ) + n) = 0;
                *((gridCC + i * (y) ) + n) = 0;
            }
        }
    }
    shuffleArray(grid, gridCC, x, y);

}

/**
 * @brief Displays the current gen to cout
 *
 * This method displays the current generation to cout, in
 * main is where frequency of display is determined.
 *
 * @param grid The 2D array of the field
 * @param x The max width
 * @param y The mac height
 * @param gen The current generation
 */

void displayGrid(int *grid, int *x, int *y, int gen) {
    const char* spaces[2];
    printf("Generation: %d\n", gen);
    for (int i = 0; i < *x; i++) {
        for (int j = 0; j < *y; j++) {
            if (*((grid + i * (*y) ) + j) < 0) {
                *spaces = " ";
            }
            else {
                *spaces = "  ";
            }
           printf("%s%d ", *spaces, *((grid + i * (*y) ) + j));
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief Displays the current gen to cout in the form of CSV
 *
 * This method displays the current generation to cout, in
 * main is where frequency of display is determined.
 *
 * @param grid The 2D array of the field
 * @param x The max width
 * @param y The mac height
 * @param gen The current generation
 */

void createCSV(int *grid, int *x, int *y, int gen) {
    for (int i = 0; i < *x; i++) {
        for (int j = 0; j < *y; j++) {
           printf("%d,", *((grid + i * (*y) ) + j));
        }
        printf("\n");
    }
}

/**
 * @brief Divide the work between the nodes
 * 
 * @param dividedWork This is the amount of work that is to be divided
 * @param leftover The leftover for the last node
 * @param width The width of the grid
 * @param numWorkers The number of worker nodes
 */
void divideWork(int* dividedWork, int* leftover, int* width, int* height, 
                                                            int* numWorkers) {
    *dividedWork = (*width * *height) / (*numWorkers);
    *leftover = (*width * *height) % (*numWorkers);
}

/**
 * @brief Main entry point of the program.
 *
 * @return The exit status of the program.
 */
int main(int argc, char* argv[]) {
    int* tmpGrid;
    int gridWidth;
    int gridHeight;
    float preyProb;
    float predProb;
    int totalGenerations;
    int displayInterval;
    int numThreads;
    int numBlocks;
    int* ptrGrid;
    int* ptrGridCC;
    int* d_gridCC;
    int* d_grid;
    int* d_work;
    int* d_leftover;
    int* d_gridWidth;
    int* d_gridHeight;
    int* d_numWorkers;
    int isValid = 0;
    int dividedWork;
    int leftover;
    int numWorkers;
    int* d_seed;
    int seed;
    if (validateInputValues(&gridWidth, &gridHeight, &predProb, &preyProb, 
                                &totalGenerations, &displayInterval, &numThreads, 
                                &numBlocks, argv, argc)) {   
        seed = time(NULL);
        if (displayInterval == 0) {
            displayInterval = totalGenerations;
        }
        //Setup the grid
        int grid[gridWidth * gridHeight];
        int gridCC[gridWidth * gridHeight];
        ptrGrid = grid;
        ptrGridCC = gridCC;
        // Setup the grid
        setupGrid(ptrGrid, ptrGridCC, gridWidth, gridHeight, &predProb, &preyProb);
        // Determine the number of threads
        numWorkers = numThreads * numBlocks;
        // Loadbalance the work
        divideWork(&dividedWork, &leftover, &gridWidth, &gridHeight, &numWorkers);
        // Allocate space on the  Device for the seed
        cudaMalloc(&d_seed, sizeof(int));
        cudaMemcpy(d_seed, &seed, sizeof(int), cudaMemcpyHostToDevice);
        // CUDA Transfer GridCC
        cudaMalloc(&d_gridCC, sizeof(int) * gridWidth * gridHeight);
        cudaMemcpy(d_gridCC, gridCC, sizeof(int) * gridWidth * gridHeight,
                                                        cudaMemcpyHostToDevice);
        // CUDA Transfer Grid
        cudaMalloc(&d_grid, sizeof(int) * gridWidth * gridHeight);
        cudaMemcpy(d_grid, grid, sizeof(int) * gridWidth * gridHeight, 
                                                        cudaMemcpyHostToDevice);
        // Transfer the divided workPartition
        cudaMalloc(&d_work, sizeof(int));
        cudaMemcpy(d_work, &dividedWork, sizeof(int), cudaMemcpyHostToDevice);
        // Transfer the leftovers
        cudaMalloc(&d_leftover, sizeof(int));
        cudaMemcpy(d_leftover, &leftover, sizeof(int), cudaMemcpyHostToDevice);
        // Transfer the gridWidth
        cudaMalloc(&d_gridWidth, sizeof(int));
        cudaMemcpy(d_gridWidth, &gridWidth, sizeof(int), cudaMemcpyHostToDevice);
        // Transfer the gridHeight
        cudaMalloc(&d_gridHeight, sizeof(int));
        cudaMemcpy(d_gridHeight, &gridHeight, sizeof(int), cudaMemcpyHostToDevice);
        // Transfer the numWorkers
        cudaMalloc(&d_numWorkers, sizeof(int));
        cudaMemcpy(d_numWorkers, &numWorkers, sizeof(int), cudaMemcpyHostToDevice);
        for (int currentGen = 0; currentGen < totalGenerations; currentGen++) {
            // Display the grid
            if (currentGen == 0 || ((currentGen % displayInterval) == 0)) {
                cudaMemcpy(grid, d_grid, sizeof(int) * gridWidth * gridHeight, 
                                                        cudaMemcpyDeviceToHost);
                //createCSV(ptrGrid, &gridWidth, &gridHeight, currentGen);
            }
            // Send CUDA to do work NOTE: the kernel is asynchronous, but any 
            // calls are added to a queue, so it can be treated as sequential
            incrementGeneration<<<numBlocks, numThreads>>>(d_grid, d_work, 
                                        d_leftover, d_gridWidth, d_gridHeight, 
                                        d_numWorkers, d_gridCC, d_seed);
            cudaMemcpy(&seed, d_seed, sizeof(int), cudaMemcpyDeviceToHost);
            seed = seed + currentGen + 1;
            cudaMemcpy(d_seed, &seed, sizeof(int), cudaMemcpyHostToDevice);
            // Swap the two grids
            tmpGrid = d_grid;
            d_grid = d_gridCC;
            d_gridCC = tmpGrid;
            
        }
        cudaMemcpy(grid, d_grid, sizeof(int) * gridWidth * gridHeight, 
                                                        cudaMemcpyDeviceToHost);
        // Print the grid
        //createCSV(ptrGrid, &gridWidth, &gridHeight, totalGenerations);
        // Free the CUDA Memory
        cudaFree(d_seed);
        cudaFree(d_gridCC);
        cudaFree(d_grid);
        cudaFree(d_work);
        cudaFree(d_leftover);
        cudaFree(d_gridWidth);
        cudaFree(d_gridHeight);
        cudaFree(d_numWorkers);
    }
    else {
         perror("BAD INPUT:\n -GridWidth [int], -GridLen [int] -PredProb" 
                "[float] - PreyProb [float] -Generations [int] -DisplayInterv"
                "[int] -NumberOfThreadsPerBlock [int] -NumberCUDABlocks [int]\n");
        isValid = 1;
    }
    return isValid;
}

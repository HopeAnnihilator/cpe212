int generate_random_integer_for_sorting() {
    // use assembly to generate random integer then take value in register and store to variable
    asm ("call rand");
    register int randint asm("eax");

    // equivalent of 
    // int randint = rand();
    
    return randint;
}

void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    // create filestream and open file
    ifstream input;
    input.open(imagefile.c_str());
    string theLinesWithActualDataOnThemINeedToUse;

    // i dont know why i did but whatever, dump the first 2 lines
    string dumpTheFirstTwoLines;
    for (int i = 0; i < 2; i++) {
        getline(input, dumpTheFirstTwoLines);
    }

    // read image data and save to array
    for (int i = 0; i < MAXROWS; i++) {
        getline(input, theLinesWithActualDataOnThemINeedToUse);
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = theLinesWithActualDataOnThemINeedToUse[j * 2] - 48;
        }
    }

    // close filestream 
    input.close();
}

void write_array(int arrayToCopy[MAXROWS][MAXCOLS], int arrayToHold[MAXROWS][MAXCOLS]) {
    // swap values in array
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            arrayToHold[i][j] = arrayToCopy[i][j];
        }
    }
}

void sort_array(int tempArray[MAXROWS][MAXCOLS], int check){
    // make the computer guess two rows to swap
    int swapThis = generate_random_integer_for_sorting() % MAXROWS;
    int withThis = generate_random_integer_for_sorting() % MAXROWS;

    // make sure random ints arent the same
    if (swapThis == withThis) {
        return;
    }

    // swap some of the stuff for some reason i dont really remember why
    // oh this is the horizontal and vertical flip
    for(int i = 0; i < MAXROWS; i++) {
        switch(check) {
            case 0:
                tempArray[i][swapThis] = tempArray[i][swapThis] ^ tempArray[i][withThis];
                tempArray[i][withThis] = tempArray[i][swapThis] ^ tempArray[i][withThis];
                tempArray[i][swapThis] = tempArray[i][swapThis] ^ tempArray[i][withThis];
                break;
            case 1:
                tempArray[swapThis][i] = tempArray[swapThis][i] ^ tempArray[withThis][i];
                tempArray[withThis][i] = tempArray[swapThis][i] ^ tempArray[withThis][i];
                tempArray[swapThis][i] = tempArray[swapThis][i] ^ tempArray[withThis][i];
                break;
            default:
                return;
        }
    }
}

bool check_if_sorted(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int check) {
    // a function to check if horizontal/vertical flips are successful or if the computer has to try again
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            // if any values dont match return false
            switch(check) {
                case 0:
                    if (tempArray[i][j] != image[i][9 - j]) {
                        return false;
                    }
                    break;
                case 1:
                    if (tempArray[i][j] != image[9 - i][j]) {
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
    }
    // if everything matches return true
    return true;
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    
    // clone array 
    write_array(image, tempArray);

    // attempt to horizontally flip array until successful
    while (true) {
        sort_array(tempArray, 0);
        bool check = check_if_sorted(image, tempArray, 0);
        if (check) {
            break;
        }
    }
    
    // write temp array to original array and return
    write_array(tempArray, image);
    return;
}

void FlipVertical(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];

    // clone array
    write_array(image, tempArray);

    // attempt to vertically flip array until successful
    while (true) {
        sort_array(tempArray, 1);
        bool check = check_if_sorted(image, tempArray, 1);
        if (check) {
            break;
        }
    }

    // write temp array to original array and return
    write_array(tempArray, image);
    return;
}

bool is_corner(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int mutationArray[5][5], int corner) {
    // check if permutation matches a corner rotation
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            switch (corner) {
                case 0:
                    if (image[i][j] != mutationArray[j][5 - i - 1]) {
                        return false;
                    }
                    break;
                case 1:
                    if (image[i][5 + j] != mutationArray[j][5 - i - 1]) {
                        return false;
                    }
                    break;
                case 2:
                    if (image[5 + i][5 + j] != mutationArray[j][5 - i - 1]) {
                        return false;
                    }
                    break;
                case 3:
                    if (image[5 + i][j] != mutationArray[j][5 - i - 1]) {
                        return false;
                    }
                    break;
                case 4:
                    if (image[i][j] != mutationArray[5 - j - 1][i]) {
                        return false;
                    }
                    break;
                case 5:
                    if (image[i][5 + j] != mutationArray[5 - j - 1][i]) {
                        return false;
                    }
                    break;
                case 6:
                    if (image[5 + i][5 + j] != mutationArray[5 - j - 1][i]) {
                        return false;
                    }
                    break;
                case 7:
                    if (image[5 + i][j] != mutationArray[5 - j - 1][i]) {
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }
    }
    // if permutation matches a corner rotation, write to appropriate corner
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            switch (corner) {
                case 0:
                    tempArray[i][5 + j] = mutationArray[i][j];
                    break;
                case 1:
                    tempArray[5 + i][5 + j] = mutationArray[i][j];
                    break;
                case 2:
                    tempArray[5 + i][j] = mutationArray[i][j];
                    break;
                case 3:
                    tempArray[i][j] = mutationArray[i][j];
                    break;
                case 4:
                    tempArray[5 + i][j] = mutationArray[i][j];
                    break;
                case 5:
                    tempArray[i][j] = mutationArray[i][j];
                    break;
                case 6:
                    tempArray[i][5 + j] = mutationArray[i][j];
                    break;
                case 7:
                    tempArray[5 + i][5 + j] = mutationArray[i][j];
                    break;
                default:
                    return false;
            }
        }
    }

    // return successful
    return true;
}

// move locations for generating permutations
void movespot (int *x, int *y) {
    if (*y > 1) {
        *y += -1;
    } else {
        *y = 5;
        *x += -1;
    }
}

void mutate(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int mutationArray[5][5], int direction) {
    // create all permutations of a 5x5 array
    // use count to find if all corners are found and return quickly
    int count = 0;
    bool success = false;
    
    // test 0 array as corner
    for (int i = 0; i < 4; i++) {
        success = is_corner(image, tempArray, mutationArray, i + direction);
        if (success) {
            count++;
        }
    }

    // generate permutations
    int x = 5;
    int y = 5;
    while (x > 0) {
        if (count == 4) {
            // if all corners found, exit
            break;
        }
        // i dont remember how this works i copied it from a project i did years ago
        else if (mutationArray[x - 1][y -1] == 1) {
            mutationArray[x - 1][y -1] = 0;
            movespot(&x, &y);
        } else {
            mutationArray[x - 1][y -1] = 1;
            for (int i = 0; i < 4; i++) {
                success = is_corner(image, tempArray, mutationArray, i + direction);
                if (success) {
                    count++;
                }
            }
            x = 5;
            y = 5;
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    // create a 5x5, 0 array to work with
    int mutationArray[5][5];
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                mutationArray[i][j] = 0;
            }
        }
    // generate all permutations of 5x5 array and test if image rotates
    mutate(image, tempArray, mutationArray, 0);

    // write solutionn to image
    write_array(tempArray, image);
}

void RotateCCW(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    // create a 5x5, 0 array to work with
    int mutationArray[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mutationArray[i][j] = 0;
        }
    }
    // generate all permutations of 5x5 array and test if image rotates
    mutate(image, tempArray, mutationArray, 4);

    // write solutionn to image
    write_array(tempArray, image);
}


int check_accuracy(int image[MAXROWS][MAXCOLS], int clone[MAXROWS][MAXCOLS]) {
    // check how closely the tranposed tempArray relates to the original array
    int accuracyTotal = 0;

    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            if (image[i][j] == clone[j][i]) {
                accuracyTotal++;
            }
        }
    }
    // return how many values matched
    return accuracyTotal;
}

void swap_places(int tempArray[MAXROWS][MAXCOLS], int row1, int col1, int row2, int col2) {
    // randomly swap 2 values in the temp array
    if (row1 == row2 && col1 == col2) {
        return;
    }
    tempArray[row1][col1] = tempArray[row1][col1] ^ tempArray[row2][col2];
    tempArray[row2][col2] = tempArray[row1][col1] ^ tempArray[row2][col2];
    tempArray[row1][col1] = tempArray[row1][col1] ^ tempArray[row2][col2];
}



void Transpose(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    // create tempArray
    write_array(image, tempArray);

    // placeholder variables for use
    int accuracy = 0;
    int prevAccuracy = 100;
    int row1, col1, row2, col2;
    while(accuracy != 100) {
        // check how closely images relate
        prevAccuracy = check_accuracy(image, tempArray);
        
        // generate 4 random integers
        row1 = generate_random_integer_for_sorting() % MAXROWS;
        col1 = generate_random_integer_for_sorting() % MAXROWS;
        row2 = generate_random_integer_for_sorting() % MAXROWS;
        col2 = generate_random_integer_for_sorting() % MAXROWS;

        // swap the two values using random integers
        swap_places(tempArray, row1, col1, row2, col2);

        // check current accuracy
        accuracy = check_accuracy(image, tempArray);

        // if array is less correct, undo
        if (accuracy < prevAccuracy) {
            swap_places(tempArray, row1, col1, row2, col2);
        }
    }

    // write temp array to original array
    write_array(tempArray, image);
}

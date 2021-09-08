int generate_random_integer_for_sorting() {
    asm ("call rand");
    register int randint asm("eax");
    //int randint = rand();
    return randint;
}


void sort_array(int arrayToSort[MAXROWS][MAXCOLS], int check){
    //guess two rows to swap
    int swapThis = generate_random_integer_for_sorting() % MAXROWS;
    int withThis = generate_random_integer_for_sorting() % MAXROWS;

    //arrays to temporarily store rows
    int arrayToSwap[MAXCOLS];
    int arrayToMove[MAXCOLS];

    //fill placeholders
    for (int i = 0; i < MAXCOLS; i++) {
        switch(check) {
            case 0:
                arrayToSwap[i] = arrayToSort[i][swapThis];
                arrayToMove[i] = arrayToSort[i][withThis];
                break;
            case 1:
                arrayToSwap[i] = arrayToSort[swapThis][i];
                arrayToMove[i] = arrayToSort[withThis][i];
                break;
            default:
                return;
        }
    }

    //swap the rows in real array
    for (int i = 0; i < MAXCOLS; i++) {
        switch(check) {
            case 0:
                arrayToSort[i][swapThis] = arrayToMove[i];
                arrayToSort[i][withThis] = arrayToSwap[i];
                break;
            case 1:
                arrayToSort[swapThis][i] = arrayToMove[i];
                arrayToSort[withThis][i] = arrayToSwap[i];
                break;
            default:
                return;
        }
    }

}

void print_array(int arrayToPrint[MAXROWS][MAXCOLS]) {
    for (int j = 0; j < MAXROWS; j++) {
        for (int i = 0; i < MAXCOLS; i++) {
            cout << arrayToPrint[j][i];
        }
        cout << endl;
    }
    cout << endl << endl;
}


void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    ifstream input;
    input.open(imagefile.c_str());
    string theLinesWithActualDataOnThemINeedToUse;

    string dumpTheFirstTwoLines;
    for (int i = 0; i < 2; i++) {
        getline(input, dumpTheFirstTwoLines);
    }

    //read image and save to array
    for (int i = 0; i < MAXROWS; i++) {
        getline(input, theLinesWithActualDataOnThemINeedToUse);
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = theLinesWithActualDataOnThemINeedToUse[j * 2] - 48;
        }
    }
}

bool check_if_sorted(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int check) {
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
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
    return true;
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    //read by columns, clone array
    for (int j = 0; j < MAXROWS; j++) {
        for (int i = 0; i < MAXCOLS; i++) {
            tempArray[i][j] = image[i][j];
        }
    }
    while (true) {
        sort_array(tempArray, 0);
        bool check = check_if_sorted(image, tempArray, 0);
        if (check) {
            break;
        }
    }
    for (int j = 0; j < MAXROWS; j++) {
        for (int i = 0; i < MAXCOLS; i++) {
            image[i][j] = tempArray[i][j];
        }
    }
    return;
}

void FlipVertical(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];

    //read by row, clone array
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            tempArray[i][j] = image[i][j];
        }
    }

    while (true) {
        sort_array(tempArray, 1);
        bool check = check_if_sorted(image, tempArray, 1);
        if (check) {
            break;
        }
    }
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = tempArray[i][j];
        }
    }
    return;
}


void movespot (int *x, int *y) {
    if (*y > 1) {
        *y += -1;
    } else {
        *y = 5;
        *x += -1;
    }
}


bool is_corner(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int mutationArray[5][5], int corner) {
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
    //print_array_5(mutationArray);
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
    return true;
}

void mutate(int image[MAXROWS][MAXCOLS], int tempArray[MAXROWS][MAXCOLS], int mutationArray[5][5], int direction) {
    int count = 0;
    bool success = false;
    for (int i = 0; i < 4; i++) {
        success = is_corner(image, tempArray, mutationArray, i + direction);
        if (success) {
            count++;
        }
    }
    int x = 5;
    int y = 5;
    while (x > 0) {
        if (count == 4) {
            break;
        }
        else if (mutationArray[x - 1][y -1] == 1) {
            mutationArray[x - 1][y -1] = 0;
            movespot(&x, &y);
        } else {
            mutationArray[x - 1][y -1] = 1;
            //print_array_4(mutationArray);
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
    int mutationArray[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mutationArray[i][j] = 0;
        }
    }
    mutate(image, tempArray, mutationArray, 0);
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = tempArray[i][j];
        }
    }
}

void RotateCCW(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    int mutationArray[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mutationArray[i][j] = 0;
        }
    }
    mutate(image, tempArray, mutationArray, 4);
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = tempArray[i][j];
        }
    }
}


int check_accuracy(int image[MAXROWS][MAXCOLS], int clone[MAXROWS][MAXCOLS]) {
    int accuracyTotal = 0;

    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            if (image[i][j] == clone[j][i]) {
                accuracyTotal++;
            }
        }
    }
    return accuracyTotal;
}

void swap_places(int tempArray[MAXROWS][MAXCOLS], int randint1, int randint2, int randint3, int randint4) {
    int item1 = tempArray[randint1][randint2];
    int item2 = tempArray[randint3][randint4];
    tempArray[randint1][randint2] = item2;
    tempArray[randint3][randint4] = item1;
}



void Transpose(int image[MAXROWS][MAXCOLS]) {
    int tempArray[MAXROWS][MAXCOLS];
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            tempArray[i][j] = image[i][j];
        }
    }
    int accuracy = 0;
    int prevAccuracy = 100;
    int randint1, randint2, randint3, randint4;
    while(accuracy != 100) {
        accuracy = check_accuracy(image, tempArray);
        prevAccuracy = accuracy;
        randint1 = generate_random_integer_for_sorting() % MAXROWS;
        randint2 = generate_random_integer_for_sorting() % MAXROWS;
        randint3 = generate_random_integer_for_sorting() % MAXROWS;
        randint4 = generate_random_integer_for_sorting() % MAXROWS;
        swap_places(tempArray, randint1, randint2, randint3, randint4);
        accuracy = check_accuracy(image, tempArray);
        if (accuracy <= prevAccuracy) {
            swap_places(tempArray, randint1, randint2, randint3, randint4);
            prevAccuracy = accuracy;
        }
    }
    for (int i = 0; i < MAXROWS; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = tempArray[i][j];
        }
    }
}

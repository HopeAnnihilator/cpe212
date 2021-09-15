void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    // create filestream and open file
    ifstream input;
    input.open(imagefile.c_str());
    string data;

    // dump the first two lines, headers
    for (int i = 0; i < 2; i++) {
        getline(input, data);
    }

    // read image data and save to array
    for (int row = 0; row < MAXROWS; row++) {
        getline(input, data);
        for (int col = 0; col < MAXCOLS; col++) {
            image[row][col] = data[col * 2] - 48;
        }
    }

    // close filestream
    input.close();
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS; row++) {
        for (int col=0; col < MAXCOLS / 2; col++) {
            image[row][col] = image[row][col] ^ image[row][9 - col];
            image[row][9 - col] = image[row][col] ^ image[row][9 - col];
            image[row][col] = image[row][col] ^ image[row][9 - col];
        }
    }
}

void FlipVertical(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS / 2; row++) {
        for (int col=0; col < MAXCOLS; col++) {
            image[row][col] = image[row][col] ^ image[9 - row][col];
            image[9 - row][col] = image[row][col] ^ image[9 - row][col];
            image[row][col] = image[row][col] ^ image[9 - row][col];
        }
    }
}


void Transpose(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS - 1; row++) {
        for (int col = row + 1; col < MAXROWS; col++) {
            image[row][col] = image[row][col] ^ image[col][row];
            image[col][row] = image[row][col] ^ image[col][row];
            image[row][col] = image[row][col] ^ image[col][row];
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    for (int row = 0; row < MAXROWS / 2; row++) {
        for (int col = 0; col < MAXCOLS / 2; col++) {
            image[row][col] = image[row][col] ^ image[row][9 - col]; 
            image[row][9 - col] = image[row][col] ^ image[row][9 - col]; 
            image[row][col] = image[row][col] ^ image[row][9 - col]; 
            image[row][col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[9 - row][9 - col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[row][col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[row][col] = image[row][col] ^ image[9 - row][col]; 
            image[9 - row][col] = image[row][col] ^ image[9 - row][col]; 
            image[row][col] = image[row][col] ^ image[9 - row][col]; 
        }
    }
}

void RotateCCW(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS / 2; row++) {
        for (int col = 0; col < MAXCOLS / 2; col++) {
            image[row][col] = image[row][col] ^ image[9 - row][col]; 
            image[9 - row][col] = image[row][col] ^ image[9 - row][col]; 
            image[row][col] = image[row][col] ^ image[9 - row][col]; 
            image[row][col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[9 - row][9 - col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[row][col] = image[row][col] ^ image[9 - row][9 - col]; 
            image[row][col] = image[row][col] ^ image[row][9 - col]; 
            image[row][9 - col] = image[row][col] ^ image[row][9 - col]; 
            image[row][col] = image[row][col] ^ image[row][9 - col]; 
        }
    }
}

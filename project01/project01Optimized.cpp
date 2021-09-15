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
    for (int i = 0; i < MAXROWS; i++) {
        getline(input, data);
        for (int notJ = 0; notJ < MAXCOLS; notJ++) {
            image[i][notJ] = data[notJ * 2] - 48;
        }
    }

    // close filestream
    input.close();
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]){
    for (int i=0; i < MAXROWS; i++) {
        for (int notJ=0; notJ < MAXCOLS / 2; notJ++) {
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ];
            image[i][9 - notJ] = image[i][notJ] ^ image[i][9 - notJ];
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ];
        }
    }
}

void FlipVertical(int image[MAXROWS][MAXCOLS]){
    for (int i=0; i < MAXROWS / 2; i++) {
        for (int notJ=0; notJ < MAXCOLS; notJ++) {
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ];
            image[9 - i][notJ] = image[i][notJ] ^ image[9 - i][notJ];
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ];
        }
    }
}


void Transpose(int image[MAXROWS][MAXCOLS]){
    for (int i = 0; i < MAXROWS - 1; i++) {
        for (int notJ = i + 1; notJ < MAXROWS; notJ++) {
            image[i][notJ] = image[i][notJ] ^ image[notJ][i];
            image[notJ][i] = image[i][notJ] ^ image[notJ][i];
            image[i][notJ] = image[i][notJ] ^ image[notJ][i];
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    for (int i = 0; i < MAXROWS / 2; i++) {
        for (int notJ = 0; notJ < MAXCOLS / 2; notJ++) {
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
            image[i][9 - notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[9 - i][9 - notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
            image[9 - i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
        }
    }
}

void RotateCCW(int image[MAXROWS][MAXCOLS]){
    for (int i = 0; i < MAXROWS / 2; i++) {
        for (int notJ = 0; notJ < MAXCOLS / 2; notJ++) {
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
            image[9 - i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[9 - i][9 - notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[9 - i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
            image[i][9 - notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
            image[i][notJ] = image[i][notJ] ^ image[i][9 - notJ]; 
        }
    }
}

void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    // create filestream and open file
    ifstream input;
    input.open(imagefile.c_str());
    string data;

    // dump the first two lines
    for (int i = 0; i < 2; i++) {
        getline(input, data);
    }

    // read image data and save to array
    for (int i = 0; i < MAXROWS; i++) {
        getline(input, data);
        for (int j = 0; j < MAXCOLS; j++) {
            image[i][j] = data[j * 2] - 48;
        }
    }

    // close filestream
    input.close();
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]){
    for (int i=0; i < MAXROWS; i++) {
        for (int j=0; j < MAXCOLS / 2; j++) {
            image[i][j] = image[i][j] ^ image[i][9 - j];
            image[i][9 - j] = image[i][j] ^ image[i][9 - j];
            image[i][j] = image[i][j] ^ image[i][9 - j];
        }
    }
}

void FlipVertical(int image[MAXROWS][MAXCOLS]){
    for (int i=0; i < MAXROWS / 2; i++) {
        for (int j=0; j < MAXCOLS; j++) {
            image[i][j] = image[i][j] ^ image[9 - i][j];
            image[9 - i][j] = image[i][j] ^ image[9 - i][j];
            image[i][j] = image[i][j] ^ image[9 - i][j];
        }
    }
}


void Transpose(int image[MAXROWS][MAXCOLS]){
    for (int i = 0; i < MAXROWS - 1; i++) {
        for (int j = i + 1; j < MAXROWS; j++) {
            image[i][j] = image[i][j] ^ image[j][i];
            image[j][i] = image[i][j] ^ image[j][i];
            image[i][j] = image[i][j] ^ image[j][i];
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    Transpose(image);
    FlipHorizontal(image);
}

void RotateCCW(int image[MAXROWS][MAXCOLS]){
    Transpose(image);
    FlipVertical(image);
}

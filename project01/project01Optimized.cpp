void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    // create filestream and open file
    ifstream input;
    input.open(imagefile.c_str());
    string inputData;

    // dump the first two lines, headers
    for (int i = 0; i < 2; i++) {
        getline(input, inputData);
    }

    // read image data and save to array
    for (int row = 0; row < MAXROWS; ++row) {
        getline(input, inputData);
        for (int col = 0; col < MAXCOLS; ++col) {
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + col] = inputData[col * 2] - 48;
        }
    }

    // close filestream
    input.close();
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS; ++row) {
        for (int col = 0; col < MAXCOLS / 2; ++col) {
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]);
        }
    }
}

void FlipVertical(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS / 2; ++row) {
        for (int col = 0; col < MAXCOLS; ++col) {
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]);
        }
    }
}


void Transpose(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS; ++row) {
        for (int col = row + 1; col < MAXROWS; ++col) {
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[col * 10 + row]);
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    for (int row = 0; row < MAXROWS / 2; ++row) {
        for (int col = 0; col < MAXCOLS / 2; ++col) {
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]);
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]);
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]);
        }
    }
}

void RotateCCW(int image[MAXROWS][MAXCOLS]){
    for (int row = 0; row < MAXROWS / 2; ++row) {
        for (int col = 0; col < MAXCOLS / 2; ++col) {
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]);
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]);
            swap((&image[0][0])[row * 10 + col], (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]);
        }
    }
}

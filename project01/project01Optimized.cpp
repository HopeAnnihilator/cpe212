void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS]) {
    // create filestream and open file
    ifstream input;
    input.open(imagefile.c_str());
    string data;

    // dump the first two lines, headers
    for (int i = 0; i < 2; i++) {
        input.ignore (numeric_limits<streamsize>::max(), '\n' );
    }

    // read image data and save to array
    for (int row = MAXROWS - 1; row >= 0; row--) {
        getline(input, data);
        for (int col = MAXCOLS - 1; col >= 0; col--) {
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + col] = data[col * 2] - 48;
        }
    }

    // close filestream
    input.close();
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS]){
    for (int row = MAXROWS - 1; row >= 0; row--) {
        for (int col = MAXCOLS / 2; col >= 0; col--) {
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)];
            (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)];
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)];
        }
    }
}

void FlipVertical(int image[MAXROWS][MAXCOLS]){
    for (int row = MAXROWS / 2; row >= 0; row--) {
        for (int col = MAXCOLS - 1; col >= 0; col--) {
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col];
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col];
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col];
        }
    }
}


void Transpose(int image[MAXROWS][MAXCOLS]){
    for (int row = MAXROWS - 1; row >= 0; row--) {
        for (int col = row + 1; col < MAXROWS; col++) {
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ image[col][row];
            image[col][row] = (&image[0][0])[row * 10 + col] ^ image[col][row];
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ image[col][row];
        }
    }
}

void RotateCW(int image[MAXROWS][MAXCOLS]) {
    for (int row = MAXROWS / 2; row >= 0; row--) {
        for (int col = MAXCOLS / 2; col >= 0; col--) {
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
        }
    }
}

void RotateCCW(int image[MAXROWS][MAXCOLS]){
    for (int row = MAXROWS / 2; row >= 0; row--) {
        for (int col = MAXCOLS / 2; col >= 0; col--) {
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + col]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[(MAXROWS - 1 - row) * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
            (&image[0][0])[row * 10 + col] = (&image[0][0])[row * 10 + col] ^ (&image[0][0])[row * 10 + (MAXCOLS - 1 -col)]; 
        }
    }
}


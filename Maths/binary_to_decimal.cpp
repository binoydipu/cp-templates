ll binaryToDecimal(string &binaryStr) {
    ll result = 0;
    int length = binaryStr.size();
    for (int i = 0; i < length; i++) {
        if (binaryStr[i] == '1') {
            result = result * 2 + 1;
        }
        else if (binaryStr[i] == '0') {
            result = result * 2;
        }
    }
    return result;
}
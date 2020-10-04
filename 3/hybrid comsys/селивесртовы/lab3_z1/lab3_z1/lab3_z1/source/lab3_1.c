int lab1_1( char a, char b, char c, char d) {
#pragma HLS INTERFACE ap_ctrl_none port=return
int y;
y = a*b+c+d;
return y;
}

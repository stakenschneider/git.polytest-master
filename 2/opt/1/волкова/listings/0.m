clc; clearvars

f1 = @(X) 3000*X(1)+2000*X(2);
f2 = @(X) 5500*X(3) + 3000*X(4);
f3 = @(X) 6 - X(1) - 2*X(2) - X(3) - 2*X(4) ;

z1 = @(N) -f1(N); 
z2 = @(N) -f2(N); 

% restrictions
A = [1,2,1,2;
    2,1,2,1;
    1,-1,1,- 1;
    1800 , 1200 , -2200 , -1200];
b = [6; 8; 4; 0];
lb = [0; 0; 0; 0];

% optimize
[x_1, z1_opt] = fmincon(z1, lb, A, b, [], [], lb,[], [],optimset('Display','iter'))
[x_2, z2_opt] = fmincon(z2, lb, A, b, [], [], lb,[], [],optimset('Display','iter'))
[x_3, f3_opt] = fmincon(f3, lb, A, b, [], [], lb,[], [],optimset('Display','iter'))
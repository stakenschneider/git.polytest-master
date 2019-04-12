clear all;
close all; 
clc;
format long g;

% 1 / F1 -> min
mF1 = @(X) 1 / (60 * X(1) + 300 * X(2) + 2000 * X(3));
% 1 / F2 -> min
mF2 = @(X) 1 / ((0.1 * X(1) + 10 * X(2) + 70 * sqrt(X(3))) ^ 1.5);
% F3 -> min
pF3 = @(X) 30 * X(1) + 100 * X(2) + 220 * X(3);
% F4 -> min
pF4 = @(X) log(20 * X(1) + 3 * X(2) + 0.01 * X(3));
% 1 / F5 -> min
mF5 = @(X) 1 / ((1 / mF1(X)) / (X(1) + X(2) + X(3)));
% 1 / F6 -> min
mF6 = @(X) 1 / (((1 / mF1(X)) + (1 / mF2(X))) - (pF3(X) + pF4(X)));

rF1 = 13940;
rF2 = 7258.939;
rF3 = 2660;
rF4 = 6.613;
rF5 = 198.485;
rF6 = 16501.964;

A = [1, 0, 0;
    -1, 0, 0;
     0, 1, 0;
     0, -1, 0;
     0, 0, 1;
     0, 0, -1;
     1, 1, 1];
 
B = [70;
     -35;
     30;
     -15;
     1;
     -0.5;
     80];

Aeq = [];
Beq = [];

S = [35; 15; 0.5];

[xS, resultS] = fminimax(@m4f, S, A, B, Aeq, Beq);

formatter = '-- FS --\n%s\n%s\n%s\n%s\n\n';
s1 = sprintf('FS = (%.3f, %.3f, %.3f, %.3f, %.3f)', resultS(2:6));
s2 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', xS, sum(xS));
s3 = sprintf('F2 = %.3f, F3 = %.3f, F4 = %.3f, F5 = %.3f, F6 = %.3f', 1 / mF2(xS), pF3(xS), pF4(xS), 1 / mF5(xS), 1 / mF6(xS));
s4 = sprintf('F2/rF2 = %.3f%%, F3/rF3 = %.3f%%, F4/rF4 = %.3f%%, F5/rF5 = %.3f%%, F6/rF6 = %.3f%%', (1 / mF2(xS)) / rF2 * 100, pF3(xS) / rF3 * 100, pF4(xS) / rF4 * 100, (1 / mF5(xS)) / rF5 * 100, (1 / mF6(xS)) / rF6 * 100);
fprintf(formatter, s1, s2, s3, s4);




clear all;
close all; 
clc;
format long g;

% -F7 -> min
mF7 = @(X) -(30 * X(1) + 200 * X(2) + 1780 * X(3));
% -F8 -> min
mF8 = @(X) -(X(1) + 10 * X(3));
% F9 -> min
pF9 = @(X) X(1) + 2 * X(2);

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

[x7, result7] = fmincon(mF7, S, A, B, Aeq, Beq);

formatter = '-- F7 max --\n%s\n%s\n\n';
s1 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x7, sum(x7));
s2 = sprintf('!F7 = %.3f, F8 = %.3f, F9 = %.3f', -result7, -mF8(x7), pF9(x7)); 
fprintf(formatter, s1, s2);




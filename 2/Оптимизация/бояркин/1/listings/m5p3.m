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

K = 0.85

rF7 = 9250;
rF8 = 67.162;

A = [1, 0, 0;
    -1, 0, 0;
     0, 1, 0;
     0, -1, 0;
     0, 0, 1;
     0, 0, -1;
     1, 1, 1;
     -30, -200, -1780;
     -1, 0, -10];
 
B = [70;
     -35;
     30;
     -15;
     1;
     -0.5;
     80;
     -rF7 * K;
     -rF8 * K];

Aeq = [];
Beq = [];

S = [35; 15; 0.5];

[x9, result9] = fmincon(pF9, S, A, B, Aeq, Beq);

fprintf('%.3f >= F7 >= %.2f * %.3f\n', rF7, K, rF7);
fprintf('%.3f >= F7 >= %.3f\n\n', rF7, rF7 * K);

fprintf('%.3f >= F8 >= %.2f * %.3f\n', rF8, K, rF8);
fprintf('%.3f >= F8 >= %.3f\n\n', rF8, rF8 * K);

formatter = '-- F9 max --\n%s\n%s\n\n';
s1 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x9, sum(x9));
s2 = sprintf('F7 = %.3f, F8 = %.3f, !F9 = %.3f', -mF7(x9), -mF8(x9), result9); 
fprintf(formatter, s1, s2);
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

A = [1, 0, 0;
    -1, 0, 0;
     0, 1, 0;
     0, -1, 0;
     0, 0, 1;
     0, 0, -1;
     1, 1, 1;
     -30, -200, -1780];
 
B = [70;
     -35;
     30;
     -15;
     1;
     -0.5;
     80;
     -rF7 * K];

Aeq = [];
Beq = [];

S = [35; 15; 0.5];

[x8, result8] = fmincon(mF8, S, A, B, Aeq, Beq);

fprintf('%.3f >= F7 >= %.1f * %.3f\n', rF7, K, rF7);
fprintf('%.3f >= F7 >= %.3f\n\n', rF7, rF7 * K);

formatter = '-- F8 max --\n%s\n%s\n\n';
s1 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x8, sum(x8));
s2 = sprintf('F7 = %.3f, !F8 = %.3f, F9 = %.3f', -mF7(x8), -result8, pF9(x8)); 
fprintf(formatter, s1, s2);
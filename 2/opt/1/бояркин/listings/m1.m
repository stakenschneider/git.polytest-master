clear all;
close all; 
clc;
format long g;

% -F1 -> min
mF1 = @(X) -(60 * X(1) + 300 * X(2) + 2000 * X(3));
% -F2 -> min
mF2 = @(X) -((0.1 * X(1) + 10 * X(2) + 70 * sqrt(X(3))) ^ 1.5);
% F3 -> min
pF3 = @(X) 30 * X(1) + 100 * X(2) + 220 * X(3);
% F4 -> min
pF4 = @(X) log(20 * X(1) + 3 * X(2) + 0.01 * X(3));
% -F5 -> min
mF5 = @(X) -((-mF1(X)) / (X(1) + X(2) + X(3)));
% -F6 -> min
mF6 = @(X) -(((-mF1(X)) + (-mF2(X))) - (pF3(X) + pF4(X)));

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

[x1, result1] = fmincon(mF1, S, A, B, Aeq, Beq);
[x2, result2] = fmincon(mF2, S, A, B, Aeq, Beq);
[x3, result3] = fmincon(pF3, S, A, B, Aeq, Beq);
[x4, result4] = fmincon(pF4, S, A, B, Aeq, Beq);
[x5, result5] = fmincon(mF5, S, A, B, Aeq, Beq);
[x6, result6] = fmincon(mF6, S, A, B, Aeq, Beq);

formatter = '-- F1 max --\n%s\n%s\n\n-- F2 max --\n%s\n%s\n\n-- F3 min --\n%s\n%s\n\n-- F4 min --\n%s\n%s\n\n-- F5 max --\n%s\n%s\n\n-- F6 max --\n%s\n%s\n\n';
s1 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x1, sum(x1));
s2 = sprintf('!F1 = %.3f, F2 = %.3f, F3 = %.3f, F4 = %.3f, F5 = %.3f, F6 = %.3f', -result1, -mF2(x1), pF3(x1), pF4(x1), -mF5(x1), -mF6(x1));
s3 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x2, sum(x2));
s4 = sprintf('F1 = %.3f, !F2 = %.3f, F3 = %.3f, F4 = %.3f, F5 = %.3f, F6 = %.3f', -mF1(x2), -result2, pF3(x2), pF4(x2), -mF5(x2), -mF6(x2)); 
s5 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x3, sum(x3));
s6 = sprintf('F1 = %.3f, F2 = %.3f, !F3 = %.3f, F4 = %.3f, F5 = %.3f, F6 = %.3f', -mF1(x3), -mF2(x3), result3, pF4(x3), -mF5(x3), -mF6(x3)); 
s7 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x4, sum(x4));
s8 = sprintf('F1 = %.3f, F2 = %.3f, F3 = %.3f, !F4 = %.3f, F5 = %.3f, F6 = %.3f', -mF1(x4), -mF2(x4), pF3(x4), result4, -mF5(x4), -mF6(x4));
s9 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x5, sum(x5));
s10 = sprintf('F1 = %.3f, F2 = %.3f, F3 = %.3f, F4 = %.3f, !F5 = %.3f, F6 = %.3f', -mF1(x5), -mF2(x5), pF3(x5), pF4(x5), -result5, -mF6(x5)); 
s11 = sprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f, x1 + x2 + x3 = %.3f', x6, sum(x6));
s12 = sprintf('F1 = %.3f, F2 = %.3f, F3 = %.3f, F4 = %.3f, F5 = %.3f, !F6 = %.3f', -mF1(x6), -mF2(x6), pF3(x6), pF4(x6), -mF5(x6), -result6);
fprintf(formatter, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12);




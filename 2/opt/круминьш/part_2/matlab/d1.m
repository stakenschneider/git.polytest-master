clc; clearvars

% Исходные условия
P1=[0.2, 0.5, 0.3;
    0, 0.7, 0.3;
    0, 0.2, 0.8];
R1=[100, 230, 410;
    500, 150, 500;
    -50, 100, 350];
 
syms Er Fr
eqn1 = Er - 0.5*Fr == 16;
eqn2 = Er - 0.4*Fr == 7;
[A, B] = equationsToMatrix([eqn1, eqn2], [Er, Fr])
X = linsolve(A, B)


G=P1.*R1;
GS=sum(G,2);



% syms Er Fr
% eqn1 = Er - 0.5*Fr == 16;
% eqn2 = Er - 0.4*Fr == 7;
% [A, B] = equationsToMatrix([eqn1, eqn2], [Er, Fr])
% X = linsolve(A, B)
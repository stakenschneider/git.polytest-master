clc; clearvars

f1 = @(X) 3*X(1)+2*X(2);
f2 = @(X) 5.5*X(3) + 3*X(4);
f3 = @(X) 6 - X(1) - 2*X(2) - X(3) - 2*X(4) ;
z1 = @(N) -f1(N); 
z2 = @(N) -f2(N); 

A = [1,2,1,2;
    2,1,2,1;
    1,-1,1,- 1;
    1.8 , 1.2 , -2.2 , -1.2];
b = [6; 8; 4; 0];

lb = [0; 0; 0; 0];

[x_1, z1_opt] = fmincon(z1, lb, A, b, [], [], lb);
[x_2, z2_opt] = fmincon(z2, lb, A, b, [], [], lb);
[x_3, f3_opt] = fmincon(f3, lb, A, b, [], [], lb);

f = @(N) (1-z1(N)/z1_opt)^2+(1-z2(N)/z2_opt)^2+(1-f3(N)/f3_opt)^2;

options = optimoptions('fmincon','Display','none');

alpha = 0.1:0.1:0.9;
Ka = icdf('Normal', alpha, 0, 1); % Квантили распределения N(0,1)
global K
global m1; global m2; global m3; global m4
global d1; global d2; global d3; global d4
m1=2;m2=1;m3=2;m4=1;
d1=1;d2=1;d3=1;d4=1;

[Ndet, ~] = fmincon(f, lb,[2,1,2,1; A], [8; b], [], [], lb, [], [], options);

N = zeros(4,numel(alpha));
for i = 1:numel(alpha)
 K = Ka(i);
 [N(:,i), ~] = fmincon(f, lb, ...
 A, b, [], [], lb, [], @nonlin, options);
end
%% Вывод результатов
F1 = cellfun(f1, num2cell(N,1));
F2 = cellfun(f2, num2cell(N,1));
F3 = cellfun(f3, num2cell(N,1));

function [c, ceq] = nonlin(N)
global K;
global m1; global m2; global m3; global m4
global d1; global d2; global d3; global d4
  c = m1*N(1)+m2*N(2) + m3*N(3)+m4*N(4) + K*sqrt(d1*N(1)^2 + d2*N(2)^2 + d3*N(3)^2 + d4*N(4)^2) - 8;
 ceq = [];
end


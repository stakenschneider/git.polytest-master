clc; clearvars

f1 = @(X) 3*X(1)+2*X(2);
f2 = @(X) 5.5*X(3) + 3*X(4);
f3 = @(X) 6 - X(1) - 2*X(2) - X(3) - 2*X(4) ;

z1 = @(N) -f1(N); 
z2 = @(N) -f2(N); 

% Функциональные ограичения 
A = [1,2,1,2;
    2,1,2,1;
    1,-1,1,- 1;
    1.8 , 1.2 , -2.2 , -1.2];
b = [6; 8; 4; 0];

% Параметрические ограничения
lb = [0; 0; 0; 0];

% Поиск оптимумов частных критериев
[x_1, z1_opt] = fmincon(z1, lb, A, b, [], [], lb);
[x_2, z2_opt] = fmincon(z2, lb, A, b, [], [], lb);
[x_3, f3_opt] = fmincon(f3, lb, A, b, [], [], lb);

% fgoalattain
f = @(N) [z1(N), z2(N), f3(N)];
goal = [z1_opt, z2_opt, f3_opt];
w = abs(goal);

A = [1,2,1,2;
    2,1,2,1;
    1,-1,1,- 1;
    1.8 , 1.2 , -2.2 , -1.2];
b = [6; 8; 4; 0];

[N, f_opt, af] = fgoalattain(f, lb, goal, w, A, b, [], [], lb, [], [],optimset('Display','iter') )
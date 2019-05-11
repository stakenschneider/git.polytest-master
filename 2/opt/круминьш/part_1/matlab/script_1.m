clc; clearvars
% Параметры
Tmin1 = (18*60)*0.7;  %Минимально допустимое время работы 1 станка
Tmin2 = (20*60)*0.7;  %Минимально допустимое время работы 2 станка
Tmax1 = (18*60);  %Максимально допустимое время работы 1 станка
Tmax2 = (20*60);  %Максимально допустимое время работы 2 станка
coeff = 0.7;

% Целевые функции
f1 = @(X) 30*X(1) + 20*X(3); % -> max
f2 = @(X) 3*(X(1)+X(2))+12*(X(3)+X(4)); % -> min
f3 = @(X) 45*X(2) + 21*X(4); % -> max

z1 = @(N) -f1(N); % -> min
z3 = @(N) -f3(N); % -> min

% Функциональные ограничения (в данном случае только линейные)
A = [1,1,5,5;
    -1,-1,-5,-5;
    2,2,7,7;
    -2,-2,-7,-7;
    1,1,0,0;
    0,0,1,1];
b = [Tmax1; -Tmin1; Tmax2; -Tmin2;  5000; 9000];

Aeq = [];
beq = [];
% Параметрические ограничения
lb = [0; 0; 0; 0];
ub = [5000; 5000; 9000; 9000];



%% Поиск оптимумов частных критериев
startingPoint = lb;
[x, z1_opt] = fmincon(z1, startingPoint, A, b, Aeq, beq, lb, ub)
[x, f2_opt] = fmincon(f2, startingPoint, A, b, Aeq, beq, lb, ub)
[x, z3_opt] = fmincon(z3, startingPoint, A, b, Aeq, beq, lb, ub)


z1_bound = coeff*z1_opt;
z1_norm = @(N) z1(N)/abs(z1_opt);
f2_norm = @(N) f2(N)/abs(f2_opt);
z3_norm = @(N) z3(N)/abs(z3_opt);
f = @(N) 0.5*z1_norm(N) +0.2*f2_norm(N) + 0.3*z3_norm(N);
A = [1,1,5,5;
    -1,-1,-5,-5;
    2,2,7,7;
    -2,-2,-7,-7;
    1,1,0,0;
    0,0,1,1;
    -30,-30,-20,-20];
b = [Tmax1; -Tmin1; Tmax2; -Tmin2;  5000; 9000; z1_bound];
[N, f_opt] = fmincon(f, startingPoint, A, b, Aeq, beq, lb, ub)


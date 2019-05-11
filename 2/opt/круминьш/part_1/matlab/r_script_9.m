clc; clearvars
% Параметры
Tmin1 = (18*60)*0.7;  %Минимально допустимое время работы 1 станка
Tmin2 = (20*60)*0.7;  %Минимально допустимое время работы 2 станка
Tmax1 = (18*60);  %Максимально допустимое время работы 1 станка
Tmax2 = (20*60);  %Максимально допустимое время работы 2 станка

% Целевые функции
f1 = @(X) 30*X(1) + 20*X(3); % -> max
f2 = @(X) 3*(X(1)+X(2))+12*(X(3)+X(4)); % -> min
f3 = @(X) 45*X(2) + 21*X(4); % -> max
z1 = @(N) -f1(N); % -> min
z3 = @(N) -f3(N); % -> min

% Обобщенный критерий (по пункту Е задачи многокритериальной оптимизации)
z1_opt = -9160;
f2_opt = 1814.4;
z3_opt = -12804;

f = @(N) (1-z1(N)/z1_opt)^2+(1-f2(N)/f2_opt)^2+(1-z3(N)/z3_opt)^2;
% Функциональные ограничения
A = [
    1,1,5,5;
    -1,-1,-5,-5;
    -2,-2,-7,-7;
    1,1,0,0;
    0,0,1,1];
b = [Tmax1;-Tmin1;  -Tmin2;  5000; 9000];
Aeq = [];
beq = [];
% а также функция nonlin, объявленная в конце файла
% Параметрические ограничения
lb = [0; 0; 0; 0];
ub = [5000; 5000; 9000; 9000];
% Опции оптимизатора
options = optimoptions('fmincon','Display','none');
startingPoint = [0, 0, 0, 0];
% Параметры для задачи стохастического программирования
alpha = 0.1:0.1:0.9;
Ka = icdf('Normal', alpha, 0, 1); % Квантили распределения N(0,1)
global K
global m1; global m2; global m3; global m4
global d1; global d2; global d3; global d4
m1=2;m2=2;m3=7;m4=7;
d1=1;d2=1;d3=3.5;d4=3.5;
% Решение детерминированной задачи:
[Ndet, ~] = fmincon(f, startingPoint,[2,2,7,7; A], [Tmax2; b], Aeq, beq, lb, ub, [], options);
% Решение стохастической задачи:
N = zeros(4,numel(alpha));
for i = 1:numel(alpha)
 K = Ka(i);
 [N(:,i), ~] = fmincon(f, startingPoint, ...
 A, b, Aeq, beq, lb, ub, @nonlin, options);
end
%% Вывод результатов
F1 = cellfun(f1, num2cell(N,1));
F2 = cellfun(f2, num2cell(N,1));
F3 = cellfun(f3, num2cell(N,1));
fprintf('alpha = %.1f, X_11 = %6.4f, X_12 = %6.4f, x_21 = %6.4f, x_22 = %6.3f, f1 = %.2f, f2 = %.0f, f3 = %.2f\n', [alpha; N(1,:); N(2,:); N(3,:); N(4,:); F1; F2; F3])
fprintf('%.1f&%6.4f&%6.4f&%6.4f&%6.3f&%.2f&%.0f&%.2f\n', [alpha; N(1,:); N(2,:); N(3,:); N(4,:); F1; F2; F3])
fprintf('Для детерминированных ограничений:\n')
fprintf('X_11 = %3.4f, X_12 = %3.4f, x_21 = %6.4f, x_22 = %6.3f, f1 = %.2f, f2 = %.0f, f3 = %.2f\n', ...
 Ndet(1), Ndet(2), Ndet(3), Ndet(4), f1(Ndet), f2(Ndet), f3(Ndet))
%% Функция, задающая нелинейные ограничения
function [c, ceq] = nonlin(N)
global K;
global m1; global m2; global m3; global m4
global d1; global d2; global d3; global d4
  c = m1*N(1)+m2*N(2) + m3*N(3)+m4*N(4) + K*sqrt(d1*N(1)^2 + d2*N(2)^2 + d3*N(3)^2 + d4*N(4)^2) - 1200;
 ceq = [];
end


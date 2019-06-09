function tim_8
clc; clearvars

f1 = @(X) 0.8*X(1)+2*X(2)+5*X(3)+4*X(4)+6*X(5)+5*X(6); %->max
f2 = @(X) 0.9*X(1)+8*X(2)+2*X(5); %->min
function [f3] = f3(X)
if (0.3*X(1)+X(2)+X(3)+X(4)+X(5)+0.5*X(6)) <= 25
f3 = 50*X(1)+30*X(2)+30*X(3)+50*X(4)+70*X(5)+20*X(6); %->min
else
f3 = 50*X(1)+30*X(2)+30*X(3)+50*X(4)+70*X(5)+20*X(6) +100*(0.3*X(1)+0.5*X(6)+X(2)+X(3)+X(4)+X(5)-25); %->min
end
end

function [c, ceq] = nonlin(N)

  c = m1*N(1)+m2*N(2) + m3*N(3)+m4*N(4)+m5*N(5)+m6*N(6) + K*sqrt(d1*N(1)^2 + d2*N(2)^2 + d3*N(3)^2 + d4*N(4)^2+ d5*N(5)^2+ d6*N(6)^2) - 100;
 ceq = [];
end

z1 = @(N) -f1(N); 

% Функциональные ограичения 
A = [0.3,1,1,1,1,0.5];
b = 100;

% Параметрические ограничения
lb = [0;   0; 3;   2;   0; 0];
ub = [100; 3; 100; 100; 5; 100];

% Поиск оптимумов частных критериев
[x_1, z1_opt] = fmincon(z1, lb, A, b, [], [], lb,ub);
[x_2, f2_opt] = fmincon(f2, lb, A, b, [], [], lb,ub);
[x_3, f3_opt] = fmincon(@f3, lb, A, b, [], [], lb,ub);

f = @(N) (1-z1(N)/z1_opt)^2+(1-f2(N)/f2_opt)^2+(1-f3(N)/f3_opt)^2;

options = optimoptions('fmincon','Display','none');

alpha = 0.1:0.1:0.9;
Ka = icdf('Normal', alpha, 0, 1); 
global K
global m1; global m2; global m3; global m4;global m5; global m6
global d1; global d2; global d3; global d4;global d5;global d6
m1=0.3;m2=1;m3=1;m4=1;m5=1;m6=0.5;
d1=0.15;d2=0.2;d3=0.2;d4=0.2;d5=0.2;d6=0.25;

[Ndet, ~] = fmincon(f, lb,[0.2,1,1,1,1,0.5; A], [100; b], [], [], lb, ub, [], options);

N = zeros(6,numel(alpha));
for i = 1:numel(alpha)
 K = Ka(i);
 [N(:,i), ~] = fmincon(f, lb, A, b, [], [], lb, ub, @nonlin, options);
end

F1 = cellfun(f1, num2cell(N,1));
F2 = cellfun(f2, num2cell(N,1));
F3 = cellfun(@f3, num2cell(N,1));

fprintf('%.1f& %6.4f& %6.4f& %6.4f& %6.4f& %6.4f& %6.4f& %6.4f& %6.4f& %6.4f \\\\ \\hline \n', [alpha; N(1,:); N(2,:); N(3,:); N(4,:);N(5,:);N(6,:); F1; F2; F3])

fprintf('\nДля детерминированных ограничений:\n')
fprintf('X_1 = %3.4f, X_2 = %3.4f, x_3= %6.4f, x_4 = %6.3f,x_5 = %6.3f,x_6 = %6.3f, f1 = %.2f, f2 = %.0f, f3 = %.2f\n', ...
 Ndet(1), Ndet(2), Ndet(3), Ndet(4),Ndet(5),Ndet(6), f1(Ndet), f2(Ndet), f3(Ndet))

end
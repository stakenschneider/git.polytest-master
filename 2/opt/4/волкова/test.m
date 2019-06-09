function test
clc;
% начальные значения
S = 5;
N = 5;   % число заявок в сети
M = 4;   % число узлов

p = [0   0.3  0.3  0.4;...
    0.4  0    0.2  0.4;...
    0.1  0.2  0    0.7;...
    0.2  0.7  0.1  0  ];

m = [1;1;1;1];      % число каналов в i-ом узле
c = [1 1 1 1];      % стоимостные коэффициенты
a = [1;1;1;1];      % коэффициенты нелинейности

%% нахождение вероятностей w
w = fsolve(@wfun,[1;0;0;0]);
    function F = wfun(w)
        for j = 1:M
            sum_t = 0;
            for i = 1:M
                sum_t = sum_t + w(i)*p(i,j);
            end
            F(j) = sum_t - w(j);
        end
        F = [F(1); F(2);F(3);F(4); sum(w) - 1];
    end

options = optimset('Display','iter');
[w,fval] = fsolve(@wfun,[1;0;0;0],options)
        
%% find lambda
function [ lambda ] = findlambda(w,u)
for i = 1:1:M
   for n = 0:1:N
       my = 1;
       for j = 1:1:n
           if (j >= m(i))
               my = my*m(i)*u(i);
           else my = my*j*u(i);
           end
       end  
       z(i,n+1) = (w(i)^n)/my;
   end
end
G(1, :) = z(1, :);

for r = 2:1:M
    for k = 1:1:N
        sum = 0;
        for l = 0:1:k
            sum = sum + z(r, l + 1)*G(r - 1, k - l + 1);
        end
        G(r, k + 1) = sum;
    end
end
 
lambda = 0;
lambda = G(M, N - 1)/G(M,N);
end

%% нелинейное ограничение
function [ctmp , ceqtmp] = limitation(x)
ctmp = 0;
    for i = 1:M
        ctmp = ctmp + c(i)*x(i)^a(i);
    end
    ctmp = ctmp  - S;
    ceqtmp = [];
end

%% optimization
fun = @(x)(-findlambda(w,x));
[my_u,fval] = fmincon(fun,w,[],[],[],[],[0;0;0;0],[],@limitation,optimset('Display','iter'))
end
clear all; clc;
%% Параметры сети
M = 5; N = 5;
m = [1 1 1 1 5];
omega = [0.2 0.2 0.2 0.2 0.2];
mu = [3 2 3 3 2/17];
%% Начальные константы
G = zeros(5,6);
G(:, 1) = 1;
%% Считаем Z
for i = 1:1:M
   for ni = 0:1:N
       multiplic = 1;
       for j = 1:1:ni
           if (j >= m(i))
               multiplic = multiplic*m(i)*mu(i);
           else multiplic = multiplic*j*mu(i);
           end
       end  
       z(i,ni+1) = (omega(i)^ni)/multiplic;
   end
end
G(1, :) = z(1, :);
%% Считаем G
for r = 2:1:M
    for k = 1:1:N
        sum = 0;
        for l = 0:1:k
            sum = sum + z(r, l + 1)*G(r - 1, k - l + 1);
        end
        G(r, k + 1) = sum;
    end
end
%% Считаем среднее время ответа
sum = 0;
for n = 1:1:N
    sum = sum + n*z(5, n + 1)*G(M - 1, N - n + 1);
end
av_n_M_M = sum/G(M, N + 1);
av_T_reply = (M - av_n_M_M)/(av_n_M_M*mu(M))

            
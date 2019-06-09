function tim_1
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

z1 = @(N) -f1(N); 

A = [0.3,1,1,1,1,0.5];
b = 100;

lb = [0;   0; 3;   2;   0; 0];
ub = [100; 3; 100; 100; 5; 100];

[x_1, z1_opt] = fmincon(z1, lb, A, b, [], [], lb,ub);
[x_2, f2_opt] = fmincon(f2, lb, A, b, [], [], lb,ub);
[x_3, f3_opt] = fmincon(@f3, lb, A, b, [], [], lb,ub);

z1_norm = @(N) z1(N)/abs(z1_opt);
f2_norm = @(N) f2(N)/abs(f2_opt);
z3_norm = @(N) f3(N)/abs(f3_opt);

f = @(N) 0.7*z1_norm(N) +0.1*f2_norm(N) + 0.2*z3_norm(N);

[N, opt] = fmincon(f, lb, A, b, [], [], lb,ub)
-z1(N)
f2(N)
f3(N)
end
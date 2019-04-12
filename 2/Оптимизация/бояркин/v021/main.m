clear all;
close all; 
clc;
format long g;

% delete(gcp);
% distcomp.feature('LocalUseMpiexec', false);
% parpool();

p =   [0 0.3 0.6 0.1;
       0.2 0 0 0.8;
       0.4 0.2 0 0.4;
       0.8 0.1 0.1 0];

M = 4;
N = 5;
S = 9;

c = [2 2 2 2];
a = [1 1 1 1];

%% Initialize w

A = p' - diag(ones(1, M));
A(4, :) = [1; 1; 1; 1];
b = [0; 0; 0; 1];
w = inv(A) * b;
w = (1 / w(1)) * w';

%% Error

e = 1e-06;

%% First approximation

fprintf('Start Conditions\ne = %f\nw = [%.6f %.6f %.6f %.6f]\n\n', e, w);

%% Syms u

u = sym('u', [1 M]);

%% Find characteristics

[L, Lam, T] = fl3(u, w, c, M, N);
[pL, pLam, T] = fl3(u, w, c, M, N - 1);

Function = sym(zeros(1, M));

for i = 1 : M
    Function(i) = simplify(S * (L(i) - pL(i)) * a(1) / (c(i) * a(i)));
end

%% Newton method with jacobian matrix

uCurrent = [3 3 3 3];
uPrevious = zeros(1, M);

jaco = jacobian(Function - u);

index = 0;
condition = true;
while condition
    resf = zeros(M, 1);
    % parfor i = 1 : M
    for i = 1 : M
        resf(i) = subs(Function(i) - u(i), u, uCurrent);
    end
    
    fprintf('%d | u = [%.6f %.6f %.6f %.6f] | F(u) = [%.6f %.6f %.6f %.6f]\n', index, double(uCurrent), double(resf));
    
    uPrevious = uCurrent;
    
    resjaco = zeros(M, M);
    % parfor i = 1 : M
    for i = 1 : M
        for j = 1 : M
            resjaco(i, j) = subs(jaco(i, j), u, uPrevious);
        end
    end
    
    resf = zeros(M, 1);
    % parfor i = 1 : M
    for i = 1 : M
        resf(i) = subs(Function(i) - u(i), u, uPrevious);
    end
    
    uCurrent = uPrevious - (resjaco \ resf)';

    condition = false;
    for i = 1 : M
        condition = condition || abs(uCurrent(i) - uPrevious(i)) > e;
    end
    
    index = index + 1;
    
    if (~condition)
        fprintf('%d | u = [%.6f %.6f %.6f %.6f] | F(u) = [%.6f %.6f %.6f %.6f]\n', index, double(uCurrent), double(resf));
    end
end

resf = zeros(M, 1);
% parfor i = 1 : M
for i = 1 : M
    resf(i) = subs(Function(i) - u(i), u, uCurrent);
end

rU = double(uCurrent);
rL = double(subs(L, u, uCurrent));
rLam = double(subs(Lam, u, uCurrent));
fprintf('\nResult\nu = [%.6f %.6f %.6f %.6f]\nF(u) = [%.6f %.6f %.6f %.6f]\nL(N) = [%.6f %.6f %.6f %.6f]\nlam(N) = [%.6f %.6f %.6f %.6f]\n', rU, double(resf), rL, rLam);

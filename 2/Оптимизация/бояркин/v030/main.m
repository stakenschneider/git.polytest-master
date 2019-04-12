clear all;
close all; 
clc;
format long g;

% delete(gcp);
% distcomp.feature('LocalUseMpiexec', false);
% parpool();

p =   [0 0.1 0.6 0.3;
       0.7 0 0.2 0.1;
       0.9 0 0 0.1;
       0.3 0.3 0.4 0];

M = 4;
N = 5;

lam_1_ = 3;

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

u0 = zeros(1, M);
for i = 1 : M
    u0(i) = w(i) / (c(i) * w(1)) * lam_1_;
end

fprintf('Start Conditions\ne = %f\nw = [%.6f %.6f %.6f %.6f]\nu0 = [%.6f %.6f %.6f %.6f]\n\n', e, w, u0);

%% Syms u

u = sym('u', [1 M]);

%% Find characteristics

[L, Lam, T] = fl3(u, w, c, M, N);
[pL, pLam, T] = fl3(u, w, c, M, N - 1);

Function = sym(zeros(1, M));
Function(1) = simplify(lam_1_ / Lam(1) * u(1));

for i = 2 : M
    % Function(i) = simplify(Function(1) * (L(i) - pL(i)) / (L(1) - pL(1)) * (c(1) * a(1)) / (c(i) * a(i)));
    Function(i) = simplify(u(1) * (L(i) - pL(i)) / (L(1) - pL(1)) * (c(1) * a(1)) / (c(i) * a(i)));
end

%% Newton method with jacobian matrix

% uCurrent = u0;
uCurrent = [10 10 10 10];
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
    
    rU = double(uCurrent);
    fprintf('%d | u = [%.6f %.6f %.6f %.6f] | F(u) = [%.6f %.6f %.6f %.6f] | S = %.6f\n', index, double(uCurrent), double(resf), c * rU');
    
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
        rU = double(uCurrent);
        fprintf('%d | u = [%.6f %.6f %.6f %.6f] | F(u) = [%.6f %.6f %.6f %.6f] | S = %.6f\n', index, double(uCurrent), double(resf), c * rU');
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
rS = c * rU';
fprintf('\nResult\nu = [%.6f %.6f %.6f %.6f]\nF(u) = [%.6f %.6f %.6f %.6f]\nL(N) = [%.6f %.6f %.6f %.6f]\nlam(N) = [%.6f %.6f %.6f %.6f]\nS = %.6f\n', rU, double(resf), rL, rLam, rS);

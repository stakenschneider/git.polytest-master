function [c, ceq] = m8f(X)
    global K;
    
    M1 = 1;
    M2 = 1;
    M3 = 1;
    D1 = M1 / 2;
    D2 = M2 / 2;
    D3 = M3 / 2;
    
    c = M1 * X(1) + M2 * X(2) + M3 * X(3) + K * sqrt(D1 * (X(1) ^ 2) + D2 * (X(2) ^ 2) + D3 * (X(3) ^ 2)) - 80;
    ceq = [];
end
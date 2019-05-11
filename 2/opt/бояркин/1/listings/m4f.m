function result = m4f(X)
    % 1 / F1 -> min
    mF1 = 1 / (60 * X(1) + 300 * X(2) + 2000 * X(3));
    % 1 / F2 -> min
    mF2 = 1 / ((0.1 * X(1) + 10 * X(2) + 70 * sqrt(X(3))) ^ 1.5);
    % F3 -> min
    pF3 = 30 * X(1) + 100 * X(2) + 220 * X(3);
    % F4 -> min
    pF4 = log(20 * X(1) + 3 * X(2) + 0.01 * X(3));
    % 1 / F5 -> min
    mF5 = 1 / ((1 / mF1) / (X(1) + X(2) + X(3)));
    % 1 / F6 -> min
    mF6 = 1 / (((1 / mF1) + (1 / mF2)) - (pF3 + pF4));

    rF1 = 13940;
    rF2 = 7258.939;
    rF3 = 2660;
    rF4 = 6.613;
    rF5 = 198.485;
    rF6 = 16501.964;
    
    result(1) = mF1 * rF1;
    result(2) = mF2 * rF2;
    result(3) = pF3 / rF3;
    result(4) = pF4 / rF4;
    result(5) = mF5 * rF5;
    result(6) = mF6 * rF6;
end
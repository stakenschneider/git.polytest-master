function [L, Lam, T] = fl3(u, w, c, M, N)
    P = sym(zeros(M, N + 1, N + 1));
    T = sym(zeros(1, M));
    L = sym(zeros(1, M));
    Lam = sym(zeros(1, M));
    
    P(:, 1, 1) = 1;
    for r = 1 : N
        %% Step 1
        
        for i = 1 : M
            T(i) = 0;
            for n = 1 : r
                T(i) = T(i) + n / (min(n, c(i)) * u(i)) * P(i, n, r);
            end
        end
        
        %% Step 2
        
        if (r == N)
            for i = 1 : M
                temp = 0;
                for j = 1 : M
                    temp = temp + w(j) * T(j) / w(i);
                end

                Lam(i) = simplify(r / temp);
            end
        else
            temp = 0;
            for j = 1 : M
                temp = temp + w(j) * T(j) / w(1);
            end

            Lam(1) = simplify(r / temp);
        end
        
        %% Step 3
        
        for i = 1 : M
            for n = 1 : r
                P(i, n + 1, r + 1) = w(i) / w(1) * Lam(1) / (min(n, c(i)) * u(i)) * P(i, n, r);
            end
            
            P(i, 1, r + 1) = 1;
            for n = 1 : r
                P(i, 1, r + 1) = P(i, 1, r + 1) - P(i, n + 1, r + 1);
            end
        end
    end
    
    for i = 1 : M
        tempSum = 0;
        for j = 1 : N
            tempSum = tempSum + j * P(i, j + 1, N + 1);
        end
        
        L(i) = tempSum;
    end
    
    L = simplify(L);
    Lam = simplify(Lam);
    T = simplify(T);
end

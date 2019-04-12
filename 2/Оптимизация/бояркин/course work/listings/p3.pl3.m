function [L, Lam] = pl3(u, w, c, M, N, G)
    L = sym(zeros(1, M));
    Lam = sym(zeros(1, M));
    
    for i = 1 : M
        tempSum = 0;
        for n = 1 : N
            Z = 0;
            if (n == 0)
                Z = 1;
            else
                %% Find Z(i, n)
                tempMul = 1;
                for j = 1 : n
                    tempMul = tempMul * min(j, c(i)) * u(i);
                end

                Z = (w(i) ^ n) / tempMul;
            end
            
            tempSum = tempSum + n * Z * G(M - 1, N - n + 1);
        end
        
        L(i) = tempSum / G(M, N + 1);
        Lam(i) = w(i) * G(M, N - 1 + 1) / G(M, N + 1);
    end
    
    L = simplify(L);
    Lam = simplify(Lam);
end
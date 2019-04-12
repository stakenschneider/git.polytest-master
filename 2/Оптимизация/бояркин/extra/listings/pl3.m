function [L, Lam] = pl3(u, w, M, N, G)
    L = sym(zeros(1, M));
    Lam = sym(zeros(1, M));
    
    for i = 1 : M
        tempSum = 0;
        for n = 1 : N
            tempSum = tempSum + ((w(i) / u(i)) ^ n) * G(M, N - n + 1);
        end
        
        L(i) = tempSum / G(M, N + 1);
        Lam(i) = w(i) * G(M, N - 1 + 1) / G(M, N + 1);
    end
    
    L = simplify(L);
    Lam = simplify(Lam);
end
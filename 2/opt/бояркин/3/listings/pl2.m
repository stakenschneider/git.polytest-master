function [rL, rLam, rT] = pl2(u, w, c, M, N)
    L = zeros(1, M);
    lam = zeros(1, M);
    t = zeros(1, M);
    
    for i = 1 : M
        tempSum = 0;
        for n = 1 : N
            tempSum = tempSum + ((w(i) / u(i)) ^ n) * gl2(u, w, c, M, N - n);
        end
        
        lam(i) = w(i) * gl2(u, w, c, M, N - 1) / gl2(u, w, c, M, N);
        L(i) = tempSum / gl2(u, w, c, M, N);
        t(i) = tempSum / (w(i) * gl2(u, w, c, M, N - 1));
    end
    
    rL = L;
    rLam = lam;
    rT = t;
end
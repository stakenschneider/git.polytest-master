function [L, lumbda1] = fl1(u, w, c, M, N)
    P = zeros(M, N + 1, N + 1);
    t = zeros(1, M);
    
    P(:, 1, 1) = 1;
    for r = 1 : N
        %% Step 1
        
        for i = 1 : M
            t(i) = 0;
            for n = 1 : r
                t(i) = t(i) + n / (min(n, c(i)) * u(i)) * P(i, n, r);
            end
        end
        
        %% Step 2
        
        temp = 0;
        for i = 1 : M
            temp = temp + w(i) * t(i) / w(1);
        end
        
        lumbda1 = r / temp;
        
        %% Step 3
        
        for i = 1 : M
            for n = 1 : r
                P(i, n + 1, r + 1) = w(i) / w(1) * lumbda1 / (min(n, c(i)) * u(i)) * P(i, n, r);
            end
            
            P(i, 1, r + 1) = 1;
            for n = 1 : r
                P(i, 1, r + 1) = P(i, 1, r + 1) - P(i, n + 1, r + 1);
            end
        end
    end

    L = t;
end

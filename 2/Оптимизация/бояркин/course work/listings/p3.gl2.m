function [rG] = gl2(u, w, c, M, N)
    G = zeros(M, N + 1);
    G(:, 1) = 1;
    
    for k = 0 : N
        %% Find G(1, k)
        
        tempMul = 1;
        for j = 1 : k
            tempMul = tempMul * min(j, c(1)) * u(1);
        end

        G(1, k + 1) = (w(1) ^ k) / tempMul;
    end
    
    for r = 2 : M
        for k = 1 : N
            %% Find G(r, k)
            
            tempSum = 0;
            for h = 0 : k
                Z = 0;
                if (h == 0)
                    Z = 1;
                else
                    %% Find Z(r, h)
                    tempMul = 1;
                    for j = 1 : h
                        tempMul = tempMul * min(j, c(r)) * u(r);
                    end

                    Z = (w(r) ^ h) / tempMul;
                end
                
                tempSum = tempSum + Z * G(r - 1, k - h + 1);
            end
            
            G(r, k + 1) = tempSum;
        end
    end
    
    rG = G(M, N + 1);
end
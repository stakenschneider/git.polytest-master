clc;

R = [Inf   4   4   3;
       2 Inf   1   3;
       2   4 Inf   3;
       2   4   1 Inf];
D = [  0 Inf Inf Inf;
     Inf   0 Inf Inf;
     Inf Inf   0 Inf;
     Inf Inf Inf   0];
 
p = cell(4);
% Нахождение путей   
for i = 1:4
    for j = 1:4
        b = R(i, j);
        if b ~= Inf
            D(j, b) = 1;
            p{j, b} = [b];
        end
    end 
end
% k - узел посредник
% p - запоминание траектории
for k = 1:4
    for i = 1:4
        for j = 1:4
            new_d = D(i, k) + D(k, j);  
            if new_d < D(i, j)
                D(i, j) = new_d;
                p{i, j} = [p{i, k}, p{k, j}];   
            end
        end
     end
end

D 
p

% Алгоритм флойда
D = [  0  0.3341   Inf   Inf;
       Inf   0   Inf   0.3374;
       0.3314    Inf  0   Inf ;
       Inf    Inf    0.3466 0;];
prevD = D;
 

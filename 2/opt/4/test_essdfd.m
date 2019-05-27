function test_essdfd
% nachal'nie znacheniya





S = 10;
N = 7;                                    % chislo zayavok v seti
M = 3;                                    % chislo uzlov

p = [0   0.1  0.3;...
    0.2  0    0.2;...
    0.3  0.2  0.5];

m = [4;3;3;3];                             % chislo kanalov v im uzle
c = [3 3 3 2];                             % stoimostnyye koef
a = [3;1;2;1];                             % koef nelineynosti





%% nakhodeniye veroyatnostey w
for j = 1:M
    test(j,1) = 0;
end
test(1,1) = 1;

w = fsolve(@wfun,test);

    function F = wfun(w)
        for j = 1:M
            sum_t = 0;
            for i = 1:M
                sum_t = sum_t + w(i)*p(i,j);
            end
            F(j) = sum_t - w(j);
            my = j;
        end
        
        for j=my:10
            F(j) = 0;
        end
        F = [F(1); F(2); F(3); F(4); F(5); F(6); F(7); F(8); F(9); F(10); sum(w) - 1];
    end

%% find lambda
function [ lambda ] = findlambda(w,u)

for i = 1:1:M
   for n = 0:1:N
       my = 1;
       for j = 1:1:n
           if (j >= m(i))
               my = my*m(i)*u(i);
           else my = my*j*u(i);
           end
       end  
       z(i,n+1) = (w(i)^n)/my;
   end
end
G(1, :) = z(1, :);

for r = 2:1:M
    for k = 1:1:N
        sum = 0;
        for l = 0:1:k
            sum = sum + z(r, l + 1)*G(r - 1, k - l + 1);
        end
        G(r, k + 1) = sum;
    end
end
 
lambda = 0;
lambda = G(M, N - 1)/G(M,N);
end

%% nelineynoye ogranicheniye
function [ctmp , ceqtmp] = limitation(x)
ctmp = 0;
    for i = 1:M
        ctmp = ctmp + c(i)*x(i)^a(i);
    end
    ctmp = ctmp  - S;
    ceqtmp = [];
end

%% optimization
for i = 1:M
    lb(i,1) = 0;
end

fun = @(x)(-findlambda(w,x));
[my_u,fval] = fmincon(fun,w,[],[],[],[],lb,[],@limitation,optimoptions('fmincon','Algorithm','sqp'))
end
lb = [0 0 0 0];
ub = [100 100 100 100];
x0=[0 0 0 0];
 
options = optimset('Algorithm', 'interior-point');
% для каждого критерия по отдельности:
[x, fval] = fmincon(inline('-12*x(1)-5*x(2)-15*x(3)-10*x(4)'), x0, [], [], [], [], lb, ub, @constrStoh, options)


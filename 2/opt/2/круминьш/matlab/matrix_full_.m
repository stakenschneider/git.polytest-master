clc; clearvars

%М - математическое ожидание
%D - дисперсия
%P - вероятность
P12 = 1; M12 = 23; D12 = 16; 
P22 = 0.2; M22 = 28; D22 = 36; 
P23 = 0.7; M23 = 25; D23 = 16; 
P25 = 0.1; M25 = 43; D25 = 25; 
P31 = 0.5; M31 = 12; D31 = 4; 
P34 = 0.5; M34 = 43; D34 = 9; 
P41 = 0.6; M41 = 20; D41 = 9; 
P46 = 0.4; M46 = 27; D46 = 25; 
P53 = 0.5; M53 = 35; D53 = 36;
P56 = 0.5; M56 = 19; D56 = 16; 

syms q12
syms q22
syms q23
syms q25
syms q31
syms q34
syms q41
syms q46
syms q53
syms q56
syms w61
syms s

Q=[0 q12 0 0 0 0;
   0 q22 q23 0 q25 0;
   q31 0 0 q34 0 0;
   q41 0 0 0 0 q46;
   0 0 q53 0 0 q56;
   w61 0 0 0 0 0];

A1 = eye(size(Q,1)) - transpose(Q);
disp(A1);

det_A1 = det(A1);

det_dw=diff(det_A1, w61);

det2_A1=subs(det_A1, w61, 0);

We= -det_dw/det2_A1;
disp(We);


syms s

We=subs(We, q12, P12*exp(M12*s+D12/2*s^2));
We=subs(We, q22, P22*exp(M22*s+D22/2*s^2));
We=subs(We, q23, P23*exp(M23*s+D23/2*s^2));
We=subs(We, q25, P25*exp(M25*s+D25/2*s^2));
We=subs(We, q31, P31*exp(M31*s+D31/2*s^2));
We=subs(We, q34, P34*exp(M34*s+D34/2*s^2));
We=subs(We, q41, P41*exp(M41*s+D41/2*s^2));
We=subs(We, q46, P46*exp(M46*s+D46/2*s^2));
We=subs(We, q53, P53*exp(M53*s+D53/2*s^2));
We=subs(We, q56, P56*exp(M56*s+D56/2*s^2));

We = simplify(We)
We0 = subs(We, 's', 0)  % We(0)
 
% Нахождение мат. ожидания и дисперсии
Me = We/We0;
 
% Нахождение производной 1-го порядка при s=0
m1 = diff(Me, 's');     
m1 = subs(m1, 's', 0)   % Замена символа s на 0 в выражении m1
 s
% Нахождение производной 2-го порядка при s=0
m2 = diff(Me, 's',2);
m2=subs(m2, 's', 0)     % Замена символа s на 0 в выражении m2
 
% Нахождение дисперсии времени выхода процесса в завершающий узел графа
D = m2 - (m1)^2
clc; clearvars

%М - математическое ожидание
%D - дисперсия
%P - вероятность
P12 = 1; M12 = 20; D12 = 9; 
P22 = 0.6; M22 = 30; D22 = 16; 
P23 = 0.4; M23 = 40; D23 = 25; 
P32 = 0.5; M32 = 28; D32 = 16; 
P34 = 0.5; M34 = 37; D34 = 16; 
P45 = 1; M45 = 30; D45 = 25; 
P51 = 0.2; M51 = 30; D51 = 16; 
P55 = 0.1; M55 = 10; D55 = 4; 
P56 = 0.7; M56 = 30; D56 = 16; 

syms q12
syms q22
syms q23
syms q32
syms q34
syms q45
syms q51
syms q55
syms q56
syms w61
syms s

Q=[0 q12 0 0 0 0;
   0 q22 q23 0 0 0;
   0 q32 0 q34 0 0;
   0 0 0 0 q45 0;
   q51 0 0 0 q55 q56;
   w61 0 0 0 0 0];

A1 = eye(size(Q,1)) - transpose(Q);
disp(A1);

det_A1 = det(A1);
disp(det_A1);

det_dw=diff(det_A1, w61);
disp(det_dw);

det2_A1=subs(det_A1, w61, 0);
disp(det2_A1);

We= -det_dw/det2_A1;
disp(We);


syms s

We=subs(We, q12, P12*exp(M12*s+D12/2*s^2));
We=subs(We, q22, P22*exp(M22*s+D22/2*s^2));
We=subs(We, q23, P23*exp(M23*s+D23/2*s^2));
We=subs(We, q32, P32*exp(M32*s+D32/2*s^2));
We=subs(We, q34, P34*exp(M34*s+D34/2*s^2));
We=subs(We, q45, P45*exp(M45*s+D45/2*s^2));
We=subs(We, q51, P51*exp(M51*s+D51/2*s^2));
We=subs(We, q55, P55*exp(M55*s+D55/2*s^2));
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
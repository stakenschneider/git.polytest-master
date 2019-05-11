clc; clearvars

% Вероятности
p12=1;
p22=0.6;
p23=0.4;
p32=0.5;
p34=0.5;
p45=1;
p51=0.2;
p55=0.1;
p56=0.7;

m12=20;
m22=30;
m23=40;
m32=28;
m34=37;
m45=30;
m51=30;
m55=10;
m56=30;

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

Q1=[0 q12 0 0 0 0;
   0 q22 q23 0 0 0;
   0 q32 0 q34 0 0;
   0 0 0 0 q45 0;
   q51 0 0 0 q55 q56;
   w61 0 0 0 0 0];
A1 = eye(size(Q,1)) - transpose(Q1);
disp(A1);

det_A1 = det(A1);
disp(det_A1);

det_dw=diff(det_A1, w61);

det2_A1=subs(det_A1, w61, 0);
disp(det2_A1);

M20= -(det_dw/det2_A1);
disp(M20);


% A_inv = inv(A1);
% M20=A_inv(6,1);
% disp(M20);

M20=subs(M20, q12, p12*m12/(m12-s));
M20=subs(M20, q22, p22*m22/(m22-s));
M20=subs(M20, q23, p23*m23/(m23-s));
M20=subs(M20, q32, p32*m32/(m32-s));
M20=subs(M20, q34, p34*m34/(m34-s));
M20=subs(M20, q45, p45*m45/(m45-s));
M20=subs(M20, q51, p51*m51/(m51-s));
M20=subs(M20, q55, p55*m55/(m55-s));
M20=subs(M20, q56, p56*m56/(m56-s));


M20=simplify(M20);
fprintf("M20\n");
disp(M20);


m1 = diff(M20, 's');     
m1 = subs(m1, 's', 0)  

m2 = diff(M20, 's',2);
m2=subs(m2, 's', 0) 

D = m2 - (m1)^2
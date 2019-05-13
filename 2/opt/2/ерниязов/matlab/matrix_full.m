clc; clearvars

P12 = 1;   M12 = 38; D12 = 16;
P23 = 0.1; M23 = 32; D23 = 16;
P24 = 1;   M24 = 30; D24 = 16;
P32 = 0.1; M32 = 43; D32 = 25;
P35 = 1;   M35 = 28; D35 = 16;
P45 = 0.9; M45 = 37; D45 = 25;
P54 = 0.3; M54 = 20; D54 = 9;
P56 = 0.9; M56 = 19; D56 = 9;

syms q12
syms q23
syms q24
syms q32
syms q35
syms q45
syms q54
syms q56
syms w61
syms s

Q=[0 q12 0 0 0 0;
   0 0 q23 q24 0 0;
   0 q32 0 0 q35 0;
   0 0 0 0 q45 0;
   0 0 0 q54 0 q56;
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

We=subs(We, q12, P12*exp(M12*s+D12/2*s^2));
We=subs(We, q23, P23*exp(M23*s+D23/2*s^2));
We=subs(We, q24, P24*exp(M24*s+D24/2*s^2));
We=subs(We, q32, P32*exp(M32*s+D32/2*s^2));
We=subs(We, q45, P45*exp(M45*s+D45/2*s^2));
We=subs(We, q54, P54*exp(M54*s+D54/2*s^2));
We=subs(We, q56, P56*exp(M56*s+D56/2*s^2));
We=subs(We, q35, P35*exp(M35*s+D35/2*s^2));

We = simplify(We)
We0 = subs(We, 's', 0)  % We(0)
 
Me = We/We0;
 
m1 = diff(Me, 's');
m1 = subs(m1, 's', 0)
 
m2 = diff(Me, 's',2);
m2=subs(m2, 's', 0)
 
D = m2 - (m1)^2

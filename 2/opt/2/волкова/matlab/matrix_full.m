clc; clearvars

P12 = 1;   M12 = 38; D12 = 16;
P24 = 0.1; M22 = 32; D22 = 16;
P46 = 1;   M23 = 30; D23 = 16;
P56 = 0.1; M32 = 43; D32 = 25;
P45 = 1;   M34 = 28; D34 = 16;
P53 = 0.9; M45 = 37; D45 = 25;
P34 = 0.3; M51 = 20; D51 = 9;
P23 = 0.9; M55 = 19; D55 = 9;
P31 = 0.7; M56 = 33; D56 = 16;

syms q12
syms q23
syms q32
syms q24
syms q34
syms q45
syms q53
syms q46
syms q56
syms w61
syms s

Q=[0 q12 0 0 0 0;
   0 0 q23 q24 0 0;
   q31 0 0 q34 0 0;
   0 0 0 0 q45 q46;
   0 0 q53 0 0 q56;
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
We=subs(We, q32, P32*exp(M32*s+D32/2*s^2));
We=subs(We, q24, P24*exp(M24*s+D24/2*s^2));
We=subs(We, q34, P34*exp(M34*s+D34/2*s^2));
We=subs(We, q45, P45*exp(M45*s+D45/2*s^2));
We=subs(We, q53, P53*exp(M53*s+D53/2*s^2));
We=subs(We, q46, P46*exp(M46*s+D46/2*s^2));
We=subs(We, q56, P56*exp(M56*s+D56/2*s^2));

We = simplify(We)
We0 = subs(We, 's', 0)  % We(0)
 
Me = We/We0;
 
m1 = diff(Me, 's');
m1 = subs(m1, 's', 0)
 
m2 = diff(Me, 's',2);
m2=subs(m2, 's', 0)
 
D = m2 - (m1)^2

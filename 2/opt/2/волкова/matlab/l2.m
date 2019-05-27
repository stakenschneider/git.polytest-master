close all; clc;
format long g;
syms s
syms W61;

% W-functions
P12 = 1;   M12 = 38; D12 = 128;    W12 = P12*exp(M12*s+D12*s^2);
P23 = 0.9; M23 = 19; D23 = 40.5;   W23 = P23*exp(M23*s+D23*s^2);
P24 = 0.1; M24 = 32; D24 = 128;    W24 = P24*exp(M24*s+D24*s^2);
P31 = 0.7; M31 = 33; D31 = 128;    W31 = P31*exp(M31*s+D31*s^2);
P34 = 0.3; M34 = 20; D34 = 40.5;   W34 = P34*exp(M34*s+D34*s^2);
P45 = 1;   M45 = 28; D45 = 128;    W45 = P45*exp(M45*s+D45*s^2);
P46 = 1;   M46 = 30; D46 = 128;    W46 = P46*exp(M46*s+D46*s^2);
P53 = 0.9; M53 = 37; D53 = 128;    W53 = P53*exp(M53*s+D53*s^2);
P56 = 0.1; M56 = 43; D56 = 312.5;  W56 = P56*exp(M56*s+D56*s^2);

Q=[0 W12 0 0 0 0;
   0 0 W23 W24 0 0;
   W31 0 0 W34 0 0;
   0 0 0 0 W45 W46;
   0 0 W53 0 0 W56;
   W61 0 0 0 0 0];

A = eye(size(Q, 1)) - Q';
detA = det(A);
dDetA = diff(detA, W61, 1);
detA0 = subs(detA, W61, 0);

We = dDetA / detA0;
We = simplify(We);

We0 = subs(We, 's', 0);
fprintf('We(0) = %.3f\n', double(We0));

M = We / We0;

m1 = diff(M, 's', 1);
m1 = subs(m1, 's', 0);
fprintf('m1 = %.3f\n', double(m1));

m2 = diff(M, 's', 2);
m2 = subs(m2, 's', 0);
fprintf('m2 = %.3f\n', double(m2));

d = m2 - m1 ^ 2;
fprintf('d = %.3f\n', double(d));

clc; clearvars

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

det_dw=diff(det_A1, w61);

det2_A1=subs(det_A1, w61, 0);

We= -det_dw/det2_A1;
disp(We);

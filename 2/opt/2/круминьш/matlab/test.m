clc; clearvars

% Вероятности
p01=0.5;
p02=0.5;
p10=0.5;
p12=0.5;

m01=1;
m02=0.5;
m10=2;
m12=1.2;


syms q01
syms q02
syms q10
syms q12
syms w20
syms s

Q=[0 q01 q02;
    q10 0 q12;
    w20   0   0];

Q1=[0 q01 q02;
    q10 0 q12;
    w20   0   0];
A1 = eye(size(Q,1)) - transpose(Q1);
disp(A1);

det_A1 = det(A1);
disp(det_A1);

det_dw=diff(det_A1, w20);
fprintf("dd\n");
disp(det_dw);

det2_A1=subs(det_A1, w20, 0);
disp(det2_A1);

WEE= -(det_dw/det2_A1);
disp(WEE);


% A_inv = inv(A1);
% M20=A_inv(3,1);
% disp(M20);
% 
% M20=subs(M20, q01, p01*m01/(m01-s));
% M20=subs(M20, q02, p02*m02/(m02-s));
% M20=subs(M20, q10, p10*m10/(m10-s));
% M20=subs(M20, q12, p12*m12/(m12-s));
% 
% M20=simplify(M20);
% disp(M20);
% 
% 
% m1 = diff(M20, 's');     
% m1 = subs(m1, 's', 0)  
% 
% m2 = diff(M20, 's',2);
% m2=subs(m2, 's', 0) 
% 
% D = m2 - (m1)^2
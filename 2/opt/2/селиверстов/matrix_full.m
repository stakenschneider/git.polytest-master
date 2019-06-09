clc; clearvars

P11 = 0.1; M11 = 30; D11 = 16;
P12 = 0.8;   M12 = 26; D12 = 36;
P13 = 0.1; M13 = 12; D13 = 16;
P26 = 0.3   M26 = 30; D26 = 25;
P34 = 1; M34 = 13; D34 = 25;
P41 = 0.2;   M41 = 11; D41 = 16;
P42 = 0.3; M42 = 12; D42 = 16;
P45 = 0.5; M45 = 17; D45 = 9;
P56 = 0.3; M56 = 28; D56 = 36;
P57 = 0.7; M57 = 14; D57 = 36;
P73 = 0.3; M73 = 32; D73 = 25;
P74 = 0.7; M74 = 22; D74 = 9;

syms q11
syms q12
syms q13
syms q26
syms q34
syms q41
syms q42
syms q45
syms q56
syms q57
syms q73
syms q74
syms w61
syms s

Q=[q11 q12 q13 0 0 0 0;
   0 0 0 0 0 q26 0;
   0 0 0 q34 0 0 0;
   q41 q42 0 0 q45 0 0;
   0 0 0 0 0 q56 q57;
   w61 0 0 0 0 0 0];
   0 0 q73 q74 0 0 0];

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

a11 = 0.4*M11; b11 = 1.6*M11;
a12 = 0.4*M12; b12 = 1.6*M12;
a13 = 0.4*M13; b13 = 1.6*M13;
a26 = 0.4*M26; b26 = 1.6*M26;
a34 = 0.4*M34; b34 = 1.6*M34;
a41 = 0.4*M41; b41 = 1.6*M41;
a42 = 0.4*M42; b42 = 1.6*M42;
a45 = 0.4*M45; b45 = 1.6*M45;
a56 = 0.4*M56; b56 = 1.6*M56;
a57 = 0.4*M57; b57 = 1.6*M57;
a73 = 0.4*M73; b73 = 1.6*M73;
a74 = 0.4*M74; b74 = 1.6*M74;

W11 = P11*((exp(s*a11)-exp(s*b11))/((a11-b11)*s));
W12 = P12*((exp(s*a12)-exp(s*b12))/((a12-b12)*s));
W13 = P13*((exp(s*a13)-exp(s*b13))/((a13-b13)*s));
W26 = P26*((exp(s*a26)-exp(s*b26))/((a26-b26)*s));
W34 = P34*((exp(s*a34)-exp(s*b34))/((a34-b34)*s));
W41 = P41*((exp(s*a41)-exp(s*b41))/((a41-b41)*s));
W42 = P42*((exp(s*a42)-exp(s*b42))/((a42-b42)*s));
W45 = P45*((exp(s*a45)-exp(s*b45))/((a45-b45)*s));
W56 = P56*((exp(s*a56)-exp(s*b56))/((a56-b56)*s));
W57 = P57*((exp(s*a57)-exp(s*b57))/((a57-b57)*s));
W73 = P73*((exp(s*a73)-exp(s*b73))/((a73-b73)*s));
W74 = P74*((exp(s*a74)-exp(s*b74))/((a74-b74)*s));

We = simplify(We);
We0 = limit(We, 's', 0)
Me = We/We0;

% первый начальный момент
m1 = diff(Me, 's', 1);
m1 = limit(m1, 's', 0)

% второй начальный момент
m2 = diff(Me, 's', 2);
m2 = limit(m2, 's', 0)

% третий начальный момент
m3 = diff(Me, 's', 3);
m3 = limit(m3, 's', 0)

% дисперсия
D = m2 - (m1)^2

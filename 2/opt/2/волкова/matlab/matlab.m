clc; clearvars

% W-functions
P12 = 1;   M12 = 38; D12 = 128;
P23 = 0.9; M23 = 19; D23 = 40.5;
P24 = 0.1; M24 = 32; D24 = 128;
P31 = 0.7; M31 = 33; D31 = 128;
P34 = 0.3; M34 = 20; D34 = 40.5;
P45 = 1;   M45 = 28; D45 = 128;
P46 = 1;   M46 = 30; D46 = 128;
P53 = 0.9; M53 = 37; D53 = 128;
P56 = 0.1; M56 = 43; D56 = 312.5;

syms s

W12 = P12*exp(M12*s+D12*s^2);
W46 = P46*exp(M46*s+D46*s^2);
W24 = P24*exp(M24*s+D24*s^2);
W34 = P34*exp(M34*s+D34*s^2);
W45 = P45*exp(M45*s+D45*s^2);
W23 = P23*exp(M23*s+D23*s^2);
W31 = P31*exp(M31*s+D31*s^2);
W53 = P53*exp(M53*s+D53*s^2);
W56 = P56*exp(M56*s+D56*s^2);

We = -((W12*W23*W34*W45*W56 + W12*W23*W34*W46 + W12*W24*W46 + W12*W24*W45*W56)/(W12*W23*W31 + W34*W45*W53 + W12*W24*W31*W45*W53 - 1));
 
We = simplify(We);
We0 = subs(We, 's', 0);
fprintf('We(0) = %.3f\n', double(We0));

Me = We/We0;
 
m1 = diff(Me, 's');
m1 = subs(m1, 's', 0);
fprintf('me1 = %.3f\n', double(m1));

m2 = diff(Me, 's',2);
m2 = subs(m2, 's', 0);
fprintf('me2 = %.3f\n', double(m2));

D = m2 - (m1)^2;
fprintf('D = %.3f\n', double(D));

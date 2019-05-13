clc; clearvars

P12 = 1;   M12 = 38; D12 = 16;
P23 = 0.9; M55 = 19; D55 = 9;
P24 = 0.1; M22 = 32; D22 = 16;
P31 = 0.7; M56 = 33; D56 = 16;
P34 = 0.3; M51 = 20; D51 = 9;
P45 = 1;   M34 = 28; D34 = 16;
P46 = 1;   M23 = 30; D23 = 16;
P53 = 0.9; M45 = 37; D45 = 25;
P56 = 0.1; M32 = 43; D32 = 25;

syms s

W12 = P12*exp(M12*s+D12/2*s^2);
W23 = P23*exp(M23*s+D23/2*s^2);
W24 = P24*exp(M24*s+D24/2*s^2);
W34 = P34*exp(M34*s+D34/2*s^2);
W45 = P45*exp(M45*s+D45/2*s^2);
W23 = P23*exp(M23*s+D23/2*s^2);
W32 = P31*exp(M31*s+D31/2*s^2);
W53 = P53*exp(M53*s+D53/2*s^2);
W56 = P56*exp(M56*s+D56/2*s^2);
 
We = -((W12*W24*W45*W45 + W12W23W34W45W56)/(W12W23W31+W12W24W45W53W31+W34W45W53-1));
 
We = simplify(We)
We0 = subs(We, 's', 0)  % We(0)
 
Me = We/We0;
 
m1 = diff(Me, 's');
m1 = subs(m1, 's', 0)

m2 = diff(Me, 's',2);
m2=subs(m2, 's', 0)

D = m2 - (m1)^2

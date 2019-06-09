clc; clearvars

P12 = 1;   M12 = 38; D12 = 16;
P23 = 0.1; M23 = 32; D23 = 16;
P24 = 1;   M24 = 30; D24 = 16;
P32 = 0.1; M32 = 43; D32 = 25;
P35 = 1;   M35 = 28; D35 = 16;
P45 = 0.9; M45 = 37; D45 = 25;
P54 = 0.3; M54 = 20; D54 = 9;
P56 = 0.9; M56 = 19; D56 = 9;

syms s

W12 = P12*exp(M12*s+D12/2*s^2);
W23 = P23*exp(M23*s+D23/2*s^2);
W24 = P24*exp(M24*s+D24/2*s^2);
W35 = P35*exp(M35*s+D35/2*s^2);
W45 = P45*exp(M45*s+D45/2*s^2);
W32 = P31*exp(M31*s+D31/2*s^2);
W54 = P54*exp(M54*s+D54/2*s^2);
W56 = P56*exp(M56*s+D56/2*s^2);
 
We = ((W12W23W35W56+W12W24W45W56)/(1-W45W54-W23W32+W23W32W45W54));
 
We = simplify(We)
We0 = subs(We, 's', 0)  % We(0)
 
Me = We/We0;
 
m1 = diff(Me, 's');
m1 = subs(m1, 's', 0)

m2 = diff(Me, 's',2);
m2=subs(m2, 's', 0)

D = m2 - (m1)^2

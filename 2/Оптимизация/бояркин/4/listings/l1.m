clear all;
close all; 
clc;
format long g;

syms s;

% W-functions
W12 = 0.5 * exp(10*s + 8 * s^2);
W16 = 0.5 * exp(23 * s + 312.5 * s^2);
W22 = 0.2 * exp(13 * s + 128 * s^2);
W26 = 0.8 * exp(11 * s + 128 * s^2);
W35 = 1 * exp(10 * s + 40.5 * s^2);
W41 = 0.4 * exp(37 * s + 128 * s^2);
W43 = 0.3 * exp(12 * s + 128 * s^2);
W46 = 0.3 * exp(12 * s + 1200.5 * s^2);
W54 = 0.3 * exp(15 * s + 312.5  * s^2);
W55 = 0.5 * exp(19 * s + 8 * s^2);
W56 = 0.2 * exp(42 * s + 40.5 * s^2);

% We(s)
We = (W12 * W26 + W16 - W16 * W22 - W16 * W35 * W54 * W43 - W16 * W55 - W12 * W26 * W55 - W12 * W26 * W35 * W54 * W43 + W16 * W22 * W35 * W54 * W43 + W16 * W22 * W55) / (1 - W35 * W54 * W43 - W22 - W55 + W22 * W55 + W22 * W35 * W54 * W43);
We = simplify(We);

% We(0)
We0 = subs(We, 's', 0);
fprintf('We(0) = %.3f\n', double(We0));

% Me(s)
Me = We / We0;

% me1
me1 = diff(Me, 's', 1);
me1 = subs(me1, 's', 0);
fprintf('me1 = %.3f\n', double(me1));

% me2
me2 = diff(Me, 's', 2);
me2 = subs(me2, 's', 0);
fprintf('me2 = %.3f\n', double(me2));

% de
de = me2 - me1 ^ 2;
fprintf('de = %.3f\n', double(de));

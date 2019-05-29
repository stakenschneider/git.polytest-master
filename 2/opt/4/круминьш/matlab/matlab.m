clc; clearvars

A = [1 0 0 0 0;
 0.2 -1 0.2 0.5 0.3;
 0.3 0.2 -1 0.1 0.1;
 0.2 0.6 0.1 -1 0.1;
 0.3 0.1 0.1 0.4 -1];
b=[8; 0; 0; 0; 0];
lambdaj=A\b

N=5;
Q = [0 0.2 0.3 0.2 0.3;
 0.1 0 0.2 0.6 0.1;
 0.6 0.2 0 0.1 0.1;
 0 0.5 0.1 0 0.4;
 0.5 0.3 0.1 0.1 0];
lambdaij=[];
for i = 1:N
 for j = 1:N
     lambdaij(i,j) = lambdaj(i)*Q(i, j);
 end
end
lambdaij


caA = 0;
 caB = [0 0 0 0 0];
for j = 1:N
 for i = 1:N
 caA(j,i) = lambdaij(i,j)/lambdaj(j)*Q(i, j);
 caB(j)=caB(j)+lambdaij(i,j)/lambdaj(j)*(1-Q(i,j));
 end
end
 caA = caA-eye(5);
 caA(1,:) = [1 0 0 0 0];
 caA;
 caA^-1;
 caB = -caB';
 caB(1)=0.16;
 caj = (caA^-1)*caB

 
 
 
 %m=[11.5,8,11,9.5];
 m=[10,10,10,10];
 cs=[0.04,0.04,0.04,0.04];

 for i = 2:N
 [Lj(i-1), Pj(i-1)] = params(lambdaj(i), caj(i), m(i-1), cs(i-1));
 end
Lj
Pj
L = sum(Lj)

% E1=(max(Pj)-Pj(1)*lambdaj(2))/(Pj(1));
% E2=(max(Pj)-Pj(2)*lambdaj(3))/(Pj(2));
% E3=(max(Pj)-Pj(3)*lambdaj(4))/(Pj(3));
% E4=(max(Pj)-Pj(4)*lambdaj(5))/(Pj(4));
% E1
% E2
% E3
% E4
% 
% nextJ1=min([E1,E2,E3,E4]);
% nextJ2=max([E1,E2,E3,E4]);
% nextJ1
% nextJ2
  
 function [ fLj, fPj ] = params( fl, fca, fm, fcs )
 Lj = '(l/m)^2*(ca+csj)*exp(-2*(1-l/m)*(1-ca)^2/(3*(l/m)*(ca+csj)))/(2*(1-l/m))';
 syms m;
 syms l;
 syms ca;
 syms csj;
 fLj = subs(Lj,l, fl);
 fLj = subs(fLj,m, fm);
 fLj = subs(fLj,ca, fca);
 fLj = subs(fLj,csj, fcs);
 fLj = vpa(fLj);
 
 Pj = '-((l)/(l-m)^2)';
 fPj = subs(Pj,l, fl);
 fPj = subs(fPj,m, fm);
 fPj = -1*vpa(fPj);
 end


clear all;
close all; 
clc;
format long g;

f = [0 12.6 8.4 14.7 12.3];

A=[];
b=[];

Aeq = [0.4 -0.9 -0.7 -0.6 -0.5;
       -0.3 0.9 0.8 -0.3 -0.4;
       -0.1 0 -0.1 0.9 0.9;
       1 1 1 1 1];
Beq = [0; 0; 0; 1];

lb = zeros(5, 1);
ub = ones(5, 1);

[w, opt] = linprog(f, A, b, Aeq, Beq, lb, ub)


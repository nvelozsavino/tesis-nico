% Agrega señal, Amp = 0, Sigma = 11, t0 = 0
% Agrega señal, Amp = 258, Sigma = 29, t0 = 30
% Agrega señal, Amp = 238, Sigma = 7, t0 = 65

clc
clear all
close all;
Amp=[0 258 238];
sigma=[11 29 7]*1e-3;
t0=[0 30 65]*1e-3;
tf=1/10;
dt=tf/1000;
t=0:dt:tf;
gauss=Amp(2)*exp(-0.5*((t-t0(2))/sigma(2)).^2)+Amp(3)*exp(-0.5*((t-t0(3))/sigma(3)).^2);
plot(t,gauss)
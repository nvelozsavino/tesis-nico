clear all;
close all;
clc;
k=1.3806488e-23;
h=6.62606957e-34;
c=3e8;

T=5000;

N=1000;

lmin=10e-9;
lmax=1000e-9;

fmin=c/lmax;
fmax=c/lmin;

df=(fmax-fmin)/N;

f=((1:N)*df)+fmin;

for i=1:N
    u=h*f(i)/(k*T);
    r(i)=((8*pi*(k*T)^4)/((h*c)^3))*((u^3)/(exp(u)-1));
end

plot(1e9*c./f,r);
grid on;
xlabel ('Longitud de Onda \lambda(nm)');
%axis([lmin*1e9 lmax*1e9 0 0.02]);


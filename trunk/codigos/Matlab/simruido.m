clear all;
close all;
clc;
FPS=30;
Tint=1/FPS;
M=200;
N=4;
t=(1:M*N)*Tint/M;

x=2*sin(2*pi*30*t+pi/6)+1*sin(2*pi*60*t+pi/5)+sin(2*pi*90*t);
y=x+2*randn(size(t));

jm=length(t)/N;
plot(t,y,'k');
hold on;
colores=['k','b','r','g'];
for i=1:N
    
    ti=t(1+jm*(i-1):jm*i);
    yi=y(1+jm*(i-1):jm*i);
    plot(ti,yi,colores(i)); hold on;
end
grid on;
xlabel('Tiempo (s)');

        
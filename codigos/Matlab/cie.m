close all;
clear all;
clc;
% blue=load('../C++/archivos/blue.txt');
% red=load('../C++/archivos/red.txt');
% green=load('../C++/archivos/green.txt');
c=load('../C++/archivos/ciexyz64_1-2.csv');
l=c(:,1);
r=c(:,2);
g=c(:,3);
b=c(:,4);
figure;
% plot(blue(:,1),blue(:,2),'b-+',red(:,1),red(:,2),'r-x',green(:,1),green(:,2),'g-o')
plot(l,b,'b-+',l,r,'r-x',l,g,'g-o');
grid on;
xlabel('Longitud de onda \lambda (nm)')
title('Funciones Colorimétricas del Observador del estándar 10° CIE 1964');
legend('Azul','Rojo','Verde');
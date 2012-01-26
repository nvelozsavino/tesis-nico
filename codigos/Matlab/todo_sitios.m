clear all;
close all;
clc;
numImag=5;
veces=10;
pasos=0.05:0.1:0.95;
a=[];
m=[];
s=[];

for v=1:(length(pasos))
    nombre=strcat('archivos/small',num2str(pasos(v),'%.2f'));
    [at,mt,st]=sitios(nombre,numImag,veces);
    a=[a at'];
    m=[m mt'];
    s=[s st'];
end
    
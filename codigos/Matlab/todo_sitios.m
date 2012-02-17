clear all;
close all;
clc;
numImag=5;
veces=10;
ps=0.1:0.1:2.5;
a=[];
m=[];
s=[];
for v=1:(length(ps))
    nombre=strcat('archivos/pasosmall3-',num2str(ps(v),'%.2f'));
    [at,mt,st]=sitios(nombre,numImag,veces);

    a{v}=at';
    m(v)=mt;
    s(v)=st;
end



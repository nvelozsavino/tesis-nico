clear all;
close all;
clc;
numImag=5;
veces=10;
ps=50:25:300;
a=[];
m=[];
s=[];
for v=1:(length(ps))
    nombre=strcat('archivos/sound2-',num2str(ps(v),'%.2f'));
    [at,mt,st]=sitios(nombre,numImag,veces);

    a{v}=at';
    m(v)=mt;
    s(v)=st;
end



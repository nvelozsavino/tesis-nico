clear all;
close all;
clc;
numImag=5;
veces=5;
ps=10:10:180;%5:5:175;
a=[];
m=[];
s=[];
for v=1:(length(ps))
    nombre=strcat('../C++/tesis/ruido45-',num2str(ps(v),'%.2f'));
    [at,mt,st]=sitios(nombre,numImag,veces);

    a{v}=at';
    m(v)=mt;
    s(v)=st;
end



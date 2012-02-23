clear all;
close all;
clc;
numImagenes=5;
veces=10;
pasos=0:1:5;
alphas=[];
alpha_mean=[];
alpha_std=[];
numeradores={};
denominadores={};
cosine_alphas={};
polinomios={};
for v=1:(length(pasos))
    nombre=strcat('archivos/señalDC1-',num2str(pasos(v),'%.2f'));
    [at,mt,st,num,den,cosa,p]=sitios(nombre,numImagenes,veces);

    alphas{v}=at';
    alpha_mean(v)=mt;
    alpha_std(v)=st;
    numeradores{v}=num;
    denominadores{v}=den;
    cosine_alphas{v}=cosa;
    polinomios{v}=p;
end



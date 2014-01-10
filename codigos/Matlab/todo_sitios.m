clear all;
close all;
clc;
numImagenes=5;
veces=2;
pasos=100:20:280;
alphas=[];
alpha_mean=[];
alpha_std=[];
numeradores={};
denominadores={};
% cosine_alphas={};
polinomios={};
for v=1:(length(pasos))
    nombre=strcat('d:\calibracion/calF-',num2str(pasos(v),'%.2f'));
    [at,mt,st,num,den,p]=sitios(nombre,numImagenes,veces);

    alphas{v}=at';
    alpha_mean(v)=mt;
    alpha_std(v)=st;
    numeradores{v}=num;
    denominadores{v}=den;
%     cosine_alphas{v}=cosa;
    polinomios{v}=p;
end



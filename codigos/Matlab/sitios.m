
function [alpha,alpha_mean,alpha_std,num,den,cosa]=sitios(nombre,numImagenes,numVeces)
    alpha=[];
    for i=0:(numVeces-1)
        for j=0:(numImagenes-5)
            name=strcat(nombre,'-',num2str(i),'-',num2str(j),'.txt');           
            data{i+1,j+1}=load(name);
            num{i+1,j+1}=data{i+1,j+1}(:,1);
            den{i+1,j+1}=data{i+1,j+1}(:,2);           
            cosa{i+1,j+1}=data{i+1,j+1}(:,3);
            p{i+1,j+1}=polyfit(den{i+1,j+1},num{i+1,j+1},1);
            alpha((i*(numImagenes-4)+j+1))=acos(p{i+1,j+1}(1));
        end
    end
    
    alpha_mean=mean(alpha);
    alpha_std=std(alpha); 


end
% 
% data=load('paso-0-0');
% num=data(:,1);
% den=data(:,2);
% coc=data(:,3);
% 
% figure;
% 
% 
% plot(den,num,'.');
% axis([-512 512 -256 256]); 
% grid on;
% title('den vs num');
% 
% p=polyfit(den,num,1);
% alpha=acos(p(1));
clc;
clear all;
close all;
c=3e8;
rs=1;
rr=1;
IF=1;
dl=1e-9;
li=1e-9;
lf=10e-6;
l=li:dl:lf;
N=length(l);
Nf=3*N+1;
l0=546.1e-9;
s0=10e-9;
Intl=IF*exp(-((l-l0).^2/(2*s0^2)));
fi=0;
ff=c/li;
df=ff/Nf;
f=fi:df:ff;
Intf=zeros(size(f));
for i=1:length(f)
    lamda=c/f(i);

    jf=1+(lamda-li)*N/(lf-li);
    fji=floor(jf);
    cji=ceil(jf);
    if fji<1 || cji>length(Intl)
        Intf(i)=0;
    elseif (jf>fji)
        Yf=Intl(fji);
        Yc=Intl(cji);
        m=(Yc-Yf)/(cji-fji);
        Y=Yf+m*(jf-fji);
        Intf(i)=Y;
    else
        Intf(i)=Intl(jf);
    end
end
P=(idct(Intf));
N=length(P);
Xmax=li*N/2;
% x=Xmax/2*linspace(0,1,N);
Patron=[fliplr(P(2:N)) P];
Patron=Patron/max(Patron);
x=1e6*Xmax/2*linspace(-1,1,2*N-1);
plot(x,Patron);grid on;
axis([-8 +8 -1.2 1.2]);
xlabel('Desplazamiento del piezoeléctrico (\mum)');
ylabel('Amplitud');
title('Patrón de interferencia','FontWeight','bold','FontSize',14);
[pksp,locsp]=findpeaks(Patron(length(Patron)/2-10:length(Patron)));
[pksn,locsn]=findpeaks(-Patron(length(Patron)/2-10:length(Patron)));
xa=x(length(Patron)/2-1:length(Patron));
pics=[];
locs=[];
for k=1:min([length(pksp) length(pksn)])
    pics=[pics pksp(k) -pksn(k)];
    locs=[locs xa(locsp(k)) xa(locsn(k))];
end
It=0.5+0.5*pics;
ctrs=100*abs(diff(It));
figure
plot(locs(2:length(locs)),ctrs);; grid on;
xlabel('Posición del piezoeléctrico (\mum)');
ylabel('Contraste (%)');
title('Contraste vs. posición del piezoeléctrico','FontWeight','bold','FontSize',14);
rel=[];
rpos=[];
for k=1:length(ctrs)-1
    rel(k)=abs(100*(1-ctrs(k)/ctrs(k+1)));
    rpos(k)=locs(k+2);
end
figure;
plot(rpos,rel); grid on;
xlabel('Posición del piezoeléctrico (\mum)');
ylabel('Porcentaje de mejora (%)');
title('Mejora del contraste con un desplazamiento de 180° en dirección hacia el 0','FontWeight','bold','FontSize',12);
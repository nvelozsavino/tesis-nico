clear all;
close all;
clc;
FPS=30;
Tint=1/FPS;
M=200;
N=4;
T=Tint/M;
Fs=1/T;
t=(0:(M*N)-1)*T;
freqs=[30 60 120 240 300];
amps=[0.82 0.1854 0.3801 0.2067 0.2006];
phases=pi*rand(size(freqs));
x=zeros(size(t));
for i=1:length(freqs)
    x=x+(amps(i)*sin(2*pi*freqs(i)*t+phases(i)));
end
% x=2*sin(2*pi*30*t+pi/6)+1*sin(2*pi*60*t+pi/5)+sin(2*pi*90*t);
y=x+0.5*randn(size(t));

jm=length(t)/N;
% plot(t,y,'k');
% hold on;
fmax=120;
[b,a]=butter(10,2*fmax/Fs,'low');
y2=filtfilt(b,a,y);
colores=['c','m','r','g'];
ctrl=zeros([1 jm]);
f1=figure;
% subplot(3,1,1);
for i=1:N
    ctrl=ctrl+(y2(1+jm*(i-1):jm*i))/N;
    ti=t(1+jm*(i-1):jm*i);
    yi=y(1+jm*(i-1):jm*i);
    plot(ti,yi,colores(i)); hold on;
end
hold on;
plot(t,y2,'k','LineWidth',2);
maxplot=max([abs(max(y)) abs(min(y))]);
grid on;
xlabel('Tiempo (s)');
ylabel('Amplitud relativa');
title('Ruido simulado','FontWeight','bold');
axis([0  t(length(t)) -maxplot maxplot]);
f2=figure;

tc=(0:M-1)*T;
plot(tc,ctrl,'k','LineWidth',2); grid on;
xlabel ('Tiempo (s)');
ylabel ('Amplitud relativa');
title ('Señal de control durante el tiempo de adquisición cámara','FontWeight','bold');
% axis([0  tc(length(tc)) -maxplot maxplot]);
f3=figure;
% subplot(2,1,1);
control=[];
ctrl(length(ctrl))=ctrl(1);
plot (t,y2,'kx-'); hold on;
for i=1:N
    control=[control ctrl];
    ci=control(1+jm*(i-1):jm*i);
    ti=t(1+jm*(i-1):jm*i);
    plot(ti,ci,colores(i),'LineWidth',2); hold on;
end

grid on; xlabel('Tiempo (s)');
ylabel ('Amplitud relativa');
title ('Señal de control','FontWeight','bold');
axis([0  t(length(t)) -maxplot maxplot]);
legend('Envolvente Original', 'Señal en Imagen 1', 'Señal en Imagen 2', 'Señal en Imagen 3', 'Señal en Imagen 4');


f4=figure;
% subplot(2,1,2);

plot(t,y-control,'k');
axis([0  t(length(t)) -maxplot maxplot]);
grid on;
xlabel('Tiempo (s)');
ylabel('Amplitud relativa');
title('Ruido Obtenido','FontWeight','bold');
meany=mean(y)
meany2=mean(y-control)
std_y=std(y)
std_y2=std(y-control)
sumy=sum(y.^2)
sumy2=sum((y-control).^2)

set(f1,'Position', [100 100 800 400])

set(f2,'Position', [100 100 400 400])
set(f3,'Position', [100 100 800 600])
set(f4,'Position', [100 100 800 400])
figure(f3)

fmaxf=5000;
[bf,af]=butter(1,fmaxf/Fs,'low');
controlf=filtfilt(bf,af,control);
fmaxf=120;
[bf,af]=butter(1,fmaxf/Fs,'low');
controlf=filtfilt(bf,af,controlf);
f5=figure;
plot(t,control,'k',t,controlf,'b');
grid on;
close all
clc
min=1;
max=length(ps);
figure
errorbar(ps(min:max),m(min:max)*180/pi,s(min:max)*180/pi,'kx'); hold on;
p=polyfit(ps(min:max),m(min:max)*180/pi,1);
y=polyval(p,ps(min:max));
plot(ps(min:max),y); hold off;
grid on;

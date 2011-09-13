%load('uppg3_5.data','-ascii')
%load('uppg3_40.data','-ascii')

meanCurve40 = mean(uppg3_40,1);
meanCurve5  = mean(uppg3_5,1);
maxT = length(uppg3_40);

figure(1)
plot([meanCurve40', meanCurve5'])
axis([0 maxT 0 1])
xlabel('Time t')
ylabel('Order parameter m_1')
legend('Mean value of 100 simulations with p = 40',
       'Mean value of 100 simulations with p = 5',
       'Location', 'East')

figure(2)
plot(uppg3_5');
axis([0,maxT,0,1])
xlabel('Time t')
ylabel('Order parameter m_1')

figure(3)
plot(uppg3_40');
axis([0,maxT,0,1])
xlabel('Time t')
ylabel('Order parameter m_1')

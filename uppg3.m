load('uppg3_5.data','-ascii')
load('uppg3_40.data','-ascii')

hold on
meanCurve40 = mean(uppg3_40,1);
meanCurve5  = mean(uppg3_5,1);
plot([meanCurve40', meanCurve5'])
axis([0 6000 0 1])
xlabel('Time t')
ylabel('Order parameter m_1')
legend('Mean value of 100 simulations with p = 40','Mean value of 100 simulations with p = 5', 'Location', 'EastOutside')

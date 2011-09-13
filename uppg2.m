clear
load('uppg2_new','-ascii')
x = uppg2_new(:,2)./uppg2_new(:,1);
y = uppg2_new(:,3);
XY = sortrows([x y]);
X=XY(:,1);
Y=XY(:,2);
X1 = X; Y1 = Y;


for i=1:100
    X1 = (X1(1:(end-1)) + X1(2:end))/2; 
    Y1 = (Y1(1:(end-1)) + Y1(2:end))/2;
end


hold on

Ptheoretic = @(x) 1/2 * erfc((1+x)./sqrt(2*x));

figure(1)
clf
Ytheoretic = Ptheoretic(X);
plot(X,Y,X,Ytheoretic)
axis([0 1.5 0 0.05])
xlabel('p/N')
ylabel('P_{Error}')
figure(2)
clf
Y1theoretic = Ptheoretic(X1);
plot(X1,Y1,X1,Y1theoretic)
axis([0 1.5 0 0.05])
xlabel('p/N')
ylabel('P_{Error}')
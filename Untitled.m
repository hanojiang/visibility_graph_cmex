index=1;b=zeros(1,1000);
for i=100:100:100000
    a=rand(i,1);
    b(index)=length(findVgEdge(a))/2;
    index=index+1;
end
    
    
%% test1
index=1;b=zeros(1,1000);c=zeros(1,1000);
for i=100:100:100000
    a=rand(i,1);
    tic;
    [aa,bb,cc]=findVgEdge(a);
    b(index)=length(aa);
    t=toc;
    c(index)=t;
    index=index+1;
end

% 
% %% test2
% a=rand(4096,1);
% [left,right,weight]=findVgEdge(a);
% for i=1:length(left)
% aaa(i)=(a(left(i))-a(right(i)));
% end
% aaa=aaa';
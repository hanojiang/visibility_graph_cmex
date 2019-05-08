classdef VGgai
    %UNTITLED2 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        timeseries
        nodeNumber
        type
        weighted
        %         W
        degree
        bc%between centrality
        dc%degree centrality
        cc%closeness centrality
    end
    properties(Dependent)
        W
    end
    
    methods
        %         function obj = VG(timeseries)
        %             if varargin < 1
        %                 disp('输入参数不足');
        %             else
        %             obj.timeseries=timeseries;
        %             end
        %         end
        %         function obj = VG(timeseries,type,obj.weighted)
        %         end
        
        
        function obj = VGgai(timeseries,type,weighted)
            if nargin < 1
                disp('输入参数不足');
            elseif nargin < 2
                obj.timeseries=timeseries;
                obj.type='vg';
                obj.weighted=0;
            elseif nargin < 3
                obj.timeseries=timeseries;
                obj.type=type;
                obj.weighted=0;
            else
                obj.timeseries=timeseries;
                obj.type=type;
                obj.weighted=weighted;
            end
            obj.nodeNumber=length(obj.timeseries);
        end
        %         function obj=set.timeseries(obj,timeseries)
        %             obj.timeseries=timeseries;
        %         end
        %         function timeseries=get.timeseries(obj)
        %             timeseries=obj.timeseries;
        %         end
        function w=get.W(obj)
            N=1;tao=10;
            w=diag(ones(obj.nodeNumber-1,1),1);
            switch obj.type
                case 'vg'
                    for i=1:obj.nodeNumber-2
                        slope=obj.timeseries(i+1)-obj.timeseries(i);
                        for j=i+2:obj.nodeNumber
                            newslope=(obj.timeseries(j)-obj.timeseries(i))/(j-i);
                            if newslope > slope
                                slope=newslope;
                                %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                                w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                            else
                                w(i,j)=0;
                            end
                        end
                    end
                    %                 case 'lpvg'
                    %                     for i=1:obj.nodeNumber-2
                    %                         slope=obj.timeseries(i+1)-obj.timeseries(i);
                    %                         torrent=0;
                    %                         for j=i+2:obj.nodeNumber
                    %                             newslope=(obj.timeseries(j)-obj.timeseries(i))/(j-i);
                    %                             if newslope > slope
                    %                                 slope=newslope;
                    %                                 %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                    %                                 w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                    %                             elseif torrent <= N
                    %                                 torrent =torrent+1;
                    %                                 %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                    %                                 w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                    %                             else
                    %                                 w(i,j)=0;
                    %                             end
                    %                         end
                    %                     end
                    %
                    %                 case 'lphvg'
                    %
                    %                     for i=1:obj.nodeNumber-2
                    %                         torrent=0;
                    %                         for j=i+2:obj.nodeNumber
                    %                             temp=obj.timeseries(i+1:j-1);
                    %                             if max(temp) < min(obj.timeseries(i),obj.timeseries(j))
                    %                                 %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                    %                                 w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                    %                             elseif torrent <=N
                    %                                 torrent=torrent+1;
                    %                                 %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                    %                                 w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                    %                             else
                    %                                 w(i,j)=0;
                    %                                 if obj.timeseries(j) >= obj.timeseries(i)
                    %                                     break
                    %                                 end
                    %                             end
                    %                         end
                    %                     end
                    
                case 'lpvg'
                    for i=1:obj.nodeNumber-2
                        slope=obj.timeseries(i+1)-obj.timeseries(i);
                        torrent=slope;
                        for j=i+2:obj.nodeNumber
                            newslope=(obj.timeseries(j)-obj.timeseries(i))/(j-i);
                            torrent=[torrent,newslope];
                            if newslope>slope
                                slope=newslope;
                                w(i,j)=1;
                            elseif sum(newslope<=torrent)-1<=N
                                w(i,j)=1;
                            else
                                w(i,j)=0;
                            end
                        end
                        torrent=[];
                    end
                    
                case 'lphvg'
                    for i=1:obj.nodeNumber-2
                        for j=i+2:obj.nodeNumber
                            temp=obj.timeseries(i+1:j-1);
                            if max(temp)<min(obj.timeseries(i),obj.timeseries(j))
                                w(i,j)=1;
                            elseif sum(temp>=min(obj.timeseries(i),obj.timeseries(j)))<=N
                                w(i,j)=1;
                            else
                                w(i,j)=0;
                            end
                        end
                    end
                    
                    
                case 'hvg'
                    
                    for i=1:obj.nodeNumber-2
                        for j=i+2:obj.nodeNumber
                            temp=obj.timeseries(i+1:j-1);
                            if max(temp) < min(obj.timeseries(i),obj.timeseries(j))
                                %                         w(i,j)=exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2);
                                w(i,j)=obj.weighted*exp(-(j-i-1)^2/tao/(obj.timeseries(i)-obj.timeseries(j))^2)+1-obj.weighted;
                                %                     w(i,j)=abs(atan((obj.timeseries(i)-obj.timeseries(j))/(j-i)));
                            else
                                w(i,j)=0;
                                if obj.timeseries(j) >= obj.timeseries(i)
                                    break
                                end
                            end
                        end
                    end
                    
            end
            w=w'+w;
        end
        
        function degree=get.degree(obj)
            degree=sum(obj.W);
        end
        
        function vgPlot(obj)
            
            temp=obj.W~=0;
            [xi,xj]=find(triu(temp));
            cor=[xi ,xj];
            
            figure
            xlim([0 obj.nodeNumber]);
            for i=1:obj.nodeNumber
                line([i,i],[0,obj.timeseries(i)],'LineWidth',4,'Color','black');
            end
            
            switch obj.type
                case 'vg'
                    for i=1:size(cor,1)
                        line(cor(i,:),obj.timeseries(cor(i,:)),'Color','black');
                    end
                    title('经典可视图')
                    xlabel('节点编号')
                    ylabel('幅值')
                case 'hvg'
                    for i=1:size(cor,1)
                        if obj.timeseries(cor(i,1))<obj.timeseries(cor(i,2))
                            line(cor(i,:),obj.timeseries([cor(i,1),cor(i,1)]),'Color','black');
                        else
                            line(cor(i,:),obj.timeseries([cor(i,2),cor(i,2)]),'Color','black');
                        end
                    end
                    title('水平可视图')
                    xlabel('节点编号')
                    ylabel('幅值')
                    
                case 'lpvg'
                    for i=1:size(cor,1)
                        line(cor(i,:),obj.timeseries(cor(i,:)),'Color','black');
                    end
                    title('经典可视图')
                    xlabel('节点编号')
                    ylabel('幅值')
                case 'lphvg'
                    for i=1:size(cor,1)
                        if obj.timeseries(cor(i,1))<obj.timeseries(cor(i,2))
                            line(cor(i,:),obj.timeseries([cor(i,1),cor(i,1)]),'Color','black');
                        else
                            line(cor(i,:),obj.timeseries([cor(i,2),cor(i,2)]),'Color','black');
                        end
                    end
                    title('水平可视图')
                    xlabel('节点编号')
                    ylabel('幅值')
            end
        end
        
        function bc=get.bc(obj)
            bc= betweenness_centrality(sparse(triu(obj.W)));
        end
        function cc=get.cc(obj)
            cc = obj.nodeNumber./sum(all_shortest_paths(sparse(obj.W)));
        end
        function dc=get.dc(obj)
            dc=obj.degree/(obj.nodeNumber-1);
        end
    end
end


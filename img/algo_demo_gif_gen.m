# Create a gif of the optimization process
# See https://www.mathworks.com/help/matlab/ref/imwrite.html

filename = 'algo_demo.gif';
DelayTime = 1; # Time in seconds for each plot in the GIF
f = figure;

minW = -10;
maxW = 10;
step_size=0.1;
[W1,W2] = meshgrid(minW:step_size:maxW, minW:step_size:maxW);
E = W1.^2-2.*W1+1+2*(W2.^2-4.*W2+4);

num_simplexes = 13; # The number of iterations +1 for the initial simplex
size = 2; # The size of each vertex i.e. tje number of variables

X = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  
Y = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  

# Pasted output from algo_demo.out
X(1,:)=[ 0.744293 -7.520706 -8.296250 0.744293 ];
Y(1,:)=[ 7.368356 7.464125 -3.731882 7.368356 ];
X(2,:)=[ -5.842228 0.744293 -7.520706 -5.842228 ];
Y(2,:)=[ 1.842179 7.368356 7.464125 1.842179 ];
X(3,:)=[ 2.422772 -5.842228 0.744293 2.422772 ];
Y(3,:)=[ 1.746410 1.842179 7.368356 1.746410 ];
X(4,:)=[ 2.422772 -0.482717 -5.842228 2.422772 ];
Y(4,:)=[ 1.746410 4.581325 1.842179 1.746410 ];
X(5,:)=[ 2.422772 -2.436100 -0.482717 2.422772 ];
Y(5,:)=[ 1.746410 2.503023 4.581325 1.746410 ];
X(6,:)=[ 2.422772 0.469388 -2.436100 2.422772 ];
Y(6,:)=[ 1.746410 -0.331892 2.503023 1.746410 ];
X(7,:)=[ 2.422772 -0.495010 0.469388 2.422772 ];
Y(7,:)=[ 1.746410 1.605141 -0.331892 1.746410 ];
X(8,:)=[ 1.211127 2.422772 -0.495010 1.211127 ];
Y(8,:)=[ 2.679610 1.746410 1.605141 2.679610 ];
X(9,:)=[ 0.660969 1.211127 2.422772 0.660969 ];
Y(9,:)=[ 1.909076 2.679610 1.746410 1.909076 ];
X(10,:)=[ 0.660969 1.679410 1.211127 0.660969 ];
Y(10,:)=[ 1.909076 2.020377 2.679610 1.909076 ];
X(11,:)=[ 0.660969 1.190658 1.679410 0.660969 ];
Y(11,:)=[ 1.909076 2.322168 2.020377 1.909076 ];
X(12,:)=[ 1.302612 0.660969 1.190658 1.302612 ];
Y(12,:)=[ 2.067999 1.909076 2.322168 2.067999 ];
X(13,:)=[ 1.086224 1.302612 0.660969 1.086224 ];
Y(13,:)=[ 2.155353 2.067999 1.909076 2.155353 ];
X(14,:)=[ 0.927694 1.086224 1.302612 0.927694 ];
Y(14,:)=[ 2.010376 2.155353 2.067999 2.010376 ];
X(15,:)=[ 0.927694 1.154785 1.086224 0.927694 ];
Y(15,:)=[ 2.010376 2.075432 2.155353 2.010376 ];
X(16,:)=[ 0.927694 0.996255 1.154785 0.927694 ];
Y(16,:)=[ 2.010376 1.930455 2.075432 2.010376 ];
X(17,:)=[ 1.058380 0.927694 0.996255 1.058380 ];
Y(17,:)=[ 2.022923 2.010376 1.930455 2.022923 ];

for i = 1:num_simplexes    
      
      contour(W1, W2, E, 'linewidth',1.5);
      xlabel("w_1");
      ylabel("w_2");
      set(gca, "fontsize", 12)
      hold on;
      plot(X(i,:),Y(i,:), 'r','linewidth',1.5)
      hold off;
      drawnow
                  
      frame = getframe(f);      
      im = frame2im(frame);     
      [imind,cm] = rgb2ind(im); 
      if i == 1;          
          imwrite(imind,cm,filename,'gif','DelayTime', DelayTime , 'Compression' , 'lzw');
      else
          imwrite(imind,cm,filename,'gif','WriteMode','append','DelayTime', DelayTime , 'Compression' , 'lzw');
      end
end
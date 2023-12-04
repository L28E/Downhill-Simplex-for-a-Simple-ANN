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

num_simplexes = 18; # The number of iterations +1 for the initial simplex
size = 2; # The size of each vertex i.e. tje number of variables

X = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  
Y = zeros(num_simplexes,size+1+1); # +1 for size+1 vertices and +1 to replot the first  

# Pasted output from algo_demo.out
X(1,:)=[ -0.871277 -3.022596 -6.002734 -0.871277 ];
Y(1,:)=[ 7.176748 -4.819242 8.198514 7.176748 ];
X(2,:)=[ 0.080962 -0.871277 -3.022596 0.080962 ];
Y(2,:)=[ -2.331127 7.176748 -4.819242 -2.331127 ];
X(3,:)=[ -1.708877 0.080962 -0.871277 -1.708877 ];
Y(3,:)=[ -1.198216 -2.331127 7.176748 -1.198216 ];
X(4,:)=[ -0.842618 -1.708877 0.080962 -0.842618 ];
Y(4,:)=[ 2.706038 -1.198216 -2.331127 2.706038 ];
X(5,:)=[ -0.842618 -2.632456 -1.708877 -0.842618 ];
Y(5,:)=[ 2.706038 3.838950 -1.198216 2.706038 ];
X(6,:)=[ -0.842618 -1.723207 -2.632456 -0.842618 ];
Y(6,:)=[ 2.706038 1.037139 3.838950 2.706038 ];
X(7,:)=[ -0.842618 -0.608140 -1.723207 -0.842618 ];
Y(7,:)=[ 2.706038 0.887908 1.037139 2.706038 ];
X(8,:)=[ 0.272449 -0.842618 -0.608140 0.272449 ];
Y(8,:)=[ 2.556807 2.706038 0.887908 2.556807 ];
X(9,:)=[ 0.272449 -0.446612 -0.842618 0.272449 ];
Y(9,:)=[ 2.556807 1.759666 2.706038 2.556807 ];
X(10,:)=[ 0.668454 0.272449 -0.446612 0.668454 ];
Y(10,:)=[ 1.610434 2.556807 1.759666 1.610434 ];
X(11,:)=[ 0.668454 1.387516 0.272449 0.668454 ];
Y(11,:)=[ 1.610434 2.407576 2.556807 1.610434 ];
X(12,:)=[ 0.650217 0.668454 1.387516 0.650217 ];
Y(12,:)=[ 2.282906 1.610434 2.407576 2.282906 ];
X(13,:)=[ 1.023426 0.650217 0.668454 1.023426 ];
Y(13,:)=[ 2.177123 2.282906 1.610434 2.177123 ];
X(14,:)=[ 1.023426 0.752638 0.650217 1.023426 ];
Y(14,:)=[ 2.177123 1.920225 2.282906 2.177123 ];
X(15,:)=[ 1.006939 1.023426 0.752638 1.006939 ];
Y(15,:)=[ 1.931558 2.177123 1.920225 1.931558 ];
X(16,:)=[ 1.006939 0.883910 1.023426 1.006939 ];
Y(16,:)=[ 1.931558 1.987283 2.177123 1.931558 ];
X(17,:)=[ 1.006939 0.984425 0.883910 1.006939 ];
Y(17,:)=[ 1.931558 2.068272 1.987283 1.931558 ];
X(18,:)=[ 1.051568 1.006939 0.984425 1.051568 ];
Y(18,:)=[ 2.006231 1.931558 2.068272 2.006231 ];

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
%Small dot detection test 
function [small_closetofish_circle_location] = Small_dot_detection_test()
%Export to seperate csv file for their positions and distances between the
%two 


%cam = webcam('USB Camera');
%preview(cam)
%frames = snapshot(cam);
workingDir = tempname;
mkdir(workingDir)
mkdir(workingDir,'Image')
%FishVideo = VideoWriter('fish.avi');
centers = zeros(21,2); 
vid = imread('Distance test.jpg');


%Assume there are fish in all spots of the cut outs for the board using the
%below website 
    % http://www.mathworks.com/help/images/examples/detect-and-measure-circular-objects-in-an-image.html?s_tid=gn_loc_drop
%Run this code only on the first image to test and see if it works 
v = VideoWriter('fish.avi','Uncompressed AVI');
open(v)
for i = 1:1
    %Gets the current frames snapshot from the camera 
    %frames = snapshot(cam);
    frames = vid; 
    %Opens the figure window 
    figure  
    imshow(frames) 
%Radius is approximately 10 to 20 pixels and use the d=imdistline to test
%below 
%      d = imdistline(gca);
%     api = iptgetapi(h);
%     api.setLabelVisible(false);
%     pause();
    %Find the centers and radii of each of the circles 
    %Find the radii of 20 pixels 
    [centers, radii] = imfindcircles(frames,[3 7], 'ObjectPolarity','dark','Sensitivity',0.92)
        %Bottom right circle center is (412, 113) and top left circle is
        %(322, 114) so calculated distance is = 90 pixels 
        % Where actual distance is 6 centimeters 
        % Thus 15 pixels equals 1 centimeter 
    
    %[centerstwo, radiitwo] = imfindcircles(frames,[10 20], 'ObjectPolarity','dark','Sensitivity',0.92)
    %'Method','twostage')
    %Show the frames with the drawn circle on the shown image 
    h = viscircles(centers, radii)
    %h = viscircles(centerstwo, radiitwo)
    %imshow(frames) 
    hold on;
    viscircles(centers, radii);
    %viscircles(centerstwo, radiitwo);
    drawnow 
    %centers = centers; 
    %Taking the center locations and assigning them to radius points 
    %Write the frames to the video 
    imwrite(frames,['Image' int2str(i), '.jpg'])
    %Write the video 
    writeVideo(v,frames);
    %Clear the figure 
    %clf
end

%Divide by 15 so that each pixel is one centimeter in the csv 
%centers = (centers/15); 
RGB_values = zeros((size(centers,1)),3); 
%Loop through the centers values and get back the RGB values for each of
%the centers detected 
for i = 1:size(centers,1) 
    point = centers(i,1:2)+3;
    redValue = frames(round(point(2)), round(point(1)), 1);
    greenValue = frames(round(point(2)), round(point(1)), 2);
    blueValue = frames(round(point(2)), round(point(1)), 3);
    RGB_values(i,1:3) = [redValue, greenValue, blueValue]; 
end 



sum_RGB = zeros(size(RGB_values,1),1); 
for i = 1:size(RGB_values,1)
    %Sum each row of the values 
    sum_RGB(i) = sum(RGB_values(i,1:3));  
end
%Find the highest value in sum_RGB and then update the csv accordinlgy
[Maximum,Indice] = max(sum_RGB);
%Find the Indice in centers for where the circle is located 
small_closetofish_circle_location = round(centers(Indice,1:2))/15; 

end 

function[h] = histImage(img)
% This function calculates normalized histogram of image.
% Normalized histogram is histogram h, that has at
% each i place in it, value:
% (number of picture pixels with gray level i-1) / 
% (total num of pixels in picture).
sum = 0;
[y,x] = size(img); % getting sizes of image  
h = zeros(1,256);    % creating output histogram array
for i = 1:1: y     % runing on rows
    for j = 1:1: x % running on colomns
        % gray level is addtess to cell in output histogram array
        % we add there 1 (bacause of current pixel (y,x) has this gray level
        h(img(i,j)) = h(img(i,j)) + 1;
        % pay attention to fact, that we use here pixel value as index!
    end
end

h = h./(y*x);
end

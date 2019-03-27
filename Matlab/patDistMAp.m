function[dmap] = patDistMAp(histArray, histPattern)
% Given histograms of an image and pattern returns an array (image) 
% of distance values between
% img windows and pattern. Distance values are computed between the histograms
% of the windows and the pattern using the histogram distance function

[y,x,z] = size(histArray);
dmap = zeros(y,x);                  % output array

for i = 1:1: y       % runing on rows
    for j = 1:1: x   % running on colomns
        hist = histArray(i,j,:);
%         for k = 1:1:256             % making array 1x256 from 1x1x256
%             h1(k) = hist(1,1,k);    % there is a permute function,
%         end                         % but we will use it next time)
        h1 = permute(squeeze(hist),[2,1]);
        % Using temp variable, as MATLAB7 wants it:
        temp = emdAlgo(histPattern,h1);
        dmap(i,j) = temp;
    end
end

end


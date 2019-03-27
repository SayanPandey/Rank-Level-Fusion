function [ finalScore ] = SIFT( trainImg,testImg )
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
    %Getting images for score generation.
            I = single(trainImg) ;
            J = single(testImg) ;
            
            %sift based matching
            
            [fa, da] = vl_sift(I) ;
            [fb, db] = vl_sift(J) ;
            
            [matches, scores] = vl_ubcmatch(da, db) ;
            [m,n]=size(scores);
            finalScore=sum(scores,'double');
            finalScore=double(finalScore/(m*n));
            %disp(sum(scores,'double'));          

end


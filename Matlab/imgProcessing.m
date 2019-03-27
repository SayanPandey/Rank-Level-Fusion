%Stucture to store Names and their Scores
scoreBoard=struct;






A= dir('..\Assets\SortedImages');
 
sizeA=size(A);

for i=3:size(A)
    
    %Reading each directory 
    message=strcat('Present Working Subject :',A(i).name);
    disp(message);
    imgDir=dir(strcat('..\Assets\SortedImages\',A(i).name));
    
    %Getting test image
    if i>=3
        testImg = imread(strcat('..\Assets\SortedImages\',A(i).name,'\',imgDir(3).name));
        imshow(testImg);
        I = single(testImg) ;
    
    %Getting images
    finalScore=0;
    double(finalScore);
        for j=4:size(imgDir)
            
            %Getting images for score generation.
            J=imread(strcat('..\Assets\SortedImages\',A(i).name,'\',imgDir(j).name));
            J = single(J) ;
            
            %sift based matching
            [fa, da] = vl_sift(I) ;
            [fb, db] = vl_sift(J) ;
            [matches, scores] = vl_ubcmatch(da, db) ;
            finalScore=finalScore+sum(scores,'double');
            disp(sum(scores,'double'));
            %imgDir(j).name
        end
        finalScore=finalScore./(size(imgDir)-4);
        disp(strcat('Score for the subject :',' '));
        disp(finalScore);
    end
end     




x = imread('..\Assets\SortedImages\Aaron_Peirsol_\Aaron_Peirsol_0002.pgm');
y = imread('..\Assets\SortedImages\Aaron_Sorkin_\Aaron_Sorkin_0002.pgm');
p = rgb2gray(imread('C:\Users\Sayan\Desktop\myPhoto.jpeg'));
mn=imread('..\Assets\SortedImages\Abdullah_Gul_\Abdullah_Gul_0004.pgm');

%SIFT Verification
            I = single(x) ;
            J = single(y) ;
            image(I) ;
            image(J)
            [f,d] = vl_sift(I) ;
            perm = randperm(size(f,2)) 
            sel = perm(1:10) ;
            h1 = vl_plotframe(f(:,sel)) ;
            h2 = vl_plotframe(f(:,sel)) ;
            set(h1,'color','k','linewidth',3) ;
            set(h2,'color','y','linewidth',2) ;
            h3 = vl_plotsiftdescriptor(d(:,sel),f(:,sel)) ;
            set(h3,'color','g') ;
            Ib=J;
            [fa, da] = vl_sift(I) ;
            [fb, db] = vl_sift(Ib) ;
            [matches, scores] = vl_ubcmatch(da, db) ;
            [m,n]=size(scores);
            finalScore=sum(scores,'double');
            finalScore=double(finalScore/(m*n));


%HARRIS FEATIRES
            
            %I = rgb2gray(imread('viprectification_deskLeft.png'));
            %J = rgb2gray(imread('viprectification_deskRight.png'));
            I=x;
            J=y;
            points1 = detectHarrisFeatures(I);
            points2 = detectHarrisFeatures(J);
    
            [features1,valid_points1] = extractFeatures(I,points1);
            [features2,valid_points2] = extractFeatures(J,points2);
            
            [indexPairs,matchmetric] = matchFeatures(features1,features2);
            matchedPoints1 = valid_points1(indexPairs(:,1),:);
            matchedPoints2 = valid_points2(indexPairs(:,2),:);
            figure; showMatchedFeatures(I,J,matchedPoints1,matchedPoints2);
            %Plot facial features.
            figure;imshow(I);hold on; plot(points1);
            figure;imshow(J);hold on; plot(points2);
            
            %I = p;
            %points = detectHarrisFeatures(I);
            %imshow(I); hold on;
            %plot(points.selectStrongest(1000));
            
   
%CORRELATION BETWEEN TWO IMAGES
    c = corr2(x,y);           
    disp(c);
          

%EMD Algorithm
train=histImage(I);
test=histImage(J);
dist=patDistMAp(train,test);


%Sift test
sift=SIFT(x,mn);

    

            
            
            
            
            
            
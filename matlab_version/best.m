close all;clear;clc;

origin=imread('demo.bmp');
origin = rgb2gray(origin);  

figure,imshow(origin,[]),title('原图')

background = imopen(origin,strel('disk',10)); 
figure,imshow(background)

I=origin-background;
figure,imshow(I)



I2 = imadjust(I);
figure,imshow(I2);


I3=imbinarize(I2);
figure,imshow(I3)

se=strel('disk',5);
I4=imerode(I3,se);
I4=bwareaopen(I4,30);
figure,imshow(I4,[])

D = bwdist(I4);
figure
imshow(D,[]), title('D')

DL = watershed(D);
figure
imshow(DL,[]), title('DL')

bgm = DL == 0;
figure
imshow(bgm), title('Watershed ridge lines (bgm)')

I5=bgm|I4;
figure,imshow(I5),title('I5')

hy = fspecial('sobel');
hx = hy';
Iy = imfilter(double(I2), hy, 'replicate');
Ix = imfilter(double(I2), hx, 'replicate');
gradmag = sqrt(Ix.^2 + Iy.^2);
figure
imshow(gradmag,[]), title('Gradient magnitude (gradmag)')

gradmag2 = imimposemin(gradmag, I5);
figure,imshow(gradmag2,[]) ,title('Gradient magnitude (gradmag2)')


L = watershed(gradmag2);
L(L==1)=0;
figure,imshow(L,[])

cc = bwconncomp(L, 8);

Lrgb = label2rgb(L, 'jet', 'k', 'shuffle');
figure
imshow(Lrgb)
title('Colored watershed label matrix (Lrgb)')

figure
imshow(origin)
hold on
himage = imshow(Lrgb);
himage.AlphaData = 0.3;
title(strcat('所选区域共有',num2str(cc.NumObjects),'个细胞'))
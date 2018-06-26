function output=imbinarize(input)
threshold = graythresh(input);
output=im2bw(input,threshold);
end
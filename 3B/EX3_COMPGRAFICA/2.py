import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

gray_image = image.copy()

altura, largura, canais = image.shape

for x in range(altura):
    for y in range(largura):
        b, g, r = image[x, y]
        gray_value = (int(b) + int(g) + int(r)) // 3
        gray_image[x, y] = (gray_value, gray_value, gray_value)

histogram = [0] * 256
for x in range(altura):
    for y in range(largura):
        pixel_value = gray_image[x, y][0]
        histogram[pixel_value] += 1

total_pixels = altura * largura

cdf = [0] * 256
cdf[0] = histogram[0]
for i in range(1, 256):
    cdf[i] = cdf[i-1] + histogram[i]

equalized_image = gray_image.copy()
for x in range(altura):
    for y in range(largura):
        pixel_value = gray_image[x, y][0]
        equalized_pixel = int(255 * cdf[pixel_value] / total_pixels)
        equalized_image[x, y] = (equalized_pixel, equalized_pixel, equalized_pixel)

cv2_imshow(equalized_image)

cv2.imwrite('Imagem_equalizada.jpg', equalized_image)

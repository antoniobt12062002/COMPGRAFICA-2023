import cv2
import numpy as np
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

# Definir um threshold
limiar = 110

cv2_imshow(image)

binary_image = image.copy()

altura, largura, canais = image.shape

for x in range(altura):
    for y in range(largura):
        b, g, r = image[x, y]
        gray_value = (int(b) + int(g) + int(r)) // 3
        binary_image[x, y] = (gray_value, gray_value, gray_value)

for x in range(altura):
    for y in range(largura):
        pixel_value = binary_image[x, y][0]
        if pixel_value > limiar:
            binary_image[x, y] = (255, 255, 255)  # Define como branco (255, 255, 255)
        else:
            binary_image[x, y] = (0, 0, 0)  # Define como preto (0, 0, 0)

cv2_imshow(binary_image)

cv2.imwrite('Imagem_binarizada.jpg', binary_image)

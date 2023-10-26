import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

altura, largura, canais = image.shape

equalized_image = image.copy()

for canal in range(canais):
    histogram = [0] * 256
    for x in range(altura):
        for y in range(largura):
            pixel_value = image[x, y, canal]
            histogram[pixel_value] += 1

    total_pixels = altura * largura

    cdf = [0] * 256
    cdf[0] = histogram[0]
    for i in range(1, 256):
        cdf[i] = cdf[i-1] + histogram[i]

    # Aplica a equalização do canal
    for x in range(altura):
        for y in range(largura):
            pixel_value = image[x, y, canal]
            equalized_pixel = int(255 * cdf[pixel_value] / total_pixels)
            equalized_image[x, y, canal] = equalized_pixel

cv2_imshow(equalized_image)

cv2.imwrite('Imagem_colorida_equalizada.jpg', equalized_image)
  

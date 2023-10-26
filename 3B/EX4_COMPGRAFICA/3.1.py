import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

altura, largura, canais = image.shape

complement_image = image.copy()

for i in range(altura):
    for j in range(largura):
        b, g, r = image[i, j]

        # Calcular o complemento invertendo os valores dos canais de cor
        complement_b = 255 - b
        complement_g = 255 - g
        complement_r = 255 - r

        complement_image[i, j] = [complement_b, complement_g, complement_r]

cv2_imshow(complement_image)
cv2.imwrite('ComplementoImagem.jpg', complement_image)

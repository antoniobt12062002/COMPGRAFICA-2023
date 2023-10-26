import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

altura, largura, canais = image.shape

inverse_image = image.copy()

for i in range(altura):
    for j in range(largura):
        b, g, r = image[i, j]

        inverse_b = 255 - b
        inverse_g = 255 - g
        inverse_r = 255 - r

        inverse_image[i, j] = [inverse_b, inverse_g, inverse_r]

cv2_imshow(inverse_image)

cv2.imwrite('ComplementoImagem.jpg', inverse_image)

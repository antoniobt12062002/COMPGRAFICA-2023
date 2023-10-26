import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

altura, largura, canais = image.shape

dx = 20  # Valor de translação em X
dy = 300  # Valor de translação em Y

result_image = image.copy()

for i in range(altura):
    for j in range(largura):
        b, g, r = image[i, j]
        if (b, g, r) != (0, 0, 0):
            new_x = j + dx
            new_y = i + dy

            if 0 <= new_x < largura and 0 <= new_y < altura:
                result_image[new_y, new_x] = [b, g, r]

cv2_imshow(result_image)
cv2.imwrite('NovaImagem.jpg', result_image)

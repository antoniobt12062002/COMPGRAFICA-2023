import cv2
import math
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

altura, largura, canais = image.shape

# Ângulo de rotação em graus
angulo_rotacao = 45

# Ponto de rotação (centro da imagem)
ponto_rotacao = (largura // 2, altura // 2)

result_image = image.copy()

# Conversão de ângulo para radianos
angulo_rad = math.radians(angulo_rotacao)

for i in range(altura):
    for j in range(largura):
        b, g, r = image[i, j]

        x = j - ponto_rotacao[0]
        y = i - ponto_rotacao[1]

        new_x = int(x * math.cos(angulo_rad) - y * math.sin(angulo_rad) + ponto_rotacao[0])
        new_y = int(x * math.sin(angulo_rad) + y * math.cos(angulo_rad) + ponto_rotacao[1])

        if 0 <= new_x < largura and 0 <= new_y < altura:
            result_image[new_y, new_x] = [b, g, r]

cv2_imshow(result_image)
cv2.imwrite('NovaImagem.jpg', result_image)

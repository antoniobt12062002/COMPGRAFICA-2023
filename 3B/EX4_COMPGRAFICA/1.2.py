import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

green_image = image.copy()
graygreen_image = image.copy()

altura, largura, canais = image.shape

for x in range(altura):
    for y in range(largura):
        b, g, r = image[x, y]
        green_image[x, y] = (0, g, 0)  # Mantém o canal verde e define os canais azul e vermelho como zero
        graygreen_value = (int(g) + int(g) + int(g)) // 3
        graygreen_image[x, y] = (graygreen_value, graygreen_value, graygreen_value)

cv2_imshow(green_image)
cv2_imshow(graygreen_image)
cv2.imwrite('Imagem_em_tons_de_verde.jpg', green_image)
cv2.imwrite('Imagem_em_tons_de_verde_cinza.jpg', graygreen_image)

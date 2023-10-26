import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

blue_image = image.copy()
grayblue_image = image.copy()

altura, largura, canais = image.shape

for x in range(altura):
    for y in range(largura):
        b, g, r = image[x, y]
        blue_image[x, y] = (b, 0, 0)  # Mantém o canal azul e define os canais verde e vermelho como zero
        grayblue_value = (int(b) + int(b) + int(b)) // 3
        grayblue_image[x, y] = (grayblue_value, grayblue_value, grayblue_value)

cv2_imshow(blue_image)
cv2_imshow(grayblue_image)
cv2.imwrite('Imagem_em_tons_de_azul.jpg', blue_image)
cv2.imwrite('Imagem_em_tons_de_azul_cinza.jpg', grayblue_image)

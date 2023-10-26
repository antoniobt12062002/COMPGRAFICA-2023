import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_name = next(iter(uploaded))

image = cv2.imread(file_name)

cv2_imshow(image)

red_image = image.copy()
grayred_image = image.copy()

altura, largura, canais = image.shape

for x in range(altura):
    for y in range(largura):
        b, g, r = image[x, y]
        red_image[x, y] = (0, 0, r)  # Mantém o canal azul e define os canais verde e vermelho como zero
        grayred_value = (int(r) + int(r) + int(r)) // 3
        grayred_image[x, y] = ( grayred_value,  grayred_value,  grayred_value)

cv2_imshow(red_image)
cv2_imshow(grayred_image)
cv2.imwrite('Imagem_em_tons_de_vermelho.jpg', red_image)
cv2.imwrite('Imagem_em_tons_de_vermelho_cinza.jpg', grayred_image)

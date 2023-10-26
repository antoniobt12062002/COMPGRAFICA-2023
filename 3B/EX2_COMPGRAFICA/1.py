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

cv2_imshow(gray_image)
cv2.imwrite('Imagem_em_tons_de_cinza.jpg', gray_image)
